# Programando em C e ASM para MSX usando Visual Studio e Fusion-C
# Sessão 9: A maçã do bem e do mal.

Escrito por **Danilo Angelo (a.k.a. Damned Angel)**, 2020-2021

Vídeo da sessão 9: XXX

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

# Sessão 9: A maçã do bem e do mal.

### 9.1. Materializando uma maçã (e entendendo um pouco mais do linkers do SDCC e pacotes .lib).
###### *Github Ticket/Branch: 28/TKT0028.*

##### Objetivo: Fazer uma maçã aparecer em um lugar aleatório, mas desocupado, do jardim (previsão: 40 minutos).

1. Definindo as mecânicas da maçã:
- A primeira maçã aparece assim que o jogo começa;
- A maçã deve aparecer em uma posição livre do jardim, dentro dos limites e sem nenhum segmento da cobra.

2. Defina o caracter que usaremos temporariamente para a maçã:

```c
#define TILE_GRASS		' '
#define TILE_SNAKETAIL		'o'
#define TILE_SNAKEHEAD		'*'
#define TILE_APPLE		'#'
```

3. Crie uma nova função *dropApple()* sem parâmetros e sem retorno, antes da função *game()*:

```c
void dropApple() {
}
```

4. Entendendo as funções *rand()* e *srand()* e a constante *RAND_MAX* da biblioteca padrão do C.

5. **DESAFIO**: Utilizando a função de geração de números aleatórios rand, gere uma posição aleatória para a maçã na função *dropApple*, dentro dos limites do jardim, considerando o layout de endereçamento da tabela de nomes do VDP na VRAM. Não se preocupe, ainda, com colisões com a cobra ou com as bordas laterais:

```c
*** Resposta ao desafio somente no roteiro pós-sessão. ***
```

6. Sem adicionar *#include <stdlib.h>*, compile o programa. O que houve?

7. Entendendo um pouco mais do linker do SDCC e pacotes .lib.

8. Resolva o warning da compilação, incluindo o header *stdlib*:

```c
#include <stdbool.h>
#include <stdlib.h>
```

9. Compile o programa e confirme que o warning foi resolvido.

10. **DESAFIO**: Com um loop, garanta que a posição escolhida para a maçã está livre (não está ocupada nem pela cobra e nem pelas bordas laterais), e mostre a maçã no jardim:

```c
*** Resposta ao desafio somente no roteiro pós-sessão. ***
```

11. Após inicialização da cobra na função game(), gere a primeira maçã do jogo:

```c
	// Drop first apple
	dropApple();
}
```

12. Compile execute o programa. O que aconteceu? O que acontece se você executa multiplas vezes o jogo sem rebootar o emulador? O que acontece se você reboota o emulador e inicia uma partida?

13. **DESAFIO**: Com base na discussão que fizemos sobre as funções de números aleatórios, como você resolveria o problema identificado?

```c
*** Resposta ao desafio somente no roteiro pós-sessão. ***
```

14. Compile execute o programa. O que aconteceu?

### 9.2. Comer, comer... é o melhor para poder crescer!
###### *Github Ticket/Branch: 29/TKT0029.*

##### Objetivo: Implementar a ação da cobra de  comer... e crecer! (previsão: 20 minutos).

1. Definindo as mecânicas da alimentação:
- Quando a cabeça da cobra colide com uma maçã, a cobra come a maçã.
- Cada vez que a maçã é comida, ela desaparece e a cobra cresce um número aleatório de segmentos, definido na variável *growth*, 1 <= *growth* <= 8.
- O crescimento da cobra se dará em 1 segmento por movimentação. Ou seja, a extremidade final deve ficar fixa por *growth* ciclos de movimentação.

2. **DESAFIO**: Sem olhar a resposta abaixo, detecte que a cabeça colidiu com a maçã e evite que essa colisão finalize o jogo. Defina, também, um bloco ({}) para tratarmos posteriormente a colisão;

```c
*** Resposta ao desafio somente no roteiro pós-sessão. ***
```

3. Compile e rode o programa.

4. **DESAFIO**: Sem olhar a resposta abaixo, crie a variável *growth* e gere um valor aleatório de crescimento a cada vez que uma maçã é comida. Em seguida, implemente o crescimento da cobra.

```c
*** Resposta ao desafio somente no roteiro pós-sessão. ***
```

5. Compile e rode o programa.

### 9.3. Materializando muitas outras maçãs.
###### *Github Ticket/Branch: 30/TKT0030.*

##### Objetivo: Sempre apresentar uma maçã a ser perseguida pela cobra (previsão: 5 minutos).

1. **DESAFIO**: Sem olhar a resposta abaixo, materialize uma maçã toda vez que a anterior for comida pela cobra.

```c
*** Resposta ao desafio somente no roteiro pós-sessão. ***
```

### 9.4. Quem está contando?
###### *Github Ticket/Branch: 31/TKT0031.*

##### Objetivo: Implementar sistema de contagem de pontos (previsão: 20 minutos).

1. Definindo a mecânica da pontuação:
- A pontuação é zerada no início de cada jogo.
- A pontuação será incrementada com o mesmo número de pontos quanto for o crescimento da cobra em segmentos, no momento que a cobra come uma maçã.
- O recorde é zerado no início do programa. 
- O recorde é atualizado para o valor da pontuação toda vez que a pontuação for maior que ele.

2. **DESAFIO**: Sem olhar a resposta abaixo, incremente a pontuação conforme tamanho do crescimento da cobra quando ela come uma maçã.

```c
*** Resposta ao desafio somente no roteiro pós-sessão. ***
```

3. Rode o programa.

4. **DESAFIO**: Sem olhar a resposta abaixo, incremente o recorde sempre que a pontuação for maior que ele.

```c
*** Resposta ao desafio somente no roteiro pós-sessão. ***
```

5. Rode o programa.

### 9.5. Finalização da Sessão 9
##### Objetivo: Discutir os tópicos tratados e o modelo/dinâmica do workshop (previsão: 10 minutos).

1. Discussão geral da apresentação:
* O jogo funcional
* Lógica em geral
* LIBs x RELs
* Dinâmica geral do workshop: feedbacks e ideias.

---

**Happy MSX'ing.**
