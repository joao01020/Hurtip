# Hurtip

**Uma linguagem de programação experimental, simples e intuitiva, desenvolvida
em C++.**

A Hurtip é um projeto experimental de criação de uma linguagem de programação
própria. Seu objetivo é explorar como uma linguagem pode tornar a programação
mais acessível, reduzir a complexidade desnecessária e, futuramente, oferecer
recursos para desenvolvimento de aplicações, sistemas e dispositivos embarcados.

A proposta é construir uma linguagem com sintaxe clara e fácil de compreender,
sem abandonar a possibilidade de evoluir para recursos mais avançados.

> A Hurtip está em desenvolvimento. Atualmente, possui um interpretador
> funcional capaz de executar arquivos `.hurtip`, uma arquitetura composta por
> Lexer, Parser, AST e Interpreter, suporte a variáveis, expressões, operações
> matemáticas, lógica, estruturas de controle, funções, recursividade, escopos e
> um sistema inicial de módulos.

---

## 1. Visão do projeto

Muitas linguagens de programação oferecem grande flexibilidade e desempenho, mas
podem apresentar uma curva de aprendizado complexa para iniciantes.

A Hurtip nasce da ideia de experimentar uma abordagem diferente: criar uma
linguagem em que as instruções sejam intuitivas, legíveis e próximas da intenção
de quem está programando.

A intenção não é simplesmente criar outra linguagem, mas investigar como podemos
simplificar a experiência de desenvolvimento sem limitar sua evolução técnica.

### Objetivos principais

- Criar uma sintaxe simples e intuitiva.
- Facilitar o aprendizado de programação.
- Desenvolver uma linguagem própria, com estrutura e identidade.
- Explorar interpretação e compilação.
- Investigar possibilidades de uso em sistemas embarcados.
- Buscar eficiência e simplicidade na implementação.
- Construir uma arquitetura que permita adicionar recursos gradualmente.
- Permitir integração futura com bibliotecas externas e recursos de baixo nível.

---

## 2. Filosofia da linguagem

A Hurtip segue alguns princípios:

**Simplicidade:** comandos devem ser fáceis de compreender.

**Legibilidade:** o código deve comunicar claramente sua intenção.

**Evolução:** a linguagem deve começar pequena, mas possuir uma arquitetura que
permita crescer.

**Eficiência:** o desempenho deve ser considerado desde a concepção,
especialmente pensando em possíveis aplicações embarcadas.

**Acessibilidade:** reduzir barreiras para quem está começando a programar.

**Controle:** oferecer, progressivamente, recursos que permitam ao programador
compreender e controlar o funcionamento dos programas.

---

## 3. Sintaxe inicial

A sintaxe da Hurtip busca utilizar palavras intuitivas.

Exemplo:

```hurtip
create name = "Hurtip"
create age = 24
create is_active = true

view("Minha primeira execução!")
view(name)
view(age)
view(is_active)
```

### Declaração de variáveis

A palavra-chave `create` é utilizada para criar variáveis.

```hurtip
create name = "Hurtip"
create age = 24
create is_active = true
```

A escolha de `create` busca tornar a declaração mais compreensível e intuitiva.

As variáveis podem armazenar valores e ser utilizadas posteriormente em
expressões, operações, funções e decisões.

### Atribuição de valores

É possível atualizar o valor de uma variável já declarada.

```hurtip
create counter = 0

counter = counter + 1
counter = counter + 1

view(counter)
```

A atribuição permite modificar o conteúdo armazenado em uma variável durante a
execução do programa.

### Exibição de valores

A função nativa `view()` permite exibir valores no terminal.

```hurtip
view("Hello, Hurtip!")
```

Também é possível exibir variáveis:

```hurtip
create language = "Hurtip"
create version = 1

view(language)
view(version)
```

Atualmente, `view()` aceita múltiplos argumentos.

```hurtip
view("Language:", "Hurtip", "Version:", 1)
```

### Tipos atualmente suportados pelo interpretador

| Tipo     | Exemplo    | Representação interna |
| -------- | ---------- | --------------------- |
| Texto    | `"Hurtip"` | `std::string`         |
| Número   | `24`       | `double`              |
| Booleano | `true`     | `bool`                |

Internamente, os valores são armazenados utilizando `std::variant`.

```cpp
using RuntimeValue = std::variant<std::string, double, bool>;
```

**Observação:** o runtime utiliza `double` para representar números, mas a
sintaxe numérica atual do Lexer ainda reconhece apenas números inteiros. O
suporte a literais decimais precisa ser implementado.

### Comentários

A Hurtip permite comentários de linha utilizando `//`.

```hurtip
// Este é um comentário

create age = 24 // Comentário na mesma linha

view(age)
```

Os comentários são ignorados durante a execução do programa.

---

## 4. Operadores e expressões

A Hurtip possui suporte a diferentes operadores para realizar cálculos,
comparações e operações lógicas.

