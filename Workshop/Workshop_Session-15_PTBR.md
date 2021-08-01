# Programando em C e ASM para MSX usando Visual Studio e Fusion-C
# Sessão 15: Efeitos sonoros.

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

# Sessão 15: Efeitos sonoros.

### 15.1. O som do arrastar da cobra.
###### *Github Ticket/Branch: 56/TKT0056.*

##### Objetivo: Fornecer informação sonora do movimento da cobra (previsão: 20 minutos).

1. Lembrando os registros do PSG:
http://www.msxtop.msxall.com/Docs/MSXTopSecret2Continuo.pdf


2. Definindo a estratégia de sons do jogo.
- PSG A: Movimento da cobra, ruído, envoltória 4.
- PSG B: comer maçã, tom, volume controlado pelo jogo.
- PSG C: Level up, tom, volume controlado pelo jogo.
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

6. Após desenhar a cabeçca da cobra, econfigure a envoltória, disparando um novo efeito sonoro:
```c
			// Draws head in new position
			Vpoke(snakeHeadPos, TILE_SNAKEHEAD + (direction - 1) / 2);
			PSGwrite(13, 4);
```

7. Compile e rode o programa.

### 15.2. O som de comer maçãs.
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

3. **DESAFIO**: Sem olhar o código abaixo, monte a rotina do efeito, diminuindo o volume do canal a cada frame:

```c
		// here we will add animations and sound effects routine 
		{
			// Apple eaten effect
			if (appleEaten) {
				PSGwrite(9, 15 - appleEatenFrame);
				appleEaten = ++appleEatenFrame < 16;
			}
```

4. Compile e rode o programa.

### 15.3. O som da progressão de édens.
###### *Github Ticket/Branch: 58/TKT0058.*

##### Objetivo: Fornecer informação sonora do evento de mudança de éden (previsão: 10 minutos).

1. Definindo regras do efeito sonoro de transição de éden.
- Na mudança de eden, um efeito sonoro de um segundo sera emitido, alternando tons entre frames pares e frames ímpares:
	- No frame ímpar, um valor aleatório entre 0 e 255 será colocado no registro 4 do PSG.
	- No frame par, um valor decrescente de 60 a 30 será colocado no registro 4 do PSG.

2. Crie a variável *edenUpSound* para armazenar o valor a ser colocado no rigistro 4 do PSG:
```c
unsigned char edenUpSound;
```

3. No evento de mudança de nível, inicialize a variável *edenUpSound*, e ajuste o volume do canal C para o máximo:
```c
			// Controls eden progression
			if (!(--waitMoves)) {
				// Next Eden
				edenUp = true;
				edenUpFrame = 0;
				edenUpSound = 60;
				PSGwrite(10, 15);
```

3. **DESAFIO**: Sem olhar o código abaixo, altere a rotina do efeito de progressão de éden, produzindo os tons conforme regras definidas no item 1 acima:

```c
		// Eden Up effect
		if (edenUp) {
			if (++edenUpFrame & 1) {
				// random color & sound
				PSGwrite(4, rand());
				Vpoke(COLORTABLE + TILE_SNAKETAIL / 8,
					(rand() & 0xf0) + 3);
			} else {
				// next color & effect up sound
				PSGwrite(4, edenUpSound--);
				Vpoke(COLORTABLE + TILE_SNAKETAIL / 8
					tailColors[((eden - 1) % sizeof(tailColors))]);
			}
			if (!(edenUp = edenUpFrame < 60)) {
				PSGwrite(10, 0);
			};
		}
```

4. Compile e rode o programa.

5. Experimente os efeitos sonoros habilitanto apenas os ajustes dos registros em frames pares e ímpares isoladamente.

### 15.4. O som da explosão da cabeça da cobra.
###### *Github Ticket/Branch: 34/TKT0034.*

##### Objetivo: Fornecer informação sonora da colisão da cobra.

1. insira no arquivo *sounds.h* o vetor constante *xplodSound* com configuração do PSG para som da explosão da cabeça da cobra:
```c
static const char xplodSound[] = {
	255,	31,				// Channel A Freq		
	100,	20,				// Channel B Freq		
	255,	1,				// Channel C Freq		
	31,					// Noise Freq			
	128,					// Mixing				
	16,	16,	16,			// Channels volume
	10,	20,				// Envelope freq
	0					// Envelope
};
```

2. **DESAFIO**: Sem olhar o código abaixo, insira bloco de código para executar o som de explosão da cabeça:
```c
			for (unsigned char i = 0; i < sizeof(xplodSound); i++) {
				PSGwrite(i, xplodSound[i]);
			}
```

3. Compile e rode o programa.

### 15.5. Finalização da Sessão 14
##### Objetivo: Discutir os tópicos tratados e o modelo/dinâmica do workshop (previsão: 10 minutos).

1. Discussão geral da apresentação:
* Animação
* Sons
* Estado do jogo
* Dinâmica geral do workshop: feedbacks e ideias.

---

**Happy MSX'ing.**
