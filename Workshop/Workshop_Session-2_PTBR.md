# Programando em C e ASM para MSX usando Visual Studio e Fusion-C
# Sessão 2: Iniciando o desenvolvimento do jogo

Escrito por **Danilo Angelo (a.k.a. Damned Angel)**, 2020-2021

Vídeo da sessão 2: XXX

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

## Sessão 2: Iniciando o programa

### 2.1. Integrando a biblioteca Fusion-C
###### *Github Ticket/Branch: 7/TKT0007.*

##### Objetivo: Entender a inclusão de bibliotecas externas ao projeto (previsão: 15 minutos).

1. Vamos primeiramente configurar o VDP para o modo que usaremos no jogo. No arquivo *msxromapp.c*, substitua o conteúdo da função main() por
```c
void main(void) {
	Screen(1);
	Width(32);
}
```
Tente compilar e você receberá um erro, já que as funções *Screen()* e *Width()* não estão disponíveis nativamente na linguagem C. A biblioteca Fusion-C as implementa, mas ainda não a integramos no projeto. Vamos então fazer isso, seguindo os passos abaixo.

2. Descomente a linha abaixo no arquivo *IncludeDirectories.txt*:
```
[MSX_LIB_PATH]\fusion-c\header
```
Isso fará os arquivos .h nesse diretório acessíveis por cláusulas *include*. Você poderá ter que adaptar o caminho caso tenha usado um diretório diferente na instalação da Fusion-C.

3. Adicione a linha abaixo no início do seu fonte *msxromapp.c*:
```c
#include "msx_fusion.h"
```
Isso importará todas as declarações de funções da Fusion-C.

4. Entendendo o básico sobre arquivos header em C.

Note que o arquivo *msx_fusion.h* contém a declaração da função, mas não a implementação (abra o arquivo e veja por você mesmo!).

Se você nunca trabalhou com arquivos header (\*.h), não é esperado que nesse ponto você entenda completamente o conceito. Faça uma anotação para pesquisar o tópico depois do workshop.

Referência: **C Para Leigos, Davis**, *Stephen R.*

5. Tente compilar o programa. O que houve?

6. No próximo passo incluremos a implementação da função ao projeto. Descomente a linha abaixo no arquivo *Libraries.txt*:
```
[MSX_LIB_PATH]\fusion-c\lib\fusion.lib
```
Com isso terminamos a inclusão da biblioteca no processo de compilação do projeto.

7. Compile o programa para se certificar que ele está funcional. Se quiser, teste-o no OpenMSX.

### 2.2. Criando o loop externo do programa
###### *Github Ticket/Branch: 6/TKT0006.*

##### Objetivo: Ter a inicialização e a lógica geral do fluxo da aplicação implementadas (previsão:15 minutos).

1. Primeiramente, vamos "limpar" o template, removendo funcionalidades que não precisaremos. No arquivo *msxromapp.c*, remova todas as funções de exemplo de suporte a chamadas CALL do BASIC e a dispositivos depois do main():
* onCall*
* onDevice*

2. No mesmo arquivo, crie stubs para as funções de exibição de título do jogo, da lógica de jogo e da exibição da tela de fim de jogo:
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

**Note que as funções Cls() e InputChar são implementadas pela bibliteca **Fusion-C**, que também tem uma função Print(), mas estamos aqui usando o print() que é disponibilizado pelo template, por ser mais simples.*

3. Implemente um loop infinito na função *main()* do programa, chamando sequencialmente as funções criadas no passo anterior.
```c
	// program's infinite loop
	while (1) {
		title();
		game();
		gameOver();
	}
```

4. Compile e execute o programa.

5. Discussão de resultados e primeiras percepções sobre:
* o programa;
* o ambiente de desenvolvimento;
* a biblioteca Fusion-C;
* diferenças para BASIC, Pascal ou outras linguagens.

### 2.3. Criando uma tela funcional para o jogo
###### *Github Ticket/Branch: 8/TKT0008.*

##### Objetivo: Estabelecer uma tela de fundo funcional para o desenvolvimento do jogo (previsão:20 minutos).

1. Vamos primeiramente criar um arquivo header (*screens.h*) no qual declararemos nossas telas. Siga os passos:
* No VS, garanta que o Solution Explorer está visível, selecionando **View|Solution Explorer**.
* No Solution Explorer, expanda a pasta (filtro, na verdade) **[Solution]|[Projeto]|Header Files**.
* Clique o botão direito no filtro **Header Files** e selecione a opção **Add|New Item**.
* Na tela que apareceu, selecione o tipo **Header File (.h)**, dê o nome *screens.h* para o arquivo, certifique-se que o campo **Location** tem o diretório do seu projeto (deve ser por default) e clique em **Add**.
* Note que o arquivo foi criado e a referência a ele apareceu no Solution Explorer, sob o filtro **Header Files**.