### Operadores aritméticos

| Operador | Operação      | Exemplo  |
| -------- | ------------- | -------- |
| `+`      | Adição        | `10 + 5` |
| `-`      | Subtração     | `10 - 5` |
| `*`      | Multiplicação | `10 * 5` |
| `/`      | Divisão       | `10 / 5` |

Exemplo:

```hurtip
create sum = 10 + 5
create subtraction = 10 - 5
create multiplication = 10 * 5
create division = 10 / 5

view(sum)
view(subtraction)
view(multiplication)
view(division)
```

### Precedência matemática

O interpretador respeita a precedência dos operadores matemáticos.

```hurtip
create result = 10 + 5 * 2
create grouped_result = (10 + 5) * 2

view(result)
view(grouped_result)
```

A multiplicação é realizada antes da adição, enquanto os parênteses permitem
agrupar expressões.

### Operadores unários

A Hurtip possui suporte aos operadores unários positivos e negativos.

```hurtip
create negative = -10
create positive = +10

view(negative)
view(positive)
```

### Operadores de comparação

| Operador | Significado    |
| -------- | -------------- |
| `==`     | Igual          |
| `!=`     | Diferente      |
| `>`      | Maior que      |
| `<`      | Menor que      |
| `>=`     | Maior ou igual |
| `<=`     | Menor ou igual |

Exemplo:

```hurtip
create age = 24

view(age == 24)
view(age != 18)
view(age > 18)
view(age < 30)
view(age >= 24)
view(age <= 24)
```

As comparações produzem valores booleanos.

### Operadores lógicos

| Operador | Significado    |
| -------- | -------------- |
| `and`    | E lógico       |
| `or`     | OU lógico      |
| `not`    | Negação lógica |

Exemplo:

```hurtip
view(true and true)
view(true and false)

view(false or true)
view(false or false)

view(not true)
view(not false)
```

### Precedência lógica

O interpretador considera a precedência entre os operadores lógicos e permite
agrupamento com parênteses.

```hurtip
view(true or false and false)
view((true or false) and false)
view(not false and true)
```

### Avaliação de curto-circuito

A Hurtip possui avaliação de curto-circuito nos operadores `and` e `or`.

Isso significa que a segunda parte de uma expressão pode não ser avaliada quando
o resultado já pode ser determinado pela primeira parte.

```hurtip
view(false and missing == 1)
view(true or missing == 1)
```

Nos dois casos, a variável `missing` não precisa ser avaliada.

---

## 5. Estruturas de controle

A Hurtip possui estruturas condicionais e de repetição para controlar o fluxo de
execução dos programas.

### if e else

A estrutura `if` permite executar instruções dependendo de uma condição.

```hurtip
create age = 24

if (age >= 18) {
    view("Maior de idade")
} else {
    view("Menor de idade")
}
```

O `else` permite definir o que acontece quando a condição não é verdadeira.

### Decisões aninhadas

É possível utilizar estruturas condicionais dentro de outras estruturas
condicionais.

```hurtip
create age = 24

if (age >= 18) {
    if (age >= 21) {
        view("Idade igual ou superior a 21")
    } else {
        view("Idade entre 18 e 20")
    }
} else {
    view("Menor de idade")
}
```

Também é possível utilizar `if` sem `else`.

### Blocos de código

As instruções podem ser agrupadas utilizando chaves `{}`.

Os blocos são utilizados nas estruturas condicionais, funções e loops.

A Hurtip permite colocar a abertura do bloco na mesma linha da declaração ou na
linha seguinte.

```hurtip
if (true)
{
    view("Bloco executado")
}
```

Cada bloco possui seu próprio ambiente de variáveis, permitindo isolamento de
declarações locais.

### While

O `while` executa um bloco de código enquanto sua condição permanecer
verdadeira.

```hurtip
create counter = 0

while (counter < 5) {
    view(counter)
    counter = counter + 1
}
```

### Break

O `break` encerra a execução do loop em que está inserido.

```hurtip
create counter = 0

while (counter < 10) {
    counter = counter + 1

    if (counter == 5) {
        break
    }

    view(counter)
}
```

### Continue

O `continue` interrompe a repetição atual e passa para a próxima iteração do
loop.

```hurtip
create counter = 0

while (counter < 5) {
    counter = counter + 1

    if (counter == 3) {
        continue
    }

    view(counter)
}
```

### Loops aninhados

A Hurtip permite utilizar loops dentro de outros loops.

Também foi testado o comportamento de `break` em loops aninhados, garantindo que
a interrupção do loop interno não encerre automaticamente o loop externo.

```hurtip
create outer = 0

while (outer < 3) {
    outer = outer + 1

    create inner = 0

    while (inner < 5) {
        inner = inner + 1

        if (inner == 3) {
            break
        }

        view(inner)
    }

    view(outer)
}
```

### Recursos de controle de fluxo

