# Hurtip

**Uma linguagem de programação experimental, simples e intuitiva, desenvolvida
em C++.**

A Hurtip é um projeto experimental de criação de uma linguagem de programação
própria. Seu objetivo é explorar como uma linguagem pode tornar a programação
mais acessível, reduzir a complexidade desnecessária e oferecer recursos para
desenvolvimento de aplicações, sistemas e dispositivos embarcados.

A proposta é construir uma linguagem com sintaxe clara e fácil de compreender,
sem abandonar a possibilidade de evoluir para recursos mais avançados.

> A Hurtip está em desenvolvimento. Atualmente, possui um interpretador
> funcional capaz de executar arquivos `.hurtip`, uma arquitetura composta por
> Lexer, Parser, AST e Interpreter, suporte a variáveis, expressões, operações
> matemáticas, lógica, estruturas de controle, funções, recursividade, escopos,
> arrays, módulos e importação de bibliotecas nativas.

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
- Permitir integração com bibliotecas externas e recursos de baixo nível.

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

**Controle:** oferecer recursos que permitam ao programador compreender e
controlar o funcionamento dos programas.

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

| Tipo     | Exemplo        | Representação interna         |
| -------- | -------------- | ----------------------------- |
| Texto    | `"Hurtip"`     | `std::string`                 |
| Número   | `24`           | `double`                      |
| Booleano | `true`         | `bool`                        |
| Array    | `[10, 20, 30]` | `std::shared_ptr<ArrayValue>` |

Internamente, os valores são armazenados utilizando `std::variant`.

```cpp
using RuntimeValue = std::variant<
    std::string,
    double,
    bool,
    std::shared_ptr<ArrayValue>
>;
```

Os arrays utilizam uma estrutura própria chamada `ArrayValue`, que armazena uma
coleção de valores `RuntimeValue`. Isso permite representar arrays com
diferentes tipos de elementos e também arrays aninhados.

**Observação:** o runtime utiliza `double` para representar números, mas a
sintaxe numérica atual do Lexer ainda reconhece apenas números inteiros. O
suporte a literais decimais ainda não foi implementado.

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

| Recurso                                | Estado           |
| -------------------------------------- | ---------------- |
| `if`                                   | Implementado     |
| `else`                                 | Implementado     |
| Decisões aninhadas                     | Implementadas    |
| Blocos de código                       | Implementados    |
| Escopo próprio para blocos de controle | Implementado     |
| `while`                                | Implementado     |
| `break`                                | Implementado     |
| `continue`                             | Implementado     |
| Loops aninhados                        | Implementados    |
| `for`                                  | Não implementado |

---

## 6. Funções e escopos

A Hurtip possui suporte a funções definidas pelo programador.

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
implementados. O sistema de escopos das funções também não oferece todos os
recursos de um modelo lexical completo.

---

## 7. Arrays

A Hurtip possui uma implementação inicial de arrays, permitindo armazenar
coleções de valores em uma única variável.

Os arrays podem conter números, textos, booleanos e diferentes tipos de valores
na mesma estrutura.

### Criação de arrays

Os arrays são declarados utilizando colchetes `[]`, com seus elementos separados
por vírgulas.

```hurtip
create numbers = [10, 20, 30, 40, 50]
create names = ["Ana", "João", "Maria"]
create states = [true, false, true]
```

Também é possível criar arrays vazios:

```hurtip
create empty_array = []
```

### Arrays com diferentes tipos

A implementação permite armazenar valores de diferentes tipos em um mesmo array.

```hurtip
create mixed = [10, "Hurtip", true]

view(mixed)
```

### Acesso por índice

Os elementos podem ser acessados utilizando índices entre colchetes.

O primeiro elemento ocupa o índice `0`.

```hurtip
create numbers = [10, 20, 30]

view(numbers[0])
view(numbers[1])
view(numbers[2])
```

### Arrays aninhados

Um array pode armazenar outros arrays como elementos.

```hurtip
create matrix = [
    [1, 2],
    [3, 4],
    [5, 6]
]
```

É possível acessar os arrays internos:

```hurtip
view(matrix[0])
view(matrix[1])
```

Também é possível acessar diretamente os elementos de estruturas aninhadas:

```hurtip
view(matrix[0][0])
view(matrix[0][1])
view(matrix[1][0])
view(matrix[1][1])
```

### Exibição de arrays

A função `view()` permite exibir um array completo, incluindo estruturas
aninhadas.

```hurtip
create numbers = [10, 20, 30]
create matrix = [[1, 2], [3, 4]]

view(numbers)
view(matrix)
```

### Recursos de arrays

