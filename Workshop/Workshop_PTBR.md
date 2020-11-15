# Programando em C e ASM para MSX usando Visual Studio e Fusion-C

Escrito por Damned Angel, 2020


## Sess�o 1: Criando e configurando o projeto

### 1.1. Criando o projeto

*Nota: Esse passo assume que voc� j� instalou os Templates de Aplica��es MSX (dispon�vel em https://github.com/DamnedAngel/MSX-Templates-for-VisualStudio) no Visual Studio.*

1. Clique no bot�o **Create a New Project** na janela de abertura do VS2019. Alternativamente, selecione **File|New|Project**.
2. Na lista de templates mostrada, selecione **MSX ROM Application** (caso queira fazer o projeto no formato MSX-DOS, escolha o template **MSX-DOS Application**. Provavelmente esse item estar� no final da lista, ent�o fa�a o scroll down.
3. Configure o nome da aplica��o, a localiza��o do projeto no seu disco e o nome da solu��o (a solu��o � um agregador de projetos).
4. Clique o bot�o **Create** e o VS criar� seu projeto. Para ter certeza que o projeto foi criado corretamente, compile-o com **Build|Build Solution**. A tela de output dever�, ao final da compila��o, mostrar a mensagem **"Rebuild All: 1 succeeded, 0 failed, 0 skipped"**.

