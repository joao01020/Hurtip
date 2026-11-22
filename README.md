# Hurtip — Linguagem Básica

O núcleo de desenvolvimento da linguagem Hurtip.

A branch `feature/basic-language` é dedicada ao desenvolvimento dos recursos
fundamentais da linguagem, incluindo sintaxe, tipos de dados, expressões,
variáveis, funções, estruturas de controle e operações nativas.

Seu principal objetivo é tornar a Hurtip simples, expressiva, previsível e
acessível, sem limitar suas possibilidades futuras.

## Objetivo

Construir uma base consistente e confiável para a linguagem, permitindo que
desenvolvedores escrevam programas com uma sintaxe clara e um comportamento
intuitivo.

O núcleo da linguagem deve priorizar:

- Simplicidade e legibilidade.
- Sintaxe e semântica consistentes.
- Comportamento previsível.
- Flexibilidade no tratamento de dados.
- Eficiência na execução.
- Possibilidade de expansão para novos recursos.

## Funcionalidades implementadas

Os seguintes recursos já estão implementados no núcleo da linguagem.

### Variáveis e tipos de dados

- Declaração de variáveis utilizando `create`.
- Atribuição e reatribuição de variáveis.
- Strings.
- Números utilizando `double`.
- Valores booleanos.
- Gerenciamento de tipos em tempo de execução.

### Operadores e expressões

- Operadores aritméticos.
- Operadores de comparação.
- Operadores lógicos.
- Operadores unários.
- Precedência de operadores.
- Expressões agrupadas.
- Avaliação de curto-circuito.

### Estruturas de controle

- `if` e `else`.
- Blocos de código.
- Laços de repetição `while`.
- `break` e `continue`.
- Laços aninhados.

### Funções

- Criação de funções pelo usuário.
- Parâmetros de funções.
- Valores de retorno.
- Chamadas recursivas.
- Escopos locais e globais.
- Funções aninhadas.

### Arrays

- Criação de arrays.
- Arrays vazios.
- Elementos numéricos, strings e booleanos.
- Arrays com diferentes tipos de dados.
- Arrays aninhados.
- Acesso por índices.
- Acesso a índices aninhados.
- Atribuição e modificação de elementos.
- Consulta ao tamanho através da propriedade `.length`.
- Exibição recursiva de arrays utilizando `view()`.

### Operações nativas

- `view()` para exibição de valores.

### Valores numéricos

- Números inteiros.
- Números decimais.

## Funcionalidades planejadas

Os seguintes recursos estão previstos para desenvolvimento futuro.

### Arrays

- `push()` para adicionar elementos.
- `pop()` para remover o último elemento.
- `remove()` para remover elementos por índice.
- `contains()` para verificar a existência de elementos.
- Iteração de arrays.
- Concatenação de arrays.
- Comparação estrutural de arrays.

### Recursos da linguagem

- Laços de repetição `for`.
- Novos tipos de dados.
- Mais operações nativas.
- Melhorias nas mensagens de erro.
- Validação mais consistente de tipos.
- Expansão das capacidades de expressões.

### Melhorias futuras

- Definição formal da semântica da linguagem.
- Otimização do desempenho do interpretador.
- Melhorias no gerenciamento de memória.
- Ampliação dos testes automatizados.
- Suporte aprimorado à depuração.

## Arquitetura

O núcleo da linguagem está organizado em torno dos seguintes componentes:

| Componente  | Responsabilidade                                      |
| ----------- | ----------------------------------------------------- |
| Lexer       | Converte o código-fonte em tokens.                    |
| Parser      | Analisa os tokens e constrói a AST.                   |
| AST         | Representa expressões e instruções.                   |
| Interpreter | Executa o programa analisado.                         |
| Environment | Gerencia variáveis e escopos.                         |
| Runtime     | Gerencia valores e comportamentos durante a execução. |

### Implementação

A Hurtip é desenvolvida atualmente em C++17.

Seu sistema de execução suporta os seguintes tipos de valores:

- `std::string`
- `double`
- `bool`
- `std::shared_ptr<ArrayValue>`

Esses tipos são utilizados pelo interpretador para representar e avaliar os
valores dos programas.

## Testes

Os testes automatizados são utilizados para validar o núcleo da linguagem e
evitar regressões durante o desenvolvimento.

A cobertura atual inclui:

- Testes do Lexer.
- Testes do Parser.
- Testes de variáveis e expressões.
- Testes de operadores.
- Testes de funções.
- Testes de estruturas de controle.
- Criação e acesso a arrays.
- Arrays mistos e aninhados.
- Atribuição em arrays.
- Propriedade `length`.
- Índices inválidos em arrays.
- Tratamento de erros em tempo de execução.

Os testes são gerenciados através do CMake e CTest.

## Diretrizes de desenvolvimento

O desenvolvimento nesta branch deve seguir os seguintes princípios:

1. Manter a sintaxe simples e intuitiva.
2. Garantir consistência entre os recursos da linguagem.
3. Evitar complexidade desnecessária.
4. Preservar o comportamento dos recursos já implementados.
5. Priorizar legibilidade e previsibilidade.
6. Desenvolver novos recursos sem comprometer a estrutura existente.
7. Garantir que as funcionalidades sejam acompanhadas de testes automatizados.

## Objetivo da branch

A `feature/basic-language` tem como finalidade construir e aprimorar a base da
Hurtip.

Todas as funcionalidades fundamentais da linguagem devem ser desenvolvidas,
testadas e estabilizadas nesta branch antes de serem integradas à `main`.
