from numpy import byte
import serial
import time
from olhos import olho

class commSerial:

# Braço_Esquerdo - Braco_Direito - Tronco - Pescoço_Horizontal - Pescoço_Vertical - Olho_Esquerdo  - Olho_Direito

	def __init__(self, serial_port):
		self.bravo = [0, 0, 0, 45, 0, olho.bravo, olho.bravo]
		self.triste = [0, 0, 0, 0, 20, olho.triste, olho.triste]
		self.dormindo = [0, 0, 0, 0, 30, olho.dormindo, olho.dormindo]
		self.neutro = [0, 0, 0, 0, 0, olho.neutro, olho.neutro]
		self.feliz = [60, 30, 90, 180, 0, olho.feliz, olho.feliz]
		self.falar_nome = [0, 0, 0, 0, 0, olho.noChange, olho.noChange]
		self.falar_projeto = [0, 0, 0, 0, 0, olho.noChange, olho.noChange]
		self.soletrando = [0, 0, 0, 0, 0, olho.noChange, olho.noChange]
		self.falar_ADA = [0, 180, 180, 90, 90, olho.noChange, olho.noChange]
		self.falar_SEMEAR = [30, 60, 90, 90, 180, olho.noChange, olho.noChange]
		self.piada_simples = [0, 0, 0, 0, 0, olho.feliz, olho.feliz]
		self.piada_pergunta_e_resposta = [0, 0, 0, 0, 0, olho.feliz, olho.feliz]
		self.piada_toc_toc = [0, 0, 0, 0, 0, olho.feliz, olho.feliz]
		self.piada = [0, 0, 0, 0, 0, olho.feliz, olho.feliz]
		self.levantar_bracos = [180, 45, 45, 180, 90, olho.noChange, olho.noChange]

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
			Obs: Não conseguimos pensar em uma maneira menor de fazer isso :(
		'''
		print("Estado atual: ", currState)
		msg = None


		if currState=="Bravo":
			msg=self.createMsg(self.bravo)
		elif currState=="Neutro":
			msg=self.createMsg(self.neutro)
		elif currState=="Triste":
			msg=self.createMsg(self.triste)
		elif currState=="Feliz":
			msg=self.createMsg(self.feliz)
		elif currState=="Dormindo":
			msg=self.createMsg(self.dormindo)
		elif currState=="handsup":
			print("ENTROU!")
			msg=self.createMsg(self.levantar_bracos)
		elif currState=="Falar_nome":
			msg=self.createMsg(self.falar_nome)
		elif currState=="Falar_projeto":
			msg=self.createMsg(self.falar_projeto)
		elif currState=="Soletrando":
			msg=self.createMsg(self.soletrando)
		elif currState=="Falar_sobre_ADA": 
			msg=self.createMsg(self.falar_ADA)
		elif currState=="Falar_sobre_SEMEAR":
			msg=self.createMsg(self.falar_SEMEAR)
		elif currState=="Piada sem transição":
			msg=self.createMsg(self.piada_simples)
		elif currState=="Piada pergunta e resposta":
			msg=self.createMsg(self.piada_pergunta_e_resposta)
		elif currState=="Piada toc toc":
			msg=self.createMsg(self.piada_toc_toc)
		elif currState=="Piada":
			msg=self.createMsg(self.piada)

		if(msg != None):
			self.sendMsg(msg)
		else:
			print("WARN: Nenhum comando de braço programado/enviado")

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


		