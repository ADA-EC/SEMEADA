from numpy import byte
import serial
import time

def numsToMsg(nums):
	msg=bytearray()

	for pos in range(5):
		msg.extend(nums[pos].to_bytes(2, byteorder='little'))
		msg.extend((5).to_bytes(2, byteorder='little'))
	msg.extend((5).to_bytes(2, byteorder='little'))
	msg.extend((5).to_bytes(2, byteorder='little'))
	msg.extend((5).to_bytes(2, byteorder='little'))

	return msg

while True: #Loop para a conexão com o Arduino
	try:  #Tenta se conectar, se conseguir, o loop se encerra
		arduino = serial.Serial('COM5', 9600, dsrdtr = None, timeout=4)
		print('Arduino conectado')
		break
	except:
		pass
time.sleep(4)

# arduino.write(chr(180).encode())
# arduino.write(chr(45).encode())

numsList = [	[90, 90, 90, 90, 90],
				[0, 0, 0, 0, 0],
				[0, 90, 0, 90, 0],
				[90, 0, 90, 0, 90]	]

for n in numsList:
	msg = numsToMsg(n)
	# print(msg)
	arduino.write(msg)
	time.sleep(1)


time.sleep(2)
# while arduino.in_waiting:
#     print (arduino.readline())
for i in range(5):
	txt = arduino.read(size=26)
	if(txt != b''):
		# print(txt)
		for i in range(4):
			print(int.from_bytes(txt[2*(2*i):2*((2*i)+1)], 'little'), end=" - ")
		print(int.from_bytes(txt[16:18], 'little'))
	else:
		print("NONE")