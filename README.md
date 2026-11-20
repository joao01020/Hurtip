# Netuno

**Uma linguagem de programação experimental, simples e intuitiva, desenvolvida
em C++.**

O Netuno é um projeto experimental de criação de uma linguagem de programação
própria. Seu objetivo é explorar como uma linguagem pode tornar a programação
mais acessível, reduzir a complexidade desnecessária e, futuramente, oferecer
recursos para desenvolvimento de aplicações e sistemas embarcados.

A proposta é construir uma linguagem com sintaxe clara e fácil de compreender,
sem abandonar a possibilidade de evoluir para recursos mais avançados.

> O Netuno está em desenvolvimento. Atualmente, possui um interpretador básico
> capaz de executar arquivos `.nt`, uma arquitetura inicial composta por Lexer,
> Parser, AST e Interpreter, além de suporte inicial ao Visual Studio Code.

---

## 1. Visão do projeto

Muitas linguagens de programação oferecem grande flexibilidade e desempenho, mas
podem apresentar uma curva de aprendizado complexa para iniciantes.

O Netuno nasce da ideia de experimentar uma abordagem diferente: criar uma
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

O Netuno segue alguns princípios:

**Simplicidade:** comandos devem ser fáceis de compreender.

**Legibilidade:** o código deve comunicar claramente sua intenção.

**Evolução:** a linguagem deve começar pequena, mas possuir uma arquitetura que
permita crescer.

**Eficiência:** o desempenho deve ser considerado desde a concepção,
especialmente pensando em possíveis aplicações embarcadas.

**Acessibilidade:** reduzir barreiras para quem está começando a programar.

---

## 3. Sintaxe inicial

A sintaxe inicial do Netuno busca utilizar palavras intuitivas.

Exemplo:

```netuno
create name = "Netuno"
create age = 1

view("Minha primeira execução!")
view(name)
view(age)
```

### Declaração de variáveis

A palavra-chave `create` é utilizada para criar variáveis.

```netuno
create name = "Netuno"
create age = 1
```

A escolha de `create` busca tornar a declaração mais compreensível e intuitiva.

### Exibição de valores

A função nativa `view()` permite exibir valores no terminal.

```netuno
view("Hello, Netuno!")
```

Também é possível exibir o conteúdo de uma variável:

```netuno
create language = "Netuno"

view(language)
```

Atualmente, `view()` aceita exatamente um argumento.

### Tipos atualmente suportados pelo interpretador

| Tipo           | Exemplo    |
| -------------- | ---------- |
| Texto          | `"Netuno"` |
| Número inteiro | `10`       |

Internamente, os números são representados como `double` no interpretador,
embora a sintaxe numérica atual reconheça apenas números inteiros.

**Observação:** o Lexer já reconhece as palavras `true` e `false`, mas o suporte
a valores booleanos no interpretador ainda precisa ser implementado.

---

## 4. Arquitetura atual

O Netuno está sendo desenvolvido em C++ e utiliza uma arquitetura dividida em
etapas.

O fluxo atual de execução é:

```text
Arquivo .nt
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

```netuno
create name = "Netuno"
```

É transformado em tokens como:

- `Create`
- `Identifier`
- `Equal`
- `String`

#### Tokens reconhecidos

O Lexer possui reconhecimento para as seguintes categorias:

| Categoria              | Tokens                                                   |
| ---------------------- | -------------------------------------------------------- |
| Palavras reservadas    | `Create`, `True`, `False`                                |
| Identificadores        | `Identifier`                                             |
| Valores literais       | `String`, `Number`                                       |
| Atribuição             | `Equal` (`=`)                                            |
| Operadores aritméticos | `Plus` (`+`), `Minus` (`-`), `Star` (`*`), `Slash` (`/`) |
| Delimitadores          | `LeftParen`, `RightParen`, `Comma`                       |
| Estrutura do código    | `NewLine`, `EndOfFile`                                   |

#### Rastreamento de posição

Cada token armazena informações sobre sua localização no código-fonte:

- `line`: linha em que o token começa.
- `column`: coluna em que o token começa.

Essas informações formam a base para diagnósticos mais precisos, permitindo
identificar onde determinados elementos estão localizados.

O Lexer também reconhece palavras reservadas, diferenciando-as de
identificadores comuns.

**Importante:** o reconhecimento léxico dos operadores `+`, `-`, `*` e `/` já
está implementado, mas sua interpretação como operações matemáticas ainda está
em desenvolvimento.

### Parser — Análise sintática

O Parser recebe os tokens e verifica se eles seguem as regras gramaticais da
linguagem.

Ele também constrói a AST (_Abstract Syntax Tree_), uma representação
estruturada do programa.

Atualmente, o Parser possui suporte inicial para:

- Declarações com `create`.
- Valores literais.
- Referências a variáveis.
- Chamadas de funções.
- Argumentos separados por vírgula.
- Expressões primárias.

Também possui um mecanismo inicial de diagnóstico de erros sintáticos com
identificação de linha.

A implementação de expressões aritméticas com precedência de operadores ainda
será adicionada.

### AST — Árvore sintática abstrata

A AST representa a estrutura do código de maneira organizada.

Atualmente, existem estruturas para representar:

- Declarações de variáveis.
- Expressões.
- Chamadas de funções.
- Valores literais.
- Referências a variáveis.

Os nós da AST também armazenam informações sobre a linha de origem, permitindo
localizar determinados erros durante a execução.

A estrutura será expandida para representar operadores binários, operadores
unários e expressões agrupadas.

### Interpreter — Interpretador

O interpretador percorre as estruturas produzidas pelo Parser e executa as
instruções.

Atualmente, ele consegue:

- Criar variáveis.
- Armazenar valores.
- Recuperar valores armazenados.
- Executar a função nativa `view()`.
- Identificar variáveis não declaradas.
- Informar a linha de determinados erros de execução.

### Sistema de diagnóstico

O Netuno já possui uma implementação inicial de mensagens de erro com
identificação de linha.

Exemplo de erro de sintaxe:

```netuno
create name "Netuno"
```

Resultado:

```text
Netuno Error: Line 1: Expected '=' after variable name
```

Exemplo de erro durante a execução:

```netuno
create name = "Netuno"

