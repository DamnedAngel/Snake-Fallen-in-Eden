# Programando em C e ASM para MSX usando Visual Studio e Fusion-C
# Sessão 8: A cauda da cobra.

Escrito por **Danilo Angelo (a.k.a. Damned Angel)**, 2020-2021

Vídeo da sessão 8: XXX

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

# Sessão 8: A cauda da cobra.

### 8.1. Evitando curvas de 180 graus.
###### *Github Ticket/Branch: 23/TKT0023.*

##### Objetivo: Evitar que a cobra se mate voltando por cima de ela mesma (previsão: 30 minutos).

1. Discussão: O que precisaríamos fazer para evitar que a cobra volte por cima de ela mesma?

2. **DESAFIO**: Com base na discussão do item anterior, e sem olhar a resposta abaixo, use a combinação de comandos *if* (ou do comando *switch/case* com comandos *if*) para evitar curvas de 180 graus:

```c
			// Alternative 1: IFs inside SWITCH/CASE
			joy = JoystickRead(0);
			switch (direction) {
			case UP:
				if ((joy == LEFT) || (joy == RIGHT)) direction = joy;
				break;
			case RIGHT:
				if ((joy == UP) || (joy == DOWN)) direction = joy;
				break;
			case DOWN:
				if ((joy == LEFT) || (joy == RIGHT)) direction = joy;
				break;
			case LEFT:
				if ((joy == UP) || (joy == DOWN)) direction = joy;
				break;
			}
```

```c
			// Alternative 2: Composition of Conditions in a single IF
			if ((((direction == UP) || (direction == DOWN)) && ((joy == RIGHT) || (joy == LEFT))) ||
				(((direction == RIGHT) || (direction == LEFT)) && ((joy == UP) || (joy == DOWN))))
				direction = joy;
```

3. Compile e rode o programa.

4. Discussão: O problema foi resolvido? Você consegue imaginar uma forma de ainda causar curvas de 180 graus?

5. **DESAFIO**: Com base na discussão do item anterior, e sem olhar a resposta abaixo, implemente a solução para o ainda possível caso de curvas de 180 graus:

```c
unsigned char x, y, direction, lastDirection;
```
```c
	// Initialize game variables
	x = 10;
	y = 10;
	direction = RIGHT;
	lastDirection = 0;	// initially, none
```
```c
			Locate(x, y);
			print("*");

			lastDirection = direction;  // saves last direction after moving
			Pokew(BIOS_JIFFY, 0);
```
```c
			// Alternative 1: IFs inside SWITCH/CASE
			switch (lastDirection) {
```
```c
			// Alternative 2: Composition of Conditions in a single IF
			if ((((lastDirection == UP) || (lastDirection == DOWN)) && ((joy == RIGHT) || (joy == LEFT))) ||
				(((lastDirection == RIGHT) || (lastDirection == LEFT)) && ((joy == UP) || (joy == DOWN))))
				direction = joy;
```

6. Compile e rode o programa.

### 8.2. Desligando o "key click".
###### *Github Ticket/Branch: 24/TKT0024.*

##### Objetivo: Desligar o key click padrão do MSX, melhorando a experiência do jogo (previsão: 5 minutos).

1. **DESAFIO**: Sem olhar a resposta abaixo, descubra qual a função da Fusion-C que liga e desliga o "key click", e o desligue!

```c
void main(void) {
	KeySound(0);
	Screen(1);
	Width(32);
```

2. Compile e rode o programa.

### 8.6. Finalização da Sessão 8
##### Objetivo: Discutir os tópicos tratados e o modelo/dinâmica do workshop (previsão: 10 minutos).

1. Discussão geral da apresentação:
* Novas funções da Fusion-C
* Lógica em geral
* Experiência do jogador
* Dinâmica geral do workshop: feedbacks e ideias.

---

**Happy MSX'ing.**
