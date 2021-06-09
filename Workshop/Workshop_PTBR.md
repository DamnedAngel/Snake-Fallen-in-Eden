# Programando em C e ASM para MSX usando Visual Studio e Fusion-C

Escrito por Damned Angel, 2020-2021

---

## Abreviações usadas nesse documento

VS: Visual Studio 2019

---

## Padronizações usadas nesse documento

Esse documento é dividido em sessões de workshop, e as sessões são divididas em tópicos de estudo.

Os tópicos de estudo são dividos em passos. Esses passos terão sempre 1 dentre 3 formatos:
* Um passo com o verbo no gerúndio (ex: *Compilando o projeto.*) significa uma exposição do palestrante.
* Um passo com o verbo no imperativo (ex: *Configure a aplicação*) denota um passo para ser executado pelo participante.
* Um passo com a descrição de uma atividade (ex: *Discussão em grupo.*) descreve a proposta de uma dinâmica.

Adicionalmente, note que os trechos de código fornecidos como exemplo muitas vezes contém um trecho já existente do programa, para referência de localização.

---

## Sessão 0: Configurando o ambiente

##### Objetivo: Ter o ambiente para desenvolvimento para MSX configurado e funcionando.

Os templates para desenvolvimento para MSX foram originalmente concebidos para serem utilizados no MS Visual Studio, sob Windows. Com o tempo, eles evoluíram para serem utilizados com outros editores, IDEs e até sistemas operacionais. O uso com o Viual Studio automatiza a geração de novos projetos e o processo de compilação, mas tudo isso pode ser feito manualmente em outros ambientes.

Caso você pretenda utilizar o MS Visual Studio, comece o processo de instalação e configuração do seu ambiente pela seção 0.1 abaixo. Caso prefira utilizar outro editor/IDE, faça a instalação dessas ferramentas e salte para a seção 0.2.

### 0.1. Instalando o Visual Studio Community 2019

**Nota: APENAS PARA AQUELES QUE DESEJAM UTILIZAR O VISUAL STUDIO COMO AMBIENTE DE DESENVOLVIMENTO!**

1. Acesse https://visualstudio.microsoft.com/downloads/, faça o download do MS Visual Studio e inicie o processo de instalação.
	1. A versão Community é gratuita e suficiente.
2. **Durante o processo de instalação, instale um ou mais workloads (suporte à linguagens e plataformas). Essas extensões não são necessárias para compilar seus projetos MSX, mas o Visual Studio, aparentemente, tem dificuldades de encontrar os templates se wordloads não são instalados. Como sugestão, instale os ambientes de C++ e Jogos C++.**

### 0.2. Instalando o SDCC

1. Acesse http://sdcc.sourceforge.net/, faça o download do SDCC (Small Device C Compiler) e inicie o processo de instalação.
	1. Você pode precisar recompilar o SDCC a partir dos fontes se o binário para seu sistema operacional não estiver disponível. O processo não é complicado, entretanto.
	2. A compilação do SDCC depende do pacote "Build Essentials" no linux. O OSX já possui todas as dependências.
	3. Para garantir um processo de compilação mais rápido, configure a compilação com **make config** e remova os módulos que não lhe interessarem. Para o uso na compilação de MSX, apenas os módulos relacionados com o Z80 são necessários.
2. Após a instalação, garanta que você tem os executáveis sdcc.exe e sdasz80.exe no PATH do seu sistema operacional. Para testar isso, abra uma janela do terminal/shell/prompt de comando e digite **sdcc <enter>** e **sdasz80 <enter>**. Ao emitir esses comandos, mensagens desses programas devem aparecer na tela.

### 0.3. Instalando o HEX2BIN

1. Acesse http://hex2bin.sourceforge.net/, e faça o download do HEX2BIN.
2. O hex2bin não vem com pacote de instalação.
	1. No Windows, a forma mais fácil de "instalar" é extrair o executável hex2bin.exe do pacote de distribuição e movê-lo para a pasta onde seu sdcc.exe está localizado.
	2. No Linux e no OSX você provavelmente precisará compilar essas ferramentas (embora algumas pessoas reportaram para mim terem encontrados binários disponíveis para download). Nesse caso, faça download do codigo-fonte e o compile. É rápido e fácil.
