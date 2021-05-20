# Programando em C e ASM para MSX usando Visual Studio e Fusion-C
# Sessão 5: Colisão e temporização.

Escrito por **Danilo Angelo (a.k.a. Damned Angel)**, 2020-2021

Vídeo da sessão 5: XXX

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

## Sessão 5: Colisão e temporização.

### 5.1. Detectando colisão.
###### *Github Ticket/Branch: 15/TKT0015.*

##### Objetivo: Detectar colisão da cobra com as paredes e consigo mesma e finalizar o jogo (previsão: 30 minutos).

1. Entendendo um pouquinho mais sobre a VRAM.
* Tabelas padrões, nomes e cores da screen 1.
* Lembrando da função BASE() do MSX-BASIC: https://www.msx.org/wiki/BASE() (inglês).
* Lembrando da função VPEEK() do MSX-BASIC: https://www.msx.org/wiki/VPEEK (inglês).

2. Crie a constante NAMETABLE no arquivo *msxromapp.c*, entre as cláusulas *#include* e as declarações de variáveis:
```c
#define NAMETABLE			0x1800
```

3. Discussão:
* Como converter os valores das variáveis *x* e *y* nos endereços de VRAM correspondentes à posição da cabeça da cobra na tabela de nomes?

4. **DESAFIO**: Sem olhar as respostas abaixo, use a função Vpeek para recuperar o conteúdo do jardim (tela) na posição para onde a cabeça da cobra está indo e armezene na variável *content*.
```c
bool EoG;
unsigned char x, y;
unsigned char joy;
unsigned char content;
```
```c
		// move snake
		switch (joy) {
			...
		}

		content = Vpeek(NAMETABLE + y * 32 + x);
```

5. Discussão:
* Qual a posição adequada para o comendo Vpeek, e por quê?

6. **DESAFIO**: Sem olhar as respostas abaixo, ajuste a variável EoG se o valor da variável content for diferente de 32 (ASCII do espaço).
```c
		content = Vpeek(NAMETABLE + y * 32 + x);
		if ((joy > 0) && (content != 32)) {
			EoG = true;
		}

```
Ou, pensando em C:
```c
		content = Vpeek(NAMETABLE + y * 32 + x);
		EoG = ((joy > 0) && (content != ' '));
```

7. Discussão:
* Por que precisamos incluir o teste "joy > 0" na avaliação da de EoG?

8. Compile e rode o programa.

### 5.2. Controlando a cadência do jogo.
###### *Github Ticket/Branch: 16/TKT0016.*

##### Objetivo: Controlar a velocidade o jogo através do sistema de interrupções do MSX (previsão: 60 minutos).

1. Entendendo o básico de interrupções no MSX.
* [VDP] A interrupção VBlank do TMS9918.
* [Z80] O tratamento de interrupções no Z80.
* [Arquitetura MSX] Hooks e, em particular, o Hook H.TIMI (FD9Fh).

Referências:
* TMS9918: http://map.grauw.nl/resources/video/ti-vdp-programmers-guide.pdf (inglês).
* vBlank: https://www.youtube.com/watch?v=aUkHk_mjtOU (espanhol).
* Interrupções no Z80: http://map.grauw.nl/articles/interrupts.php (inglês).
* Hooks: https://www.msx.org/wiki/System_hooks (inglês).
* Muito de tudo acima: http://www.msxtop.msxall.com/Portugues/Projeto_msx_top_secret.htm (português).

2. Comparando quatro estratégias de temporização:
* **[Z80] Rotinas de tratamento de interrupção**
  * Vantagens:
    * *Execução mais rápida possível ("O que vc não precisa, se você está usando C" - Grauw).*
    * Não trava o processador enquanto a interrupção não acontecer.
  * Desvantagens:
    * "Bypass" da BIOS;
    * Demanda instalação de rotinas de tratamento de interrupção.
