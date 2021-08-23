# Programando em C e ASM para MSX usando Visual Studio e Fusion-C
# Sessão 12: Gráficos, parte 2!

Escrito por **Danilo Angelo (a.k.a. Damned Angel)**, 2020-2021

Vídeo da sessão 12: XXX

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

# Sessão 12: Gráficos, parte 2!

### 12.1. Consertando o intervalo de código de caracteres usados para os tiles da grama.
###### *Github Ticket/Branch: 49/TKT0049.*

##### Objetivo: Retornar ao plano de mapa de caracteres original (previsão: 30 minutos).

1. Relembrando os problemas do caracter de grama, que travava o jogo na geração da maçã, e a solução temporária adotada.

2. Compile o projeto em modo DEBUG, execute o jogo e observe a posição atual dos tiles de grama no mapa de caracteres, cobrindo os caracteres de espaço, ponto de exclamação e outros.

3. Retorne o código para condição original (com a trava), ajustando o código da constante *TILE_GRASS*:

4. Compile o projeto em modo DEBUG, execute o jogo e observe a nova posição dos tiles de grama no mapa de caracteres, liberando os caracteres de espaço, ponto de exclamação e outros.

```c
#define TILE_GRASS					0xa8
```

5. Crie a constante TILE_GRASS_EMPTY referenciando o último dos 8 tiles de grama.

```c
#define TILE_GRASS_EMPTY				0xaf
```

6. Substitua todos os espaços do jardim nas constantes *titleScreen* e *gameScreen* (arquivo screens.h) pelo código 0xaf. Na *titleScreen*, para evitar a junção da constante hexadecimal *0xaf* com textos que podem iniciar com uma sequência válida de dígitos hexadecimais (**\xafDa**mned Angel, por exemplo), mantenha um espaço comum separando as palavras da grama:*\xaf Damned Angel's \xaf*:

```c
static const char titleScreen[] = \
"+------------------------------+"\
"|\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1 ... \xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1|"\
"|\xaf\xaf Damned Angel's \xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf\xaf|"\
	(... 18 linhas ...)
"|\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1 ... \xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1|"\
"+------------------------------+"\
" Score 0     High 0     Eden 1 \0";
```
```c
static const char gameScreen[] = \
"+------------------------------+"\
"|\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1 ... \xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1|"\
	(... 19 linhas ...)
"|\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1 ... \xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1\xa1|"\
"+------------------------------+"\
" Score 0     High 0     Eden 1 \0";
```

7. Compile, rode o programa e note o que houve com as telas do jogo. O que acontece com a jogo? E o que está acontecendo com a cabeça da cobra? Por que não notamos o problema com a cabeça da cobra antes?

8. **DESAFIO**: Sem olhar na resposta abaixo, corrija o tile da cabeça da cobra:

```c
	// initialize snake

	// ...

	Vpoke(snakeHeadPos, TILE_SNAKEHEAD + 1);
```

9. Compile, rode o programa e verifique se o problema foi corrigido.

10. **DESAFIO**: Sem olhar na resposta abaixo, corrija o problema do travamento do jogo.

```c
void dropApple() {
	do {
		applePos = NAMETABLE + 32 + rand() % (21 * 32);
	} while (Vpeek(applePos) != TILE_GRASS_EMPTY);
```

11. Compile, rode o programa e verifique se o problema foi corrigido. E agora, o que houve?

12. **DESAFIO**: Corrija o problema encontrado no item 11 acima.

```c
				EoG = (content != TILE_GRASS_EMPTY);
```

13. Compile, rode o programa e verifique se o problema foi corrigido. E dessa vez, o que houve?

14. **DESAFIO**: Corrija o problema encontrado no item 13 acima.

```c
			// Erases last tail segment
			if (growth == 0) {
				Vpoke(*snakeTail, TILE_GRASS_EMPTY);
```

15. Compile, rode o programa e verifique se o problema foi corrigido. E agora, como ficou?

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
