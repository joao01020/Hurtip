# Hurtip

**Uma linguagem de programação experimental, simples e intuitiva, desenvolvida em C++.**

A Hurtip é um projeto experimental de criação de uma linguagem de programação própria. Seu objetivo é explorar como uma linguagem pode tornar a programação mais acessível, reduzir a complexidade desnecessária e oferecer recursos para desenvolvimento de aplicações, sistemas e dispositivos embarcados.

A proposta é construir uma linguagem com sintaxe clara e fácil de compreender, sem abandonar a possibilidade de evoluir para recursos mais avançados.

Atualmente, a Hurtip possui um interpretador funcional desenvolvido em C++17, com Lexer, Parser, AST e Interpreter.

## Recursos

A linguagem já oferece variáveis, expressões, operações matemáticas e lógicas, estruturas de controle como `if`, `while` e `for`, operador de incremento `++`, funções, recursividade, escopos, arrays, módulos com ambientes persistentes e importação de bibliotecas nativas.

Consulte [Recursos implementados](docs/features.md) para conhecer as funcionalidades disponíveis, suas limitações e os recursos ainda não implementados.

## Exemplo

```hurtip
create name = "Hurtip"
create age = 24

function greet(person)
{
    view("Olá, " + person)
}

greet(name)
view(age)
```

## Documentação

- [Primeiros passos](docs/getting-started.md)
- [Recursos implementados](docs/features.md)
- [Referência da linguagem](docs/language-reference.md)
- [Arrays](docs/arrays.md)
- [Sistema de módulos e bibliotecas](docs/modules.md)
- [Arquitetura](docs/architecture.md)
- [Diagnósticos](docs/diagnostics.md)
- [Testes](docs/testing.md)
- [Extensão para VS Code](docs/vscode-extension.md)

## Tecnologias

C++17, CMake, GCC/G++, CTest e Visual Studio Code.

## Estado do projeto

A Hurtip está em desenvolvimento experimental. Sua sintaxe, funcionalidades e arquitetura podem evoluir ao longo do projeto.

## Licença

Distribuído sob a licença [MIT](LICENSE).
