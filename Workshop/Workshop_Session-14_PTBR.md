# Programando em C e ASM para MSX usando Visual Studio e Fusion-C
# Sessão 14: Animação e Sons.

Escrito por **Danilo Angelo (a.k.a. Damned Angel)**, 2020-2021

Vídeo da sessão 14: XXX

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

# Sessão 14: Animação e Sons.

### 14.1. Animando a explosão da cabeça da cobra.
###### *Github Ticket/Branch: 55/TKT0055.*

##### Objetivo: Ilustrar a explosão da cabeça, reforçando a colisão (previsão: 30 minutos).

1. Crie a variável booleana *collision* para guardar o estado de colisão a variável *collisionFrame*, para armazenar o frame da animação. Inicialize as duas na função *game()*:
```c
bool EoG;
bool collision;

unsigned char collisionFrame;
```
```c
	// Initialize game variables
	EoG = false;
	collision = false;
	collisionFrame = TILE_HEADXPLOD;
```

2. Refactoring: Teste a colisão imediatamente depois da atribuição à variável content:
```c
		EoG = (content != TILE_GRASS_EMPTY) && (content != TILE_APPLE);
		if (EoG) {
			// Collision start
		}

		if (content == TILE_APPLE) {
			//...
		}
```

3. Substitua a variável *EoG* pela *collision* na detecção de colisão:
```c
		collision = (content != TILE_GRASS_EMPTY) && (content != TILE_APPLE);
		if (collision) {
			// Collision start
```

4. Refactoring: Mova os blocos de comer a maçã e do desenho da cabeça da cobra para o *else* do *if* da colisão (pois não queremos executá-los quando a cobra colidir). Mantenha as demais atualizações fora do *else* (ainda queremos executá-las no momento que a cobra colidir):
```c
		if (collision) {
			// Collision start
		} else {
			if (content == TILE_APPLE) {
			// ...
			}

			// Draws head in new position
			Vpoke(snakeHeadPos,
				TILE_SNAKEHEAD + (direction - 1) / 2);
		}

		// Erases last tail segment
		// ...

		// Replaces head with tail segment
		Vpoke(*snakeHead, TILE_SNAKETAIL);

		// update buffer
		snakeHead++;
		if (snakeHead > &snake[511]) snakeHead = snake;
		*snakeHead = snakeHeadPos;
```

5. Evite o movimento da cobra quando o jogo entra no estado de colisão, adicionando uma condição na entrada do bloco de movimento:
```c
		// from this point on, 1 pass per frame
		if ((Peekw(BIOS_JIFFY) >= waitFrames) && (! collision)) {
```

6. Mova o código de ajuste da cor de fundo da explosão e desenho do tile da explosão do fim da função *game()* para junto da detecção de colisão. Tenha certeza da usar o primeiro tile da sequência de explosão:
```c
		if (collision) {
			// Collision start
			if (content < TILE_VINE) {
				Vpoke(COLORTABLE + 0x12,
					(tileColors_game[TILE_HEADXPLOD / 8] & 0xf0) |
					(tileColors_game[TILE_GRASS / 8] & 0x0f));
			}
			Vpoke(snakeHeadPos, TILE_HEADXPLOD);
			Beep();
		} else {
```

7. Monte a rotina de animação, trocando o tile a cada 6 frames. No último frame, atribua *true* à *EoG*:
```c
		// here we will add animations and sound effects routine 
		{
			// Process collision
			if (collision && (Peekw(BIOS_JIFFY) >= 6)) {
				Vpoke(snakeHeadPos, ++collisionFrame);
				EoG = (collisionFrame == TILE_HEADXPLOD + 7);
				Pokew(BIOS_JIFFY, 0);
			}
		}
```

8. Compile e execute o projeto. Teste a colisão com a vinha e com o rabo da cobra.

### 12.2. A vinha.
###### *Github Ticket/Branch: 50/TKT0050.*

##### Objetivo: Implementar o desenho das vinhas (previsão: 15 minutos).

1. Identifique o código hexadecimal de cada um dos 6 tiles da vinha.

