from enum import Enum

class olho(Enum):
	neutro = 0
	feliz = 1
	triste = 2
	bravo = 3
	dorme = 4
	nada = 5

# 1 - 7 - 15 - 11 - 15 - 12 - 15
class comando(Enum):
	ofensa = 0 #Ela fica triste se é ofendida
	ELOGIO = 1 #Ela fica feliz se é elogiada
	silencio = 2 #Ela muda de estado se ninguém fala com ela
	Dancar = 3 #Ela dança
	Acordar = 4 #Ela acorda do modo repouso
	Dormir = 5 #Ela entra em modo repouso
	Girar = 6 #Ela gira em torno do seu eixo principal
	Levantar_bracos = 7 #Ela levanta os braços
	Piada = 8 #Ela conta uma piada
	Esta_bem = 9 #Ela diz qual o estado emocional atual
	Apresentar = 10 #Ela se apresenta
	SEMEAR = 11 #Ela fala um pouco sobre o Grupo SEMEAR
	ADA = 12 #Ela fala um pouco sobre a ADA
	Musica = 13 #Ela toca uma música 
	Soletrar = 14 #Ela soletra a palavra que pedirem
	Stop = 15 #Ela para de falar
	Desculpa = 16 #Ela deixa de ficar triste se pedem desculpas
	Falar_nome = 17 #Ela fala o próprio nome
	Falar_projeto = 18 #Ela fala sobre si mesma

SOLETRAR_DICT = {
	"a": "A",
	"b": "Bê",
	"c": "Cê",
	"d": "Dê",
	"e": "Ê",
	"f": "É fi",
	"g": "Gê",
	"h": "A gá",
	"i": "I",
	"j": "Jota",
	"k": "Ká",
	"l": "É li",
	"m": "Ê mi",
	"n": "Ê ni",
	"o": "Ô",
	"p": "Pê",
	"q": "Quê",
	"r": "É ri",
	"s": "É si",
	"t": "Tê",
	"u": "Ú",
	"v": "Vê",
	"w": "Dábliu",
	"x": "Xis",
	"y": "Ípsilom",
	"z": "Zê",
	"ç": "Cê cedilha",
	"á": "A com acento agudo",
	"ã": "A com til",
	"â": "A com acento circunflexo",
	"à": "A com crase",
	"ó": "Ô com acento agudo",
	"õ": "Ô com til",
	"ô": "Ô com acento circunflexo",
	"é": "Ê com acento agudo",
	"ê": "Ê com acento circunflexo",
	"ú": "Ê com acento agudo",
	"ü": "Ú com trema",
	"í": "I com acento agudo",
	"0": "Zero",
	"1": "Um",
	"2": "Dois",
	"3": "Três",
	"4": "Quatro",
	"5": "Cinco",
	"6": "Seis",
	"7": "Sete",
	"8": "Oito",
	"9": "Nove"
}