3. Após a instalação, garanta que você tem o executável hex2bin.exe no PATH do seu sistema operacional. Para testar isso, abra uma janela do terminal/shell/prompt de comando e digite **hex2bin <enter>**. Ao emitir esse comando, uma mensagem do programa será exibida.

### 0.4. Instalando o PYTHON

1. Acesse https://www.python.org/, faça o download do pacote de instalação do PYTHON e inicie o processo de instalação.
2. Após a instalação, garanta que você tem o executável python.exe no PATH do seu sistema operacional. Para testar isso, abra uma janela do terminal/shell/prompt de comando e digite **python <enter>**. Ao emitir esse comando, uma mensagem do programa será exibida.

### 0.5. Preparando a estrutura de diretórios para seus projetos

1. Faça download do arquivo MSX.zip localizado em uma pinned message do canal templates-e-ide do Discord Server MSX Revamp.
	1. Esse arquivo contém, além da árvore de diretórios RECOMENDADA para o desenvolvimento de aplicações MSX, a biblioteca fusion-c e um projeto MSX de exemplo, 100% funcional.
2. Decompacte o arquivo no local apropriado no seu computador. Explore a estrutura.

### 0.6.a. Fazendo download dos templates de projetos MSX (VISUAL STUDIO)

1. Acesse https://github.com/DamnedAngel/MSX-Templates-for-VisualStudio/releases/tag/v00.05.00, desça até a seção **Assets** e faça download dos arquivos *.Template.zip .
2. Abra o Windows Explorer e navegue para a pasta **C:\Users\[User Name]\Documents\Visual Studio [Version]\Templates\ProjectTemplates\**. Caso seja necessário, crie os diretórios.
3. Copie os templates baixados para essa pasta.
4. Abra o Visual Studio, selecione a opção de criar um novo projeto e verifique se as opções de criar projetos MSX estão presentes.
	1. Em algumas instalações, por algum motivo o Visual Studio não consegue encontrar os templates. É um bug do Visual Studio. Se for esse seu caso, seguem algumas coisas que você pode tentar:
		1. Descompacte os templates cada um para um diretório específico. Em princípio, o Visual Studio consegue identificar templates compactados ou armazenados em diretórios. Em alguns casos o VS consegue encontrar apenas os templates em diretórios.
		2. Instale workloads diferentes no VS. Exsitem casos de ambientes nos quais o VS passou a enxergar os templates após instalação dos workloads de C++ e Jogos C++.
		3. Re-instale o Visual Studio. Sim, it sucks.
5. Para usar os templates, selecione o template desejado na tela de criação do projeto e siga as instruções.

### 0.6.b. Fazendo download dos templates de projetos MSX (OUTROS AMBIENTES QUE NÃO O VISUAL STUDIO)

1. Acesse https://github.com/DamnedAngel/MSX-Templates-for-VisualStudio/releases/tag/v00.05.00, desça até a seção **Assets** e faça download dos arquivos *.Application.zip.
2. Para usá-los, descompacte o template desejado nao diretório **projecs** da estrutura de desenvolvimento citada na seção 0.5 acima. Renomeie o diretório da solução para o que lhe interessar e pronto, seu projeto está pronto para ser evoluído.

### 0.7. instalando o emulador openMSX

1. Acesse https://openmsx.org/, faça download do instalador para o seu sistema operacional e inicie o processo de instalação.
2. Faça o download das ROMS MSX em http://www.msxarchive.nl/pub/msx/emulator/openMSX/systemroms.zip e o descompacte nas pastas abaixo:
	1. Linux e OSX: ~/.openMSX/share/systemroms
	2. Windows: C:\Users\your_user_name\My Documents\openMSX\share\systemroms
3. Faça o download da imagem de Hard Disk do Ricardo Pinheiro em https://we.tl/t-pHJk47w7Yj e a descompacte em algum lugar apropriado no seu HD.
4. Dispare o executável Catapult. Ele iniciará uma busca pelas ROMs disponíveis. Se ele não iniciar, force o processo na opção de menu File|Test MSX Hardware.
5. No interface principal do Catapult, selecione:
	1. Em MSX Type, o modelo Panasonic FS-A1GT.
	2. em Extensions, o módulo ide
