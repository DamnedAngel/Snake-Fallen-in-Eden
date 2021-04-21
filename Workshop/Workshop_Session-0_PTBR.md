# Programando em C e ASM para MSX usando Visual Studio e Fusion-C
# Sessão 0: Configurando o Ambiente de Desenvolvimento

Escrito por **Danilo Angelo (a.k.a. Damned Angel)**, 2020-2021

Vídeo da sessão 0: https://youtu.be/RGDKg4krgFc

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

Long live **MSX**!

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

## Sessão 0: Configurando o ambiente

##### Objetivo: Ter o ambiente para desenvolvimento para MSX configurado e funcionando.

Os templates para desenvolvimento para MSX foram originalmente concebidos para serem utilizados no MS Visual Studio, sob Windows. Com o tempo, eles evoluíram para serem ustilizados com outros editores, IDEs e até sistemas operacionais. O uso com o Viual Studio automatiza a geração de novos projetos e o processo de compilação, mas tudo isso pode ser feito manualmente em outros ambientes.

Caso você pretenda utilizar o MS Visual Studio, comece o processo de instalação e configuração do seu ambiente pela seção 0.1 abaixo. Caso prefira utilizar outro editor/IDE, faça a instalação dessas ferramentas e salte para a seção 0.2.

### 0.1. Instalando o Visual Studio Community 2019

**Nota: APENAS PARA AQUELES QUE DESEJAM UTILIZAR O VISUAL STUDIO COMO AMBIENTE DE DESENVOLVIMENTO!**

1. Acesse https://visualstudio.microsoft.com/downloads/, faça o download do **MS Visual Studio** e inicie o processo de instalação.
	1. A versão Community é gratuita e suficiente.
2. **Durante o processo de instalação, instale um ou mais workloads (suporte à linguagens e plataformas).** Essas extensões **não** são necessárias para compilar seus projetos MSX, mas o Visual Studio, aparentemente, tem dificuldades de encontrar os templates se wordloads não são instalados. Como sugestão, instale os ambientes de C++ e Jogos C++.

### 0.2. Instalando o SDCC

1. Acesse http://sdcc.sourceforge.net/, faça o download do **SDCC** (Small Device C Compiler) e inicie o processo de instalação.
	1. Você pode precisar recompilar o SDCC a partir dos fontes se o binário para seu sistema operacional não estiver disponível. O processo não é complicado, entretanto.
	2. A compilação do SDCC depende do pacote "Build Essentials" no linux. O OSX já possui todas as dependências.
	3. Para garantir um processo de compilação mais rápido, configure a compilação com **./configure** e remova os módulos que não lhe interessarem. Para o uso na compilação de MSX, apenas os módulos relacionados com o Z80 são necessários. Você pode usar o modo iterativo ou **./configure CPPFLAGS=-I/opt/homebrew/Cellar/boost/1.75.0_2/include --disable-mcs51-port --disable-z180-port --disable-r2k-port --disable-r2ka-port --disable-r3ka-port --disable-tlcs90-port --disable-ds390-port --disable-ds400-port --disable-pic14-port --disable-pic16-port --disable-hc08-port --disable-s08-port --disable-stm8-port --disable-pdk13-port --disable-pdk14-port --disable-pdk15-port --enable-pdk16-port**

2. Após a instalação, garanta que você tem os executáveis **sdcc.exe** e **sdasz80.exe** no PATH do seu sistema operacional. Para testar isso, abra uma janela do terminal/shell/prompt de comando e digite **sdcc \<enter\>** e **sdasz80 \<enter\>**. Ao emitir esses comandos, mensagens desses programas devem aparecer na tela.

### 0.3. Instalando o HEX2BIN

1. Acesse http://hex2bin.sourceforge.net/, e faça o download do **HEX2BIN**.
2. O hex2bin não vem com pacote de instalação.
	1. No Windows, a forma mais fácil de "instalar" é extrair o executável hex2bin.exe do pacote de distribuição e movê-lo para a pasta onde seu sdcc.exe está localizado.
	2. No Linux e no OSX você provavelmente precisará compilar essas ferramentas (embora algumas pessoas reportaram para mim terem encontrados binários disponíveis para download). Nesse caso, faça download do codigo-fonte e o compile. É rápido e fácil.
3. Após a instalação, garanta que você tem o executável **hex2bin.exe** no PATH do seu sistema operacional. Para testar isso, abra uma janela do terminal/shell/prompt de comando e digite **hex2bin \<enter\>**. Ao emitir esse comando, uma mensagem do programa será exibida.

