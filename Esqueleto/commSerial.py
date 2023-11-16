from utils import olho

from numpy import byte

import serial
import time

class commSerial:

# Braço_Esquerdo - Braco_Direito - Tronco - Pescoço_Horizontal - Pescoço_Vertical - Olho_Esquerdo  - Olho_Direito

	def __init__(self, serial_port):
		self.state_position_dict = {
			"Bravo":			[0,   0,   0,   45,  0,   olho.bravo,  olho.bravo],
			"Triste":			[0,   0,   0,   0,   20,  olho.triste, olho.triste],
			"Dormindo":			[0,   0,   0,   0,   30,  olho.dorme,  olho.dorme],
			"Neutro":			[0,   0,   0,   0,   0,   olho.neutro, olho.neutro],
			"Feliz":			[60,  30,  90,  180, 0,   olho.feliz,  olho.feliz],
			"Falar_nome":		[0,   0,   0,   0,   0,   olho.nada,   olho.nada],
			"Falar_projeto":	[0,   0,   0,   0,   0,   olho.nada,   olho.nada],
			"Soletrando":		[0,   0,   0,   0,   0,   olho.nada,   olho.nada],
			"Falar_ADA":		[0,   180, 180, 90,  90,  olho.nada,   olho.nada],
			"Falar_SEMEAR":		[30,  60,  90,  90,  180, olho.nada,   olho.nada],
			"Piada":			[0,   0,   0,   0,   0,   olho.feliz,  olho.feliz],
			"Levantar_bracos":	[180, 45,  45,  180, 90,  olho.nada,   olho.nada]
		}

		MAX_TRIES = 2
		num_tries = 0
		while num_tries < MAX_TRIES: #Loop para a conexão com o Arduino
			try:  #Tenta se conectar, se conseguir, o loop se encerra
				self.arduino = serial.Serial(serial_port, 9600, dsrdtr = None, timeout=4)
				print('Arduino conectado')
				break
			except:
				num_tries += 1
		
		if(num_tries == MAX_TRIES):
			raise Exception(f"\nFailed to connect to Arduino.\nPORT: {serial_port}\n")
		time.sleep(5)

	def mudancaEstado (self, currState, prevState):
		'''Função que seleciona qual mensagem deve ser enviada para o arduino
		'''
		print("Estado atual: ", currState)
		msg = None

		if(currState=="Dançando"):
			print("DANÇA")
		elif(not (currState in self.state_position_dict)):
			print("WARN: Nenhum comando de braço programado")
		else:
			msg=self.createMsg(
				self.state_position_dict[currState]
			)
			self.sendMsg(msg)

	def createMsg (self, lista):
		msg=bytearray()

		for pos in range(5):
			msg.extend(lista[pos].to_bytes(2, byteorder='little'))
			msg.extend((5).to_bytes(2, byteorder='little'))
		
		for pos in range(5, 7):
			msg.extend(lista[pos].to_bytes(2, byteorder='little'))

		return msg


	def sendMsg(self, msg):
		# print(msg)
		for i in range(5):
			print(int.from_bytes(msg[2*(2*i):2*((2*i)+1)], 'little'), end=" - ")
		print(int.from_bytes(msg[20:21], 'little'), end=" - ")
		print(int.from_bytes(msg[22:23], 'little'))
		self.arduino.write(msg)
		# print("Mensagem lida:")
		# txt=self.arduino.read(size=24)
		# if(txt != b''):
		# 	print(txt)
		# 	for i in range(5):
		# 		print(int.from_bytes(txt[2*(2*i):2*((2*i)+1)], 'little'), end=" - ")
		# 	print(int.from_bytes(txt[20:21], 'little'), end=" - ")
		# 	print(int.from_bytes(txt[22:23], 'little'))
		# else:
		# 	print("NONE")


		