| Recurso                                              | Estado            |
| ---------------------------------------------------- | ----------------- |
| Estrutura de arrays no runtime                       | Implementada      |
| Criação de arrays                                    | Implementada      |
| Arrays vazios                                        | Implementados     |
| Arrays numéricos                                     | Implementados     |
| Arrays de strings                                    | Implementados     |
| Arrays booleanos                                     | Implementados     |
| Arrays com diferentes tipos                          | Implementados     |
| Arrays aninhados                                     | Implementados     |
| Acesso por índice                                    | Implementado      |
| Acesso encadeado                                     | Implementado      |
| Exibição com `view()`                                | Implementada      |
| Atribuição por índice                                | Não implementada  |
| Propriedade `length`                                 | Não implementada  |
| Métodos `push()`, `pop()`, `remove()` e `contains()` | Não implementados |
| Iteração com `for`                                   | Não implementada  |
| Concatenação de arrays                               | Não implementada  |
| Comparação estrutural                                | Não implementada  |

**Limitação atual:** os arrays podem ser criados, consultados e exibidos, mas
ainda não é possível modificar individualmente seus elementos por índice.

O próximo passo é permitir operações como:

```hurtip
create numbers = [10, 20, 30]

numbers[0] = 50

view(numbers)
```

Esse comportamento ainda está em desenvolvimento.

---

## 8. Sistema de módulos e bibliotecas

A Hurtip possui mecanismos separados para carregar arquivos da própria linguagem
e importar bibliotecas nativas.

Essa separação utiliza duas instruções com responsabilidades distintas: `load` e
`import`.

### 8.1. Load — arquivos da própria linguagem

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

### Recursos de `load` implementados

- Carregamento de arquivos `.hurtip`.
- Associação de alias com `as`.
- Registro de funções por namespace.
- Chamadas de funções utilizando o namespace do módulo.
- Resolução de caminhos relativos ao arquivo que executa `load`.
- Cache de módulos carregados.
- Detecção de dependências circulares.
- Testes de integração entre arquivos.

### 8.2. Import — bibliotecas nativas

A instrução `import` permite incorporar bibliotecas nativas registradas no
interpretador.

Diferentemente de `load`, que carrega arquivos `.hurtip`, o `import` atual
utiliza um sistema de registro de funções implementadas em C++.

Exemplo:

```hurtip
import "math"

create result = math.sum(10, 20)

view(result)
```

Também é possível utilizar aliases:

```hurtip
import "math" as mathematics

create result = mathematics.sum(10, 20)

view(result)
```

O alias permite escolher o nome utilizado para acessar a biblioteca dentro do
programa.

### Biblioteca math

A primeira biblioteca nativa implementada é `math`.

Atualmente, ela disponibiliza a função:

| Função           | Descrição                   | Exemplo            |
| ---------------- | --------------------------- | ------------------ |
| `math.sum(a, b)` | Soma dois valores numéricos | `math.sum(10, 20)` |

Exemplo completo:

```hurtip
import "math"

create result = math.sum(10, 20)

view(result)
```

Resultado:

```text
30
```

A função valida a quantidade e os tipos dos argumentos recebidos. Quando a
chamada é inválida, o interpretador apresenta uma mensagem de erro.

### Registro de bibliotecas

As bibliotecas nativas são registradas no interpretador por meio de uma
interface interna.

O registro centralizado é realizado por `registerStandardLibraries()`, que
mantém a inicialização das bibliotecas separada do arquivo principal da
aplicação.

Essa estrutura permite adicionar novas bibliotecas sem concentrar toda a
implementação no `main.cpp`.

### Diferença entre load e import

| Instrução | Finalidade                               | Origem                        |
| --------- | ---------------------------------------- | ----------------------------- |
| `load`    | Carregar módulos e arquivos do projeto   | Arquivos `.hurtip`            |
| `import`  | Importar bibliotecas nativas registradas | Implementações nativas em C++ |

Essa distinção evita misturar o mecanismo de organização de arquivos da própria
linguagem com o mecanismo de integração de bibliotecas nativas.

### Estado atual

| Recurso                                     | Estado           |
| ------------------------------------------- | ---------------- |
| `load` de arquivos `.hurtip`                | Implementado     |
| Alias de módulos com `as`                   | Implementado     |
| Namespace de módulos                        | Implementado     |
| Resolução de caminhos relativos             | Implementada     |
| Cache de módulos                            | Implementado     |
| Detecção de dependências circulares         | Implementada     |
| `import` de bibliotecas nativas             | Implementado     |
| Importação com alias                        | Implementada     |
| Registro de funções nativas                 | Implementado     |
| Registro centralizado de bibliotecas        | Implementado     |
| Biblioteca nativa `math`                    | Implementada     |
| Função `math.sum()`                         | Implementada     |
| Carregamento dinâmico de bibliotecas        | Não implementado |
| API pública para bibliotecas de terceiros   | Não implementada |
| Isolamento completo de variáveis por módulo | Não implementado |

---

## 9. Arquitetura atual

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

