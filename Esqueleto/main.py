from comandos import comando
import processamento_voz
import state_machine
import sintese_voz
import PLN
#Bibliotecas de PLN
from spacy.lang.pt.stop_words import STOP_WORDS
import spacy

# Teste Servo: 1 - 7 - 15 - 11 - 15 - 12 - 15
# Teste Olho: 0 - 16 - 11 - 15 - 1 - 2 - 5
def main():
	pln_tokenizer = spacy.load("pt_core_news_sm")
	pln_tokenizer.Defaults.stop_words.remove("estar")
	stop_words = STOP_WORDS
	nlp = spacy.load("Esqueleto/model-last")

	robo = state_machine.MaqEstados(serial_port="COM9")
	print("criado")

	if(comando.elogio == 1):
		print("oe")

	while True:
		msg = input('Mensagem: ')

		if(msg == 'Ouvir'):
			texto = processamento_voz.get_audio("audio.wav")
			sintese_voz.speak(texto)
			numComando = PLN.pln(texto, nlp, stop_words, pln_tokenizer)
			# robo.send(str(numComando))
		else:
			robo.send(msg)

if (__name__ == '__main__'):
	main()