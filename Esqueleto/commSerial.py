import serial
import time

class commSerial:

		

	def __init__(self):
		self.neutro = []
		self.bravo = []
		self.triste = []
		self.feliz = []
		self.dormindo = []
		self.falar_nome = []
		self.falar_projeto = []
		self.soletrando = []
		self.falar_ADA = []
		self.falar_SEMEAR = []
		self.piada_simples = []
		self.piada_pergunta_e_resposta = []
		self.piada_toc_toc = []
		self.piada = []
		self.tocar_musica = []

		while True: #Loop para a conexão com o Arduino
			try:  #Tenta se conectar, se conseguir, o loop se encerra
				self.arduino = serial.Serial('COM3', 9600, dsrdtr = None)
				print('Arduino conectado')
				break
			except:
				pass
		time.sleep(5)

	def mudancaEstado (currState, prevState):
		'''Formato do dado:
			BE BD Tr PH PV OE OD NL
			(Para mais informações, acessar 'formato.txt')
		'''
	
	def sendMsg(self, msg):
		self.arduino.write(msg.encode())