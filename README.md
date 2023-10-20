# 🤖 SEMEADA

## O que é o projeto?
O projeto, desenvolvido pela [ADA](http://adaec.icmc.usp.br/sobre-nos/) em parceria com o [SEMEAR](https://semear.eesc.usp.br/), se trata de um robô de mesa capaz de captar comandos de fala e interpretá-los, por meio de **processamento de linguagem natural**, para realizar ações. Até o momento, o robô é capaz de obedecer aos seguintes comandos:
* Dançar
* Acordar
* Dormir
* Girar
* Levantar os braços
* Contar uma piada
* Falar sobre seu atual estado emocional
* Se apresentar
* Falar sobre a ADA
* Falar sobre o SEMEAR
* Tocar uma música
* Soletrar uma palavra
* Falar sobre o projeto

Além disso, o robô, através de máquinas de estado, possui a habilida de **simular sentimentos**, tendo assim um **"estado de espírito"**.

A seguir descrevemos mais detalhadamente o funcionamento do projeto.

## Funcionamento
Quando o robô é inicializado, o mesmo fica em estado de espera, aguardando o acionamento. Quando recebe a mensagem "Ouvir", inicia a captação de áudio (posteriormente será utilizado um botão para iniciar a captação). O áudio é armazenado em uma faixa de som (audio.wav) posteriormente enviada para `processamento_voz.py`, que utiliza a biblioteca `speech_recognition` para transformar o áudio captado em texto. O texto então é submetido 

![Fluxo](https://github.com/ADA-EC/SEMEADA/blob/main/readme/fluxo_robo.png)

## Executando o projeto
### Treinando o modelo

### Rodando o código
Para rodar o projeto, executar o comando: <br>
`python Esqueleto/main.py`

## Estrutura de pastas do projeto
- 📁 Codigo ➡️ contém arquivos de estudo do início do projeto
- 📁 Esqueleto ➡️ contém todo o código do robô
  - 🐍`comandos.py` ➡️ mapemaneto dos comandos em números, chamado pelo PLN
  - 🐍`commSerial.py` ➡️ faz a comunicação do código python com o Arduino, chamada pela máquina de estados
  - 🐍`main.py` ➡️ coordena todas as funções do robô
    - inicializa o robô
    - chama o processamento de áudio
    - recebe o texto de volta
    - envia o texto para o processamento
    - recebe o número do comando
    - envia para a máquina de estados   
  - 🐍`olhos.py` ➡️ mapeamento dos olhos para cada estado de humor
  - 🐍`PLN.py` ➡️ recebe o texto da *main*, faz o pré processamento do texto, submete ao modelo, retorna o valor do comando para a *main*
  - 🐍`processamento_voz.py` ➡️ chamada pela *main*, capta o áudio, transforma em texto e retorna para a *main*
  - 🐍`rostos.py` ➡️ faz a conexão com o arduino (não sei se está sendo utilizada, verificar remoção)
  - 🐍`sintese_voz.py` ➡️ usado para repetir o comando de voz de volta (verificar remoção)
  - 🐍`state_machine.py` ➡️ controla o estado de humor do robô, gerencia execução dos comandos (recebe da *main* o comando e envia para *commSerial*)
- 📁 Falhas_treinamento_PLN ➡️ contém o histórico de tentativas de treinamento do modelo
- 📁 Gravar ➡️ armazena o arquivo de áudio captado
- 📁 Maquina_Estados ➡️ contém as imagens das máquinas de estados desenvolvidas no JFLAP
- 📁 Olhos ➡️ contém os arquivos com as imagens usada para teste das telas LCD
- 📁 PCB ➡️ contém o projeto das placas do robô
- 📁 Testes Arduino ➡️ contém os arquivos comunicação com os componentes físicos do robô
- 📁 Treinamento_PLN ➡️ contém os arquivos de treinamento do modelo de processamento de linguagem natural

## O hardware


## Tecnologias Usadas

### Bibliotecas utilizadas
A seguir uma lista das bibliotecas utilizadas e como fazer sua instalação, além de dicas para contornar possíveis erros durante a instalação. (Todas as instalações foram feitas utilizando o pip, não usar o WSL)
- Pandas <br>
  `pip install pandas`
- SpaCy <br>
  `pip install spacy`
- Seaborn <br>
  `pip install seaborn`
- SpaCy Language Detector <br>
  `pip install spacy-langdetect`
- SpaCy pt_core_news_sm <br>
  `python -m spacy download pt_core_news_sm`
- gTTS <br>
  `pip install gTTS`
- SpeechRecognition [Caso não dê certo, tente rodar “pip3 install SpeechRecognition”] <br>
  `pip install SpeechRecognition`
- PlaySound [Caso não dê certo, tente dar um downgrade para a versão 1.2.2 (pip install playsound==1.2.2)] <br>
  `pip install playsound==1.2.2`
- PyDub <br>
  `pip install pydub`
- SoundDevice <br>
  `pip install sounddevice`
- SoundFile <br>
  `pip install SoundFile`
- Pyserial <br>
  `pip install pyserial`
- PyAudio <br>
  `pip install pyaudio`

### Máquina de Estados
Para realizar o projeto, fizemos algumas máquinas de estados modificadas que indicam o estado do robô após realizar os comandos.
Um exemplo disso é a maquina de estado desenvolvida para vários comandos diversos, mostrada abaixo. Nela, após realizar um comando como dançar, ele fica automaticamente no estado de "feliz".

![Máquina de Estados - Diversos](https://github.com/ADA-EC/SEMEADA/blob/main/Maquina_Estados/Diversos.png)

Além disso, nota-se na imagem que alguns comandos não serão obedecidos se o robô estiver em determinado estado emocional, como o comando "dançar" também, que só pode ser realizado quando este está "feliz", "neutro" ou "triste".

Alguns comentários foram adicionados aos desenhos, para facilitar compreensão e auxiliar no entendimento na hora de construir o código em Python. Um exemplo de comentário pode ser visto na imagem abaixo, referente à máquina de estados "Tocar música".

![Máquina de Estados - Tocar Música](https://github.com/ADA-EC/SEMEADA/blob/main/Maquina_Estados/Tocar_musica.png)

## Membros
- [Érika Hortência](https://github.com/erika-hortencia)
- [Gabriela Barion Vidal](https://github.com/GabrielaVidal7)
- [Rodrigo Bragato Piva](https://github.com/Rodrigo-P)
- Marcos Almeida


## Agradecimentos
- [Victor Amaral](https://github.com/felfipe)
- [Breno Seixas]([https://github.com/TsuyoshiSonobe](https://github.com/TheGuardianB))
- [Tsuyoshi Sonobe](https://github.com/TsuyoshiSonobe)
- [Pedro Torrente](https://github.com/pdrtorrente)
- Manuella Porto
