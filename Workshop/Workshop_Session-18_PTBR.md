# Programando em C e ASM para MSX usando Visual Studio e Fusion-C
# Sessão 18: O assembler e a relva.

Escrito por **Danilo Angelo (a.k.a. Damned Angel)**, 2020-2021

Vídeo da sessão 18: XXX

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

# Sessão 18: O assembler e a relva.

### 18.1. Montando o éden com relva.
###### *Github Ticket/Branch: 61/TKT0061.*

##### Objetivo: incluir um arquivo assembler puro no projeto e desenvolver uma rotina de montagem do éden com relva, compatível com chamadas em C (previsão: 90 minutos).

1. Adicione o arquivo *eden.s* no projeto. Para quem usa o Visual Studio, adicione o arquivo sob o filtro *ASM Source Files*. Para outros ambientes, apenas crie o arquivo no filesystem e abra no seu editor.

2. No final do arquivo de configuração Application Sources.txt, adicione referência para *eden.s*:
```c
;----------------------------------------------------------
;	Additional source files
;	Add below additional source files for your application
;	using relative paths from the project folder
;yourSourceCodeHere.s
;yourSourceCodeHere.c
eden.s
```

3. Compile o projeto e certifique-se que o processo de build está incluindo o arquivo novo.

4. Crie o cabeçalho do arquivo *eden.s* e da rotina *_buildEden*:
```c
; ----------------------------
; Lib to create the eden
; ----------------------------

; ----------------------------------------------------------
;	buildEden (int VRAMAddr, char* RAMAddr, unsigned int blockLength)
;
_buildEden::
```

5. Copie a rotina *blockToVRAM* do arquivo *msxromapp.c". Vamos utilizá-la como base para a *buildEden*:
```c
; ----------------------------------------------------------
;	buildEden (int VRAMAddr, char* RAMAddr, unsigned int blockLength)
;
_buildEden::
	ld		hl,		#2
	add		hl,		sp

	ld		a,		(hl)
	out		(#0x99),a
	inc		hl
	ld		a,		(hl)
;	and		#0x3f
	or		#0x40
	out		(#0x99),a

	inc		hl
	ld		e,		(hl)
	inc		hl
	ld		d,		(hl)

	inc		hl
	inc		hl
	ld		b,		(hl)
	ld		c,		#0x98
	push		bc
	dec		hl
	ld		b,		(hl)
	ld		l,		e
	ld		h,		d
	
label1:
	outi
	jr		nz,		label1

	pop		bc
	xor		a		; = ld a, 0
	cp		b
	ret		z

	dec		b
	push		bc
	ld		b,		#255
	jr		label1
```

6. Relembrando a *blockToVRAM*: uma leitura da rotina.

7. Substitua, na função *title*, a chamada à *_print* por uma chamada à *buildEden*:
```c
void title() {
	// Set colors
	blockToVRAM(COLORTABLE, tileColors_title, sizeof(tileColors_title));

	// Build screen
	buildEden (NAMETABLE, titleScreen, sizeof(titleScreen));
```

8. Compile o programa. O que houve? Como resolver?

9. Entendendo A palavra-chave *extern*.

10. Adicione a declaração da função externa *buildEden*:
```c
extern void buildEden(int VRAMAddr, char* RAMAddr, unsigned int blockLength);
```

11. Compile e execute o programa. O que você notou?

12. Substitua, na função *game*, a chamada à *_print* por uma chamada à *buildEden*:
```c
	// Set colors
	blockToVRAM(COLORTABLE, tileColors_game, sizeof(tileColors_game));

	srand(Peekw(BIOS_JIFFY));

	// Build screen
	buildEden(NAMETABLE, gameScreen, sizeof(gameScreen));
```

13. Compile e execute o programa. Novamente, o que você notou?

14. Ajuste a rotina para colocar relvas aleatoriamente quando achar o caracter 0xaf:
```c
_buildEden::
	ld		hl,		#2
	add		hl,		sp

	ld		a,		(hl)
	out		(#0x99),a
	inc		hl
	ld		a,		(hl)
;	and		#0x3f
	or		#0x40
	out		(#0x99),a

	inc		hl
	ld		e,		(hl)
	inc		hl
	ld		d,		(hl)

	inc		hl
	inc		hl
	ld		b,		(hl)
;	ld		c,		#0x98
	push		bc
	dec		hl
	ld		b,		(hl)
	ld		l,		e
	ld		h,		d
	
_newChar:
	ld		a,		(hl)
	inc		hl
	cp		#0xaf
	jr nz,		outToVRAM
	ld		a,		r
	rlca
	ld		r,		a
	and		#0x0f ;16 tiles
	add		#0xa8 ;TILE_GRASS

outToVRAM:
	out		(#0x98), a
	djnz		_newChar

	pop		bc
	xor		a		; = ld a, 0
	cp		b
	ret		z

	dec		b
	push		bc
	ld		b,		#255
	jr		_newChar
```

15. Compile e execute o programa. O que houve?

16. Adicione tiles das relvas mais claras na função buildTiles():
```c
	blockToVRAM(PATTERNTABLE + TILE_GRASS * 8, tiles_grass, sizeof(tiles_grass));
	blockToVRAM(PATTERNTABLE + (TILE_GRASS + 8) * 8, tiles_grass, sizeof(tiles_grass));
```

17. Compile e execute o programa. O que houve?

18. Conserte a detecção de colisão:
```c
	collision = (content < TILE_GRASS)
		&& (content != TILE_APPLE);
```

19. Compile e execute o programa. E agora, o que houve?

20. Crie novas relvas no caminhar da cobra:
```c
	// Erases last tail segment
	if (growth == 0) {
		Vpoke (*snakeTail, 
		TILE_GRASS + (rand() & 0x0f));
```

21. Compile e execute o programa.


... e com isso, finalizamos nosse jogo!

### 18.2. Finalização da Sessão 18
##### Objetivo: Discutir os tópicos tratados e o modelo/dinâmica do workshop (previsão: 10 minutos).

1. Discussão geral da apresentação:
* O jogo completo.
* Assembler.
* o Z80.
* Arquivos em assembler puro.

---
