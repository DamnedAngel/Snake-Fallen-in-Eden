# Programando em C e ASM para MSX usando Visual Studio e Fusion-C
# Sessão 2: Iniciando o desenvolvimento do jogo

Escrito por **Danilo Angelo (a.k.a. Damned Angel)**, 2020-2021

Vídeo da sessão 2: https://youtu.be/BNeZ2RBIkuc

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
* Um passo com o verbo no gerúndio (ex: *Compilando o projeto.*) significa uma exposição do palestrante (assista o vídeo no YouTube com a exposição em https://youtu.be/BNeZ2RBIkuc)
* Um passo com o verbo no imperativo (ex: *Configure a aplicação*) denota um passo para ser executado pelo participante.
* Um passo com a descrição de uma atividade (ex: *Discussão em grupo.*) descreve a proposta de uma dinâmica.

Adicionalmente, note que os trechos de código fornecidos como exemplo muitas vezes contém um trecho já existente do programa, para referência de localização.

---

## Sessão 2: Iniciando o programa

### 2.1. Integrando a biblioteca Fusion-C
###### *Github Ticket/Branch: 7/TKT0007.*

##### Objetivo: Entender a inclusão de bibliotecas externas ao projeto; familiarizar-se com a Fusion-C (previsão: 15 minutos).

1. Explorando a Fusion-C: revisando o header *msx_fusion.h*.

Note que o arquivo *msx_fusion.h* contém a declaração da função, mas não a implementação (abra o arquivo e veja por você mesmo!).

Se você nunca trabalhou com arquivos header (\*.h), não é esperado que nesse ponto você entenda completamente o conceito. Faça uma anotação para pesquisar o tópico depois do workshop.

Referência: **C Para Leigos, Davis**, *Stephen R.*

2. Vamos primeiramente configurar o VDP para o modo que usaremos no jogo. No arquivo *msxromapp.c*, substitua o conteúdo da função main() por
```c
void main(void) {
	Screen(1);
	Width(32);
	
	print("Oi!\0");
}
```
Tente compilar e você receberá um erro, já que as funções *Screen()* e *Width()* não estão disponíveis nativamente na linguagem C. A biblioteca Fusion-C as implementa, mas ainda não a integramos no projeto. Vamos então fazer isso, seguindo os passos abaixo.

3. Adicione a linha abaixo no início do seu fonte *msxromapp.c*:
```c
#include "msx_fusion.h"
```
Isso instruirá ao compilador para considerar todas os símbolos (funcões, variáveis, estruturas etc.) do header.

Tente compilar. O que houve?

4. Descomente a linha abaixo no arquivo *IncludeDirectories.txt*:
```
[MSX_LIB_PATH]\fusion-c\header
```
Isso fará os arquivos .h nesse diretório acessíveis por cláusulas *include*. Você poderá ter que adaptar o caminho caso tenha usado um diretório diferente na instalação da Fusion-C.

Tente compilar. O que houve?

5. No próximo passo incluremos a implementação da função ao projeto. Descomente a linha abaixo no arquivo *Libraries.txt*:
```
[MSX_LIB_PATH]\fusion-c\lib\fusion.lib
```

Tente compilar. O que houve?

Com isso terminamos a inclusão da biblioteca no processo de compilação do projeto.

6. Teste seu programa no OpenMSX.

### 2.2. Criando o loop externo do programa
###### *Github Ticket/Branch: 6/TKT0006.*

##### Objetivo: Ter a inicialização e a lógica geral do fluxo da aplicação implementadas (previsão:15 minutos).

1. Primeiramente, vamos "limpar" o template, removendo funcionalidades que não precisaremos. No arquivo *msxromapp.c*, remova todas as funções de exemplo de suporte a chamadas CALL do BASIC e a dispositivos depois do main():
* onCall*
* onDevice*

Tente compilar. O que houve?

2. Como removemos as rotinas de exemplo de extensão do CALL e de DEVICES, precisamos configurar o projeto para não incluir o suporte a essas extensões. Altere os seguintes parâmetros, em *ApplicationSettings.txt* para **OFF**:
```c
CALL_EXPANSION			_OFF						; _ON: expands BASIC's CALL instruction; _OFF: Don't expand
DEVICE_EXPANSION		_OFF						; _ON: creates BASIC's device; _OFF: Don't create
```

Tente compilar. O que houve?

2. No mesmo arquivo, crie stubs para as funções de exibição de título do jogo, da lógica de jogo e da exibição da tela de fim de jogo:
```c
void title() {
	Cls();
	print ("My Snake Game\0");
	InputChar();
}

void game() {
	Cls();
	print ("Game\0");
	InputChar();
}

void gameOver() {
	Cls();
	print ("Game Over\0");
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

### 2.3. Finalização da Sessão 2
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
