# Programando em C e ASM para MSX usando Visual Studio e Fusion-C
# Sessão 10: Joysticks, Édens de dificuldade e uma fonte diferenciada.

Escrito por **Danilo Angelo (a.k.a. Damned Angel)**, 2020-2021

Vídeo da sessão 10: https://youtu.be/M4LeT1-IxwY

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
* Um passo com o verbo no gerúndio (ex: *Compilando o projeto.*) significa uma exposição do palestrante (assista o vídeo no YouTube com a exposição em https://youtu.be/M4LeT1-IxwY)
* Um passo com o verbo no imperativo (ex: *Configure a aplicação*) denota um passo para ser executado pelo participante.
* Um passo com a descrição de uma atividade (ex: *Discussão em grupo.*) descreve a proposta de uma dinâmica.

Adicionalmente, note que os trechos de código fornecidos como exemplo muitas vezes contém um trecho já existente do programa, para referência de localização.

---

# Sessão 10: Joysticks, Édens de dificuldade e uma fonte diferenciada.

### 10.1. Consertar a espera pela liberação das teclas.
###### *Github Ticket/Branch: 32/TKT0032.*

##### Objetivo: Impedir a mudança de telas Game Over -> Abertura -> Jogos se o jogador estiver com alguma tecla ininterruptamente apertada (previsão: 15 minutos).

1. Entendo o problema atual: Por que o programa não está aguardando as teclas serem soltas?
- Diferença de tratamento entre teclado e joysticks.
- A dualidade das setas e barra de espaço.

2. **DESAFIO**: Sem olhar a resposta abaixo e com base na discussão sobre as abstrações da BIOS de teclado e joysticks, resolva o problema identificado.

```c
*** Resposta ao desafio somente no roteiro pós-sessão. ***
```

### 10.2. Implementando suporte a Joysticks.
###### *Github Ticket/Branch: 37/TKT0037.*

##### Objetivo: Permitir que o jogador controle a cobra pelo teclado ou por qualquer uma das portas de joystick (previsão: 30 minutos).

1. Definindo as mecânica de uso de múltiplos joysticks:
- Não colocaremos opção de seleção de joysticks. Todos funcionarão durante o jogo, de forma priorizada.
- Setas terão prioridade sobre o Joystick 1. Ambos terão prioridade sobre o Joystick 2.
- Os botões dos Joysticks e a barra de espaço terão funcionalidades idênticas, sem diferença de prioridades.
- Ou seja:
  - Qualquer botão de joystick apertado ou a barra de espaço pressionada contarão como disparo de gatilho (servirá para mudança de tela).
  - Se algum comando das setas estiver sendo dado, use esse comando.
  - Senão, se algum comando no Joystick 1 estiver sendo dado, use esse comando.
  - Senão, use quaisquer comandos do Joystick 2 (ou nenhum, se não houver).


2. **DESAFIO**: Sem olhar a resposta abaixo, crie a função *allJoysticks* sem parâmetros que retorna comandos conforme a estratégia estabelecida acima.

```c
*** Resposta ao desafio somente no roteiro pós-sessão. ***
```

3. **DESAFIO**: Similarmente, sem olhar a resposta abaixo crie a função *allTriggers* sem parâmetros que retorna um comando de gatilho se qualquer botão de joystick estiver apertado ou se a barra de espaço estiver apertada.

```c
*** Resposta ao desafio somente no roteiro pós-sessão. ***
```

4. Substitua *JoystickRead()* por *allJoysticks()* na atribuição a variável *joy*.

```c
		while (lastJiffy == Peekw(BIOS_JIFFY)) {
			joy = allJoysticks();
```

5. Compile e rode o programa. Como testar?

6. **DESAFIO**: Sem olhar a resposta abaixo, altere os testes de entradas do jogador nas funções *title()* e *gameOver()* para aceitarem comandos de teclas ou gatilhos para trocar de tela:

```c
*** Resposta ao desafio somente no roteiro pós-sessão. ***
```

5. Compile e rode o programa.

### 10.3. Aumentando a dificuldade.
###### *Github Ticket/Branch: 33/TKT0033.*

##### Objetivo: Aumentar progressivamente a dificuldade do jogo, mapeada na transição entre "Édens"/níveis (previsão: 30 minutos).

1. Definindo a mecânica de progressão de dificuldade:
- A cada 100 movimentações da cobra, a cobra transiciona para o próximo Éden (aumenta o nível);
- A cada progressão de Éden, a espera para o próximo passo da cobra diminui em 1 frame (ou seja, aumenta a velocidade de movimentação da cobra).

2. Crie a variável *waitFrames* para controlar o número de frames a serem aguardados antes de movimentar a cobra:

```c
unsigned char waitFrames;
```

3. Inicialize a variável *waitFrames* na função *game()*:

```c
	// initialize difficulty
	waitFrames = 15;
```

4. **DESAFIO**: Sem olhar a resposta abaixo, use a variável *waitFrames* para controlar a condição de movimento:

```c
*** Resposta ao desafio somente no roteiro pós-sessão. ***
```

5. Crie a variável *waitMoves* para controlar o número de movimentos da cobra antes de passar para o próximo Eden:

```c
unsigned char waitFrames, waitMoves;
```

6. Inicialize a variável *waitMoves* na função *game()*:

```c
	// initialize difficulty
	waitFrames = 15;
	waitMoves = 100;
```

7. **DESAFIO**: Sem olhar a resposta abaixo, crie um bloco (vazio ainda) para implementarmos o progresso de Édens e use a variável *waitMoves* para controlorar a execução desse bloco:

```c
*** Resposta ao desafio somente no roteiro pós-sessão. ***
```

8. Crie a variável *eden* para controlar em qual Éden (nível de  dificuldade) o jogo está:

```c
unsigned char waitFrames, waitMoves, eden;
```

9. Inicialize a variável *eden* na função *game()*:

```c
	// initialize difficulty
	waitFrames = 15;
	waitMoves = 100;
	eden = 1;
```

10. **DESAFIO**: Sem olhar a resposta abaixo, implemente o processo de progredir para o próximo Éden, aumentando a velocidade do jogo: 

```c
*** Resposta ao desafio somente no roteiro pós-sessão. ***
```

11. Compile e teste o jogo. O que achou do resultado ate agora?

### 10.4. Uma fonte diferenciada.
###### *Github Ticket/Branch: 38/TKT0038.*

##### Objetivo: Implementar uma fonte diferenciada da padrão (previsão: 15 minutos).

1. Definindo a estratégia da montagem da nova fonte.
- Relembrando o funcionamento do VDP.
- Partição da tabela de padrões em áreas de fonte e de tiles gráficos: manteremos os tiles de 0 a 127 para fonte, e reservaremos os tiles de 128 a 256 para gráficos.
- Mecanismo de montagem da fonte: deslocamento de todos os pixels das 4 primeiras linhas do tile para a direita, para configurar uma versão em itálico da fonte original do MSX.

2. **DESAFIO**: Sem olhar a resposta abaixo, defina a constrante *PATTERNTABLE*, de forma similar à definição que já fizemos da constante *NAMETABLE*.

```c
*** Resposta ao desafio somente no roteiro pós-sessão. ***
```

3. **DESAFIO**: Sem olhar a resposta abaixo, implemente a função buildFont() que altera o padrão dos tiles 0 a 127, conforme estratégia de montagem da fonte discutida acima.

```c
*** Resposta ao desafio somente no roteiro pós-sessão. ***
```

4. Chame a rotina buildFont após a mudança de modo da tela:

```c
	Screen(1);
	Width(32);
	buildFont();
```

5. Compile e rode o programa.

### 10.5. Ajustando as cores básicas.
###### *Github Ticket/Branch: 39/TKT0039.*

##### Objetivo: Deixar o jogo com "cara" de jardim (previsão: 5 minutos).

1. **DESAFIO**: Sem olhar a resposta abaixo, ajuste as cores do jogo para verde escuro sobre verde claro, e deixe a borda preta.

```c
*** Resposta ao desafio somente no roteiro pós-sessão. ***
```

2. Compile e rode o programa.

### 10.6. Finalização da Sessão 10
##### Objetivo: Discutir os tópicos tratados e o modelo/dinâmica do workshop (previsão: 10 minutos).

1. Lição de casa: preencher o arquivo Tile Template.txt para a próxima sessão.

2. Discussão geral da apresentação:
* Comentários sobre o estado corrente do jogo
* Novas ideias?
* Joysticks e triggers
* Dificuldade progressiva
* Relembrando o VDP
* Redefinição de tiles/fonts
* Dinâmica geral do workshop: feedbacks e ideias.

---

**Happy MSX'ing.**
