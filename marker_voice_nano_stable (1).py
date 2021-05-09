#begin
# import the necessary packages
from vosk import Model, KaldiRecognizer
import pyaudio
import sys
import os
import subprocess
from picamera.array import PiRGBArray
from picamera import PiCamera
from threading import Thread
import numpy as np
import imutils
import serial
import time
import cv2
default_command = 50
canListen = False
UI = False

def start_stream():
    p = pyaudio.PyAudio()
    global stream
    stream = p.open(format=pyaudio.paInt16, channels=1, rate=16000, input=True, frames_per_buffer=8000)
    stream.start_stream()

def model_init(model_path):
    model = Model(model_path)
    global rec
    rec = KaldiRecognizer(model, 16000)
    
def commands_init():
    global commands
    commands = [u'дай пять',
                u'квадрат',
                u'лети',
                u'сидеть лежать',

                u'пой',
                u'голос',

                u'юла',
                u'волчок',
                u'дела']


def find_command(word, commands):
    global canListen
    for ind, comm in enumerate(commands):
        if comm in word:
            canListen = False

            if ind == 5:
                return 4
            if ind in (6, 7, 8):
                return 5
            
            return ind
    return default_command
def play_sound():
    song_0 = r'/home/animel/Документы/downloads/sound/0001givefive.mp3'
    song_1 = r'/home/animel/Документы/downloads/sound/0002square.mp3'
    song_2 = r'/home/animel/Документы/downloads/sound/0003fly.mp3'
    song_3 = r'/home/animel/Документы/downloads/sound/0004sit.mp3'
    song_4 = r'/home/animel/Документы/downloads/sound/0005sing.mp3'
    song_5 = r'/home/animel/Документы/downloads/sound/0006yula.mp3'
    global command
    if command == 0:
        subprocess.call(['vlc'] + [song_0] + ['vlc://quit'])
    elif command == 1:
        subprocess.call(['vlc'] + [song_1] + ['vlc://quit'])
    elif command == 2:
        subprocess.call(['vlc'] + [song_2] + ['vlc://quit'])
    elif command == 3:
        subprocess.call(['vlc'] + [song_3] + ['vlc://quit'])
    elif command == 4:
        subprocess.call(['vlc'] + [song_4] + ['vlc://quit'])
    elif command == 5:
        subprocess.call(['vlc'] + [song_5] + ['vlc://quit'])    
        
def processing_the_result(res):
    start_index = res.rfind(':')
    res = res[start_index + 2 : -2].replace('"', '')
    return res



class ShapeDetector:
	def __init__(self):
		pass
	
	
	# shape:
	# 0 unidentified
	# 1 circle
	# 2 pentagon
	# 3 triangle
	# 4 square
	# 5 rectangle
	
	def detect(self, c):
		global command
		# initialize the shape name and approximate the contour
		shape = 0
		peri = cv2.arcLength(c, True)
		approx = cv2.approxPolyDP(c, 0.045 * peri, True)
		#print(len(approx))
		# if the shape is a triangle, it will have 3 vertices
		if len(approx) == 3:
			shape = 3
		
		# if the shape has 4 vertices, it is either a square or
		# a rectangle
		elif len(approx) == 4:
			# compute the bounding box of the contour and use the
			# bounding box to compute the aspect ratio
			(x, y, w, h) = cv2.boundingRect(approx)
			ar1 = w / float(h)
			ar2 = float(h) / w
			if(0.95 <= ar1 <= 1.05) and (0.95 <= ar2 <= 1.05):
				shape = 4
			if(ar1 > 3.5)or (ar2>3.5):
				shape = 5
		else:
			shape = 1
			
		
		
		# return the name of the shape
		return shape
	
	def getCoords(self, c):
		M = cv2.moments(c)
		sumX = M['m10']
		sumY = M['m01']
		count = M['m00']

		peri = cv2.arcLength(c, True)
		approx = cv2.approxPolyDP(c, 0.04 * peri, True)
		(x, y, side, h) = cv2.boundingRect(approx)

		if count > 0:
			cX = int(sumX / count)
			cY = int(sumY / count)
			return (cX, cY, count, side)
		else:
			return(0, 0, 0, 0)


