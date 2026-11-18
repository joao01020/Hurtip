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
> capaz de executar arquivos `.nt`, além de suporte inicial ao Visual Studio
> Code.

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

### Tipos atualmente suportados

| Tipo           | Exemplo    |
| -------------- | ---------- |
| Texto          | `"Netuno"` |
| Número inteiro | `10`       |

Internamente, os números são representados como `double` no interpretador,
embora a sintaxe numérica atual reconheça apenas números inteiros.

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

O Lexer lê o código-fonte e identifica os elementos da linguagem.

Por exemplo:

```netuno
create name = "Netuno"
```

É transformado em uma sequência de tokens, como:

- `Create`
- `Identifier`
- `Equal`
- `String`

O Lexer também mantém informações sobre as linhas do código-fonte.

### Parser — Análise sintática

O Parser recebe os tokens e verifica se eles seguem as regras gramaticais da
linguagem.

Ele também constrói a AST (_Abstract Syntax Tree_), uma representação
estruturada do programa.

Atualmente, o Parser reconhece declarações, expressões, valores literais,
referências a variáveis e chamadas de funções.

Também possui um mecanismo inicial de diagnóstico de erros sintáticos com
identificação de linha.

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
alguns erros do Parser e do Interpreter, mas a localização por arquivo e a
padronização completa das mensagens ainda precisam ser implementadas.

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
    ├──
```
