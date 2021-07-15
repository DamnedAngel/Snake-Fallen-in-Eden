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

##### Objetivo: Retornr ao plano de mapa de caracteres original (previsão: 30 minutos).

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

8. **DESAFIO**: Corrija o tile da cabeça da cobra:

```c
	// initialize snake

	// ...

	Vpoke(snakeHeadPos, TILE_SNAKEHEAD + 1);
```

9. Compile, rode o programa e verifique se o problema foi corrigido.

10. **DESAFIO**: Corrija o problema do travamento do jogo.

```c
	// initialize snake

	// ...

	Vpoke(snakeHeadPos, TILE_SNAKEHEAD + 1);
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

4. Se você usa Visual Studio, adicione-o arquivo ao projeto, sob o filtro *Header Files*.

5. Embora não corramos o risco no nosso projeto, como boa prática, garanta que o arquivo não incorrerá em definições duplicadas caso seja referenciado por múltiplos arquivos fonte do projeto, inserindo na primeira linha:

```c
#pragma once
```

6. **DESAFIO**: Sem olhar a resposta abaixo, referencie o arquivo tiles.h no arquivo principal do nosso programa msxromapp.c.

```c
#include "screens.h"
#include "tiles.h"
```

7. Compile o projeto para garantir que o arquivo tiles.h está ok. Corrija qualquer problema de sintaxe que existir, se existir.

8. Refactoring: migre as definições de códigos de tiles do arquivo msxromapp.c para o início do arquivo tiles.h.

```c
#pragma once

#define TILE_GRASS		' '
#define TILE_SNAKETAIL		'o'
#define TILE_SNAKEHEAD		'*'
#define TILE_APPLE		'#'
```

9. Com base no mapa de caracteres de referência, altere a constante *TILE_APPLE* para o valor final. Se quiser, rode o programa para vê-lo funcionando com um caracter diferente representando a maçã.

```c
#define TILE_APPLE		0x98
```

10. **DESAFIO**: Sem olhar a resposta abaixo, crie a função *blockToVRAM(VRAMAddr, RAMAddr, blockLength)* para tranferir um bloco de dados da RAM para a VRAM.

```c
void blockToVRAM(int VRAMAddr, char* RAMAddr, unsigned int blockLength) {
	VpokeFirst(VRAMAddr);
	for (; blockLength > 0; blockLength--)
		VpokeNext(*(RAMAddr++));
}
``` 

11. **DESAFIO**: Sem olhar a resposta abaixo, crie a função *buildTiles()* e insira nela uma linha para montar o tile da maçã na VRAM usando a função *blockToVRAM*.

```c
void buildTiles() {
	blockToVRAM(PATTERNTABLE + TILE_APPLE * 8, tiles_apple, sizeof(tiles_apple));
}
``` 

12. **DESAFIO**: Chame a função *buildTiles()* a partir da função *main()*, após inicializar o modo de vídeo, mas antes da chamada à função *charMap()*.

```c
	buildFont();
	buildTiles();

#ifdef DEBUG
	charMap();
	while (!(allJoysticks() || allTriggers())) {}	// waits until key press
#endif
``` 

13. Compile e rode o programa. A maçã apareceu no mapa de caracteres? E no jogo?

### 11.3. Montando os outros tiles do jogo.
###### *Github Ticket/Branch: 45/TKT0045.*

##### Objetivo: Montar os demais tiles do jogo (previsão: 15 minutos).

1. **DESAFIO**: Sem olhar a resposta abaixo, repita os passos 9 e 11 para cada grupo de tiles definido no arquivo tiles.h.

```c
#define TILE_APPLE		0x98
#define TILE_SNAKEHEAD		0x80
#define TILE_SNAKETAIL		0x88
#define TILE_HEADXPLOD		0x90
#define TILE_VINE		0xa0
#define TILE_GRASS		0xa8
```
```c
void buildTiles() {
	blockToVRAM(PATTERNTABLE + TILE_APPLE * 8,
		tiles_apple, sizeof(tiles_apple));
	blockToVRAM(PATTERNTABLE + TILE_SNAKEHEAD * 8,
		tiles_snakeHead, sizeof(tiles_snakeHead));
	blockToVRAM(PATTERNTABLE + TILE_SNAKETAIL * 8,
		tiles_snakeTail, sizeof(tiles_snakeTail));
	blockToVRAM(PATTERNTABLE + TILE_HEADXPLOD * 8,
		tiles_headXplod, sizeof(tiles_headXplod));
	blockToVRAM(PATTERNTABLE + TILE_VINE * 8,
		tiles_vine, sizeof(tiles_vine));
	blockToVRAM(PATTERNTABLE + TILE_GRASS * 8,
		tiles_grass, sizeof(tiles_grass));
}
```

2. Compile e rode o programa. O mapa de caracteres foi atualizado? O que aconteceu com o jogo? Por quê?

3. Corrija temporariamente o problema, alterando o endereço VRAM dos tiles de grama para o código original, de espaço:

```c
#define TILE_GRASS		' '
```

4. Compile e rode o programa. Note a nova posição, temporária, dos tiles de grama. O jogo funcionou? O que está estranho?

### 11.4. Olha pra frente!
###### *Github Ticket/Branch: 46/TKT0046.*

##### Objetivo: Fazer a cobra olhar sempre para frente (previsão: 5 minutos).

1. **DESAFIO**: Sem olhar a resposta abaixo, selecione o tile correto da cabeça da cobra, em função da direção, em cada movimento.

```c
			// direction = 1 (UP),    tile = (direction-1)/2) = 0
			// direction = 3 (RIGHT), tile = (direction-1)/2) = 1
			// direction = 5 (DOWN),  tile = (direction-1)/2) = 2
			// direction = 7 (LEFT),  tile = (direction-1)/2) = 3
			Vpoke (snakeHeadPos, TILE_SNAKEHEAD + (direction - 1) / 2);
```

2. Compile e rode o programa.

### 11.5. Tile de colisão.
###### *Github Ticket/Branch: 46/TKT0046.*

##### Objetivo: Mostrar um tile de explosão da cabeça no evento da colisão (previsão: 5 minutos).

1. **DESAFIO**: Sem olhar a resposta abaixo, selecione um dos tiles da animação de explosão da cabeça quando acontecer uma colisão.

```c
	Vpoke(snakeHeadPos, TILE_HEADXPLOD + 3);
	Beep();
	Poke(BIOS_JIFFY, 0);
	while (Peek(BIOS_JIFFY) < 90) {}
```

2. Compile e rode o programa.


### 11.6. Finalização da Sessão 10
##### Objetivo: Discutir os tópicos tratados e o modelo/dinâmica do workshop (previsão: 10 minutos).

1. Lição de casa: colorir o jogo e a tela de abertura (na sessão que vem eu passarei a minha solução, mas seria bacana se cada um tivesse a sua).

2. Discussão geral da apresentação:
* Comentários sobre o estado corrente do jogo
* VDP / Tabela de padrões
* Arquivos header
* Dinâmica geral do workshop: feedbacks e ideias.

---

**Happy MSX'ing.**