| Recurso                                | Estado        |
| -------------------------------------- | ------------- |
| `if`                                   | Implementado  |
| `else`                                 | Implementado  |
| Decisões aninhadas                     | Implementadas |
| Blocos de código                       | Implementados |
| Escopo próprio para blocos de controle | Implementado  |
| `while`                                | Implementado  |
| `break`                                | Implementado  |
| `continue`                             | Implementado  |
| Loops aninhados                        | Implementados |
| `for`                                  | Pendente      |

---

## 6. Funções e escopos

A Hurtip possui suporte inicial a funções definidas pelo programador.

As funções permitem organizar instruções em blocos reutilizáveis, receber
parâmetros e retornar valores.

### Declaração de funções

A palavra-chave `function` é utilizada para declarar uma função.

```hurtip
function greet()
{
    view("Hello, Hurtip!")
}

greet()
```

### Parâmetros

As funções podem receber parâmetros para trabalhar com diferentes valores.

```hurtip
function sum(a, b)
{
    return a + b
}

view(sum(10, 20))
```

### Valores de retorno

A instrução `return` permite devolver um resultado para quem chamou a função.

```hurtip
function double(number)
{
    return number * 2
}

create result = double(10)

view(result)
```

### Funções aninhadas e chamadas sucessivas

A Hurtip permite que funções chamem outras funções.

```hurtip
function sum(a, b)
{
    return a + b
}

function calculate()
{
    create result = sum(10, 20)
    view(result)

    return result
}

function main()
{
    create value = calculate()
    view(value)
}

main()
```

### Recursividade

Uma função pode chamar a si mesma, permitindo implementar algoritmos recursivos.

```hurtip
function factorial(n)
{
    if (n <= 1) {
        return 1
    }

    return n * factorial(n - 1)
}

view(factorial(5))
```

Resultado:

```text
120
```

### Sistema de escopos

A Hurtip utiliza ambientes para armazenar variáveis e controlar sua
visibilidade.

Atualmente, o sistema oferece:

- Ambiente global.
- Ambientes locais de funções.
- Ambientes próprios para blocos.
- Busca de variáveis nos ambientes ancestrais.
- Atualização de variáveis existentes em ambientes superiores.
- Restauração do ambiente anterior após a execução de blocos.
- Isolamento de variáveis locais entre chamadas de funções.

Exemplo:

```hurtip
create number = 10

if (true) {
    create number = 20
    view(number)
}

view(number)
```

Resultado:

```text
20
10
```

O bloco utiliza uma variável local sem substituir a variável existente no
ambiente externo.

**Limitações atuais:** closures e captura de ambientes léxicos ainda não foram
implementados. O sistema de escopos das funções também não oferece ainda todos
os recursos de um modelo lexical completo.

---

## 7. Sistema de módulos e bibliotecas

A Hurtip está sendo desenvolvida com uma separação conceitual entre o
carregamento de arquivos do próprio projeto e a importação de bibliotecas
externas.

A ideia é utilizar duas instruções com responsabilidades distintas: `load` e
`import`.

Essa separação permitirá organizar projetos, reutilizar código e, futuramente,
ampliar as possibilidades da linguagem por meio de bibliotecas externas.

### 7.1. Load — arquivos da própria linguagem

A instrução `load` é destinada ao carregamento de outros arquivos `.hurtip`.

Seu objetivo é permitir que um programa seja dividido em vários arquivos,
mantendo cada parte organizada e reutilizável.

Exemplo:

```hurtip
load "modules/math.hurtip" as math

view(math.sum(10, 20))
view(math.doubleSum(10, 20))
```

Nesse modelo, o arquivo carregado pertence ao próprio projeto e também utiliza a
sintaxe da Hurtip.

O alias `as` permite associar um nome ao módulo, possibilitando acessar suas
funções por meio de um namespace.

### Recursos de `load` já implementados

- Carregamento de arquivos `.hurtip`.
- Associação de alias com `as`.
- Registro de funções por namespace.
- Chamadas de funções utilizando o namespace do módulo.
- Resolução de caminhos relativos ao arquivo que executa `load`.
- Cache de módulos carregados.
- Detecção de dependências circulares.
- Testes de integração entre arquivos.

### 7.2. Import — bibliotecas externas

A ideia de `import` é oferecer um mecanismo separado para incorporar bibliotecas
externas à Hurtip.

Enquanto `load` trabalha com arquivos `.hurtip` do próprio projeto, `import`
deverá permitir utilizar recursos desenvolvidos e disponibilizados fora dele.

Exemplos conceituais de uso futuro:

```hurtip
import math
import graphics
import networking
```

Esses exemplos representam uma direção planejada para a linguagem, não uma
sintaxe já implementada ou definitivamente especificada.

A ideia é que bibliotecas externas possam oferecer funcionalidades que não
precisam ser reimplementadas diretamente na linguagem, ampliando suas
possibilidades.

Entre as possibilidades futuras estão:

- Bibliotecas matemáticas.
- Bibliotecas gráficas.
- Comunicação e redes.
- Integração com sistemas operacionais.
- Bibliotecas de terceiros.
- Integração com bibliotecas C/C++.
- Recursos para sistemas embarcados.

### 7.3. Diferença entre load e import

| Instrução | Finalidade                             | Origem               |
| --------- | -------------------------------------- | -------------------- |
| `load`    | Carregar módulos e arquivos do projeto | Arquivos `.hurtip`   |
| `import`  | Incorporar bibliotecas externas        | Bibliotecas externas |

Essa distinção é uma decisão arquitetural importante para a evolução da Hurtip.

Ela evita misturar o mecanismo de organização de arquivos da própria linguagem
com o mecanismo de integração de bibliotecas externas.

### Estado atual

| Recurso                                     | Estado       |
| ------------------------------------------- | ------------ |
| `load` de arquivos `.hurtip`                | Implementado |
| Alias de módulos com `as`                   | Implementado |
| Namespace de módulos                        | Implementado |
| Resolução de caminhos relativos             | Implementada |
| Cache de módulos                            | Implementado |
| Detecção de dependências circulares         | Implementada |
| `import` de bibliotecas externas            | Planejado    |
| Sistema de bibliotecas externas             | Pendente     |
| Isolamento completo de variáveis por módulo | Pendente     |
| Biblioteca padrão                           | Pendente     |

---

## 8. Arquitetura atual

A Hurtip está sendo desenvolvida em C++17 e utiliza uma arquitetura dividida em
etapas.

O fluxo atual de execução é:

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

### Lexer — Análise léxica

O Lexer lê o código-fonte e identifica os elementos da linguagem, transformando
o texto em uma sequência de tokens.

Por exemplo:

```hurtip
create name = "Hurtip"
```

É transformado em tokens como:

- `Create`
- `Identifier`
- `Equal`
- `String`

#### Tokens reconhecidos

| Categoria                | Elementos                                                                                                                     |
| ------------------------ | ----------------------------------------------------------------------------------------------------------------------------- |
| Palavras reservadas      | `create`, `true`, `false`, `if`, `else`, `while`, `function`, `return`, `load`, `as`, `break`, `continue`, `and`, `or`, `not` |
| Identificadores          | Nomes de variáveis e identificadores                                                                                          |
| Valores literais         | `String`, `Number`, `True`, `False`                                                                                           |
| Atribuição               | `Equal` (`=`)                                                                                                                 |
| Operadores aritméticos   | `Plus` (`+`), `Minus` (`-`), `Star` (`*`), `Slash` (`/`)                                                                      |
| Operadores de comparação | `EqualEqual`, `BangEqual`, `Greater`, `Less`, `GreaterEqual`, `LessEqual`                                                     |
| Delimitadores            | `LeftParen`, `RightParen`, `LeftBrace`, `RightBrace`, `Comma`                                                                 |
| Estrutura do código      | `NewLine`, `EndOfFile`                                                                                                        |
| Controle de fluxo        | `Break`, `Continue`, `Return`                                                                                                 |

O Lexer também reconhece comentários de linha iniciados por `//`.

#### Rastreamento de posição

Cada token armazena informações sobre sua localização no código-fonte:

- `line`: linha em que o token começa.
- `column`: coluna em que o token começa.

Essas informações formam a base para diagnósticos mais precisos.

### Parser — Análise sintática

O Parser recebe os tokens e verifica se eles seguem as regras gramaticais da
linguagem.

Ele também constrói a AST (_Abstract Syntax Tree_), uma representação
estruturada do programa.

Atualmente, o Parser possui suporte para:

- Declarações com `create`.
- Atribuição de variáveis.
- Valores literais.
- Referências a variáveis.
- Chamadas de funções.
- Declarações de funções.
- Parâmetros e retornos.
- Carregamento de módulos.
- Expressões aritméticas.
- Expressões unárias.
- Expressões agrupadas.
- Operadores de comparação.
- Operadores lógicos.
- Precedência de operadores.
- Estruturas condicionais.
- Blocos de código.
- Loops `while`.
- Instruções `break` e `continue`.
- Verificação de uso de `break` e `continue` dentro de loops.
- Abertura de blocos na mesma linha ou na linha seguinte.

O Parser possui mecanismos de diagnóstico que já identificam diferentes
estruturas sintáticas inválidas, mas ainda precisa de melhorias para padronizar
e ampliar o tratamento de erros.

### AST — Árvore sintática abstrata

A AST representa a estrutura do código de maneira organizada.

Atualmente, existem estruturas para representar:

- Declarações de variáveis.
- Atribuições.
- Expressões.
- Valores literais.
- Referências a variáveis.
- Expressões binárias.
- Expressões unárias.
- Chamadas de funções.
- Acesso a membros.
- Declarações de funções.
- Instruções de retorno.
- Declarações de carregamento de módulos.
- Decisões condicionais.
- Blocos de código.
- Loops.
- Instruções de interrupção e continuação de loops.