Nota: Se você não está usando o VS, faça processo similar na sua IDE, ou simplesmente crie o arquivo *screens.h* no diretório do seu projeto.

2. No arquivo *screens.h*, crie uma constante (*static const char gameScreen[]*, terminada em nulo) com o mapa da tela do jogo, de 32x24 posições, com uma borda nas 23 linhas superiores e informações de status (score, hiscore e level) na última linha.

* Use "-" para bordas horizontais, "|" pa verticais e "+" para as intersecções.

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

3. Agora, para utilizar o que definimos no aquivo *screens.h*, em nossa rotina de exibição de tela no arquivo *msxromapp.c*, esse último precisa "conhecer" o primeiro. Precisamos, assim, referenciar o arquivo header no *msxromapp.c*. Para isso, inclua a seguinte linha no topo do arquivo .c, após outras cláusulas "include":

```c
#include "screens.h"
```

4. Por fim, precisamos substituir o stub de tela de jogo pelo novo background, simples mas funcional. Na função *game()*, substitua a impressão da string *"Game"* pela impressão de nossa nova constante *gameScreen*:
```c
	//print("Game");
	print(gameScreen);
```

5. Compile e execute o programa.

6. Discussão de resultados e percepções sobre:
* constantes;
* arquivos header;
* a impressão na última posição da tela (canto inferior direito, ou coordenadas (31,23)); print versus vpoke;
* diferenças para BASIC, Pascal ou outras linguagens.

7. Ajuste, se necessário, a impressão do último caracter da tela para evitar o scroll.
* Esse ajuste é preliminar, até construirmos nossa própria rotina de impressão em Assembly, que vai permitir desenhar o gramado, dar mais velocidade para a criação da tela e evitar o scroll quando usamos a última posição da tela.

### 2.4. Criando uma tela de abertura funcional
###### *Github Ticket/Branch: 10/TKT0010*

##### Objetivo: Estabelecer uma tela de abertura informativa para o jogo (previsão:10 minutos).

A criação da tela de abertura é similar à criação da tela de background do jogo. Assim os passos são similares:

1. No arquivo *screens.h*, crie a constante *titleScreen[]* com o mapa da tela de abertura, de forma similar à *gameScreen*, também com 32x24 posições.

2. Na função *title()*, substitua a impressão da string *"My Snake Game"* pela impressão da constante *titleScreen*.
```c
	//print("My Snake Game");
	print(titleScreen);
```

3. Compile e execute o programa.


### 2.5. Criando uma tela de fim de jogo funcional
###### *Github Ticket/Branch: 11/TKT0011*

##### Objetivo: Estabelecer uma tela de fim de jogo adequada para o jogo (previsão:10 minutos).

A criação da tela de fim de jogo é um pouco diferente, pois queremos permitir que o jogador avalie a situação geral do jogo e revise o placar.

1. No arquivo *screens.h*, crie a constante *gameOverMsg[]* com uma mensagem de 3 linhas (32 x 3 posições) de "Game Over" o mapa da tela de abertura:

2. Remova o *Cls()* da função *gameOver()* e substitua a impressão da string *"My Snake Game"* pela constante *gameOverMsg*, a partir da linha 9:

```c
void gameOver() {
	//Cls();
	//print("Game Over");
	Locate(0, 9);
	print(gameOverMsg);
	InputChar();
}
```
*Note que a função Locate() é implementada pela biblioteca **Fusion-C**.*

3. Compile e execute o programa.

### 2.6. Finalização da Sessão 2
##### Objetivo: Discutir os tópicos tratados e o modelo/dinâmica do workshop (previsão: 15 minutos).

1. Lição de casa: ler o manual do TMS9118 (http://map.grauw.nl/resources/video/ti-vdp-programmers-guide.pdf), seções 7.1, 7.1.1 (7.1.2 não precisa), 8.1 inteira (8.1.1, 8.1.2 e 8.1.3).

2. Lição de casa (para quem não entendeu o conceito de arquivos header): pesquisar e estudar o uso de arquivos header em C.

2. Discussão geral da apresentação:
* Uso de bibliotecas em C.
* Fusion-C para desenvolvedores MSX-BASIC.
* Arquivos .c e arquivos .h.
* Constantes.
* O loop externo do programa.
* Dinâmica geral do workshop: feedbacks e ideias.

---

**Happy MSX'ing.**
