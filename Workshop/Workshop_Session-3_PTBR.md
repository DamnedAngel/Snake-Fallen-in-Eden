# Programando em C e ASM para MSX usando Visual Studio e Fusion-C
# Sessão 3: Implementando a Cobra! (parte 1)

Escrito por **Danilo Angelo (a.k.a. Damned Angel)**, 2020-2021

Vídeo da sessão 3: XXX

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

## Sessão 3: Implementando a Cobra! (parte 1)

### 3.1. Uma cabeça no jardim
###### *Github Ticket/Branch: 13/TKT0013.*

##### Objetivo: Fazer a cabeça da cobra aparecer no jardim, com posição controlada por variáveis (previsão: 15 minutos).

1. Vamos iniciar fazendo uma solução básica para o problema, adotando um estilo de programação próximo ao MSX-BASIC. A intenção é darmos um passo por vez para quem vem da linguagem clássica, e irmos pegando momento progressivamente.

A movimentação é bidimensional (cima-baixo, esquerda-direita), então vamos implementar o controle da cabeça com duas variáveis *x* e *y* para essas dimensões.

Ao contrário do MSX-BASIC, todas as variáveis em C precisam ser declaradas antes do primeiro uso. Declare as duas variáveis no arquivo *msxromapp.c*, logo após as diretivas *#include*:
```c
unsigned char x, y;
```

2. Adicione, na função *game()*, a inicialização das variáveis, para que a cobra sempre inicialize o jogo dessa posição default:
```c
void game() {
	Cls();
	print(gameScreen);

	// Initialize game variables
	x = 10;
	y = 10;

	InputChar();
}
```

3. Adicione, após a inicialização da variáveis, mas antes do *InputChar()*, comandos para impressão da cabeça:
```c
void game() {
	Locate(x, y);
	print("*");
}
```

4. Compile e execute.

5. Tente alterar os valores de *x* e *y*, compile e execute.

6. Discussão:
* Por que escolhemos declarar as variáveis *x* e *y* como globais e não dentro da função *game()*?

7. Restaure os valores de *x=10* e *y=10*.

### 3.2. Movimentando a cabeça.
###### *Github Ticket/Branch: 14/TKT0014.*

##### Objetivo: Fazer a cabeça da cobra passear pelo jardim, comandada pelas setas do teclado (previsão: 30 minutos).

1. Para que possamos começar a dinâmica do jogo, necessitamos criar um loop que mantenha a mecânica em execução até que o jogo acabe. Vamos, assim, criar a variável booleana *EoG* para controle desse loop (End of Game) no arquivo *msxromapp.c*, logo após as diretivas *#include*:
```c
bool EoG;
```

2. Em seguida, inicialize a variável com o valor *false*, no bloco de inicialização de variáveis da função *game()*:
```c
	// Initialize game variables
	x = 10;
	y = 10;
	EoG = true;
```

3. Por fim, criemos a estrutura do loop ao redor dos comandos para impressão da cabeça da cobra. Com isso, o jogo ficará agora em um loop eterno, mas mais tarde artibuiremos *true* à EoG quando a cobra colidir com as paredes ou com ela mesma, o que permitirá ao jogo sair do loop:
```c
	// Game's main loop
	while (! EoG) {
		Locate(x, y);
		print("*");
	}
```

4. Compile o programa.

5. Discussão:
* O que houve? Por quê?

6. Adicione suporte à variáveis booleanas ao seu programa, adicionando o seguinte include no início do arquivo *msxromapp.c*:
```c
#include <stdbool.h>
```

7. Compile e rode o programa.

8. **DESAFIO**: Sem olhar as respostas abaixo, pesquise como fazer uma leitura de Joystick na Fusion-C e implemente a leitura na variável joy.
```c
unsigned char x, y;
bool EoG;
unsigned char joy;
```
```c
	while (!EoG) {
		joy = JoystickRead(0);

		Locate(x, y);
		print("*");
	}
```

9. Conhecendo a estrutura ***switch/case*** em C:
```c
SINTAXE:

switch (expressão)
{
    case <constante_1>:
      // bloco de comandos

      break;

    case <constante_2>:
      // bloco de comandos

      break;
    .
    .
    .
    case <constante_n>:
      // bloco de comandos

      break;

    default:
      // bloco de comandos
}
```
* A *expressão* é avaliada uma vez e comparada com as *constantes* de cada bloco ***case***, na ordem estipulada.
* Se/quando houver uma correspondência, o *bloco de comandos* correspondente é executados.
* Ao encontrar a cláusula ***break***, a estrutura ***switch*** é finalizada.
* Se um block ***case*** não for finalizado com ***break***,  os *blocos de comandos* subsequentes são executados também (até que um ***break*** seja encontrado).
* Se/quando a expressão não corresponder a nenhuma das *constantes*, o *bloco de comandos* após a cláusula ***default*** é executado.

