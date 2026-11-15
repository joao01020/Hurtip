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
> capaz de executar arquivos `.nt`.

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

### Parser — Análise sintática

O Parser recebe os tokens e verifica se eles seguem as regras gramaticais da
linguagem.

Ele também constrói a AST (_Abstract Syntax Tree_), uma representação
estruturada do programa.

### AST — Árvore sintática abstrata

A AST representa a estrutura do código de maneira organizada.

Atualmente, existem estruturas para representar:

- Declarações de variáveis.
- Expressões.
- Chamadas de funções.
- Valores literais.
- Referências a variáveis.

### Interpreter — Interpretador

O interpretador percorre as estruturas produzidas pelo Parser e executa as
instruções.

Atualmente, ele consegue:

- Criar variáveis.
- Armazenar valores.
- Recuperar valores armazenados.
- Executar a função nativa `view()`.

---

## 5. Tecnologias utilizadas

| Tecnologia | Utilização                                 |
| ---------- | ------------------------------------------ |
| C++        | Implementação da linguagem                 |
| C++17      | Padrão da linguagem utilizada              |
| CMake      | Configuração e gerenciamento da compilação |
| GCC / G++  | Compilação do projeto                      |
| VS Code    | Ambiente de desenvolvimento                |

A escolha do C++ permite explorar estruturas de dados, gerenciamento de memória
e desempenho, além de oferecer uma base interessante para futuras experiências
com compiladores e sistemas embarcados.

---

## 6. Estrutura do projeto

A organização atual do repositório é:

```text
Netuno/
├── CMakeLists.txt
├── README.md
├── .gitignore
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
└── tests/
    └── CMakeLists.txt
```

### Organização dos diretórios

- `include/netuno/`: declarações das estruturas e classes.
- `src/`: implementação dos componentes da linguagem.
- `examples/`: programas de exemplo escritos em Netuno.
- `tests/`: espaço reservado para testes automatizados.

---

## 7. Como executar

### Requisitos

- Compilador C++ com suporte a C++17.
- CMake 3.16 ou superior.
- Sistema operacional Linux, Windows ou macOS com ambiente de compilação
  configurado.

### Clonar o projeto

```bash
git clone <repository-url>
cd Netuno
```

### Configurar a compilação

```bash
cmake -S . -B build
```

### Compilar

```bash
cmake --build build
```

### Executar um programa

Crie um arquivo com a extensão `.nt`.

Exemplo: `examples/program.nt`

```netuno
create name = "Netuno"

view("Minha primeira execução!")
view(name)
```

Execute:

```bash
./build/netuno examples/program.nt
```

Saída esperada:

```text
Minha primeira execução!
Netuno
```

---

## 8. Interpretação e compilação

O primeiro estágio do Netuno utiliza um interpretador.

Essa escolha permite desenvolver e testar a linguagem de maneira gradual, sem
precisar implementar imediatamente um compilador completo.

Entretanto, a arquitetura está sendo pensada para permitir futuras experiências
com compilação.

Uma possível evolução seria:

```text
        Código .nt
             |
             v
       Lexer / Parser
             |
             v
            AST
             |
             v
    Representação interna
          (IR)
         /    \
        /      \
       v        v
Interpreter   Compiler
       |        |
       v        v
  Execução    Código nativo
```

A representação intermediária (IR) ainda não está implementada. Ela é uma
possibilidade arquitetural para compartilhar a análise do código entre
diferentes formas de execução.

---

## 9. Direção futura: sistemas embarcados

Um dos objetivos de longo prazo é investigar como o Netuno poderia simplificar o
desenvolvimento para microcontroladores e outros dispositivos embarcados.

A proposta é estudar uma linguagem que permita escrever instruções de maneira
mais simples, mantendo a possibilidade de gerar código eficiente.

Algumas áreas que poderão ser exploradas:

- Controle de GPIO.
- Leitura de sensores.
- Comunicação serial.
- Wi-Fi e Bluetooth.
- Controle de periféricos.
- Desenvolvimento para microcontroladores como ESP32.
- Geração de código nativo para arquiteturas específicas.

Esses recursos ainda não fazem parte da implementação atual.

A ideia é investigar como uma sintaxe mais simples poderia ser traduzida para
operações eficientes, sem comprometer o controle necessário em sistemas com
recursos limitados.

---

## 10. Roadmap

O desenvolvimento será realizado por etapas.

### Etapa 1 — Fundamentos

- [x] Criar a estrutura inicial do projeto.
- [x] Configurar CMake.
- [x] Implementar o Lexer.
- [x] Implementar o Parser.
- [x] Criar estruturas básicas da AST.
- [x] Implementar o interpretador inicial.
- [x] Executar arquivos externos `.nt`.
- [x] Implementar declaração de variáveis com `create`.
- [x] Implementar a função nativa `view()`.

### Etapa 2 — Melhorias da linguagem

- [ ] Sistema de erros com identificação de arquivo e linha.
- [ ] Suporte a números decimais.
- [ ] Operações matemáticas.
- [ ] Comparações e operadores lógicos.
- [ ] Condicionais.
- [ ] Estruturas de repetição.
- [ ] Mais funções nativas.
- [ ] Sistema de testes automatizados.

### Etapa 3 — Evolução da arquitetura

- [ ] Melhorar a estrutura da AST.
- [ ] Desenvolver um sistema de tipos mais completo.
- [ ] Implementar uma representação intermediária (IR).
- [ ] Estudar otimizações.
- [ ] Investigar a criação de um compilador.

### Etapa 4 — Exploração de sistemas embarcados

- [ ] Projetar uma interface para recursos de hardware.
- [ ] Estudar geração de código para microcontroladores.
- [ ] Explorar integração com ESP32.
- [ ] Desenvolver exemplos de automação e controle.
- [ ] Avaliar desempenho e consumo de recursos.

_O roadmap representa possibilidades e objetivos de desenvolvimento, não
funcionalidades já disponíveis._

---

## 11. Estado atual

**Versão:** 0.1.0 — Experimental

O Netuno já consegue ler arquivos `.nt`, analisar sua estrutura e executar
instruções básicas por meio de um interpretador desenvolvido em C++.

O projeto ainda está em sua fase inicial. Sua prioridade é consolidar os
fundamentos da linguagem antes de avançar para recursos mais complexos.

---

## 12. Licença

A licença do projeto ainda não foi definida.

---

**Netuno — Simplicidade para programar. Liberdade para evoluir.**