mode = 1 # 1 - SEARCH, 2 - MOVE, 3 - STOP, 4 - LISTEN
xCenter = 0
yCenter = 0
tXCenter = 0
tYCenter = 0
side = 0
command = default_command


def getArduinoPort():
  usbList = os.listdir('/dev')
  for p in usbList:
    if 'ttyUSB' in p or 'ttyACM' in p:
      return '/dev/' + p
  return 'none'

def doit():
  while True:
    global mode
    global xCenter
    global yCenter
    global side
    
    global default_command
    port = getArduinoPort()
    if 'none' in port:
      print('Arduino not connected')
    else:
      print('Arduino connected to %s' % port)
      arduino = serial.Serial(port, 115200, timeout=.1)
      time.sleep(2)
      canSendToArduino = True
      while canSendToArduino:
        try:
          global command
          print("command =", command)
          
          
          arduino.write([9,mode, command, 240-xCenter,yCenter,side])#serial.to_bytes(
          
          
          time.sleep(0.05)
          
          #print("ARDUINO -",arduino.read())
          #command = default_command
          
        except serial.SerialException:
          print('Connection was lost')
arduino_thread = Thread(target=doit)
arduino_thread.start()
def voice():
    model_path = r'/home/animel/Документы/downloads/microfon/vosk-model-small-ru-0.4'
    song = r'/home/animel/Документы/downloads/microfon/123.mp3'
    start_stream()
    model_init(model_path)
    commands_init()
    while True:
        
        global canListen
        global default_command
        if (canListen):
            global command
            command = default_command
            data = stream.read(1000, exception_on_overflow = False)
            #print(rec)

            if len(data) == 0:
                break
            if rec.AcceptWaveform(data):
                res = rec.Result()
                res = processing_the_result(res)
                print(res)
                
                command = find_command(res, commands)
                print(command)
                play_sound()
                if command != default_command:
                    time.sleep(0.5)
                    #elephant.write(command)
                    #elephant.write(serial.to_bytes([command]))
                    if command == 4:
                        time.sleep(7)
                        subprocess.call(['vlc'] + [song] + ['vlc://quit'])
                
                    canListen = False
            
    
voice_thread = Thread(target=voice)
voice_thread.start()
time.sleep(1)
# initialize the camera and grab a reference to the raw camera capture
camera = PiCamera()
camera.resolution = (240, 240)# 640 480
camera.framerate = 32
rawCapture = PiRGBArray(camera, size=(240, 240))# 640 480
# allow the camera to warmup
time.sleep(4) #0.1
# capture frames from the camera

if UI:
    cv2.namedWindow('image') # Main image
    cv2.namedWindow('color_filter') # Changed image
#cv2.namedWindow('settings')
#cv2.createTrackbar('h1', 'settings', 0, 255, nothing)
#cv2.createTrackbar('s1', 'settings', 0, 255, nothing)
#cv2.createTrackbar('v1', 'settings', 0, 255, nothing)
#cv2.createTrackbar('h2', 'settings', 255, 255, nothing)
#cv2.createTrackbar('s2', 'settings', 255, 255, nothing)
#cv2.createTrackbar('v2', 'settings', 50, 255, nothing)

sd = ShapeDetector()


detectTriangles = False

bufferedTriangles = []
bufferedCircles = []
bufferedRectangles = []
bufferedPentagons = []

