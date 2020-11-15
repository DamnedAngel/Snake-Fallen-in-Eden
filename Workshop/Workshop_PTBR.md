# Programando em C e ASM para MSX usando Visual Studio e Fusion-C

Escrito por Damned Angel, 2020

## Abrvia��es usadas nesse documento

VS: Visual Studio 2019


## Sess�o 1: Criando e configurando o projeto

### 1.1. Pr�-requisitos

##### Objetivo: REVISAR pr�-requisitos para o workshop (previs�o: 10 minutos).

1. VS Instalado.
2. Templates MSX (https://github.com/DamnedAngel/MSX-Templates-for-VisualStudio) instalados no VS, conforme instru��es em https://docs.google.com/document/d/1Y2rTTMBN08Au59e44pzdX0ptVWfLfMgG1gp2e-KUVIE/edit#.
3. SDCC, Hex2Bin e Python instalados e configurados no PATH.
4. Fusion-C baixada e descompactada.
5. OpenMSX instalado e rodando. Seguir roteiro do Lavadeira em:
* Parte 1: https://medium.com/relearning-msx/relearning-msx-5-setting-up-the-msx-c-environment-part-1-797d14e03a1d
* Parte 2: https://medium.com/relearning-msx/relearning-msx-6-7a5d8e3ef6a3
* Demais partes s�o interessantes, mas opcionais. O que precisamos � de um OpenMSX rodando MSXDOS para o caso de desenvolvimento para esse ambiente.
6. OpenMSX Debugger instalado e rodando.


### 1.2. Criando o projeto
###### *Github's Ticket/Branch: 2/TKT0002.*
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
###### *Github's Ticket/Branch: 3/TKT0003.*
##### Objetivo: Compreender a estrutura do projeto MSX (previs�o: 25 minutos).

1. Ajustando par�metros em ApplicationSettings.txt.
2. Configurando nome da aplica��o em TargetConfig_Debug.txt e TargetConfig_Release.txt.
3. Arquivos de configura��o do projeto.
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

*Nota: Salvar e fechar projeto ROM antes de iniciar esse item.*

1. Criando um projeto MSXDOS + compila��o e execu��o + configura��es. 
2. Criando um projeto BIN + compila��o e execu��o + configura��es. 


### 1.6. Consertando a inicializa��o de vari�veis globais do C
###### *Github's Ticket/Branch: 4/TKT0004.*
##### Objetivo: Resolver um Bug do template ROM que afetar� as demais sess�es do Workshop (previs�o: 5 minutos).

*Nota: Reabrir o projeto ROM antes de iniciar esse item.*

1. Inserir linha **call gsinit** depois da linha **init::**.

Nota: Isso � um bug no template. Ser� consertado em vers�es futuras.

### 1.7. Finaliza��o da Sess�o 1
##### Objetivo: Discutir os t�picos tratados e o modelo/din�mica do workshop (previs�o: 10 minutos).

1. T�picos apresentados.
2. Din�mica geral do workshop: feedbacks e ideias.