### Interpreter — Interpretador

O interpretador percorre as estruturas produzidas pelo Parser e executa as
instruções.

Atualmente, ele consegue:

- Criar variáveis.
- Armazenar e recuperar valores.
- Atualizar variáveis existentes.
- Trabalhar com strings, números e booleanos.
- Avaliar expressões matemáticas.
- Realizar comparações.
- Avaliar expressões lógicas.
- Executar operações com curto-circuito.
- Executar a função nativa `view()`.
- Executar funções definidas pelo usuário.
- Passar parâmetros para funções.
- Retornar valores.
- Executar funções recursivas.
- Controlar ambientes e escopos.
- Executar estruturas condicionais.
- Executar loops `while`.
- Interpretar `break` e `continue`.
- Executar loops aninhados.
- Carregar módulos e acessar funções por namespace.
- Identificar variáveis não declaradas.
- Informar a localização de determinados erros de execução.

O interpretador utiliza `std::variant` para representar os valores em tempo de
execução.

```cpp
using RuntimeValue = std::variant<std::string, double, bool>;
```

---

## 9. Sistema de diagnóstico

A Hurtip possui uma implementação inicial de mensagens de erro com identificação
de linha e coluna em diferentes situações.

Exemplo de erro de sintaxe:

```hurtip
if (true)
    view("Hello")
```

Resultado ilustrativo:

```text
Hurtip Error: Line 2, column 5: Expected '{' to begin block
```

Exemplo de bloco não fechado:

```hurtip
if (true) {
    view("Hello")
```

Resultado ilustrativo:

```text
Hurtip Error: Line 3, column 1: Expected '}' to close block
```

Exemplo de argumento inválido:

```hurtip
view(10, )
```

Resultado ilustrativo:

```text
Hurtip Error: Line 1, column 10: Expected an expression, got: )
```

Exemplo de operador inválido:

```hurtip
create result = 10 + * 5
```

Resultado ilustrativo:

```text
Hurtip Error: Line 1, column 22: Expected an expression, got: *
```

Os testes realizados confirmam que o Parser consegue identificar diferentes
situações de sintaxe inválida, incluindo:

- Blocos sem abertura `{`.
- Blocos sem fechamento `}`.
- Condições com parênteses incompletos.
- Chamadas de função incompletas.
- Argumentos ausentes.
- Vírgulas sobrando.
- Expressões incompletas.
- Sequências inválidas de operadores.

O Lexer também possui testes para situações como caracteres inválidos e strings
não terminadas.

### Próximas melhorias

- Diagnósticos mais robustos e padronizados.
- Identificação consistente de linha e coluna.
- Mensagens específicas para fim de linha e fim de arquivo.
- Tratamento de erros léxicos.
- Tratamento de erros sintáticos.
- Tratamento de erros em tempo de execução.
- Maior previsibilidade no comportamento do Parser.
- Recuperação de erros para permitir diagnósticos adicionais quando possível.

---

## 10. Testes e confiabilidade

A Hurtip possui uma estrutura de testes organizada por responsabilidade,
separando programas demonstrativos dos testes de comportamento.

### Organização atual

```text
tests/
├── CMakeLists.txt
│
├── environment/
│   └── environment_test.hurtip
│
├── scopes/
│   ├── block_assignment_test.hurtip
│   ├── block_scope_test.hurtip
│   ├── else_scope_test.hurtip
│   ├── loop_control_scope_test.hurtip
│   └── while_scope_test.hurtip
│
├── functions/
│   ├── nested_functions_test.hurtip
│   ├── recursion_scope_test.hurtip
│   └── recursion_test.hurtip
│
├── modules/
│   ├── module_test.hurtip
│   └── modules/
│       └── math.hurtip
│
├── lexer/
│   └── lexer_test.cpp
│
└── parser/
    ├── function_braces_test.hurtip
    ├── parser_braces_test.hurtip
    ├── parser_duplicate_operator_test.hurtip
    ├── parser_incomplete_expression_test.hurtip
    ├── parser_invalid_argument_test.hurtip
    ├── parser_invalid_block_test.hurtip
    ├── parser_invalid_call_test.hurtip
    ├── parser_missing_brace_test.hurtip
    ├── parser_missing_parenthesis_test.hurtip
    ├── parser_test.cpp
    ├── parser_trailing_comma_test.hurtip
    └── while_braces_test.hurtip
```

### Validações realizadas

Foram executados testes para verificar:

- Declaração e atualização de variáveis.
- Escopos locais e globais.
- Isolamento de variáveis em blocos.
- Comportamento de `if` e `else`.
- Execução de loops.
- `break` e `continue`.
- Funções e parâmetros.
- Funções aninhadas.
- Recursividade.
- Sistema de módulos.
- Abertura de blocos em linhas separadas.
- Delimitadores incompletos.
- Argumentos inválidos.
- Expressões e operadores inválidos.
- Erros léxicos.
- Validação de entradas recebidas pelo Parser.