8. **DESAFIO**: Sem olhar o resultado abaixo, monte uma estrutura ***switch/case*** para alterar os valores das variáveis *x* e *y* em função dos valores de *joy*.
```c
		joy = JoystickRead(0);
		
		// move snake
		switch (joy) {
		case 1:
			y--;
			break;
		case 3:
			x++;
			break;
		case 5:
			y++;
			break;
		case 7:
			x--;
			break;
		}
```

9. Compile e rode o programa (dica: teste com toques BEM rápidos na teclas de setas).

10. Discussão:
* O que houve? Por quê?

### 3.3. Detectando colisão.
###### *Github Ticket/Branch: 15/TKT0015.*

##### Objetivo: Detectar colisão da cobra com as paredes e consigo mesma e finalizar o jogo (previsão: 20 minutos).

1. Entendendo um pouquinho mais sobre a VRAM.
* Tabelas padrões, nomes e cores da screen 1.
* Lembrando da função BASE() do MSX-BASIC (https://www.msx.org/wiki/BASE()).
* Lembrando da função VPEEK() do MSX-BASIC (https://www.msx.org/wiki/VPEEK).

2. Crie a constante NAMETABLE no arquivo *msxromapp.c*, entre as cláusulas *#include* e as declarações de variáveis:
```c
#define NAMETABLE			0x1800
```

3. Discussão:
* Como converter os valores das variáveis *x* e *y* nos endereços de VRAM correspondentes?

4. **DESAFIO**: Sem olhar as respostas abaixo, recupere o conteúdo do jardim (tela) na posição para onde a cabeça da cobra está indo e armezene na variável *content*.
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

5. **DESAFIO**: Sem olhar as respostas abaixo, ajuste a variável EoG se o valor da variável content for diferente de 32 (ASCII do espaço).
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

6. Compile e rode o programa.

### 3.4. Controlando a cadência do jogo.
###### *Github Ticket/Branch: 16/TKT0016.*

##### Objetivo: Controlar a velocidade o jogo através do sistema de interrupções do MSX (previsão: 20 minutos).

1. Entendendo o básico de interrupções do VDP.
* Rotina de tratamento de interrupção;
* Halt do Z80;
* Apoio da BIOS. Jiffy.

2. Crie uma variável inteira, sem sinal e de 16 bits para controlar o progresso do *Jiffy* chamada *lastJiffy*. No final de loop, grave o último *Jiffy* detectado na variável e no início do loop do jogo aguarde até a BIOS mudar o valor do *Jiffy*.
```c
unsigned char content;
unsigned int lastJiffy;
```
```c
	// Game's main loop
	while (!EoG) {
		while (lastJiffy == Peekw(BIOS_JIFFY)) {}
		// from this point on, 1 pass per frame

		...

		lastJiffy = Peekw(BIOS_JIFFY);
	}
```

3. Apenas para manter nossa lembrança, vamos colocar um comentário no final do loop de jogo, agora sincronizado a 1 execução por frame, que ali futuramente colocaremos nossa rotina simples de geração dos sons:

```c
		Locate(x, y);
		print("*");

		// here we will add the sound effects routine
		{
		}

		lastJiffy = Peekw(BIOS_JIFFY);
```
4. Compile e rode o programa.

5. Agora, para movimentar a cabeça da cobra, vamos colocar uma velocidade inicial de 4 posições por segundo. Assim, supondo NTSC e PAL-M com 60 frames por segundo, vamos aguardar o Jiffy chegar a 15 para executar a movimentação e, em seguida, zeramos essa variável para outro ciclo. Lembre-se que o bloco de efeitos sonoros deve ser executado a cada frame.
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
### 3.5. Finalização da Sessão 3
##### Objetivo: Discutir os tópicos tratados e o modelo/dinâmica do workshop (previsão: 10 minutos).

1. Discussão geral da apresentação:
* Switch/Case;
* VDP, tabelas, VPEEK, VPOKE.
* Interrupções, temporização, Jiffy.
* Os vários loops internos do programa para controle de temporização.
* Dinâmica geral do workshop: feedbacks e ideias.

---

**Happy MSX'ing.**