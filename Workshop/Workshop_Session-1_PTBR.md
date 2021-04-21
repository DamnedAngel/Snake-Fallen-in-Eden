# Programando em C e ASM para MSX usando Visual Studio e Fusion-C
# Sessão 1: Usando Templates de Projetos

Escrito por **Danilo Angelo (a.k.a. Damned Angel)**, 2020-2021

Vídeo da sessão 1: https://youtu.be/TYXZTF-IzWs

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
* Um passo com o verbo no gerúndio (ex: *Compilando o projeto.*) significa uma exposição do palestrante (assista o vídeo no YouTube com a exposição em https://youtu.be/TYXZTF-IzWs)
* Um passo com o verbo no imperativo (ex: *Configure a aplicação*) denota um passo para ser executado pelo participante.
* Um passo com a descrição de uma atividade (ex: *Discussão em grupo.*) descreve a proposta de uma dinâmica.

Adicionalmente, note que os trechos de código fornecidos como exemplo muitas vezes contém um trecho já existente do programa, para referência de localização.

---

## Sessão 1: Criando e configurando o projeto

### 1.1. Pré-requisitos

##### Objetivo: REVISAR pré-requisitos para o workshop (previsão: 10 minutos).

* Para quem vai usar o Visual Studio:
	* VS Instalado.
	* Templates MSX para Visual Studio (https://github.com/DamnedAngel/MSX-Templates-for-VisualStudio) instalados no VS.
* Para quem não vai usar o Visual Studio:
	* Templates MSX para uso SEM Visual Studio (https://github.com/DamnedAngel/MSX-Templates-for-VisualStudio) baixados.
* SDCC, Hex2Bin e Python instalados e configurados no PATH.
* Fusion-C baixada e descompactada.
* OpenMSX instalado e rodando.
* OpenMSX Debugger instalado e rodando.

Se você não tem o ambiente de desenvolvimento configurado na sua máquina ainda, por favor veja o vídeo sobre o roteiro de configuração em https://youtu.be/RGDKg4krgFc.
**Não deixe de se inscrever no canal e dar like no vídeo!**


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
3. Faça download ou copie o template **MSX.ROM.Application.zip** baixado previamente para o diretório estabelecido no item anterior.
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
##### Objetivo: Experimentar a criação de outros projetos MSX e explorá-los (previsão: 20 minutos).

*Nota: Salve e feche o projeto ROM antes de iniciar esse item.*

1. Criando um projeto MSXDOS + compilação e execução + configurações. 
2. Criando um projeto BIN + compilação e execução + configurações. 

### 1.6. Finalização da Sessão 1
##### Objetivo: Discutir os tópicos tratados e o modelo/dinâmica do workshop (previsão: 10 minutos).

1. Discussão geral da apresentação:
* Tópicos apresentados.
* Dinâmica geral do workshop: feedbacks e ideias.

---

**Happy MSX'ing.**
