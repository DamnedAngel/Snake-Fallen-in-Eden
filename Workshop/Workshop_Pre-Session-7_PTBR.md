# Programando em C e ASM para MSX usando Visual Studio e Fusion-C
# Sessão 7: O movimento constante da cobra.

Escrito por **Danilo Angelo (a.k.a. Damned Angel)**, 2020-2021

Vídeo da sessão 7: XXX

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
###### *Github Ticket/Branch: 20/TKT0020.*

##### Objetivo: Aguardar o jogador parar de dar comandos antes de apagar as telas Iniciais e de Game Over (previsão: 15 minutos).

1. O atual estado do jogo tem um comandos *InputChar* para aguardar o jogador apertar uma tecla para sair da tela inicial e de game over. O problema é que se o jogador já veio da tela anterior com alguma tecla apertada, o *InputChar* recebe o código da tecla e passa de tela. Isso faz com que seja muito dificil ver a telas de game over ou incil após perder um jogo. Vamos então aguardar não existirem teclas apertadas ou dados no buffer do teclado. 

2. **DESAFIO**: Sem olhar a resposta abaixo, remova o *InputChar* da função *game()* e, manipulando a variável *Jiffy*, aguarde 1,5 segundos (90 *Jiffys*) antes de retornar para a função. Isso gerará uma espera anes de mostrar a mensagem de Game Over.

```c
*** Resposta ao desafio somente no roteiro pós-sessão. ***
```

3. Coloque um *Beep* para aviso sonoro que a cobra colidiu imediatamente antes do código do item anterior. Isso ajudará o jogador a entender por que o jogo ficou 1,5 segundos sem responder comandos. Mais tarde, melhoraremos esse aviso.

```c
	Beep();
```

4. Compile e rode o programa.

5. **DESAFIO**: Sem olhar a resposta abaixo, descubra qual a função da Fusion-C lê o conteúdo do teclado, sem aguardar se não houver teclas apertadas. Use essa função para aguardar não haver teclas apertadas antes de executar o *InputChar* nas funções *title()* e *gameOver()*.

```c
*** Resposta ao desafio somente no roteiro pós-sessão. ***
```

5. Compile e rode o programa.


### 7.2. O movimento constante da Cobra.
###### *Github Ticket/Branch: 21/TKT0021.*

##### Objetivo: Implementar o movimento esperado da cabeça da cobra: ela deve se movimentar constantemente e os comandos devem alterar a direção, ao invés de ficar parada e os comandos fazê-la andar (previsão: 30 minutos).

1. Crie a variável global *direction* para armazenar a direção da cobra. O padrão de valores dela será semelhante ao retornado pela função *JoystickRead()* (ou *STICK* do MSXBASIC). No jogo do workshop não trabalharemos com movimentos diagonais. Então os valors válidos serão apenas 1 (UP), 3 (RIGHT), 5 (DOWN) e 7 (LEFT). Essa variável também não poderá assumir o valor 0 (cobra parada):

```c
unsigned char x, y, direction;            // wait for keypress
```

2. Inicialize a variável *direction* com o valor *RIGHT* (3), dentro da função *game*:

```c
	// Initialize game variables
	x = 10;
	y = 10;
	direction = RIGHT;
```

3. **DESAFIO**: Sem olhar as resposta abaixo, atualize o valor da variável *direction* se - e apenas se - o valor da variável *joy* for ovimentos diagonais. Então os valors válidos serão apenas 1 (UP), 3 (RIGHT), 5 (DOWN) e 7 (LEFT).

```c
*** Resposta ao desafio somente no roteiro pós-sessão. ***
```

4. Substitua *joy* por *direction* no comnda *case* que implementa a movimentação da cobra:

```c
			// move snake
			switch (direction) {
```

5. Compile e rode o programa. Discuta o resultado:
* O movimento constante funcionou?
* Comandos para direcionar a cobra funcionaram? Que situações não funcionam bem?
* O que houve com a o sistema de detecção de colisão?

6. **DESAFIO**: Sem olhar a resposta abaixo, corrija o problema de detecção de colisão:

```c
*** Resposta ao desafio somente no roteiro pós-sessão. ***
```

7. Compile e rode o programa. Discuta o resultado.

### 7.3. Corrigindo o problema de comandos que falham.
###### *Github Ticket/Branch: 22/TKT0022.*

##### Objetivo: Dar uma sensação mais fluida ao controle da cobra (previsão: 15 minutos).

1. Discussão: por que os comandos direcionais estão falhando em algumas situações?

2. **DESAFIO**: Com base na discussão do item anterior, e sem olhar a resposta abaixo, corrija o problema das falhas intermitentes de comandos:

```c
*** Resposta ao desafio somente no roteiro pós-sessão. ***
```

3. Compile e rode o programa. O problema foi resolvido?

### 7.4. Evitando curvas de 180 graus.
###### *Github Ticket/Branch: 23/TKT0023.*

##### Objetivo: Evitar que a cobra se mate voltando por cima de ela mesma (previsão: 30 minutos).

1. Discussão: O que precisaríamos fazer para evitar que a cobra volte por cima de ela mesma?

2. **DESAFIO**: Com base na discussão do item anterior, e sem olhar a resposta abaixo, use a combinação de comandos *if* (ou do comando *switch/case* com comandos *if*) para evitar curvas de 180 graus:

```c
*** Resposta ao desafio somente no roteiro pós-sessão. ***
```

3. Compile e rode o programa.

4. Discussão: O problema foi resolvido? Você consegue imaginar uma forma de ainda causar curvas de 180 graus?

5. **DESAFIO**: Com base na discussão do item anterior, e sem olhar a resposta abaixo, implemente a solução para o ainda possível caso de curvas de 180 graus:

```c
*** Resposta ao desafio somente no roteiro pós-sessão. ***
```

6. Compile e rode o programa.

### 7.5. Desligando o "key click".
###### *Github Ticket/Branch: 24/TKT0024.*

##### Objetivo: Desligar o key click padrão do MSX, melhorando a experiência do jogo (previsão: 5 minutos).

1. **DESAFIO**: Sem olhar a resposta abaixo, descubra qual a função da Fusion-C que liga e desliga o "key click", e o desligue!

```c
*** Resposta ao desafio somente no roteiro pós-sessão. ***
```

2. Compile e rode o programa.

### 7.6. Finalização da Sessão 7
##### Objetivo: Discutir os tópicos tratados e o modelo/dinâmica do workshop (previsão: 10 minutos).

1. Discussão geral da apresentação:
* Novas funções da Fusion-C
* Lógica em geral
* Experiência do jogador
* Dinâmica geral do workshop: feedbacks e ideias.

---

**Happy MSX'ing.**
