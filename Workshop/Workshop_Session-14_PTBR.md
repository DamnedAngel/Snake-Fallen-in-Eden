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

1. Crie a variável booleana *collision* para guardar o estado de colisão e a variável *collisionFrame*, para armazenar o frame da animação. Inicialize as duas na função *game()*:
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
			// Collision animation
			if (collision && (Peekw(BIOS_JIFFY) >= 6)) {
				Vpoke(snakeHeadPos, ++collisionFrame);
				EoG = (collisionFrame == TILE_HEADXPLOD + 7);
				Pokew(BIOS_JIFFY, 0);
			}
		}
```

8. Compile e execute o projeto. Teste a colisão com a vinha e com o rabo da cobra.

### 14.2. Efeito visual na mudança de éden.
###### *Github Ticket/Branch: 41/TKT0041.*

##### Objetivo: Promover identificação visual a cada éden e a cada mudança de éden (previsão: 20 minutos).

1. Regras para identificação visual de édens e transições.
- Em cada éden o rabo da cobra terá cor diferente dos édens anteriores, usando ordenadamente as cores do MSX1, até essas se esgotarem. Nesse ponto, o ciclo recomeçará.  
- Algumas cores não deverão ser utilizadas, para evitar baixo contraste com outros elementos do jogo, e pra evitar contraste excessivo, a saber:
	- 0: cor da borda (preto, contraste excessivo);
    - 1: preto (contraste excessivo);
    - 3: verde claro (grama);
    - 8: vermelho (maçã);
    - 11: amarelo (baixo contraste com a grama);
    - 15: branco (contraste excessivo).
- Na mudança de eden, o rabo cobra piscará por um segundo, tendo, nos frames pares, a próxima cor que assumirá e nos frames ímpares uma cor aleatória enrte 0 e 15.

2. **DESAFIO**: Crie, no arquivo *tiles.h*, um array de cores possíveis para a cobra assumir chamado *tailColors*, excluindo as cores inválidas estabelecidas no item 1 acima.

```c
static const char tailColors[] = {
	0x23,
	0x43,
	0x53,
	0x63,
	0x73,
	0x93,
	0xa3,
	0xc3,
	0xd3,
	0xe3,
};
```

3. Crie a variável booleana *edenUp* para guardar o estado de mudança de éden e a variável *edenUpFrame*, para armazenar o frame da mudança. Inicialize *edenUp* na função *game()*:
```c
bool edenUp;

unsigned char edenUpFrame;
```
```c
	// Initialize game variables
	edenUp = false;
```

4. No evento de mudança de éden, ligue a flag edenUp e inicialize a contagem de frames:
```c
			if (!(--waitMoves)) {
				// Next Eden
				edenUp = true;
				edenUpFrame = 0;
```

5. Discussão: O que podemos usar como índice do vetor de cores?

6. **DESAFIO**: Monte a rotina do efeito, trocando o cor a cada frame, conforme as regras do item 1 acima. No último frame, atribua *false* à *edenUp*:
```c
	// here we will add animations and sound effects routine 
	{
		// Eden Up effect
		if (edenUp) {
			if (++edenUpFrame & 1) {
				// random color
				Vpoke(COLORTABLE + TILE_SNAKETAIL / 8,
					(rand() & 0xf0) + 3);
			} else {
				// next color
				Vpoke(COLORTABLE + TILE_SNAKETAIL / 8,
					tailColors[((eden - 1) % sizeof(tailColors))]);
			}
			edenUp = edenUpFrame < 60;
		}
```


### 14.3. O som do arrastar da cobra.
###### *Github Ticket/Branch: 56/TKT0056.*

##### Objetivo: Fornecer informação sonora do movimento da cobra (previsão: 20 minutos).

1. Lembrando os registros do PSG:
http://www.msxtop.msxall.com/Docs/MSXTopSecret2Continuo.pdf


2. Definindo a estratégia de sons do jogo.
- PSG A: Movimento da cobra, envoltória 4.
- PSG B: comer maçã, volume controlado pelo jogo.
- PSG C: Level up, volume controlado pelo jogo.
- PSG A, B e C: Explosão, envoltória 0.

3. Crie o arquivo *sounds.h* e nele crie o vetor constante de inicialização do PSG *gameSound* para o jogo:
```c
#pragma once

static const char gameSound[] = {
	0,	0,		// Channel A Freq	none; movement
	255,	0,		// Channel B Freq	eat apple
	40,	0,		// Channel C Freq	level up
	31,			// Noise Freq		(Movement noise)
	49,			// Mixing		A: noise, B: tone, C: Tone
	16,	0,	0,	// Channels volume
	100,	4,		// Envelope freq
};
```

4. Inclua o header *sounds.h* no nosso programa principal:
```c
#include "sounds.h"
```

5. Inicialize o PSG na função *game()*:
```c
	// initialize sound
	for (unsigned char i = 0; i < sizeof(gameSound); i++) {
		PSGwrite(i, gameSound[i]);
	}
```

6. No final da movimentação da cobra, reconfigure a envoltória, disparando um novo efeito sonoro:

```c
			PSGwrite(13, 4);
```

7. Compile e rode o programa.

### 14.4. O som de comer maçãs.
###### *Github Ticket/Branch: 57/TKT0057.*

##### Objetivo: Fornecer informação sonora do evento de comer maçã (previsão: 10 minutos).

1. Crie a variável booleana *appleEaten* e a variável *appleEatenFrame*, para contar os frames do som. Inicialize *appleEaten* na função *game()*:
```c
bool appleEaten;

unsigned char appleEatenFrame;
```
```c
	// Initialize game variables
	appleEaten = false;
```

2. No evento de comer a maçã, ligue a flag appleEaten e inicialize a contagem de frames:
```c
				if (content == TILE_APPLE) {
					dropApple();

					appleEaten = true;
					appleEatenFrame = 16;
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
