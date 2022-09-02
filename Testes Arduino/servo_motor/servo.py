from numpy import byte
import serial
import time

while True: #Loop para a conexão com o Arduino
    try:  #Tenta se conectar, se conseguir, o loop se encerra
        arduino = serial.Serial('COM5', 9600, dsrdtr = None, timeout=4)
        print('Arduino conectado')
        break
    except:
        pass
time.sleep(4)

# arduino.flushInput()
# arduino.flushOutput()

time.sleep(.1)

# arduino.write(chr(180).encode())
# arduino.write(chr(45).encode())

num1 = 270
num2 = 30

msg = num1.to_bytes(2, 'little')+num2.to_bytes(2, 'little')

print(msg)

arduino.write(msg)

# while arduino.in_waiting:
#     print (arduino.readline())
for i in range(10):
    txt=arduino.read()
    if(txt != b''):
        print(txt)
        print(int.from_bytes(txt, 'little'))