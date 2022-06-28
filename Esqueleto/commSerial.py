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


		if currState=="Bravo":
			msg=createMsg(self.bravo)
		elif currState=="Neutro":
			msg=createMsg(self.neutro)
		elif currState=="Triste":
			msg=createMsg(self.triste)
		elif currState=="Feliz":
			msg=createMsg(self.feliz)
		elif currState=="Dormindo":
			msg=createMsg(self.dormindo)
		elif currState=="handsup":
			msg=createMsg(self.levantar_bracos)
		elif currState=="Falar_nome":
			msg=createMsg(self.falar_nome)
		elif currState=="Falar_projeto":
			msg=createMsg(self.falar_projeto)
		elif currState=="Soletrando":
			msg=createMsg(self.soletrando)
		elif currState=="Falar_sobre_ADA": 
			msg=createMsg(self.falar_ADA)
		elif currState=="Falar_sobre_SEMEAR":
			msg=createMsg(self.falar_SEMEAR)
		elif currState=="Piada sem transição":
			msg=createMsg(self.piada_simples)
		elif currState=="Piada pergunta e resposta":
			msg=createMsg(self.piada_pergunta_e_resposta)
		elif currState=="Piada toc toc":
			msg=createMsg(self.piada_toc_toc)
		elif currState=="Piada":
			msg=createMsg(self.piada)


	def createMsg (lista):
		msg=bytearray()

		for pos in range(5):
			msg.append(lista[pos].to_bytes(2, byteorder='big'))
			msg.append((5).to_bytes(2, byteorder='big'))
		
		for pos in range(5, 7):
			msg.append(lista[pos].to_bytes(2, byteorder='big'))

		msg.append((0).to_bytes(2, byteorder='big'))

		return msg


	def sendMsg(self, msg):
		self.arduino.write(msg.encode())