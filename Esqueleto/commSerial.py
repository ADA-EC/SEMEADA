import serial
import time

class commSerial:
	
	def __init__(self):
		while True: #Loop para a conexão com o Arduino
			try:  #Tenta se conectar, se conseguir, o loop se encerra
				self.arduino = serial.Serial('COM7', 9600, dsrdtr = None)
				print('Arduino conectado')
				break
			except:
				pass
		time.sleep(5)

	def sendMsg(self, msg):
		self.arduino.write(msg.encode())