### Testes unitários

O Lexer possui 13 verificações unitárias, cobrindo palavras reservadas,
identificadores, valores, operadores, delimitadores, comentários, posições dos
tokens e erros léxicos.

O Parser possui 40 verificações unitárias, cobrindo declarações, expressões,
precedência, funções, estruturas de controle, sintaxe inválida e validação da
entrada de tokens.

### CTest

O projeto possui integração funcional com CTest no CMake principal:

```cmake
include(CTest)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
```

O arquivo `tests/CMakeLists.txt` cadastra os testes de integração e os
executáveis de testes unitários.

### Resultado mais recente

| Categoria                        | Testes aprovados |
| -------------------------------- | ---------------: |
| Testes de integração `.hurtip`   |               21 |
| Teste unitário do Lexer          |     1 executável |
| Teste unitário do Parser         |     1 executável |
| Total registrado no CTest        |               23 |
| Verificações unitárias do Lexer  |               13 |
| Verificações unitárias do Parser |               40 |

**Último resultado confirmado:**

```text
100% tests passed, 0 tests failed out of 23
```

Os 40 testes do Parser são verificações internas de um único executável
registrado no CTest, e não 40 testes CTest independentes.

### Executar os testes

Para executar toda a suíte:

```bash
ctest --test-dir build --output-on-failure
```

Para executar os testes unitários individualmente:

```bash
./build/tests/lexer_tests
./build/tests/parser_tests
```

Os testes de resistência com entradas extremas, expressões profundamente
aninhadas e fuzz testing ainda estão planejados para uma etapa posterior.

---

## 11. Suporte ao Visual Studio Code

A Hurtip possui uma extensão inicial para o Visual Studio Code, criada para
reconhecer a linguagem e facilitar a edição de arquivos `.hurtip`.

### Recursos disponíveis

- Reconhecimento da extensão `.hurtip`.
- Identificação da linguagem Hurtip.
- Realce de sintaxe.
- Destaque de palavras-chave.
- Destaque da função `view()`.
- Destaque de strings e números.
- Destaque de operadores.
- Fechamento automático de parênteses e aspas.
- Tema de ícones personalizado.

### Identidade visual

O projeto possui uma identidade visual própria, incluindo ícone para a Hurtip e
variações em diferentes resoluções.

O ícone dos arquivos `.hurtip` foi integrado ao tema Seti do VS Code,
preservando os ícones existentes para os demais tipos de arquivos.

O tema personalizado é identificado como **Seti + Hurtip**.

### Estrutura da extensão

```text
vscode-extension/
├── package.json
├── language-configuration.json
│
├── syntaxes/
│   └── hurtip.tmLanguage.json
│
└── icons/
    ├── hurtip-file.png
    ├── hurtip-file.svg
    ├── hurtip-icon-theme.json
    │
    └── seti/
        ├── seti-circular-128x128.png
        ├── seti.woff
        ├── vs-seti-icon-theme.json
        └── vs-seti-icon-theme.backup.json
```

A extensão ainda é experimental e está em desenvolvimento local. Sua publicação
em um marketplace ainda não foi realizada.

---

## 12. Tecnologias utilizadas

| Tecnologia       | Utilização                                     |
| ---------------- | ---------------------------------------------- |
| C++              | Implementação da linguagem                     |
| C++17            | Padrão da linguagem utilizada                  |
| CMake            | Configuração e gerenciamento da compilação     |
| GCC / G++        | Compilação do projeto                          |
| CTest            | Infraestrutura de testes automatizados         |
| VS Code          | Ambiente de desenvolvimento                    |
| TextMate Grammar | Realce de sintaxe no VS Code                   |
| JSON             | Configuração da extensão e dos temas de ícones |
| Git              | Controle de versão                             |

A escolha do C++ permite explorar estruturas de dados, gerenciamento de memória
e desempenho, além de oferecer uma base interessante para futuras experiências
com compiladores e sistemas embarcados.

---

## 13. Estrutura do projeto

A organização atual do repositório separa os componentes da linguagem por
responsabilidade.

```text
Hurtip/
├── CMakeLists.txt
├── README.md
├── .gitignore
│
├── assets/
│   ├── icon.png
│   ├── logo.png
│   ├── icons/
│   └── linux/
│       └── hurtip.desktop
│
├── include/
│   └── hurtip/
│       ├── ast/
│       │   └── ast.hpp
│       ├── environment/
│       │   └── environment.hpp
│       ├── interpreter/
│       │   └── interpreter.hpp
│       ├── lexer/
│       │   └── lexer.hpp
│       ├── parser/
│       │   └── parser.hpp
│       └── token.hpp
│
├── src/
│   ├── main.cpp
│   │
│   ├── environment/
│   │   └── environment.cpp
│   │
│   ├── interpreter/
│   │   ├── interpreter.cpp
│   │   ├── interpreter_expressions.cpp
│   │   └── interpreter_signals.hpp
│   │
│   ├── lexer/
│   │   └── lexer.cpp
│   │
│   └── parser/
│       └── parser.cpp
│
├── examples/
│   ├── hello.hurtip
│   └── program.hurtip
│
├── tests/
│   ├── CMakeLists.txt
│   ├── environment/
│   ├── functions/
│   ├── lexer/
│   ├── modules/
│   ├── parser/
│   └── scopes/
│
└── vscode-extension/
    ├── package.json
    ├── language-configuration.json
    ├── syntaxes/
    └── icons/
```

