# Programando em C e ASM para MSX usando Visual Studio e Fusion-C
# Sessão 16a: Sprites!

Escrito por **Danilo Angelo (a.k.a. Damned Angel)**, 2020-2021

Vídeo da sessão 16a: https://youtu.be/czx3ol2ecs0

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
* Um passo com o verbo no gerúndio (ex: *Compilando o projeto.*) significa uma exposição do palestrante (assista o vídeo no YouTube com a exposição em https://youtu.be/czx3ol2ecs0)
* Um passo com o verbo no imperativo (ex: *Configure a aplicação*) denota um passo para ser executado pelo participante.
* Um passo com a descrição de uma atividade (ex: *Discussão em grupo.*) descreve a proposta de uma dinâmica.

Adicionalmente, note que os trechos de código fornecidos como exemplo muitas vezes contém um trecho já existente do programa, para referência de localização.

---

# Sessão 16a: Sprites!

### 16a.1. Mostrar bônus por comer maçãs.
###### *Github Ticket/Branch: 61/TKT0061.*

##### Objetivo: Mostrar bônus por comer maçãs e detectar o primeiro bug no tratamento de sprites pela Fusion-C (previsão: 90 minutos).

1. A Fusion-C tem muitos problemas com sprites no MSX1. Configurem, inicialmente, o emulador para trabalhar com o Turbo-R (Panasonic FS-A1GT). Depois resolveremos os problemas para que tudo funcione no MSX1.

2. Entendendo o sistema de sprites do VDP do MSX1:
- Suporte para 32 sprites;
- Dois tamanhos de sprite:
  - Tamanho 0: 8x8 pixels; 8 bytes;
  - Tamanho 1: 16x16 pixels; 32 bytes.
- **Tabela de padrões de sprites:**
  - 2048 bytes;
  - 256 padrões 8x8 ou 64 padrões 16x16.
- **Tabela de atributos de sprites:**
  - 32 entradas x 4 bytes = 128 bytes:
    - Byte 0: Coordenada X;
    - Byte 1: Coordenada Y;
    - Byte 2: Nome do sprite (referência ao padrão);
    - Byte 3: Cor + Early clock.

3. Faça download do arquivo *sprites.h* na pasta com o código fonte do seu projeto. Inspecione o arquivo para descobrir seu conteúdo.

4. Se você usa Visual Studio, adicione-o arquivo ao projeto, sob o filtro *Header Files*.

5. Referencie o arquivo *sprites.h* no arquivo principal do nosso programa *msxromapp.c*.
```c
#include "sprites.h"
```

6. Compile o projeto para garantir que o arquivo *sprites.h* está ok. Corrija qualquer problema de sintaxe que existir, se existir.

7. **DESAFIO**: Crie diretivas constantes para referência às tabelas de padrões e atributos de sprites do VDP, de forma similar às de referência às tabelas de nomes, padrões e cores.
```c
#define NAMETABLE				0x1800
#define PATTERNTABLE			0x0000
#define COLORTABLE				0x2000
#define SPRITEPATTERNTABLE		0x3800
#define SPRITEATTRIBUTETABLE	0x1b00
```

8. Definindo o comportamento do indicador de bônus por comer a maçã:
- O bônus por comer a maçã deverá aparecer por 90 frames (1,5 segundos);
- O valor deve aparer levemente acima da posição da maçã comida;
- Durante os 90 frames, o número deverá se mover 1 pixel para cima a cada 4 frames.

9. Refactoring: por claridade do código, altere o código para *appleEatenFrame* iniciar em 0 e contar até 90 (1,5 segundos). Lembre de limitar o controle do volume do PSG apenas até o frame 15.
```c
				if (content == TILE_APPLE) {
					dropApple();

					appleEaten = true;
					appleEatenFrame = 0;
```
```c
			// Apple eaten effect
			if (appleEaten) {
				if (appleEatenFrame < 16) 
					PSGwrite(9, 15 - appleEatenFrame);
				appleEaten = ++appleEatenFrame < 90;
			}
```

10. Compile e rode o programa, garantindo que o jogo continua com comportamento igual ao anterior.

11. Abra o arquivo da Fusion-C *vdp_sprites.h*. Inspecione seu conteúdo.

12. **DESAFIO**: Sem olhar o código abaixo e com base em tudo o que você aprendeu nos itens acima, crie a função *buildSprites()* para configurar a tabela de padrão de sprites.
```c
void buildSprites() {
	SpriteOn();
	SpriteReset();
	Sprite8();
	SpriteSmall();

	// Alternative 1: Fusion-C / BASIC Style
	for (unsigned char i = 0; i < sizeof(sprite_patterns)/8; i++) {
		SetSpritePattern(i, sprite_patterns + (i * 8), 8);
	}
}
```
```c
	buildFont();
	buildTiles();
	buildSprites();
```

13. **DESAFIO**: Mostre o bônus quando uma maçã é comida, fazendo a animação conforme definido no item 7 acima.
```c
unsigned char appleEatenFrame;
unsigned char appleEatenBonusX;
unsigned char appleEatenBonusY;
``` 
```c
	appleEaten = true;
	appleEatenFrame = 0;
	appleEatenBonusX = 8 * (snakeHeadPos % 32);
	appleEatenBonusY = 8 * (snakeHeadPos / 32) - 4;
``` 
```c
	// Apple eaten effect
	if (appleEaten) {
		if (appleEatenFrame < 16) 
			PSGwrite(9, 15 - appleEatenFrame);
		if (!(appleEatenFrame & 3)) {
			PutSprite(0, bonus, appleEatenBonusX, appleEatenBonusY--, 4);
		}
		if(!(appleEaten = ++appleEatenFrame < 90)) {
			PutSprite(0, 0, 0, 255, 0);
			appleEatenBonusX = 0;
			appleEatenBonusY = 255;	
		}
	}
``` 

14. Compile e execute (no Turbo-R!!!) o jogo para ver o efeito.

15. Agora execute o jogo em um MSX 1. O que houve? Diagnosticaremos e trataremos esse problema mais para frente!

16. **DESAFIO**: Adicione o sprite do Bevel por baixo do sprite do bonus. Utilize os defines/constantes de cores nos *PutSprite()*.
```c
	// Apple eaten effect
	if (appleEaten) {
		if (appleEatenFrame < 16) 
			PSGwrite(9, 15 - appleEatenFrame);
		if (!(appleEatenFrame & 3)) {
			PutSprite(0, bonus, appleEatenBonusX, --appleEatenBonusY, BONUS_COLOR);
			PutSprite(1, 9, appleEatenBonusX, appleEatenBonusY, BONUSBEVEL_COLOR);
		}
		if(!(appleEaten = ++appleEatenFrame < 90)) {
			PutSprite(0, 0, 0, 192, 0);
			PutSprite(1, 0, 0, 192, 0);
		}
	}
``` 

17. Compile e execute (no Turbo-R!!!) o jogo para ver o efeito. Teste cores diferentes.

18. Discussão: você consegue encontrar um pequeno problema na implementação?

19. **DESAFIO**: Corrija o problema identificado.
```c
		<mova a collision animation para antes do efeito de comer maçã>
``` 
```c
		if(!(appleEaten = (++appleEatenFrame < 90) && (!EoG))) {
``` 

20. Compile e execute (no Turbo-R!!!) o jogo para ver o efeito.

21. Compile e execute o jogo no Hotbit. O que houve? Você Reconhece os desenhos?

22. Explorando o problema de escrita no registro 14 do VDP.
- Endereçamento da VRAM.
- Implementação do Vpeek + VpeekFirst + VDPwriteNi.
- Consequência no VDP do MSX1.

23. Corrija o problema encontrado, consertando o endereço da tabela de padrões de sprite:
```c
void buildSprites() {
	VDPwriteNi(6, SPRITEPATTERNTABLE >> 11);
```
```c
		lastJiffy = Peekw(BIOS_JIFFY);
		VDPwriteNi(6, SPRITEPATTERNTABLE >> 11);
	}
```

24. Compile e execute o jogo em no Hotbit. Discuta os resultados. Aconteceu algum problema? Consertaremos o problema na sessão 16b.


### 16a.2. Finalização da Sessão 16a
##### Objetivo: Discutir os tópicos tratados e o modelo/dinâmica do workshop (previsão: 10 minutos).

1. Discussão geral da apresentação:
* Sprites
* Estado do jogo
* Bugs da Fusion-C
* Dinâmica geral do workshop: feedbacks e ideias.

---