2. **DESAFIO**: Usando os códigos dos tiles da vinha identificado no item anterior, substitua as bordas do jardim nas constantes *titleScreen*, *gameScreen* e *gameOverMsg*.

```c
static const char titleScreen[] = \
"\xa2\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1 ... \xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa4"\
"\xa0\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1 ... \xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa0"\
"\xa0\xaf\xaf Damned Angel's \xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xa0"\
	(... 18 linhas ...)
"\xa0\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1 ... \xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa0"\
"\xa3\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1 ... \xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa5"\
" Score 0     High 0     Eden 1 \0";
```
```c
static const char gameScreen[] = \
"\xa2\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1 ... \xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa4"\
"\xa0\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1 ... \xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa0"\
	(... 19 linhas ...)
"\xa0\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1 ... \xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa0"\
"\xa3\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1 ... \xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa5"\
" Score 0     High 0     Eden 1 \0";
```
```c
static const char gameOverMsg[] = \
"\xa0                              \xa0"\
"\xa0          Game  Over          \xa0"\
"\xa0                              \xa0\0";
```

3. Compile e rode o programa.


### 12.3. Cores.
###### *Github Ticket/Branch: 51/TKT0051.*

##### Objetivo: Colorir o jogo (previsão: 20 minutos)!

1. Relembrando da tabela de cores do VDP em modo Screen 1.

2. Relembrando as cores dos tiles na implementação de referência: 
![Mapa de Caracteres da Implementação de referência](Workshop_Session-11_PTBR_img1.png "Mapa de Caracteres da Implementação de referência")

3. Crie a constante COLORTABLE:

```c
#define NAMETABLE			0x1800
#define PATTERNTABLE			0x0000
#define COLORTABLE			0X2000
```

4. **DESAFIO**: Sem olhar a resposta abaixo, crie, no arquivo tiles.h, o array de constantes *tileColors* com o mapa de cores. Use nossa rotina blockToVRAM para transferir os dados para a tabela de cores na VRAM.

```c
static const char tileColors[] = {
	0xc3,			// 0x00 - Graphic Symbols **Unused**
	0xc3,			// 0x08 - Graphic Symbols **Unused**
	0xc3,			// 0x10 - Graphic Symbols **Unused**
	0xc3,			// 0x18 - Graphic Symbols **Unused**
	0xc3,			// 0x20 - Symbols
	0xc3,			// 0x28 - Symbols
	0xc3,			// 0x30 - Numbers
	0xc3,			// 0x38 - Numbers, Symbols
	0xc3,			// 0x40 - Uppercase
	0xc3,			// 0x48 - Uppercase
	0xc3,			// 0x50 - Uppercase
	0xc3,			// 0x58 - Uppercase, Symbols
	0xc3,			// 0x60 - Lowercase
	0xc3,			// 0x68 - Lowercase
	0xc3,			// 0x70 - Lowercase
	0xc3,			// 0x78 - Lowercase, Symbols
	0xc3,			// 0x80 - Snake Head
	0x23,			// 0x88 - Snake Body
	0x80,			// 0x90 - Exploded snake head
	0x83,			// 0x98 - Apple
	0xc1,			// 0xa0 - Vine
	0x23,			// 0xa8 - Grass
	0xb3,			// 0xb0 - Grass
	0x00,			// 0xb8 - Graphic Symbols **Unused**
	0x43,			// 0xc0 - Mini Snake
	0x43,			// 0xc8 - Mini Snake
	0x43,			// 0xd0 - Mini Snake
	0x43,			// 0xd8 - Mini Snake
	0x43,			// 0xe0 - Mini Snake
	0x43,			// 0xe8 - Mini Snake
	0x43,			// 0xf0 - Mini Snake
	0x43,			// 0xf8 - Mini Snake
};
```

5. Compile e rode o programa.

### 12.4. Variação de Cores: Placar com fundo preto.
###### *Github Ticket/Branch: 52/TKT0052.*

##### Objetivo: Alterar as cores do placar (previsão: 10 minutos).

1. Refactoring: Renomeie a constante *tileColors* para *tileColors_title*.

