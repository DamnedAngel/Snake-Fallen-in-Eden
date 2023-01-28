# Programando em C e ASM para MSX usando Visual Studio e Fusion-C
# Sessão 17: Sprites!

Escrito por **Danilo Angelo (a.k.a. Damned Angel)**, 2020-2021

Vídeo da sessão 17: XXX

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

# Sessão 17: Sprites!

### 16.1. Resolver o problema de padrões de sprites errados no MSX1.
###### *Github Ticket/Branch: 61/TKT0061 (continuação).*

##### Objetivo: Resolver o problema de padrões de sprites errados no MSX1 (previsão: 90 minutos).

1. Compile o projeto como estava no final da sessão anterior e execute (no Turbo-R!!!) o jogo para ver o efeito correto.

2. Agora execute o jogo no Hotbit. O que houve? Você Reconhece os desenhos?

3. Explorando o problema de escrita no registro 14 do VDP.
- Endereçamento da VRAM.
- Implementação do Vpeek + VpeekFirst + VDPwriteNi.
- Consequência no VDP do MSX1.

4. Corrija o problema encontrado, consertando o endereço da tabela de padrões de sprite:
```c
void buildSprites() {
	VDPwriteNi(6, SPRITEPATTERNTABLE >> 11);
```
```c
		lastJiffy = Peekw(BIOS_JIFFY);
		VDPwriteNi(6, SPRITEPATTERNTABLE >> 11);
	}
```

### 17.1. Correção de bugs da Fusion-C.
###### *Github Ticket/Branch: 61/TKT0061.*

##### Objetivo: implementar montagem de sprites de forma correta e compatível com quaisquer VDPs do MSX (previsão: 90 minutos).

1. **DESAFIO**: Implemente *BuildSprites()* com uma única chamada à *SetSpritePattern()*:
```c
void buildSprites() {
	SpriteReset();
	Sprite8();
	SpriteSmall();

	/*
	// Alternative 1: Fusion-C Style
	for (unsigned char i = 0; i < sizeof(sprite_patterns)/8; i++) {
		SetSpritePattern(i, sprite_patterns + (i * 8), 8);
	}
	*/

	// Alternative 2
	SetSpritePattern(0, sprite_patterns, sizeof(sprite_patterns));
}
``` 

2. Compile e execute o jogo no Turbo-R. O que houve?

3. Execute o jogo no Hotbit. O que houve?

4. Explorando o problema de Velocidade de transferência no MSX1.
- Implementação do SetSpritePattern + Outports + OTIR.
- Consequência no VDP do MSX1.

5. **DESAFIO**: Corrija o problema encontrado, Implementando *BuildSprites()* com *blockToRAM()*:
```c
void buildSprites() {
	VDPwriteNi(6, SPRITEPATTERNTABLE >> 11);
	SpriteReset();
	Sprite8();
	SpriteSmall();

	*/
	// Alternative 1: BASIC Style
	for (unsigned char i = 0; i < sizeof(sprite_patterns)/8; i++) {
		SetSpritePattern(i, sprite_patterns + (i * 8), 8);
	}
	*/

	// Alternative 2
	//SetSpritePattern(0, sprite_patterns, sizeof(sprite_patterns));

	// Alternative 3
	blockToVRAM(SPRITEPATTERNTABLE, sprite_patterns, sizeof(sprite_patterns));
}
```

### 17.2. Finalização da Sessão 17
##### Objetivo: Discutir os tópicos tratados e o modelo/dinâmica do workshop (previsão: 10 minutos).

1. Discussão geral da apresentação:
* Sprites
* Estado do jogo
* Dinâmica geral do workshop: feedbacks e ideias.

---

**Happy MSX'ing.**
