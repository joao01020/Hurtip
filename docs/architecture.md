# Arquitetura

A Hurtip está sendo desenvolvida em C++17 e utiliza uma arquitetura dividida em etapas.

## Fluxo de execução

```text
Arquivo .hurtip
      |
      v
    Lexer
      |
      v
    Tokens
      |
      v
    Parser
      |
      v
     AST
      |
      v
  Interpreter
      |
      v
   Execução
```

## Lexer — análise léxica

O Lexer lê o código-fonte e identifica os elementos da linguagem, transformando o texto em uma sequência de tokens.

Por exemplo:

```hurtip
create name = "Hurtip"
```

Gera tokens que representam a palavra reservada `create`, o identificador `name`, o operador de atribuição e o texto.

### Tokens reconhecidos

- Palavras reservadas: `create`, `true`, `false`, `if`, `else`, `while`, `function`, `return`, `load`, `import`, `as`, `break`, `continue`, `and`, `or`, `not`.
- Identificadores.
- Strings e números.
- Valores booleanos.
- Operadores de atribuição, aritméticos e de comparação.
- Delimitadores.
- Quebras de linha e fim de arquivo.
- Instruções de controle de fluxo.

O Lexer também reconhece comentários iniciados por `//` e números decimais.

### Rastreamento de posição

Cada token armazena informações sobre sua localização:

- `line`: linha em que o token começa.
- `column`: coluna em que o token começa.

Essas informações auxiliam na apresentação de diagnósticos.

## Parser — análise sintática

O Parser recebe os tokens, verifica se seguem as regras gramaticais e constrói a AST (*Abstract Syntax Tree*).

Atualmente, possui suporte para:

- Declarações e atribuições.
- Valores literais e referências a variáveis.
- Chamadas e declarações de funções.
- Parâmetros e retornos.
- Carregamento de módulos e importação de bibliotecas.
- Aliases com `as`.
- Expressões aritméticas, unárias e agrupadas.
- Operadores de comparação e lógicos.
- Precedência de operadores.
- Estruturas condicionais e blocos.
- Loops `while`.
- Instruções `break` e `continue`.
- Arrays literais, inclusive vazios.
- Acesso por índice e acesso encadeado.
- Atribuição a elementos indexados.

O Parser possui mecanismos de diagnóstico para identificar estruturas sintáticas inválidas.

## AST — árvore sintática abstrata

A AST representa a estrutura do código de maneira organizada.

Atualmente, existem estruturas para representar:

- Declarações de variáveis.
- Atribuições.
- Expressões e valores literais.
- Referências a variáveis.
- Expressões binárias e unárias.
- Chamadas de funções.
- Acesso a membros.
- Arrays literais (`ArrayExpression`).
- Acesso a índices (`IndexExpression`).
- Declarações de funções.
- Instruções de retorno.
- Carregamento de módulos.
- Importação de bibliotecas.
- Decisões condicionais.
- Blocos de código.
- Loops.
- Interrupção e continuação de loops.

## Interpreter — interpretador

O interpretador percorre as estruturas produzidas pelo Parser e executa as instruções.

Atualmente, ele consegue:

- Criar, armazenar, recuperar e atualizar variáveis.
- Trabalhar com strings, números e booleanos.
- Avaliar expressões matemáticas, comparações e lógica.
- Executar operações com curto-circuito.
- Criar e manipular arrays.
- Validar acessos por índice.
- Executar `view()`.
- Executar funções, parâmetros e retornos.
- Executar funções recursivas.
- Controlar ambientes e escopos.
- Executar condicionais e loops.
- Interpretar `break` e `continue`.
- Carregar módulos e acessar funções por namespace.
- Manter ambientes persistentes associados aos módulos.
- Resolver dependências e detectar ciclos.
- Restaurar o contexto após falhas de carregamento.
- Importar e executar funções de bibliotecas nativas.
- Identificar variáveis não declaradas.
- Informar a localização de determinados erros de execução.

## Representação dos valores

O interpretador utiliza `std::variant` para representar valores em tempo de execução.

```cpp
using RuntimeValue = std::variant<
    std::string,
    double,
    bool,
    std::shared_ptr<ArrayValue>
>;

struct ArrayValue
{
    std::vector<RuntimeValue> elements;
};
```

A estrutura `ArrayValue` utiliza `std::vector` para armazenar elementos e `std::shared_ptr` para representar arrays como valores do runtime.

## Tecnologias

| Tecnologia | Utilização |
|---|---|
| C++17 | Implementação da linguagem |
| CMake | Configuração e compilação |
| GCC / G++ | Compilador |
| CTest | Testes automatizados |
| Git | Controle de versão |

A escolha do C++ permite explorar estruturas de dados, gerenciamento de memória e desempenho, além de oferecer uma base para futuras experiências com compiladores e sistemas embarcados.