* **[Z80] A Instrução Halt do Z80**
  * Vantagem:
    * *Implementação mais simples possível.*
    * Não faz "Bypass" da BIOS;
    * Não demanda instalação de rotinas de tratamento de interrupção nem de hook.
  * Desvantagem:
    * Trava o processador enquanto a interrupção não acontecer.
* **[Arquitetura MSX] O Hook H.TIMI (FD9Fh)**
  * Vantagem:
    * *Forma recomendada pelo padrão.*
    * Não faz "Bypass" da BIOS;
    * Não trava o processador enquanto a interrupção não acontecer.
  * Desvantagem:
    * Demanda instalação de rotinas de tratamento de hook.
* **[Arquitetura MSX] A variável Jiffy**
  * Vantagem:
    * *Estratégia que demanda o menor domínio sobre interrupções.*
    * Não faz "Bypass" da BIOS;
    * Não trava o processador enquanto a interrupção não acontecer;
    * Não demanda instalação de rotinas de tratamento de interrupção nem de hook;
    * Já fornece um contador confiável de frames.
  * Desvantagem:
    * **Funciona bem, mas é o mais próximo que existe de uma gambiarra.**

3. Explorando o suporte da Fusion-C para o tratamento de interrupções
* [Fusion-C] Suporte a rotinas de tratamento de interrupção;

4. Crie uma variável inteira, sem sinal e de 16 bits para controlar o progresso do *Jiffy* chamada *lastJiffy*. No final de loop, grave o último *Jiffy* detectado na variável.
```c
unsigned char content;
unsigned int lastJiffy;
```
```c
	// Game's main loop
	while (!EoG) {

		...

		lastJiffy = Peekw(BIOS_JIFFY);
	}
```

5. No início do loop do jogo aguarde até a BIOS mudar o valor do *Jiffy*.
```c
	// Game's main loop
	while (!EoG) {
		while (lastJiffy == Peekw(BIOS_JIFFY)) {}
		// from this point on, 1 pass per frame

		...

		lastJiffy = Peekw(BIOS_JIFFY);
	}
```

6. Apenas para manter nossa lembrança, vamos colocar um comentário no final do loop de jogo, agora sincronizado a 1 execução por frame, que ali futuramente colocaremos nossa rotina simples de geração dos sons:

```c
		Locate(x, y);
		print("*");

		// here we will add the sound effects routine
		{
		}

		lastJiffy = Peekw(BIOS_JIFFY);
```
7. Compile e rode o programa. O que houve?

8. Agora, para movimentar a cabeça da cobra, vamos colocar uma velocidade inicial de 4 posições por segundo. Assim, supondo NTSC e PAL-M com 60 frames por segundo, vamos aguardar o Jiffy chegar a 15 para executar a movimentação e, em seguida, zeramos essa variável para outro ciclo. Lembre-se que o bloco de efeitos sonoros deve ser executado a cada frame.
```c
	// Initialize game variables
	x = 10;
	y = 10;
	EoG = false;
	Pokew(BIOS_JIFFY, 0);
```
```c
		while (lastJiffy == Peekw(BIOS_JIFFY)) {}
		// from this point on, 1 pass per frame

		if (Peekw(BIOS_JIFFY) == 15) {
			joy = JoystickRead(0);

			...

			print("*");

			Pokew(BIOS_JIFFY, 0);
		}

		// here we will add the sound effects routine
		{
		}
```
### 5.3. Finalização da Sessão 5
##### Objetivo: Discutir os tópicos tratados e o modelo/dinâmica do workshop (previsão: 10 minutos).

1. Discussão geral da apresentação:
* VDP, tabelas, VPEEK, VPOKE.
* Interrupções, temporização, Jiffy.
* Os vários loops internos do programa para controle de temporização.
* Dinâmica geral do workshop: feedbacks e ideias.

2. Tarefa opcional "para casa":
* Além do Jiffy: Transforme sua temporização da estratégia Jiffy para uso do Hook H.TIMI.

---

**Happy MSX'ing.**
