# Programando em C e ASM para MSX usando Visual Studio e Fusion-C
# Sessão 10: Joysticks, Édens de dificuldade e uma maçã vermelha.

Escrito por **Danilo Angelo (a.k.a. Damned Angel)**, 2020-2021

Vídeo da sessão 10: XXX

Canal **8-bit Saga**: https://www.youtube.com/channel/UC-QPKENS07P_5q-7a7ps2HA

Discord server **MSX Revamp**: https://discord.gg/f3HDgfXKxE

Templates de projetos MSX: https://github.com/DamnedAngel/MSX-Templates-for-VisualStudio/releases

---

## Nota do autor

__A participação no workshop, bem como a utilização dos materiais associados, é livre e gratuita. 
No entanto, vale lembrar que a preparação das sessões, o desenvolvimento e a manutenção dos templates, a escrita dos programas de exemplo, a preparação da infra-estrutura e edição dos vídeos consomem tempo e recursos razoáveis.
Se você quiser reconhecer esse trabalho e prestigiar a iniciativa, faça sua colaboração através de uma das plataformas abaixo:__

* BuyMeACoffe: https://www.buymeacoffee.com/DamnedAngel​
* PayPal: danilo@angelo.eng.br
* Pix: danilo@angelo.eng.br

**Long live MSX!**

---

## Abreviações usadas nesse documento

VS: Visual Studio 2019

---

## Padronizações usadas nesse documento

Esse documento é dividido em sessões de workshop, e as sessões são divididas em tópicos de estudo.

Os tópicos de estudo são dividos em passos. Esses passos terão sempre 1 dentre 3 formatos:
* Um passo com o verbo no gerúndio (ex: *Compilando o projeto.*) significa uma exposição do palestrante (assista o vídeo no YouTube com a exposição em XXX)
* Um passo com o verbo no imperativo (ex: *Configure a aplicação*) denota um passo para ser executado pelo participante.
* Um passo com a descrição de uma atividade (ex: *Discussão em grupo.*) descreve a proposta de uma dinâmica.

Adicionalmente, note que os trechos de código fornecidos como exemplo muitas vezes contém um trecho já existente do programa, para referência de localização.

---

# Sessão 10: Joysticks, Édens de dificuldade e uma maçã vermelha.

### 10.1. Consertar a espera pela liberação das teclas.
###### *Github Ticket/Branch: 32/TKT0032.*

##### Objetivo: Impedir a mudança de telas Game Over -> Abertura -> Jogos se o jogador estiver com alguma tecla ininterruptamente apertada (previsão: 15 minutos).

1. Entendo o problema atual: Por que o programa não está aguardando as teclas serem soltas?
- Diferença de tratamento entre teclado e joysticks.
- A dualidade das setas e barra de espaço.

2. **DESAFIO**: Sem olhar a resposta abaixo e com base na discussão que fizemos sobre as funções de números aleatórios, resolva o problema identificado.

```c
void title() {

	// ...

	while (JoystickRead(0)) {}	// waits for key release
	while (!JoystickRead(0)) {}	// waits for key press
}
```
```c
void gameOver() {

	// ...

	while (JoystickRead(0)) {}	// waits for key release
	while (!JoystickRead(0)) {}	// waits for key press
}
```

### 10.2. Implementando suporte a Joysticks.
###### *Github Ticket/Branch: 37/TKT0037.*

##### Objetivo: Permitir que o jogador controle a cobra pelo teclado ou por qualquer uma das portas de joystick (previsão: 15 minutos).

1. Definindo as mecânica de uso de múltiplos joysticks:
- Não colocaremos opção de seleção de joysticks. Todos funcionarão durante o jogo, de forma priorizada.
- Setas terão prioridade sobre o Joystick 1. Ambos terão prioridade sobre o Joystick 2.
- Ou seja:
  - Se algum comando das setas estiver sendo dado, use esse comando.
  - Senão, se algum comando no Joystick 1 estiver sendo dado, use esse comando.
  - Senão, use quaisquer comandos do Joystick 2 (ou nenhum, se não houver).

2. **DESAFIO**: Sem olhar a resposta abaixo, crie a função allJoysticks sem parâmetros que retorna comandos conforme a estratégia estabelecida acima.

```c
char allJoysticks() {
	char result;	
	if (result = JoystickRead(0)) return result;
	if (result = JoystickRead(1)) return result;
	return JoystickRead(2);
}
```

2. Substitua *JoystickRead()* por *allJoysticks()* na atribuição a variável *joy*.

```c
		while (lastJiffy == Peekw(BIOS_JIFFY)) {
			joy = allJoysticks();
```

3. Compile e rode o programa. Como testar?

4. Substitua *JoystickRead()* por *allJoysticks()* na espera de liberação de teclas, tanto em *title() *quanto em *gameOver()*.

```c
	while (allJoysticks()) {}	// waits for key release
	while (!allJoysticks()) {}	// waits for key press
``` 

5. Compile e rode o programa.

### 9.3. Materializando muitas outras maçãs.
###### *Github Ticket/Branch: 30/TKT0030.*

##### Objetivo: Sempre apresentar uma maçã a ser perseguida pela cobra (previsão: 5 minutos).

1. **DESAFIO**: Sem olhar a resposta abaixo, materialize uma maçã toda vez que a anterior for comida pela cobra.

```c
			if (content == TILE_APPLE) {
				dropApple();
				growth = (rand() & 7) + 1;
			}
```

### 9.4. Quem está contando?
###### *Github Ticket/Branch: 31/TKT0031.*

##### Objetivo: Implementar sistema de contagem de pontos (previsão: 20 minutos).

1. Definindo a mecânica da pontuação:
- A pontuação é zerada no início de cada jogo.
- A pontuação será incrementada com o mesmo número de pontos quanto for o crescimento da cobra em segmentos, no momento que a cobra come uma maçã.
- O recorde é zerado no início do programa. 
- O recorde é atualizado para o valor da pontuação toda vez que a pontuação for maior que ele.

2. **DESAFIO**: Sem olhar a resposta abaixo, incremente a pontuação conforme tamanho do crescimento da cobra quando ela come uma maçã.

```c
unsigned char bonus;
unsigned int score;
```
```c
	// Initialize game variables
	score = 0;
```
```c
				bonus = (rand() & 7) + 1;
				growth += bonus;
				score += bonus;
				Locate(7, 23);
				PrintNumber(score);
```

3. Rode o programa.

4. **DESAFIO**: Sem olhar a resposta abaixo, incremente o recorde sempre que a pontuação for maior que ele.

```c
unsigned int highscore = 0;
```
```c
	Cls();
	print(gameScreen);
	Locate(18, 23);
	PrintNumber(highscore);
```
```c
				bonus = (rand() & 7) + 1;
				growth += bonus;
				score += bonus;
				Locate(7, 23);
				PrintNumber(score);
```

5. Rode o programa.

### 9.5. Finalização da Sessão 9
##### Objetivo: Discutir os tópicos tratados e o modelo/dinâmica do workshop (previsão: 10 minutos).

1. Discussão geral da apresentação:
* O jogo funcional
* Lógica em geral
* LIBs x RELs
* Dinâmica geral do workshop: feedbacks e ideias.

---

**Happy MSX'ing.**
