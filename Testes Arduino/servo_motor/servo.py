from numpy import byte
import serial
import time

while True: #Loop para a conexão com o Arduino
    try:  #Tenta se conectar, se conseguir, o loop se encerra
        arduino = serial.Serial('COM3', 9600, dsrdtr = None, timeout=3)
        print('Arduino conectado')
        break
    except:
        pass
time.sleep(5)

arduino.flushInput()
arduino.flushOutput()

time.sleep(.1)

arduino.write(chr(180).encode())
arduino.write(chr(45).encode())

# while arduino.in_waiting:
#     print (arduino.readline())
for i in range(5):
    txt=arduino.read()
    print(txt)
    print(int.from_bytes(txt, 'little'))