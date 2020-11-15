# Programando em C e ASM para MSX usando Visual Studio e Fusion-C

Escrito por Damned Angel, 2020


## Sessão 1: Criando e configurando o projeto

### 1.1. Criando o projeto

*Nota: Esse passo assume que você já instalou os Templates de Aplicações MSX (disponível em https://github.com/DamnedAngel/MSX-Templates-for-VisualStudio) no Visual Studio.*

1. Clique no botão **Create a New Project** na janela de abertura do VS2019. Alternativamente, selecione **File|New|Project**.
2. Na lista de templates mostrada, selecione **MSX ROM Application** (caso queira fazer o projeto no formato MSX-DOS, escolha o template **MSX-DOS Application**. Provavelmente esse item estará no final da lista, então faça o scroll down.
3. Configure o nome da aplicação, a localização do projeto no seu disco e o nome da solução (a solução é um agregador de projetos).
4. Clique o botão **Create** e o VS criará seu projeto. Para ter certeza que o projeto foi criado corretamente, compile-o com **Build|Build Solution**. A tela de output deverá, ao final da compilação, mostrar a mensagem **"Rebuild All: 1 succeeded, 0 failed, 0 skipped"**.

