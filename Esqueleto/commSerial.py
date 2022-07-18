from numpy import byte
import serial
import time
from olhos import olho

class commSerial:

# Braço_Esquerdo - Braco_Direito - Tronco - Pescoço_Horizontal - Pescoço_Vertical - Olho_Esquerdo  - Olho_Direito

	def __init__(self):
		self.bravo = [0, 0, 0, 45, 0, olho.bravo, olho.bravo]
		self.triste = [0, 0, 0, 0, 20, olho.triste, olho.triste]
		self.dormindo = [0, 0, 0, 0, 30, olho.dormindo, olho.dormindo]
		self.neutro = [0, 0, 0, 0, 0, olho.neutro, olho.neutro]
		self.feliz = [0, 0, 0, 0, 0, olho.feliz, olho.feliz]
		self.falar_nome = [0, 0, 0, 0, 0, olho.noChange, olho.noChange]
		self.falar_projeto = [0, 0, 0, 0, 0, olho.noChange, olho.noChange]
		self.soletrando = [0, 0, 0, 0, 0, olho.noChange, olho.noChange]
		self.falar_ADA = [0, 0, 0, 0, 0, olho.noChange, olho.noChange]
		self.falar_SEMEAR = [0, 0, 0, 0, 0, olho.noChange, olho.noChange]
		self.piada_simples = [0, 0, 0, 0, 0, olho.feliz, olho.feliz]
		self.piada_pergunta_e_resposta = [0, 0, 0, 0, 0, olho.feliz, olho.feliz]
		self.piada_toc_toc = [0, 0, 0, 0, 0, olho.feliz, olho.feliz]
		self.piada = [0, 0, 0, 0, 0, olho.feliz, olho.feliz]
		self.levantar_bracos = [180, 180, 0, 0, 0, olho.noChange, olho.noChange]

		while True: #Loop para a conexão com o Arduino
			try:  #Tenta se conectar, se conseguir, o loop se encerra
				self.arduino = serial.Serial('COM3', 9600, dsrdtr = None)
				print('Arduino conectado')
				break
			except:
				pass
		time.sleep(5)

	def mudancaEstado (self, currState, prevState):
		'''Função que seleciona qual mensagem deve ser enviada para o arduino
			Obs: Não conseguimos pensar em uma maneira menor de fazer isso :(
		'''
		print("Estado atual: ", currState)


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

		self.sendMsg(msg)

	def createMsg (self, lista):
		msg=bytearray()

		for pos in range(5):
			msg.extend(lista[pos].to_bytes(2, byteorder='big'))
			msg.extend((5).to_bytes(2, byteorder='big'))
		
		for pos in range(5, 7):
			msg.extend(lista[pos].to_bytes(2, byteorder='big'))

		msg.extend((1).to_bytes(2, byteorder='big'))

		return msg


	def sendMsg(self, msg):
		self.arduino.write(msg)
		print("Mensagem lida:")
		txt=self.arduino.read()
		print(int.from_bytes(txt, 'big'))
		print(int.from_bytes(txt, 'little'))


		