import serial

while True: #Loop para a conexão com o Arduino
    try:  #Tenta se conectar, se conseguir, o loop se encerra
        arduino = serial.Serial('COM4', 9600)
        print('Arduino conectado')
        break
    except:
        pass

arduino.write('\1'.encode())