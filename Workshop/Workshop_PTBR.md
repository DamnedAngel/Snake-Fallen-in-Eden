# Programando em C e ASM para MSX usando Visual Studio e Fusion-C

Escrito por Damned Angel, 2020-2021

---

## Abrevia��es usadas nesse documento

VS: Visual Studio 2019

---

## Padroniza��es usadas nesse documento

Esse documento � dividido em sess�es de workshop, e as sess�es s�o divididas em t�picos de estudo.

Os t�picos de estudo s�o dividos em passos. Esses passos ter�o sempre 1 dentre 3 formatos:
* Um passo com o verbo no ger�ndio (ex: *Compilando o projeto.*) significa uma explosi��o do palestrante.
* Um passo com o verbo no imperativo (ex: *Configure a aplica��o*) denota um passo para ser executado pelo participante.
* Um passo com a descri��o de uma atividade (ex: *Discuss�o em grupo.*) descreve a proposta de uma din�mica.

---

## Sess�o 1: Criando e configurando o projeto

### 1.1. Pr�-requisitos

##### Objetivo: REVISAR pr�-requisitos para o workshop (previs�o: 10 minutos).

* VS Instalado.
* Templates MSX (https://github.com/DamnedAngel/MSX-Templates-for-VisualStudio) instalados no VS, conforme instru��es em https://docs.google.com/document/d/1Y2rTTMBN08Au59e44pzdX0ptVWfLfMgG1gp2e-KUVIE/edit#.
* SDCC, Hex2Bin e Python instalados e configurados no PATH.
* Fusion-C baixada e descompactada.
* OpenMSX instalado e rodando. Seguir roteiro do Lavadeira em:
* Parte 1: https://medium.com/relearning-msx/relearning-msx-5-setting-up-the-msx-c-environment-part-1-797d14e03a1d
* Parte 2: https://medium.com/relearning-msx/relearning-msx-6-7a5d8e3ef6a3
* Demais partes s�o interessantes, mas opcionais. O que precisamos � de um OpenMSX rodando MSXDOS para o caso de desenvolvimento para esse ambiente.
* OpenMSX Debugger instalado e rodando.


### 1.2. Criando o projeto
###### *Github Ticket/Branch: 2/TKT0002.*
##### Objetivo: Dominar a cria��o de projetos MSX a partir dos templates (previs�o: 10 minutos).

1. Clique no bot�o **Create a New Project** na janela de abertura do VS. Alternativamente, selecione **File|New|Project**.
2. Na lista de templates mostrada, selecione **MSX ROM Application** (caso queira fazer o projeto no formato MSX-DOS, escolha o template **MSX-DOS Application**. Provavelmente esse item estar� no final da lista, ent�o fa�a o scroll down.
3. Configure o nome da aplica��o, a localiza��o do projeto no seu disco e o nome da solu��o (a solu��o � um agregador de projetos).
4. Clique o bot�o **Create** e o VS criar� seu projeto. Para ter certeza que o projeto foi criado corretamente, compile-o com **Build|Build Solution**. A tela de output dever�, ao final da compila��o, mostrar a mensagem **"Rebuild All: 1 succeeded, 0 failed, 0 skipped"**.

### 1.3. Compilando e rodando no OpenMSX
##### Objetivo: Executar programas MSX em desenvolvimento (previs�o: 10 minutos).

1. Compilando o projeto ROM e rodando no OpenMSX.
2. Usando modo Release/Debug.
3. Escolhendo o template da rotina principal em C e em ASM (ApplicationSources.txt):
* msxromapp.c
* msxromapp.s


### 1.4. Configurando o projeto e explorando o template
###### *Github Ticket/Branch: 3/TKT0003.*
##### Objetivo: Compreender a estrutura do projeto MSX (previs�o: 25 minutos).

1. Ajustando par�metros em ApplicationSettings.txt.
2. Configurando nome da aplica��o em TargetConfig_Debug.txt e TargetConfig_Release.txt.
3. Explorando os arquivos de configura��o do projeto.
4. Explorando a estrutura do projeto:
* msxromapp.c
* msxromapp.s
* msxromcrt0.s
* msxbios.h
* msxbios.s
* applicationsettings.s
* targetconfig.h
* targetconfig.s
* make.bat
* symbol.p

### 1.5. Criando projetos MSX-DOS e BIN
##### Objetivo: Compreender a estrutura do projeto MSX (previs�o: 20 minutos).

*Nota: Salve e feche o projeto ROM antes de iniciar esse item.*

1. Criando um projeto MSXDOS + compila��o e execu��o + configura��es. 
2. Criando um projeto BIN + compila��o e execu��o + configura��es. 

### 1.6. Finaliza��o da Sess�o 1
##### Objetivo: Discutir os t�picos tratados e o modelo/din�mica do workshop (previs�o: 10 minutos).

1. Discuss�o geral da apresenta��o:
* T�picos apresentados.
* Din�mica geral do workshop: feedbacks e ideias.

---

## Sess�o 2: Iniciando o programa

### 2.1. Integrando a biblioteca Fusion-C
###### *Github Ticket/Branch: 7/TKT0007.*

##### Objetivo: Entender a inclus�o de bibliotecas externas ao projeto (previs�o: 10 minutos).

1. Vamos primeiramente configurar o VDP para o modo que usaremos no jogo. Substitua o conte�do da fun��o main() por
```c
void main(void) {
	Screen(1);
	Width(32);
}
```
Tente compilar e voc� receber� um erro, j� que as fun��es *Screen()* e *Width()* n�o est�o dispon�veis nativamente na linguagem C. A biblioteca Fusion-C as implementa, mas ainda n�o a integramos no projeto. Vamos ent�o fazer isso, seguindo os passos abaixo.

2. Descomente a linha abaixo no arquivo IncludeDirectories.txt:
```
[MSX_LIB_PATH]\fusion-c\header
```
Isso far� os arquivos .h nesse diret�rio acess�veis por cl�usulas *include*. Voc� poder� ter que adaptar o caminho caso tenha usado um diret�rio diferente na instala��o da Fusion-C.

3. Adicione a linha abaixo no in�cio do seu fonte *msxromapp.c*:
```c
#include "msx_fusion.h"
```
Isso importar� todas as declara��es de fun��es da Fusion-C. Se voc� n�o entende direito como arquivos header (*.h) funcionam em C, talvez este seja um bom momento de dar uma pesquisada r�pida.

Note que o arquivo a msx_fusion.h cont�m a declara��o da fun��o, mas n�o a implementa��o (abra o arquivo e veja por voc� mesmo!). No pr�ximo passo incluremos a implementa��o da fun��o ao projeto.

4. Descomente a linha abaixo no arquivo Libraries.txt:
```
[MSX_LIB_PATH]\fusion-c\lib\fusion.lib
```
Com isso terminamos a inclus�o da biblioteca no processo de compila��o do projeto.

5. Compile o programa para se certificar que ele est� funcional. Se quiser, teste-o no OpenMSX.

### 2.2. Criando o loop externo do programa
###### *Github Ticket/Branch: 6/TKT0006.*

##### Objetivo: Ter a inicializa��o e a l�gica geral do fluxo da aplica��o implementadas (previs�o:15 minutos).

1. No arquivo *msxromapp.c*, remova todas as fun��es de exemplo de suporte a chamadas CALL do BASIC e a dispositivos depois do main():
* onCall*
* onDevice*

2. No mesmo arquivo, crie stubs para as fun��es de exibi��o de t�tulo do jogo, da l�gica de jogo e da exibi��o da tela de fim de jogo:
```c
void title() {
	Cls();
	print ("My Snake Game");
	InputChar();
}

void game() {
	Cls();
	print ("Game");
	InputChar();
}

void gameOver() {
	Cls();
	print ("Game Over");
	InputChar();
}
```

**Note que as fun��es Cls() e InputChar s�o implementadas pela bibliteca **Fusion-C**, que tamb�m tem uma fun��o Print(), mas estamos aqui usando o print() que � disponibilizado pelo template, por ser mais simples.*

3. Implemente um loop infinito na fun��o *main()* do programa, chamando sequencialmente as fun��es criadas no passo anterior.
```c
	// program's infinite loop
	while (1) {
		title();
		game();
		gameOver();
	}
```

4. Compile e execute o programa.

5. Discuss�o de resultados e primeiras percep��es sobre:
* o programa;
* o ambiente de desenvolvimento;
* a biblioteca Fusion-C;
* diferen�as para BASIC, Pascal ou outras linguagens.

### 2.3. Criando uma tela funcional para o jogo
###### *Github Ticket/Branch: 8/TKT0008.*

##### Objetivo: Estabelecer uma tela de fundo funcional para o desenvolvimento do jogo (previs�o:20 minutos).

1. Vamos primeiramente criar um arquivo header (*screens.h*) no qual declararemos nossas telas. Siga os passos:
* No VS, garanta que o Solution Explorer est� vis�vel, selecionando **View|Solution Explorer**.
* No Solution Explorer, expanda a pasta (filtro, na verdade) **[Solution]|[Projeto]|Header Files**.
* Clique o bot�o direito no filtro **Header Files** e selecione a op��o **Add|New Item**.
* Na tela que apareceu, selecione o tipo **Header File (.h)**, d� o nome *screens.h* para o arquivo, certifique-se que o campo **Location** tem o diret�rio do seu projeto (deve ser por default) e clique em **Add**.
* Note que o arquivo foi criado e a refer�ncia a ele apareceu no Solution Explorer, sob o filtro **Header Files**.

Nota: Se voc� n�o est� usando o VS, fa�a processo similar na sua IDE, ou simplesmente crie o arquivo *screens.h* no diret�rio do seu projeto.

2. No arquivo *screens.h*, crie uma constante (*static const char gameScreen[]*, terminada em nulo) com o mapa da tela do jogo, de 32x24 posi��es, com uma borda nas 23 linhas superiores e informa��es de status (score, hiscore e level) na �ltima linha.

* Use "-" para bordas horizontais, "|" pa verticais e "+" para as intersec��es.

```c
#pragma once

static const char gameScreen[] = \
"+------------------------------+"\
"|                              |"\

(... repete 19 linhas ...)

"|                              |"\
"+------------------------------+"\
" Score 0     High 0    Level 1  \0";
```

3. Agora, para utilizar o que definimos no aquivo *screens.h*, em nossa rotina de exibi��o de tela no arquivo *msxromapp.c*, esse �ltimo precisa "conhecer" o primeiro. Precisamos, assim, referenciar o arquivo header no *msxromapp.c*. Para isso, inclua a seguinte linha no topo do arquivo .c, ap�s outras cl�usulas "include":

```c
#include "screens.h"
```

4. Por fim, precisamos substituir o stub de tela de jogo pelo novo background, simples mas funcional. Na fun��o *game()*, substitua a impress�o da string *"Game"* pela impress�o de nossa nova constante *gameScreen*:
```c
	//print("Game");
	print(gameScreen);
```

5. Compile e execute o programa.

6. Discuss�o de resultados e percep��es sobre:
* constantes;
* arquivos header;
* a impress�o na �ltima posi��o da tela (canto inferior direito, ou coordenadas (31,23)); print versus vpoke;
* diferen�as para BASIC, Pascal ou outras linguagens.

7. Ajuste, se necess�rio, a impress�o do �ltimo caracter da tela para evitar o scroll.
* Esse ajuste � preliminar, at� construirmos nossa pr�pria rotina de impress�o em Assembly, que vai permitir desenhar o gramado, dar mais velocidade para a cria��o da tela e evitar o scroll quando usamos a �ltima posi��o da tela.

### 2.4. Criando uma tela de abertura funcional
###### *Github Ticket/Branch: 10/TKT0010*

##### Objetivo: Estabelecer uma tela de abertura informativa para o jogo (previs�o:10 minutos).

A cria��o da tela de abertura � similar � cria��o da tela de background do jogo. Assim os passos s�o similares:

1. No arquivo *screens.h*, crie a constante *titleScreen[]* com o mapa da tela de abertura, de forma similar � *gameScreen*, tamb�m com 32x24 posi��es.

2. Na fun��o *title()*, substitua a impress�o da string *"My Snake Game"* pela impress�o da constante *titleScreen*.
```c
	//print("My Snake Game");
	print(titleScreen);
```

3. Compile e execute o programa.


### 2.5. Criando uma tela de fim de jogo funcional
###### *Github Ticket/Branch: 11/TKT0011*

##### Objetivo: Estabelecer uma tela de fim de jogo adequada para o jogo (previs�o:10 minutos).

A cria��o da tela de fim de jogo � um pouco diferente, pois queremos permitir que o jogador avalie a situa��o geral do jogo e revise o placar.

1. No arquivo *screens.h*, crie a constante *gameOverMsg[]* com uma mensagem de 3 linhas (32 x 3 posi��es) de "Game Over" o mapa da tela de abertura:

2. Remova o *Cls()* da fun��o *gameOver()* e substitua a impress�o da string *"My Snake Game"* pela constante *gameOverMsg*, a partir da linha 9:

```c
void gameOver() {
	//Cls();
	//print("Game Over");
	Locate(0, 9);
	print(gameOverMsg);
	InputChar();
}
```
**Note que a fun��o Locate() � implementada pela biblioteca **Fusion-C**.*

3. Compile e execute o programa.

### 2.6. Finaliza��o da Sess�o 2
##### Objetivo: Discutir os t�picos tratados e o modelo/din�mica do workshop (previs�o: 15 minutos).

1. Discuss�o geral da apresenta��o:
* Uso de bibliotecas em C.
* Fusion-C para desenvolvedores MSX-BASIC.
* Arquivos .c e arquivos .h.
* Constantes.
* O loop externo do programa.
* Din�mica geral do workshop: feedbacks e ideias.
 
---

## Sess�o 3: Implementando a cobra

### 3.1. Uma cabe�a no jardim
###### *Github Ticket/Branch: 13/TKT0013.*

##### Objetivo: Fazer a cabe�a da cobra aparecer no jardim, com posi��o controlada por vari�veis (previs�o: 15 minutos).

1. Vamos iniciar fazendo uma solu��o b�sica para o problema, adotando um estilo de programa��o pr�ximo ao MSX-BASIC. A inten��o � darmos um passo por vez para quem vem da linguagem cl�ssica, e irmos pegando momento progressivamente.

A movimenta��o � bidimensional (cima-baixo, esquerda-direita), ent�o vamos implementar o controle da cabe�a com duas vari�veis X e Y para essas dimens�es.

Ao contr�rio do MSX-BASIC, todas as vari�veis em C precisam ser declaradas antes do primeiro uso. Declare as duas vari�veis no arquivo *msxromapp.c*, logo ap�s as diretivas *#include*:
```c
unsigned char x, y;
```

2. Adicione, na fun��o *game()*, a inicializa��o das vari�veis, para que a cobra sempre inicialize o jogo dessa posi��o default:
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

3. Adicione, ap�s a inicializa��o da vari�veis, mas antes do *InputChar()*, comandos para impress�o da cabe�a:
```c
void game() {
	Locate(x, y);
	print("*");
}
```

4. Compile e execute.

5. Tente alterar os valores de X e Y, compile e execute.

6. Discuss�o:
* O que houve? Por qu�?

7. Restaure os valores de X=10 e Y=10.

