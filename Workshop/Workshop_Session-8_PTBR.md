# Programando em C e ASM para MSX usando Visual Studio e Fusion-C
# Sessão 8: A construção de um rabo de cobra.

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

# Sessão 8: A construção de um rabo de cobra.

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
			if ((((direction == UP) || (direction == DOWN)) &&
			     ((joy == RIGHT) || (joy == LEFT))) ||
			    (((direction == RIGHT) || (direction == LEFT)) &&
			     ((joy == UP) || (joy == DOWN))))
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
			if ((((lastDirection == UP) || (lastDirection == DOWN)) &&
			     ((joy == RIGHT) || (joy == LEFT))) ||
			    (((lastDirection == RIGHT) || (lastDirection == LEFT)) &&
			     ((joy == UP) || (joy == DOWN))))
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

### 8.4. Modelando o rabo.

##### Objetivo: Discutir o modelo de dados que suportará a implementação da cobra (previsão: 30 minutos).

1. Modelando o rabo da cobra.
- A estrutura de dados;
- O tamanho da estrutura;
- Métodos de acessos.

2. Entendendo o básico de ponteiros/apontadores.
- O que são ponteiros?
- Como usar?
- Ponteiros nulos.
- O operador *.
- O operador &.
- Aritmética de ponteiros.

Referências:
https://www.tutorialspoint.com/cprogramming/c_pointers.htm
https://icarus.cs.weber.edu/~dab/cs1410/textbook/4.Pointers/operators.html

3. Interlúdio: Instalando uma rotina de tratamento de interrupção em C puro usando ponteiros (veja projeto no arquivo *Interrupt_Handler_Pointer.zip*).

### 8.5. Construindo o rabo.
###### *Github Ticket/Branch: 26/TKT0026.*

##### Objetivo: Construir e animar o rabo da cobra (previsão: 40 minutos).

1. Antes de implementar o funcionamento do rabo da cobra, vamos refatorar o nosso motor de movimento e endereçamento da VRAM para torná-lo um pouco mais eficiente e apropriado. Inicialmente, defina quais caracteres usaremos, no momento, como grama, cabeça e rabo da cobra:

```c
#define NAMETABLE	0x1800

#define TILE_GRASS	' '
#define TILE_SNAKETAIL	'o'
#define TILE_SNAKEHEAD	'*'
```

2. Agora, para padronizar a forma de endereçamento, refatore o código para usarmos endereço de VRAM para posição da cabeça da cobra, ao invés de coordenadas X e Y:

```c
--> substitua

unsigned char x, y, direction, lastDirection;

--> por

unsigned int snakeHeadPos;
unsigned char direction, lastDirection;
```
```c
--> substitua

	// Initialize game variables
	x = 10;
	y = 10;

--> por

	// Initialize game variables
	snakeHeadPos = NAMETABLE + 10 * 32 + 11;
```
```c
--> substitua

			// move snake
			switch (direction) {
			case UP:
				y--;
				break;
			case RIGHT:
				x++;
				break;
			case DOWN:
				y++;
				break;
			case LEFT:
				x--;
				break;
			}

--> por

			// move snake
			switch (direction) {
			case UP:
				snakeHeadPos-=32;
				break;
			case RIGHT:
				snakeHeadPos++;
				break;
			case DOWN:
				snakeHeadPos+=32;
				break;
			case LEFT:
				snakeHeadPos--;
				break;
			}
```
```c
--> substitua

			content = Vpeek(NAMETABLE + y * 32 + x);

--> por

			content = Vpeek(snakeHeadPos);
```
```c
--> substitua

			Locate(x, y);
			print("*");

--> por

			// Draws head in new position
			Vpoke (snakeHeadPos, TILE_SNAKEHEAD);

```

3. Rode o programa.

4. Logo abaixo das variávei globais já definidas, crie um vetor/array chamado *snake*, de 512 posições do tipo unsigned int (16 bits). Esse vetor ocupará 1000 bytes de memória. Cada posição desse vetor apontará para um endereço de VRAM onde aquele segmento de rabo está localizado.

```c
unsigned int lastJiffy;

unsigned int snake[512];
```

5. Crie dois ponteiros *snakeHead* e *snakeTail* que serão utilizados, respectivamente, para definir a primeira posição da cobra (cabeça) quanto a última posição da cobra (ponta do rabo).

```c
unsigned int snake[512];
unsigned int *snakeHead, *snakeTail;
```

6. Na função *game()* Inicialize a cobra com tamanho 2: Uma cabeça e um segmento de rabo. Se preocupe tanto com as variáveis quanto com os tiles na VRAM.

```c
	Pokew(BIOS_JIFFY, 0);

	// initialize snake
	snakeTail = snake;	// snakeTail will point to first element of snake.
	snakeHead = snake + 1;	// snakeHead will point to second element of snake, two bytes ahead of snakeTail.
	snake[0] = snakeHeadPos - 1;
	snake[1] = snakeHeadPos;
	Vpoke(snakeHeadPos - 1, TILE_SNAKETAIL);
	Vpoke(snakeHeadPos, TILE_SNAKEHEAD);
```

7. Imediatamente antes de desenhar a cabeça da cobra, apague a última posição do rabo, e incremente o ponteiro *snakeTail*:
```c
			// Erases last tail segment
			Vpoke(*snakeTail, TILE_GRASS);
			snakeTail++;
			if (snakeTail > &snake[511]) snakeTail = snake;

			// Draws head in new position
```

8. Logo após, substitua a cabeça por um segmento de rabo:
```c
			if (snakeTail > &snake[511]) snakeTail = snake;

			// Replaces head with tail segment
			Vpoke(*snakeHead, TILE_SNAKETAIL);

			// Draws head in new position
```

9. Logo após, incremente o ponteiro *snakeHead* e salve a nova posição da cabeça:
```c
			// Draws head in new position
			Vpoke (snakeHeadPos, TILE_SNAKEHEAD);
			snakeHead++;
			if (snakeHead > &snake[511]) snakeHead = snake;
			*snakeHead = snakeHeadPos;
```

10. Rode o programa.

### 8.6. Finalização da Sessão 8
##### Objetivo: Discutir os tópicos tratados e o modelo/dinâmica do workshop (previsão: 10 minutos).

1. Discussão geral da apresentação:
* PONTEIROS!
* Lógica em geral
* Dinâmica geral do workshop: feedbacks e ideias.

---

**Happy MSX'ing.**
