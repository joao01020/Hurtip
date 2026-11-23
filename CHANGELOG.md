# Histórico de Alterações

Todas as alterações relevantes da Hurtip são documentadas neste arquivo.

Este projeto segue as convenções do
[Keep a Changelog](https://keepachangelog.com/pt-BR/1.1.0/) e utiliza o
versionamento semântico.

## [0.1.0-alpha.1] - Primeiro lançamento público

### Adicionado

- Arquitetura composta por Lexer, Parser, AST e Interpreter.
- Declaração e atribuição de variáveis utilizando `create`.
- Suporte a strings, números e valores booleanos.
- Operadores aritméticos, relacionais e lógicos.
- Estruturas condicionais com `if` e `else`.
- Loops `while` com suporte a `break` e `continue`.
- Funções, parâmetros, retornos e recursividade.
- Gerenciamento de escopos.
- Sistema de carregamento de módulos utilizando `load`.
- Sistema de importação de bibliotecas nativas utilizando `import`.
- Biblioteca nativa `math`, com a função `math.sum()`.
- Diagnósticos iniciais de erros.
- Extensão experimental para Visual Studio Code.

### Tecnologias

- C++17.
- CMake para configuração e compilação.
- GCC / G++ como compiladores.
- CTest para execução de testes automatizados.

### Observações

- Esta é a primeira versão pública experimental da Hurtip.
- A linguagem ainda está em desenvolvimento ativo.
- Funcionalidades, sintaxe e interfaces podem sofrer alterações em versões
  futuras.