---

## 14. Compilação e execução

O projeto utiliza CMake para configurar e compilar a implementação em C++.

### Requisitos

- GCC / G++ com suporte a C++17.
- CMake 3.16 ou superior.
- Sistema operacional Linux ou ambiente compatível.

### Compilar

Na raiz do projeto, execute:

```bash
cmake -S . -B build
cmake --build build
```

### Executar

Para executar um arquivo Hurtip:

```bash
./build/hurtip examples/program.hurtip
```

O interpretador recebe o caminho do arquivo `.hurtip` como argumento e executa
as instruções presentes nele.

### Executar testes

Para executar um arquivo de teste manualmente:

```bash
./build/hurtip tests/functions/recursion_test.hurtip
```

Para executar toda a suíte automatizada:

```bash
ctest --test-dir build --output-on-failure
```

---

## 15. Estado atual do desenvolvimento

A Hurtip está sendo desenvolvida gradualmente, com foco na construção de uma
base sólida antes da implementação de recursos mais avançados.

### Componentes principais

| Componente                                | Estado                 |
| ----------------------------------------- | ---------------------- |
| Lexer                                     | Implementado           |
| Reconhecimento de palavras reservadas     | Implementado           |
| Reconhecimento de operadores              | Implementado           |
| Rastreamento de linha e coluna dos tokens | Implementado           |
| Parser                                    | Implementado           |
| AST                                       | Implementada           |
| Interpreter                               | Implementado           |
| Variáveis e valores no runtime            | Implementados          |
| Expressões                                | Implementadas          |
| Operações aritméticas                     | Implementadas          |
| Comparações                               | Implementadas          |
| Operadores lógicos                        | Implementados          |
| Estruturas condicionais                   | Implementadas          |
| Loops e controle de fluxo                 | Implementados          |
| Funções e parâmetros                      | Implementados          |
| Recursividade                             | Implementada           |
| Escopos                                   | Implementados          |
| Sistema inicial de módulos                | Implementado           |
| `load` de arquivos `.hurtip`              | Implementado           |
| `import` de bibliotecas externas          | Planejado              |
| Diagnósticos iniciais                     | Implementados          |
| Execução de arquivos `.hurtip` pela CLI   | Implementada           |
| Extensão inicial para VS Code             | Implementada           |
| Testes unitários do Lexer e Parser        | Implementados          |
| Testes automatizados com CTest            | Integrados e aprovados |

### Roadmap

**Núcleo da linguagem**

- [x] Lexer
- [x] Parser básico
- [x] AST
- [x] Interpreter básico
- [x] Execução de arquivos `.hurtip` por argumento na CLI
- [x] Valores e variáveis no runtime
- [x] Declaração de variáveis com `create`
- [x] Atribuição e atualização de variáveis
- [x] Strings, números e booleanos
- [x] Expressões
- [x] Operadores aritméticos (`+`, `-`, `*`, `/`)
- [x] Operadores unários (`+`, `-`)
- [x] Precedência matemática
- [x] Agrupamento de expressões com parênteses
- [x] Comentários de linha (`//`)

**Operadores e lógica**

- [x] Comparações (`==`, `!=`, `>`, `<`, `>=`, `<=`)
- [x] Operadores lógicos (`and`, `or`, `not`)
- [x] Precedência de operadores lógicos
- [x] Avaliação de curto-circuito
- [x] Validação de valores booleanos nas operações lógicas

**Controle de fluxo**

- [x] `if` / `else`
- [x] Decisões aninhadas
- [x] Blocos de código
- [x] Abertura de blocos na mesma linha ou na linha seguinte
- [x] `while`
- [x] `break`
- [x] `continue`
- [x] Loops aninhados
- [x] Escopo próprio para blocos de controle
- [x] Restauração de escopo após `break`, `continue` e `return`
- [ ] `for`

**Funções e escopos**

- [x] Funções definidas pelo usuário
- [x] Declaração de parâmetros
- [x] Chamadas de funções
- [x] Valores de retorno
- [x] `return`
- [x] Escopo local e global
- [x] Funções aninhadas
- [x] Recursividade
- [x] Isolamento de variáveis locais entre chamadas
- [ ] Closures
- [ ] Arrays e listas
- [ ] Estruturas de dados adicionais