| Categoria                | Elementos                                                                                                                               |
| ------------------------ | --------------------------------------------------------------------------------------------------------------------------------------- |
| Palavras reservadas      | `create`, `true`, `false`, `if`, `else`, `while`, `function`, `return`, `load`, `import`, `as`, `break`, `continue`, `and`, `or`, `not` |
| Identificadores          | Nomes de variáveis e identificadores                                                                                                    |
| Valores literais         | `String`, `Number`, `True`, `False`                                                                                                     |
| Atribuição               | `Equal` (`=`)                                                                                                                           |
| Operadores aritméticos   | `Plus` (`+`), `Minus` (`-`), `Star` (`*`), `Slash` (`/`)                                                                                |
| Operadores de comparação | `EqualEqual`, `BangEqual`, `Greater`, `Less`, `GreaterEqual`, `LessEqual`                                                               |
| Delimitadores            | `LeftParen`, `RightParen`, `LeftBrace`, `RightBrace`, `LeftBracket`, `RightBracket`, `Comma`                                            |
| Estrutura do código      | `NewLine`, `EndOfFile`                                                                                                                  |
| Controle de fluxo        | `Break`, `Continue`, `Return`                                                                                                           |

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
- Importação de bibliotecas nativas.
- Aliases com `as`.
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
- Arrays literais com `[]`.
- Arrays vazios.
- Elementos separados por vírgulas.
- Vírgula final opcional em arrays.
- Acesso a elementos por índice.
- Acesso encadeado a arrays aninhados.

O Parser possui mecanismos de diagnóstico que identificam diferentes estruturas
sintáticas inválidas, mas ainda existem situações que precisam de tratamento
mais abrangente.

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
- Arrays literais (`ArrayExpression`).
- Acesso a índices (`IndexExpression`).
- Declarações de funções.
- Instruções de retorno.
- Declarações de carregamento de módulos.
- Declarações de importação.
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
- Criar arrays em tempo de execução.
- Armazenar valores de diferentes tipos em arrays.
- Criar arrays aninhados.
- Avaliar acesso a elementos por índice.
- Validar o tipo do objeto acessado.
- Validar índices numéricos, inteiros e não negativos.
- Verificar os limites dos arrays.
- Exibir arrays completos e aninhados com `view()`.
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
- Importar bibliotecas nativas.
- Executar funções registradas em bibliotecas nativas.
- Identificar variáveis não declaradas.
- Informar a localização de determinados erros de execução.

O interpretador utiliza `std::variant` para representar os valores em tempo de
execução.

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

A estrutura `ArrayValue` utiliza `std::vector` para armazenar os elementos e
`std::shared_ptr` para permitir que arrays sejam representados e compartilhados
como valores do runtime.

---

## 10. Sistema de diagnóstico

A Hurtip possui uma implementação de mensagens de erro com identificação de
linha e coluna em diferentes situações.

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

O sistema de importação de bibliotecas nativas também apresenta mensagens
específicas para bibliotecas inexistentes, funções não registradas e argumentos
inválidos.

O acesso a arrays também possui validações iniciais para objetos que não são
arrays, índices inválidos e posições fora dos limites.

---

## 11. Testes e confiabilidade

A Hurtip possui uma estrutura de testes organizada por responsabilidade,
separando programas demonstrativos dos testes de comportamento.

### Organização atual