view(unknown)
```

Resultado:

```text
Netuno
Netuno Error: Line 3: Undefined variable: unknown
```

O sistema ainda está em desenvolvimento. A identificação de linha já funciona em
alguns erros do Parser e do Interpreter. O rastreamento de coluna foi adicionado
à estrutura dos tokens, mas a localização completa por linha e coluna nas
mensagens de erro ainda precisa ser integrada e padronizada.

---

## 5. Suporte ao Visual Studio Code

O Netuno possui uma extensão inicial para o Visual Studio Code, criada para
reconhecer a linguagem e facilitar a edição de arquivos `.nt`.

### Recursos disponíveis

- Reconhecimento da extensão `.nt`.
- Identificação da linguagem Netuno.
- Realce de sintaxe.
- Destaque da palavra-chave `create`.
- Destaque da função `view()`.
- Destaque de strings e números.
- Destaque do operador de atribuição `=`.
- Fechamento automático de parênteses e aspas.
- Tema de ícones personalizado.

### Identidade visual

O projeto possui uma identidade visual própria, incluindo ícone para o Netuno e
variações em diferentes resoluções.

O ícone dos arquivos `.nt` foi integrado ao tema Seti do VS Code, preservando os
ícones existentes para os demais tipos de arquivos.

O tema personalizado é identificado como **Seti + Netuno**.

### Estrutura da extensão

```text
vscode-extension/
├── package.json
├── language-configuration.json
│
├── syntaxes/
│   └── netuno.tmLanguage.json
│
└── icons/
    ├── netuno-file.png
    ├── netuno-file.svg
    ├── netuno-icon-theme.json
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

## 6. Tecnologias utilizadas

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

## 7. Estrutura do projeto

A organização atual do repositório é:

```text
Netuno/
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
│       └── netuno.desktop
│
├── include/
│   └── netuno/
│       ├── lexer.hpp
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
│   └── program.nt
│
├── tests/
│   └── CMakeLists.txt
│
└── vscode-extension/
    ├── package.json
    ├── language-configuration.json
    ├── syntaxes/
    │   └── netuno.tmLanguage.json
    └── icons/
        ├── netuno-file.png
        ├── netuno-file.svg
        └── netuno-icon-theme.json
```

---

## 8. Compilação e execução

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

Para executar um arquivo Netuno:

```bash
./build/netuno examples/program.nt
```

Exemplo de saída:

```text
Hello, World!
Netuno Vitor
1
20
30
-5
22.5
true
false
```

A saída acima corresponde a um exemplo executado durante o desenvolvimento do
interpretador; ela não significa que todas as operações e tipos envolvidos já
estejam implementados como recursos gerais da linguagem.

---

## 9. Estado atual do desenvolvimento

O Netuno está sendo desenvolvido gradualmente, com foco na construção de uma
base sólida antes da implementação de recursos mais avançados.

### Componentes principais

| Componente                                | Estado                |
| ----------------------------------------- | --------------------- |
| Lexer                                     | Implementado          |
| Reconhecimento de palavras reservadas     | Implementado          |
| Reconhecimento de operadores aritméticos  | Implementado no Lexer |
| Rastreamento de linha e coluna dos tokens | Implementado no Lexer |
| Parser básico                             | Implementado          |
| AST básica                                | Implementada          |
| Interpreter básico                        | Implementado          |
| Diagnóstico inicial de erros              | Implementado          |
| Extensão inicial para VS Code             | Implementada          |

### Próximas etapas

**Etapa atual — Expressões**

- [ ] Formalizar a gramática de expressões.
- [ ] Adicionar expressões binárias à AST.
- [ ] Adicionar expressões unárias à AST.
- [ ] Adicionar expressões agrupadas à AST.
- [ ] Implementar precedência de operadores no Parser.
- [ ] Implementar avaliação de expressões no Interpreter.
- [ ] Adicionar suporte a valores booleanos no interpretador.

**Evolução da linguagem**

- [ ] Operadores de comparação.
- [ ] Operadores lógicos.
- [ ] Estruturas condicionais `if` e `else`.
- [ ] Blocos de código.
- [ ] Funções definidas pelo usuário.
- [ ] Estrutura `while`.
- [ ] Estrutura `for`.
- [ ] Instrução `return`.
- [ ] Biblioteca padrão.

**Infraestrutura e ferramentas**

- [ ] Melhorar o sistema de diagnóstico de erros.
- [ ] Integrar localização por linha e coluna nas mensagens de erro.
- [ ] Implementar testes automatizados.
- [ ] Melhorar a interface de linha de comando.
- [ ] Expandir o suporte ao Visual Studio Code.
- [ ] Documentar formalmente a gramática da linguagem.

**Objetivos futuros**

- Explorar compilação para código nativo.
- Investigar gerenciamento de memória.
- Desenvolver recursos de baixo nível.
- Explorar suporte a microcontroladores, especialmente ESP32.
- Investigar possibilidades de aplicação em inteligência artificial e
  desenvolvimento de jogos.

---

## 10. Direção futura

O Netuno começa como um interpretador experimental, mas sua visão vai além de
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

**Netuno — Simples para começar. Flexível para evoluir.**
