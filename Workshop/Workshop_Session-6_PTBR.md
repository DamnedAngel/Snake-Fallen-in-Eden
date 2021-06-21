# Programando em C e ASM para MSX usando Visual Studio e Fusion-C
# Sessão 6: Interrupções e temporização do jogo.

Escrito por **Danilo Angelo (a.k.a. Damned Angel)**, 2020-2021

Vídeo da sessão 6: https://youtu.be/63QhovTHOYQ

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
* Um passo com o verbo no gerúndio (ex: *Compilando o projeto.*) significa uma exposição do palestrante (assista o vídeo no YouTube com a exposição em https://youtu.be/63QhovTHOYQ).
* Um passo com o verbo no imperativo (ex: *Configure a aplicação*) denota um passo para ser executado pelo participante.
* Um passo com a descrição de uma atividade (ex: *Discussão em grupo.*) descreve a proposta de uma dinâmica.

Adicionalmente, note que os trechos de código fornecidos como exemplo muitas vezes contém um trecho já existente do programa, para referência de localização.

---

# Sessão 6: Interrupções e temporização do jogo.

### 6.1. Controlando a cadência do jogo.
###### *Github Ticket/Branch: 16/TKT0016.*

##### Objetivo: Controlar a velocidade o jogo através do sistema de interrupções do MSX (previsão: 60 minutos).

1. Entendendo o básico de interrupções no MSX.
* [VDP] A interrupção VBlank do TMS9918.
* [Z80] O tratamento de interrupções no Z80.
* [Arquitetura MSX] Hooks e, em particular, o Hook H.TIMI (FD9Fh).

Referências:
* TMS9918 (Texas): http://map.grauw.nl/resources/video/ti-vdp-programmers-guide.pdf (inglês).
* Interrupções no Z80 (Grauw): http://map.grauw.nl/articles/interrupts.php (inglês).
* Interrupções no Z80 (MSX Inside): https://www.youtube.com/watch?v=dJymuMfgw9I (espanhol).
* Interrupções vBlank (MSX Inside): https://www.youtube.com/watch?v=aUkHk_mjtOU (espanhol).
* Hooks: https://www.msx.org/wiki/System_hooks (inglês).
* Muito de tudo acima: http://www.msxtop.msxall.com/Portugues/Projeto_msx_top_secret.htm (português).

2. Comparando quatro estratégias de temporização:

	2.1. **[Z80] Rotinas de tratamento de interrupção**

	* Vantagens
		* *Execução mais rápida possível ("O que vc não precisa, se você está usando C" - Grauw).*
		* Não trava o processador enquanto a interrupção não acontecer.
	* Desvantagens:
		* "Bypass" da BIOS;
		* Demanda instalação de rotinas de tratamento de interrupção e identificação do dispositivo que gerou a interrupção.

	2.2. **[Z80] A Instrução Halt do Z80**
    
	* Vantagens:
		* *Implementação mais simples possível.*
  		* Não faz "Bypass" da BIOS;
  		* Não demanda instalação de rotinas de tratamento de interrupção nem de hook.
	* Desvantagem:
    	* Trava o processador enquanto a interrupção não acontecer.
        
	2.3. **[Arquitetura MSX] O Hook H.TIMI (FD9Fh)**
    
	* Vantagens:
		* *Forma recomendada pelo padrão.*
		* Não faz "Bypass" da BIOS;
		* Não trava o processador enquanto a interrupção não acontecer.
	* Desvantagem:
		* Demanda instalação de rotinas de tratamento de hook.
	
    2.4. **[Arquitetura MSX] A variável Jiffy**
	
	* Vantagens:
		* *Estratégia que demanda o menor domínio sobre interrupções.*
		* Não faz "Bypass" da BIOS;
		* Não trava o processador enquanto a interrupção não acontecer;
		* Não demanda instalação de rotinas de tratamento de interrupção nem de hook;
		* Já fornece um contador confiável de frames.
	* Desvantagem:
		* **Funciona bem, mas é o mais próximo que existe de uma gambiarra.**

3. Explorando o suporte da Fusion-C para o tratamento de interrupções
* [Fusion-C] Suporte a rotinas de tratamento de interrupção;

4. Crie uma variável inteira, sem sinal e de 16 bits para controlar o progresso do *Jiffy* chamada *lastJiffy*. No final de loop, grave o último *Jiffy* detectado na variável.
```c
unsigned char content;
unsigned int lastJiffy;
```
```c
	// Game's main loop
	while (!EoG) {

		...

		lastJiffy = Peekw(BIOS_JIFFY);
	}
```

5. No início do loop do jogo aguarde até a BIOS mudar o valor do *Jiffy*.
```c
	// Game's main loop
	while (!EoG) {
		while (lastJiffy == Peekw(BIOS_JIFFY)) {}
		// from this point on, 1 pass per frame

		...

		lastJiffy = Peekw(BIOS_JIFFY);
	}
```

6. Apenas para manter nossa lembrança, vamos colocar um comentário no final do loop de jogo, agora sincronizado a 1 execução por frame, que ali futuramente colocaremos nossa rotina simples de geração dos sons:

```c
		Locate(x, y);
		print("*");

		// here we will add the sound effects routine
		{
		}

		lastJiffy = Peekw(BIOS_JIFFY);
```
7. Compile e rode o programa. O que houve?

8. Agora, para movimentar a cabeça da cobra, vamos colocar uma velocidade inicial de 4 posições por segundo. Assim, supondo NTSC e PAL-M com 60 frames por segundo, vamos aguardar o Jiffy chegar a 15 para executar a movimentação e, em seguida, zeramos essa variável para outro ciclo. Lembre-se que o bloco de efeitos sonoros deve ser executado a cada frame.
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

9. Compile e rode o programa. E agora, o que houve?

### 6.2. Finalização da Sessão 6
##### Objetivo: Discutir os tópicos tratados e o modelo/dinâmica do workshop (previsão: 10 minutos).

1. Discussão geral da apresentação:
* Interrupções, temporização, *Jiffy*.
* Os vários loops internos do programa para controle de temporização.
* Dinâmica geral do workshop: feedbacks e ideias.

---

**Happy MSX'ing.**