```text
tests/
├── CMakeLists.txt
├── run_test.cmake
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
├── import/
│   ├── math_import_test.hurtip
│   ├── math_alias_test.hurtip
│   ├── unknown_import_test.hurtip
│   ├── unknown_function_test.hurtip
│   ├── invalid_native_arguments_test.hurtip
│   └── invalid_native_types_test.hurtip
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
- Importação de bibliotecas nativas.
- Importação com alias.
- Bibliotecas e funções inexistentes.
- Argumentos e tipos inválidos em funções nativas.
- Abertura de blocos em linhas separadas.
- Delimitadores incompletos.
- Argumentos inválidos.
- Expressões e operadores inválidos.
- Erros léxicos.
- Validação de entradas recebidas pelo Parser.

A implementação inicial de arrays já foi adicionada, mas ainda precisa de uma
categoria própria de testes automatizados.

### Testes unitários

O Lexer possui 13 verificações unitárias, cobrindo palavras reservadas,
identificadores, valores, operadores, delimitadores, comentários, posições dos
tokens e erros léxicos.

O Parser possui 40 verificações unitárias, cobrindo declarações, expressões,
precedência, funções, estruturas de controle, sintaxe inválida e validação da
entrada de tokens.

### CTest

O projeto possui integração com CTest no CMake principal:

```cmake
include(CTest)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
```

O arquivo `tests/CMakeLists.txt` cadastra os testes de integração e os
executáveis de testes unitários.

### Resultado mais recente confirmado

| Categoria                        |       Testes |
| -------------------------------- | -----------: |
| Testes de integração `.hurtip`   |           27 |
| Teste unitário do Lexer          | 1 executável |
| Teste unitário do Parser         | 1 executável |
| Total registrado no CTest        |           29 |
| Verificações unitárias do Lexer  |           13 |
| Verificações unitárias do Parser |           40 |

**Último resultado confirmado:**

```text
100% tests passed, 0 tests failed out of 29
```

Os 40 testes do Parser são verificações internas de um único executável
registrado no CTest, e não 40 testes CTest independentes.

### Próximos testes de arrays

- Testes unitários de criação de arrays.
- Testes de arrays vazios.
- Testes de arrays com tipos diferentes.
- Testes de arrays aninhados.
- Testes de acesso por índice.
- Testes de acesso encadeado.
- Testes de índices inválidos e fora dos limites.
- Testes de exibição recursiva.
- Testes de atribuição e modificação de elementos.
- Testes de regressão para arrays.

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

---

## 12. Suporte ao Visual Studio Code

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

## 13. Tecnologias utilizadas

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

## 14. Estrutura do projeto

A organização do repositório separa os componentes da linguagem por
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
│       ├── libraries/
│       │   ├── math.hpp
│       │   └── standard_library.hpp
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
│   ├── parser/
│   │   └── parser.cpp
│   │
│   └── libraries/
│       ├── math.cpp
│       └── standard_library.cpp
│
├── examples/
│   ├── hello.hurtip
│   └── program.hurtip
│
├── tests/
│   ├── CMakeLists.txt
│   ├── run_test.cmake
│   ├── environment/
│   ├── functions/
│   ├── import/
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

## 15. Compilação e execução

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

## 16. Estado atual do desenvolvimento

A Hurtip possui um núcleo funcional implementado em C++17, com Lexer, Parser,
AST e Interpreter integrados.

A linguagem oferece suporte a variáveis, expressões, operadores aritméticos,
comparações, lógica, estruturas condicionais, loops, funções, parâmetros,
retornos, recursividade e escopos.

O sistema de módulos permite carregar arquivos `.hurtip` com `load`, utilizar
aliases e acessar funções por namespace.

O sistema de bibliotecas nativas também está implementado. O `import` permite
incorporar bibliotecas registradas no interpretador, incluindo a biblioteca
`math` e sua função `math.sum()`.

A inicialização das bibliotecas é centralizada em `standard_library`, mantendo o
registro separado do ponto de entrada da aplicação.

### Arrays: estágio atual

A Hurtip já possui uma implementação inicial de arrays distribuída entre AST,
Parser, Environment e Interpreter.

Atualmente, é possível:

- Criar arrays vazios e preenchidos.
- Armazenar números, strings e booleanos.
- Combinar diferentes tipos em um mesmo array.
- Criar arrays aninhados.
- Acessar elementos por índice.
- Acessar elementos de arrays aninhados com índices encadeados.
- Exibir arrays completos com `view()`.

O próximo passo é implementar a atribuição por índice, permitindo modificar
elementos individuais e também elementos de arrays aninhados.

Depois disso, serão desenvolvidos recursos como `length`, métodos de manipulação
e iteração com `for`.

### Componentes principais

| Componente                                | Estado        |
| ----------------------------------------- | ------------- |
| Lexer                                     | Implementado  |
| Reconhecimento de palavras reservadas     | Implementado  |
| Reconhecimento de operadores              | Implementado  |
| Rastreamento de linha e coluna dos tokens | Implementado  |
| Parser                                    | Implementado  |
| AST                                       | Implementada  |
| Interpreter                               | Implementado  |
| Variáveis e valores no runtime            | Implementados |
| Expressões                                | Implementadas |
| Operações aritméticas                     | Implementadas |
| Comparações                               | Implementadas |
| Operadores lógicos                        | Implementados |
| Estruturas condicionais                   | Implementadas |
| Loops e controle de fluxo                 | Implementados |
| Funções e parâmetros                      | Implementados |
| Recursividade                             | Implementada  |
| Escopos                                   | Implementados |
| Criação e leitura de arrays               | Implementadas |
| Arrays aninhados                          | Implementados |
| Sistema de módulos                        | Implementado  |
| `load` de arquivos `.hurtip`              | Implementado  |
| `import` de bibliotecas nativas           | Implementado  |
| Registro centralizado de bibliotecas      | Implementado  |
| Biblioteca nativa `math`                  | Implementada  |
| Diagnósticos iniciais                     | Implementados |
| Execução de arquivos `.hurtip` pela CLI   | Implementada  |
| Extensão inicial para VS Code             | Implementada  |
| Testes unitários do Lexer e Parser        | Implementados |
| Testes automatizados com CTest            | Integrados    |

---

**Hurtip — Simples para começar. Flexível para evoluir.**