for frame in camera.capture_continuous(rawCapture, format='bgr', use_video_port=True):
    # grab the raw NumPy array representing the image, then initialize the timestamp
    # and occupied/unoccupied text
    #print(mode)
    
    
    image = frame.array
    # show the frame
    # cv2.imshow('Frame', image)

    black = np.zeros((240, 240, 3), np.uint8)
    
    hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
    h1 = 0
    s1 = 0
    v1 = 0
    h2 = 255
    s2 = 255
    v2 = 50
    #h1 = cv2.getTrackbarPos('h1', 'settings')
    #s1 = cv2.getTrackbarPos('s1', 'settings')
    #v1 = cv2.getTrackbarPos('v1', 'settings')
    #h2 = cv2.getTrackbarPos('h2', 'settings')
    #s2 = cv2.getTrackbarPos('s2', 'settings')
    #v2 = cv2.getTrackbarPos('v2', 'settings')
    h_min = np.array((h1, s1, v1), np.uint8)
    h_max = np.array((h2, s2, v2), np.uint8)
    color_filter = cv2.inRange(hsv, h_min, h_max)

    blurred = cv2.GaussianBlur(color_filter, (5,5), 0)
    thresh = cv2. threshold(blurred, 60, 255, cv2.THRESH_BINARY)[1]
    
    # find contours in the thresholded image and initialize the
    # shape detector
    cnts = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL,
        cv2.CHAIN_APPROX_SIMPLE)
    cnts = imutils.grab_contours(cnts)
    
    # if marker not detected, we need to find triangles firstly
    circles = []
    rectangles = []
    pentagons = []
    if not detectTriangles:
        triangles = []
        for c in cnts:
            M = cv2.moments(c)
            sumX = M['m10']
            sumY = M['m01']
            count = M['m00']
            if count > 500 and count < 3500:
                shape = sd.detect(c)
                if shape == 1:
                    circles.append(c)
                if shape == 3:
                    triangles.append(c)
                if shape == 4:
                    rectangles.append(c)
                if shape == 5:
                    pentagons.append(c)
        if len(triangles) == 3:
            count = 0
            (t1X, t1Y, count, s) = sd.getCoords(triangles[0])
            (t2X, t2Y, count, s) = sd.getCoords(triangles[1])
            (t3X, t3Y, count, s) = sd.getCoords(triangles[2])
            
            tXCenter = int((t1X + t2X + t3X) / 3)
            tYCenter = int((t1Y + t2Y + t3Y) / 3)
            
            if UI:
                cv2.putText(image, '%d' % len(triangles), (tXCenter, tYCenter),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)
                
            
        
            detectPentagon = False
            if len(pentagons) > 0:
                for c in pentagons:
                    (cX, cY, count, s) = sd.getCoords(c)
                    if abs(cX - tXCenter) < 10 and abs(cY - tYCenter) < 10:
                        bufferedPentagons.append(c)
                        if UI:
                            c = c.astype('int')
                            cv2.drawContours(black, [c], -1, (255, 255, 255), 2)
                            cv2.putText(image, '%s' % 'LISTEN', (cX, cY),
                                cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)
                        mode = 4 # LISTEN
                        #print("pentagon")
                        detectPentagon = True
                        canListen = True
                        
                        

            detectRectangle = False
            if len(rectangles) > 0:
                for c in rectangles:
                    (cX, cY, count, s) = sd.getCoords(c)
                    if abs(cX - tXCenter) < 10 and abs(cY - tYCenter) < 10:
                        bufferedRectangles.append(c)
                        if UI:
                            c = c.astype('int')
                            cv2.drawContours(black, [c], -1, (0, 0, 255), 2)
                            cv2.putText(image, '%s' % 'STOP', (cX, cY),
                                cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)
                        mode = 3 # STOP
                        detectRectangle = True
                        #print("rectangle")

            detectCircle = False
            if len(circles) > 0:
                for c in circles:
                    (cX, cY, count, s) = sd.getCoords(c)
                    if abs(cX - tXCenter) < 10 and abs(cY - tYCenter) < 10:
                        bufferedCircles.append(c)
                        if UI:
                            c = c.astype('int')
                            cv2.drawContours(black, [c], -1, (255, 0, 0), 2)
                            cv2.putText(image, '%s' % 'MOVE', (cX, cY),
                                cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)
                        xCenter = cX
                        yCenter = cY
                        side = s
                        mode = 2 # MOVE
                        detectCircle = True
                        command = 50
                        #print("circle")
            
            if (detectRectangle or detectCircle) or detectPentagon:
                for c in triangles:
                    bufferedTriangles.append(c)
                    (cX, cY, count, s) = sd.getCoords(c)
                    if UI:
                        c = c.astype('int')
                        cv2.drawContours(black, [c], -1, (0, 255, 0), 2)
                        cv2.putText(image, '%d' % count, (cX, cY),
                            cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)
                detectTriangles = True
    if detectTriangles:
        minRadius = 50
        bufferedRectangles = []
        bufferedTriangles = []
        bufferedCircles = []
        bufferedPentagons = []

        if mode == 3:
            for c in cnts:
                M = cv2.moments(c)
                count = M['m00']
                if count > 50 and count < 5000:
                    shape = sd.detect(c)
                    if shape == 4:
                        (cX, cY, count, s) = sd.getCoords(c)
                        if (cX - xCenter)*(cX - yCenter) + (cY - yCenter)*(cY - yCenter) < minRadius*minRadius:
                                bufferedRectangles.append(c)
                                break                                
            if len(bufferedRectangles) > 0:
                movingRectangle = bufferedRectangles[0]
                (cX, cY, count, s) = sd.getCoords(movingRectangle)
                movingRectangle = movingRectangle.astype('int')
                xCenter = cX
                yCenter = cY
                side = s
                if UI:
                    cv2.drawContours(black, [movingRectangle], -1, (255, 0, 0), 2)
            else:
                detectTriangles = False
                mode = 1
        elif mode == 2:
            for c in cnts:
                M = cv2.moments(c)
                count = M['m00']
                if count > 50 and count < 5000:
                    shape = sd.detect(c)
                    if shape == 1:
                        (cX, cY, count, s) = sd.getCoords(c)
                        if (cX - xCenter)*(cX - yCenter) + (cY - yCenter)*(cY - yCenter) < minRadius*minRadius:
                                bufferedCircles.append(c)
                                break                                
            if len(bufferedCircles) > 0:
                movingCircle = bufferedCircles[0]
                (cX, cY, count, s) = sd.getCoords(movingCircle)
                movingCircle = movingCircle.astype('int')
                xCenter = cX
                yCenter = cY
                side = s
                if UI:
                    cv2.drawContours(black, [movingCircle], -1, (255, 0, 0), 2)
            else:
                detectTriangles = False
                mode = 1
        elif mode == 4:
            for c in cnts:
                M = cv2.moments(c)
                count = M['m00']
                if count > 50 and count < 5000:
                    shape = sd.detect(c)
                    if shape == 5:
                        (cX, cY, count, s) = sd.getCoords(c)
                        if (cX - xCenter)*(cX - yCenter) + (cY - yCenter)*(cY - yCenter) < minRadius*minRadius:
                                bufferedPentagons.append(c)
                                break                                
            if len(bufferedPentagons) > 0:
                movingPentagon = bufferedPentagons[0]
                (cX, cY, count, s) = sd.getCoords(movingPentagon)
                movingPentagon= movingPentagon.astype('int')
                xCenter = cX
                yCenter = cY
                side = s
                
                if UI:
                    cv2.drawContours(black, [movingPentagon], -1, (255, 0, 0), 2)
            else:
                detectTriangles = False
                mode = 1
            
    if UI:
        cv2.putText(black, '%d' % mode, (20, 20),
            cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)
        cv2.imshow('color_filter', black)
        cv2.imshow('image', image)
    
    key = cv2.waitKey(1) & 0xFF
    # clear the stream in prepatation for the next frame
    rawCapture.truncate(0)
    # if the 'q' key was pressed, break from the loop
    if key == ord('q'):
        break

if __name__=='__main__':
    def nothing(*args):
        pass




                      
