# Programando em C e ASM para MSX usando Visual Studio e Fusion-C

Escrito por Damned Angel, 2020

## Abrviações usadas nesse documento

VS: Visual Studio 2019


## Sessão 1: Criando e configurando o projeto

### 1.1. Pré-requisitos

1. VS Instalado.
2. Templates MSX (https://github.com/DamnedAngel/MSX-Templates-for-VisualStudio) instalado no VS, conforme instruções em https://docs.google.com/document/d/1Y2rTTMBN08Au59e44pzdX0ptVWfLfMgG1gp2e-KUVIE/edit#.
3. SDCC, Hex2Bin e Python instalados.
4. Fusion-C baixada e descompactada.


### 1.2. Criando o projeto
###### *Referências Github:*
* *Ticket: 2*
* *Branch: TKT0002.*
* *Diff: *

1. Clique no botão **Create a New Project** na janela de abertura do VS. Alternativamente, selecione **File|New|Project**.
2. Na lista de templates mostrada, selecione **MSX ROM Application** (caso queira fazer o projeto no formato MSX-DOS, escolha o template **MSX-DOS Application**. Provavelmente esse item estará no final da lista, então faça o scroll down.
3. Configure o nome da aplicação, a localização do projeto no seu disco e o nome da solução (a solução é um agregador de projetos).
4. Clique o botão **Create** e o VS criará seu projeto. Para ter certeza que o projeto foi criado corretamente, compile-o com **Build|Build Solution**. A tela de output deverá, ao final da compilação, mostrar a mensagem **"Rebuild All: 1 succeeded, 0 failed, 0 skipped"**.

### 1.3. Configurando o projeto e explorando o template
###### *Referências Github:*
* *Ticket: 3*
* *Branch: TKT0003.*
* *Diff: *

1. Ajustar parâmetros em ApplicationSettings.txt.
2. Configurar nome da aplicação em TargetConfig_Debug.txt e TargetConfig_Release.txt.
3. Revisar outros arquivos de configuração do projeto.
4. Explorando o projeto:
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
* 