import serial
import time

while True: #Loop para a conexão com o Arduino
    try:  #Tenta se conectar, se conseguir, o loop se encerra
        arduino = serial.Serial('COM3', 9600, dsrdtr = None)
        print('Arduino conectado')
        break
    except:
        pass

time.sleep(5)
arduino.write('\2'.encode())

while(True):
    pass