**Sistema de módulos e bibliotecas**

- [x] Carregamento de arquivos `.hurtip` com `load`
- [x] Alias de módulos com `as`
- [x] Acesso a funções por namespace
- [x] Resolução de caminhos relativos ao arquivo que executa `load`
- [x] Cache de módulos carregados
- [x] Detecção de dependências circulares
- [x] Teste de integração entre módulos
- [ ] Isolamento completo de variáveis por módulo
- [ ] Sistema de importação de bibliotecas externas com `import`
- [ ] Arquitetura para integração com bibliotecas C/C++
- [ ] Biblioteca padrão
- [ ] Gerenciador de pacotes

**Parser, diagnósticos e confiabilidade**

- [x] Diagnósticos iniciais com identificação de linha
- [x] Identificação de linha e coluna nos erros sintáticos testados
- [x] Detecção de blocos sem abertura `{`
- [x] Detecção de blocos sem fechamento `}`
- [x] Detecção de parênteses não fechados em condições
- [x] Detecção de chamadas de função incompletas
- [x] Detecção de argumentos ausentes
- [x] Detecção de vírgula sobrando nos argumentos
- [x] Detecção de expressões incompletas
- [x] Detecção de operadores inválidos em expressões
- [x] Validação de lista de tokens vazia
- [x] Validação da presença do token `EndOfFile`
- [x] Testes unitários de erros léxicos
- [x] Testes unitários de erros sintáticos
- [ ] Mensagens padronizadas para fim de linha e fim de arquivo
- [ ] Testes de erros em tempo de execução
- [ ] Tratamento robusto e padronizado de erros
- [ ] Testes de recuperação do Parser
- [ ] Testes de resistência com entradas extremas
- [ ] Testes de expressões profundamente aninhadas
- [ ] Fuzz testing do Lexer e Parser

**Testes e organização do projeto**

- [x] Organização dos exemplos em `examples/`
- [x] Separação dos testes em `tests/`
- [x] Organização dos testes por categoria
- [x] Testes manuais de regressão
- [x] Testes de escopos
- [x] Testes de funções e recursividade
- [x] Testes de módulos
- [x] Testes de sintaxe válida e inválida
- [x] Testes automatizados de mensagens de erro
- [x] Testes unitários do Lexer
- [x] Testes unitários do Parser
- [x] Integração do CTest no `CMakeLists.txt`
- [x] Cadastro dos testes no `tests/CMakeLists.txt`
- [x] Execução automatizada de toda a suíte com CTest
- [x] 13 verificações unitárias do Lexer aprovadas
- [x] 40 verificações unitárias do Parser aprovadas
- [x] 23 testes registrados e aprovados pelo CTest

**Biblioteca e ferramentas**

- [ ] Biblioteca padrão
- [x] Estrutura inicial de CLI
- [ ] CLI / tooling avançado
- [ ] Sistema de documentação
- [ ] Gerenciador de pacotes
- [ ] Ferramentas de depuração

**Recursos de baixo nível e hardware**

- [ ] Controle de memória
- [ ] Tipos de dados de baixo nível
- [ ] Ponteiros e referências
- [ ] Acesso a recursos do sistema
- [ ] Interação com bibliotecas C/C++
- [ ] Comunicação com microcontroladores
- [ ] Suporte ao ESP32

---

## 16. Direção futura

A Hurtip começa como um interpretador experimental, mas sua visão vai além de
executar pequenos programas.

A intenção é construir uma linguagem que combine uma sintaxe acessível com
recursos técnicos capazes de atender a diferentes cenários de desenvolvimento.

Uma das direções prioritárias é explorar programação de baixo nível e sistemas
embarcados, permitindo que a linguagem possa futuramente interagir diretamente
com hardware e microcontroladores.

### Evolução do ecossistema

A evolução da Hurtip também envolve a construção de um ecossistema próprio.

A separação entre `load` e `import` faz parte dessa visão:

- `load` permite organizar e reutilizar arquivos `.hurtip` dentro de um projeto.
- `import` deverá permitir incorporar bibliotecas externas.
- A biblioteca padrão deverá oferecer funcionalidades essenciais.
- Um futuro gerenciador de pacotes poderá facilitar a instalação e o
  compartilhamento de bibliotecas.

Essa arquitetura poderá abrir caminho para um ecossistema de bibliotecas e
ferramentas construído em torno da Hurtip.

### Possibilidades futuras

A partir dessa base, o projeto poderá evoluir para:

- Desenvolvimento de aplicações.
- Programação de baixo nível.
- Sistemas embarcados.
- Jogos.
- Inteligência artificial.
- Integração com bibliotecas nativas.
- Comunicação com microcontroladores, especialmente ESP32.

A evolução será gradual, priorizando uma arquitetura bem estruturada,
previsibilidade e controle sobre o funcionamento interno da linguagem.

---

**Hurtip — Simples para começar. Flexível para evoluir.**