6. Na caixa de texto Hard-Disk, selecione a imagem de HD baixada no item 3 acima.
7. Aperte o botão Start para inciar a emulação.


---

## Sessão 1: Criando e configurando o projeto

### 1.1. Pré-requisitos

##### Objetivo: REVISAR pré-requisitos para o workshop (previsão: 10 minutos).

* Para quem vai usar o Visual Studio:
	* VS Instalado.
	* Templates MSX para Visual Studio (https://github.com/DamnedAngel/MSX-Templates-for-VisualStudio) instalados no VS, conforme instruções em https://docs.google.com/document/d/1Y2rTTMBN08Au59e44pzdX0ptVWfLfMgG1gp2e-KUVIE/edit#.
* Para quem não vai usar o Visual Studio:
	* Templates MSX para uso SEM Visual Studio (https://github.com/DamnedAngel/MSX-Templates-for-VisualStudio) instalados no VS, conforme instruções em https://docs.google.com/document/d/1Y2rTTMBN08Au59e44pzdX0ptVWfLfMgG1gp2e-KUVIE/edit#.
* SDCC, Hex2Bin e Python instalados e configurados no PATH.
* Fusion-C baixada e descompactada.
* OpenMSX instalado e rodando.
* OpenMSX Debugger instalado e rodando.


### 1.2. Criando o projeto
###### *Github Ticket/Branch: 2/TKT0002.*
##### Objetivo: Dominar a criação de projetos MSX a partir dos templates (previsão: 10 minutos).

#### 1.2.a. Criando o projeto no Visual Studio
1. Clique no botão **Create a New Project** na janela de abertura do VS. Alternativamente, selecione **File|New|Project**.
2. Na lista de templates mostrada, selecione **MSX ROM Application** (caso queira fazer o projeto no formato MSX-DOS, escolha o template **MSX-DOS Application**. Provavelmente esse item estará no final da lista, então faça o scroll down.
3. Configure o nome da aplicação, a localização do projeto no seu disco (preferivelmente usar a pasta **projects** da estrutura de diretório estabelecida no roteiro de configuração do ambiente na sessão 0) e o nome da solução (a solução é um agregador de projetos).
4. Clique o botão **Create** e o VS criará seu projeto. Para ter certeza que o projeto foi criado corretamente, compile-o com **Build|Build Solution**. A tela de output deverá, ao final da compilação, mostrar a mensagem **"Rebuild All: 1 succeeded, 0 failed, 0 skipped"**.

#### 1.2.b. Criando o projeto fora do Visual Studio
1. Localize a pasta que você quer utilizar como base de seus projetos (preferivelmente usar a pasta **projects** da estrutura de diretório estabelecida no roteiro de configuração do ambiente na sessão 0);
2. Recomendo que seja criado um diretório nessa pasta que seria o similar ao diretório da "solução" no ambiente Visual Studio, para dentro dele ter o diretório do projeto. Mantendo esses dois diretórios permite não apenas ter projetos relacionados dentro de uma mesma solução, mas também manter os caminhos relativos até o diretório de bibliotecas. Você pode dar o nome que quiser para esse diretório.
3. Faça download ou copie o template **MSX.ROM.Application.zip** para o diretório estabelecido no item anterior.
4. Descompacte o arquivo observando os diretórios do zip. Ele gerará o diretório do projeto. Você pode renomear esse diretório para o nome que você quiser.
5. Abra os arquivos do projeto com seu editor ou IDE preferidos.

### 1.3. Compilando e rodando no OpenMSX
##### Objetivo: Executar programas MSX em desenvolvimento (previsão: 10 minutos).

1. Compilando o projeto ROM e rodando no OpenMSX.
2. Usando modo Release/Debug.
3. Escolhendo o template da rotina principal em C e em ASM (ApplicationSources.txt):
* msxromapp.c
* msxromapp.s


### 1.4. Configurando o projeto e explorando o template
###### *Github Ticket/Branch: 3/TKT0003.*
##### Objetivo: Compreender a estrutura do projeto MSX (previsão: 25 minutos).

1. Ajustando parâmetros em ApplicationSettings.txt.
2. Configurando nome da aplicação em TargetConfig_Debug.txt e TargetConfig_Release.txt.
3. Explorando os arquivos de configuração do projeto.
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
##### Objetivo: Compreender a estrutura do projeto MSX (previsão: 20 minutos).

*Nota: Salve e feche o projeto ROM antes de iniciar esse item.*

1. Criando um projeto MSXDOS + compilação e execução + configurações. 
2. Criando um projeto BIN + compilação e execução + configurações. 

### 1.6. Finalização da Sessão 1
##### Objetivo: Discutir os tópicos tratados e o modelo/dinâmica do workshop (previsão: 10 minutos).

1. Discussão geral da apresentação:
* Tópicos apresentados.
* Dinâmica geral do workshop: feedbacks e ideias.

---

## Sessão 2: Iniciando o programa

### 2.1. Integrando a biblioteca Fusion-C
###### *Github Ticket/Branch: 7/TKT0007.*

##### Objetivo: Entender a inclusão de bibliotecas externas ao projeto (previsão: 10 minutos).

1. Vamos primeiramente configurar o VDP para o modo que usaremos no jogo. Substitua o conteúdo da função main() por
```c
void main(void) {
	Screen(1);
	Width(32);
}
```
Tente compilar e você receberá um erro, já que as funções *Screen()* e *Width()* não estão disponíveis nativamente na linguagem C. A biblioteca Fusion-C as implementa, mas ainda não a integramos no projeto. Vamos então fazer isso, seguindo os passos abaixo.

2. Descomente a linha abaixo no arquivo IncludeDirectories.txt:
```
[MSX_LIB_PATH]\fusion-c\header
```
Isso fará os arquivos .h nesse diretório acessíveis por cláusulas *include*. Você poderá ter que adaptar o caminho caso tenha usado um diretório diferente na instalação da Fusion-C.

3. Adicione a linha abaixo no início do seu fonte *msxromapp.c*:
```c
#include "msx_fusion.h"
```
Isso importará todas as declarações de funções da Fusion-C. Se você não entende direito como arquivos header (*.h) funcionam em C, talvez este seja um bom momento de dar uma pesquisada rápida.

Note que o arquivo a msx_fusion.h contém a declaração da função, mas não a implementação (abra o arquivo e veja por você mesmo!). No próximo passo incluremos a implementação da função ao projeto.

4. Descomente a linha abaixo no arquivo Libraries.txt:
```
[MSX_LIB_PATH]\fusion-c\lib\fusion.lib
```
Com isso terminamos a inclusão da biblioteca no processo de compilação do projeto.

5. Compile o programa para se certificar que ele está funcional. Se quiser, teste-o no OpenMSX.

### 2.2. Criando o loop externo do programa
###### *Github Ticket/Branch: 6/TKT0006.*

##### Objetivo: Ter a inicialização e a lógica geral do fluxo da aplicação implementadas (previsão:15 minutos).

1. No arquivo *msxromapp.c*, remova todas as funções de exemplo de suporte a chamadas CALL do BASIC e a dispositivos depois do main():
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
**Note que a função Locate() é implementada pela biblioteca **Fusion-C**.*

3. Compile e execute o programa.

### 2.6. Finalização da Sessão 2
##### Objetivo: Discutir os tópicos tratados e o modelo/dinâmica do workshop (previsão: 15 minutos).

1. Lição de casa: ler o manual do TMS9118 (http://map.grauw.nl/resources/video/ti-vdp-programmers-guide.pdf), seções 7.1, 7.1.1 (7.1.2 não precisa), 8.1 inteira (8.1.1, 8.1.2 e 8.1.3).

2. Discussão geral da apresentação:
* Uso de bibliotecas em C.
* Fusion-C para desenvolvedores MSX-BASIC.
* Arquivos .c e arquivos .h.
* Constantes.
* O loop externo do programa.
* Dinâmica geral do workshop: feedbacks e ideias.

---

## Sess�o 3: Implementando a cobra - Parte 1

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

## Sess�o 4: Implementando a cobra - Parte 2

