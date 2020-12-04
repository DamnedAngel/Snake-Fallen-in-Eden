# Programando em C e ASM para MSX usando Visual Studio e Fusion-C

Escrito por Damned Angel, 2020

## Abreviações usadas nesse documento

VS: Visual Studio 2019

---

## Sessão 1: Criando e configurando o projeto

### 1.1. Pré-requisitos

##### Objetivo: REVISAR pré-requisitos para o workshop (previsão: 10 minutos).

1. VS Instalado.
2. Templates MSX (https://github.com/DamnedAngel/MSX-Templates-for-VisualStudio) instalados no VS, conforme instruções em https://docs.google.com/document/d/1Y2rTTMBN08Au59e44pzdX0ptVWfLfMgG1gp2e-KUVIE/edit#.
3. SDCC, Hex2Bin e Python instalados e configurados no PATH.
4. Fusion-C baixada e descompactada.
5. OpenMSX instalado e rodando. Seguir roteiro do Lavadeira em:
* Parte 1: https://medium.com/relearning-msx/relearning-msx-5-setting-up-the-msx-c-environment-part-1-797d14e03a1d
* Parte 2: https://medium.com/relearning-msx/relearning-msx-6-7a5d8e3ef6a3
* Demais partes são interessantes, mas opcionais. O que precisamos é de um OpenMSX rodando MSXDOS para o caso de desenvolvimento para esse ambiente.
6. OpenMSX Debugger instalado e rodando.


### 1.2. Criando o projeto
###### *Github Ticket/Branch: 2/TKT0002.*
##### Objetivo: Dominar a criação de projetos MSX a partir dos templates (previsão: 10 minutos).

1. Clique no botão **Create a New Project** na janela de abertura do VS. Alternativamente, selecione **File|New|Project**.
2. Na lista de templates mostrada, selecione **MSX ROM Application** (caso queira fazer o projeto no formato MSX-DOS, escolha o template **MSX-DOS Application**. Provavelmente esse item estará no final da lista, então faça o scroll down.
3. Configure o nome da aplicação, a localização do projeto no seu disco e o nome da solução (a solução é um agregador de projetos).
4. Clique o botão **Create** e o VS criará seu projeto. Para ter certeza que o projeto foi criado corretamente, compile-o com **Build|Build Solution**. A tela de output deverá, ao final da compilação, mostrar a mensagem **"Rebuild All: 1 succeeded, 0 failed, 0 skipped"**.

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
3. Arquivos de configuração do projeto.
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

*Nota: Salvar e fechar projeto ROM antes de iniciar esse item.*

1. Criando um projeto MSXDOS + compilação e execução + configurações. 
2. Criando um projeto BIN + compilação e execução + configurações. 


### 1.6. Consertando a inicialização de variáveis globais do C
###### *Github Ticket/Branch: 4/TKT0004.*
##### Objetivo: Resolver um Bug do template ROM que afetará as demais sessões do Workshop (previsão: 5 minutos).

*Nota: Reabrir o projeto ROM antes de iniciar esse item.*

1. Inserir linha **call gsinit** depois da linha **init::**.

Nota: Isso é um bug no template. Será consertado em versões futuras.

### 1.7. Finalização da Sessão 1
##### Objetivo: Discutir os tópicos tratados e o modelo/dinâmica do workshop (previsão: 10 minutos).

1. Tópicos apresentados.
2. Dinâmica geral do workshop: feedbacks e ideias.

---

## Sessão 2: Iniciando o programa

### 2.1. Integrando a bibliotec Fusion-C
###### *Github Ticket/Branch: 7/TKT0007.*

##### Objetivo: Entender a inclusão de bibliotecas externas ao projeto (previsão: 10 minutos).

1. Substitua o conteúdo da função main() por
```c
void main(void) {
	Screen(1);
}
```
Tente compilar e você receberá um erro, já que a função *Screen* é implementada pela Fusion-C, e não está disponível nativamente. Vamos então integrar a biblioteca ao projeto seguindo os passos abaixo.

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