### 0.4. Instalando o PYTHON

1. Acesse https://www.python.org/, faça o download do pacote de instalação do **PYTHON** e inicie o processo de instalação.
2. Após a instalação, garanta que você tem o executável **python.exe** no PATH do seu sistema operacional. Para testar isso, abra uma janela do terminal/shell/prompt de comando e digite **python \<enter\>**. Ao emitir esse comando, uma mensagem do programa será exibida.

### 0.5. Preparando a estrutura de diretórios para seus projetos

1. Faça download do arquivo MSX.zip localizado em uma pinned message do canal **#workshop-sessão-0** do Discord Server MSX Revamp ou em https://angelo.eng.br/msx/danilo/workshop/session0/msx.zip
	1. Esse arquivo contém, além da árvore de diretórios **recomendada** para o desenvolvimento de aplicações MSX, a biblioteca fusion-c e um projeto MSX de exemplo, 100% funcional.
2. Decompacte o arquivo no local apropriado no seu computador. Explore a estrutura.

### 0.6.a. Fazendo download dos templates de projetos MSX (VISUAL STUDIO)

1. Acesse https://github.com/DamnedAngel/MSX-Templates-for-VisualStudio/releases/tag/v00.05.00, desça até a seção **Assets** e faça download dos arquivos **[tipo do template].Template.zip**.
2. Abra o Windows Explorer e navegue para a pasta **C:\Users\[User Name]\Documents\Visual Studio [Version]\Templates\ProjectTemplates**. Caso seja necessário, crie os diretórios.
3. Copie os templates baixados para essa pasta.
4. Abra o Visual Studio, selecione a opção de criar um novo projeto e verifique se as opções de criar projetos MSX estão presentes.
	1. Em algumas instalações, por algum motivo o Visual Studio não consegue encontrar os templates. É um bug do Visual Studio. Se for esse seu caso, seguem algumas coisas que você pode tentar:
		1. Descompacte os templates cada um para um diretório específico. Em princípio, o Visual Studio consegue identificar templates compactados ou armazenados em diretórios. Em alguns casos o VS consegue encontrar apenas os templates em diretórios.
		2. Instale workloads diferentes no VS. Exsitem casos de ambientes nos quais o VS passou a enxergar os templates após instalação dos workloads de C++ e Jogos C++.
		3. Re-instale o Visual Studio. **Sim, it sucks**.
5. Para usar os templates, selecione o template desejado na tela de criação do projeto e siga as instruções.

### 0.6.b. Fazendo download dos templates de projetos MSX (OUTROS AMBIENTES QUE NÃO O VISUAL STUDIO)

1. Acesse https://github.com/DamnedAngel/MSX-Templates-for-VisualStudio/releases, desça até a seção **Assets** e faça download dos arquivos **[tipo do template].Application.zip** .
2. Para usá-los, descompacte o template desejado nao diretório **projects** da estrutura de desenvolvimento citada na seção 0.5 acima. Renomeie o diretório da solução para o que lhe interessar e pronto, seu projeto está pronto para ser evoluído.

### 0.7. instalando o emulador openMSX

1. Acesse https://openmsx.org/, faça download do instalador para o seu sistema operacional e inicie o processo de instalação.
2. Faça o download das ROMS MSX em https://angelo.eng.br/msx/danilo/workshop/session0/systemroms.zip e o descompacte nas pastas abaixo:
	1. Linux e OSX: **~/.openMSX/share/systemroms**
	2. Windows: **C:\Users\your_user_name\My Documents\openMSX\share\systemroms**
3. Faça o download da imagem de Hard Disk do Ricardo Pinheiro em https://angelo.eng.br/msx/danilo/workshop/session0/msxdisk.zip e a descompacte em algum lugar apropriado no seu HD.
4. Dispare o executável **Catapult**. Ele iniciará uma busca pelas ROMs disponíveis. Se ele não iniciar, force o processo na opção de menu **File|Test MSX Hardware**.
5. No interface principal do **Catapult**, selecione:
	1. Em **MSX Type**, o modelo **Panasonic FS-A1GT**.
	2. em **Extensions**, o módulo **ide**
6. Na caixa de texto **Hard-Disk**, selecione a imagem de HD baixada no item 3 acima.
7. Aperte o botão **Start** para inciar a emulação.

---

**Happy MSX'ing.**
