# Hurtip

**Uma linguagem de programação experimental, simples e intuitiva, desenvolvida
em C++.**

A Hurtip é um projeto experimental de criação de uma linguagem de programação
própria. Seu objetivo é explorar como uma linguagem pode tornar a programação
mais acessível, reduzir a complexidade desnecessária e, futuramente, oferecer
recursos para desenvolvimento de aplicações e sistemas embarcados.

A proposta é construir uma linguagem com sintaxe clara e fácil de compreender,
sem abandonar a possibilidade de evoluir para recursos mais avançados.

> A Hurtip está em desenvolvimento. Atualmente, possui um interpretador
> funcional capaz de executar arquivos `.hurtip`, uma arquitetura composta por
> Lexer, Parser, AST e Interpreter, suporte a variáveis, expressões, operações
> matemáticas, lógica, decisões e estruturas de repetição, além de suporte
> inicial ao Visual Studio Code.

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

---

## 3. Sintaxe inicial

A sintaxe inicial da Hurtip busca utilizar palavras intuitivas.

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
expressões, operações e decisões.

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

Também é possível exibir o conteúdo de uma variável:

```hurtip
create language = "Hurtip"

view(language)
```

Atualmente, `view()` aceita exatamente um argumento.

### Tipos atualmente suportados pelo interpretador

| Tipo     | Exemplo    | Representação interna |
| -------- | ---------- | --------------------- |
| Texto    | `"Hurtip"` | `std::string`         |
| Número   | `24`       | `double`              |
| Booleano | `true`     | `bool`                |

Internamente, os valores são armazenados utilizando `std::variant`.

**Observação:** o interpretador já trabalha com números representados como
`double`, mas a sintaxe numérica atual do Lexer reconhece apenas números
inteiros. O suporte a literais decimais ainda precisa ser implementado.

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

A Hurtip já possui suporte a diferentes operadores para realizar cálculos,
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

Os blocos são utilizados nas estruturas condicionais e nos loops.

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

| Recurso            | Estado        |
| ------------------ | ------------- |
| `if`               | Implementado  |
| `else`             | Implementado  |
| Decisões aninhadas | Implementadas |
| Blocos de código   | Implementados |
| `while`            | Implementado  |
| `break`            | Implementado  |
| `continue`         | Implementado  |
| Loops aninhados    | Implementados |
| `for`              | Pendente      |

---

## 6. Arquitetura atual

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

O Lexer possui reconhecimento para as seguintes categorias:

| Categoria                | Elementos                                                                                 |
| ------------------------ | ----------------------------------------------------------------------------------------- |
| Palavras reservadas      | `create`, `true`, `false`, `if`, `else`, `while`, `break`, `continue`, `and`, `or`, `not` |
| Identificadores          | Nomes de variáveis e identificadores                                                      |
| Valores literais         | `String`, `Number`, `True`, `False`                                                       |
| Atribuição               | `Equal` (`=`)                                                                             |
| Operadores aritméticos   | `Plus` (`+`), `Minus` (`-`), `Star` (`*`), `Slash` (`/`)                                  |
| Operadores de comparação | `EqualEqual`, `BangEqual`, `Greater`, `Less`, `GreaterEqual`, `LessEqual`                 |
| Delimitadores            | `LeftParen`, `RightParen`, `LeftBrace`, `RightBrace`, `Comma`                             |
| Estrutura do código      | `NewLine`, `EndOfFile`                                                                    |
| Controle de fluxo        | `Break`, `Continue`                                                                       |

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
- Verificação inicial de uso de `break` e `continue` dentro de loops.

O Parser possui mecanismos iniciais de diagnóstico, mas ainda precisa de
melhorias para lidar com erros sintáticos de maneira mais completa e
consistente.

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
- Decisões condicionais.
- Blocos de código.
- Loops.
- Instruções de interrupção e continuação de loops.

A estrutura também armazena informações de origem utilizadas nos diagnósticos.

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
- Executar estruturas condicionais.
- Executar loops `while`.
- Interpretar `break` e `continue`.
- Executar loops aninhados.
- Identificar variáveis não declaradas.
- Informar a linha de determinados erros de execução.

O interpretador utiliza `std::variant` para representar os valores em tempo de
execução.

Atualmente, os tipos internos são:

```cpp
using RuntimeValue = std::variant<std::string, double, bool>;
```

---

## 7. Sistema de diagnóstico

A Hurtip possui uma implementação inicial de mensagens de erro com identificação
de linha.

Exemplo de erro de sintaxe:

```hurtip
create name "Hurtip"
```

Resultado esperado:

```text
Hurtip Error: Line 1: Expected '=' after variable name
```

Exemplo de erro durante a execução:

```hurtip
create name = "Hurtip"

view(unknown)
```

Resultado esperado:

```text
Hurtip Error: Line 3: Undefined variable: unknown
```

O sistema ainda está em desenvolvimento.

A identificação de linha já funciona em determinados erros do Parser e do
Interpreter. O rastreamento de linha e coluna também existe na estrutura dos
tokens, mas a localização completa precisa ser integrada e padronizada em todas
as mensagens de erro.

As próximas melhorias incluem:

- Diagnósticos mais robustos do Parser.
- Identificação precisa de linha e coluna.
- Mensagens de erro mais claras.
- Tratamento consistente de erros léxicos, sintáticos e de execução.

---

## 8. Suporte ao Visual Studio Code

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

## 9. Tecnologias utilizadas