```c
static const char tileColors_title[] = {
```

2. Refactoring: Mova a configuração de cores da função *buildTitles* para a o início da função *title*, ajustando o nome da constante:

```c
void title() {
	// Set colors
	blockToVRAM(COLORTABLE, tileColors_title, sizeof(tileColors_title));
```

3. Refactoring: Também faça a configuração de cores imediatamente antes de chamar a rotina de exibição de mapas de caracteres, na função *main*:

```c
#ifdef DEBUG
	blockToVRAM(COLORTABLE, tileColors_title, sizeof(tileColors_title));
	charMap();
	while (!(allJoysticks() || allTriggers())) {}	// waits until key press
#endif
```

4. **DESAFIO**: Crie uma cópia da constante *tileColors_title*, chamada *tileColors_game*, e defina novas cores para os grupos de padrões dos dígitos e alfabeto. Execute a configuração com base nessa constante no início da função *game*;

```c
static const char tileColors_game[] = {
	0xc3,			// 0x00 - Graphic Symbols **Unused**
	0xc3,			// 0x08 - Graphic Symbols **Unused**
	0xc3,			// 0x10 - Graphic Symbols **Unused**
	0xc3,			// 0x18 - Graphic Symbols **Unused**
	0xa1,			// 0x20 - Symbols
	0xa1,			// 0x28 - Symbols
	0xa1,			// 0x30 - Numbers
	0xa1,			// 0x38 - Numbers, Symbols
	0xa1,			// 0x40 - Uppercase
	0xa1,			// 0x48 - Uppercase
	0xa1,			// 0x50 - Uppercase
	0xa1,			// 0x58 - Uppercase, Symbols
	0xa1,			// 0x60 - Lowercase
	0xa1,			// 0x68 - Lowercase
	0xa1,			// 0x70 - Lowercase
	0xa1,			// 0x78 - Lowercase, Symbols
	0xc3,			// 0x80 - Snake Head
	0x23,			// 0x88 - Snake Body
	0x80,			// 0x90 - Exploded snake head
	0x83,			// 0x98 - Apple
	0xc1,			// 0xa0 - Vine
	0x23,			// 0xa8 - Grass
	0xb3,			// 0xb0 - Grass
	0x00,			// 0xb8 - Graphic Symbols **Unused**
	0x43,			// 0xc0 - Mini Snake
	0x43,			// 0xc8 - Mini Snake
	0x43,			// 0xd0 - Mini Snake
	0x43,			// 0xd8 - Mini Snake
	0x43,			// 0xe0 - Mini Snake
	0x43,			// 0xe8 - Mini Snake
	0x43,			// 0xf0 - Mini Snake
	0x43,			// 0xf8 - Mini Snake
};
```
```c
void game() {
	// Set colors
	blockToVRAM(COLORTABLE, tileColors_game, sizeof(tileColors_game));
```

5. Compile e rode o programa.

### 12.5. Ajuste da cor de fundo na explosão da cabeça, quando da colisão com o próprio rabo.
###### *Github Ticket/Branch: 53/TKT0053.*

##### Objetivo: Cor da fundo da explosão ficar adequada ao terreno (previsão: 5 minutos).

1. **DESAFIO**: Sem olhar a resposta abaixo, altere as cores do fundo dos tiles da explosão da cabeça para a cor de fundo do jardim.

```c
	if (content < TILE_VINE) {
		Vpoke(COLORTABLE + 0x12, (tileColors_game[TILE_HEADXPLOD/8] & 0xf0) | (tileColors_game[TILE_GRASS/8] & 0x0f));
	}
	Vpoke(snakeHeadPos, TILE_HEADXPLOD + 3);
```

2. Compile e rode o programa.

### 12.6. Finalização da Sessão 12
##### Objetivo: Discutir os tópicos tratados e o modelo/dinâmica do workshop (previsão: 10 minutos).

1. Discussão geral da apresentação:
* Comentários sobre o estado corrente do jogo
* VDP / Tabela de cores
* Dinâmica geral do workshop: feedbacks e ideias.

---

**Happy MSX'ing.**
