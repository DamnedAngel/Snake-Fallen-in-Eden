# Programando em C e ASM para MSX usando Visual Studio e Fusion-C
# Sessão 7: O movimento constante da cobra.

Escrito por **Danilo Angelo (a.k.a. Damned Angel)**, 2020-2021

Vídeo da sessão 6: XXX

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

# Sessão 7: O movimento constante da cobra.

### 7.1. Mostrando as telas Iniciais e de Game Over corretamente.
###### *Github Ticket/Branch: XX/TKT00XX.*

##### Objetivo: Aguardar o jogador parar de dar comandos antes de apagar as telas Iniciais e de Game Over (previsão: 10 minutos).

1. Crie uma variável inteira, sem sinal e de 16 bits para controlar o progresso do *Jiffy* chamada *lastJiffy*. No final de loop, grave o último *Jiffy* detectado na variável.
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


### 7.X. Finalização da Sessão 7
##### Objetivo: Discutir os tópicos tratados e o modelo/dinâmica do workshop (previsão: 10 minutos).

1. Discussão geral da apresentação:
* XXX
* YYY
* ZZZ
* Dinâmica geral do workshop: feedbacks e ideias.

---

**Happy MSX'ing.**