| Tecnologia       | Utilização                                     |
| ---------------- | ---------------------------------------------- |
| C++              | Implementação da linguagem                     |
| C++17            | Padrão da linguagem utilizada                  |
| CMake            | Configuração e gerenciamento da compilação     |
| GCC / G++        | Compilação do projeto                          |
| VS Code          | Ambiente de desenvolvimento                    |
| TextMate Grammar | Realce de sintaxe no VS Code                   |
| JSON             | Configuração da extensão e dos temas de ícones |
| Git              | Controle de versão                             |

A escolha do C++ permite explorar estruturas de dados, gerenciamento de memória
e desempenho, além de oferecer uma base interessante para futuras experiências
com compiladores e sistemas embarcados.

---

## 10. Estrutura do projeto

A organização do repositório inclui os seguintes componentes:

```text
Hurtip/
├── CMakeLists.txt
├── README.md
├── .gitignore
│
├── assets/
│   ├── icon.png
│   ├── logo.png
│   │
│   ├── icons/
│   │   ├── icon-16.png
│   │   ├── icon-32.png
│   │   ├── icon-48.png
│   │   ├── icon-64.png
│   │   ├── icon-128.png
│   │   └── icon-256.png
│   │
│   └── linux/
│       └── hurtip.desktop
│
├── include/
│   └── hurtip/
│       ├── token.hpp
│       ├── lexer.hpp
│       ├── ast.hpp
│       ├── parser.hpp
│       └── interpreter.hpp
│
├── src/
│   ├── main.cpp
│   ├── lexer.cpp
│   ├── parser.cpp
│   └── interpreter.cpp
│
├── examples/
│   ├── hello.hurtip
│   └── program.hurtip
│
├── tests/
│   └── CMakeLists.txt
│
└── vscode-extension/
    ├── package.json
    ├── language-configuration.json
    ├── syntaxes/
    │   └── hurtip.tmLanguage.json
    └── icons/
        ├── hurtip-file.png
        ├── hurtip-file.svg
        ├── hurtip-icon-theme.json
        └── seti/
            └── vs-seti-icon-theme.json
```

---

## 11. Compilação e execução

O projeto utiliza CMake para configurar e compilar a implementação em C++.

### Requisitos

- GCC / G++ com suporte a C++17.
- CMake.
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

---

## 12. Estado atual do desenvolvimento

A Hurtip está sendo desenvolvida gradualmente, com foco na construção de uma
base sólida antes da implementação de recursos mais avançados.

### Componentes principais

| Componente                                | Estado        |
| ----------------------------------------- | ------------- |
| Lexer                                     | Implementado  |
| Reconhecimento de palavras reservadas     | Implementado  |
| Reconhecimento de operadores              | Implementado  |
| Rastreamento de linha e coluna dos tokens | Implementado  |
| Parser básico                             | Implementado  |
| AST                                       | Implementada  |
| Interpreter                               | Implementado  |
| Variáveis e valores no runtime            | Implementados |
| Expressões                                | Implementadas |
| Operações aritméticas                     | Implementadas |
| Comparações                               | Implementadas |
| Operadores lógicos                        | Implementados |
| Estruturas condicionais                   | Implementadas |
| Loops e controle de fluxo                 | Implementados |
| Diagnósticos iniciais                     | Implementados |
| Execução de arquivos `.hurtip` pela CLI   | Implementada  |
| Extensão inicial para VS Code             | Implementada  |

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
- [x] `while`
- [x] `break`
- [x] `continue`
- [x] Loops aninhados
- [ ] `for`

**Diagnósticos e confiabilidade**

- [x] Diagnósticos iniciais com identificação de linha
- [x] Rastreamento de linha e coluna nos tokens
- [ ] Diagnósticos robustos do Parser
- [ ] Rastreamento completo de linha e coluna nos diagnósticos
- [ ] Testes de erros léxicos
- [ ] Testes de erros sintáticos
- [ ] Testes de erros em tempo de execução
- [ ] Tratamento robusto de erros

**Funções e estruturas de dados**

- [ ] Funções definidas pelo usuário
- [ ] Parâmetros de funções
- [ ] Valores de retorno
- [ ] `return`
- [ ] Escopo local e global
- [ ] Arrays e listas
- [ ] Estruturas de dados

**Biblioteca e ferramentas**

- [ ] Biblioteca padrão
- [ ] Sistema de módulos e importação
- [ ] CLI / tooling avançado
- [ ] Testes automatizados
- [ ] Documentação formal da gramática

**Recursos de baixo nível e hardware**

- [ ] Controle de memória
- [ ] Tipos de dados de baixo nível
- [ ] Acesso a recursos do sistema
- [ ] Comunicação com microcontroladores
- [ ] Suporte ao ESP32

---

## 13. Direção futura

A Hurtip começa como um interpretador experimental, mas sua visão vai além de
executar pequenos programas.

A intenção é construir uma linguagem que combine uma sintaxe acessível com
recursos técnicos capazes de atender a diferentes cenários de desenvolvimento.

Uma das direções prioritárias é explorar programação de baixo nível e sistemas
embarcados, permitindo que a linguagem possa futuramente interagir diretamente
com hardware e microcontroladores.

A partir dessa base, o projeto poderá evoluir para outras áreas, como
desenvolvimento de aplicações, jogos e inteligência artificial.

A evolução será gradual, priorizando uma arquitetura bem estruturada,
previsibilidade e controle sobre o funcionamento interno da linguagem.

---

**Hurtip — Simples para começar. Flexível para evoluir.**
