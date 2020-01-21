import serial, time
arduino = serial.Serial('COM1', 115200, timeout=.1)
time.sleep(1) #give the connection a second to settle
arduino.write()
while True:
	data = arduino.readline()
	if data:
		print data.rstrip('\n')