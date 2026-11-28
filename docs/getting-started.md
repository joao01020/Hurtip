# Primeiros passos

Este documento explica como preparar o ambiente, compilar o interpretador e executar programas escritos em Hurtip.

## Requisitos

- GCC/G++ com suporte a C++17.
- CMake 3.16 ou superior.
- Linux ou ambiente compatível.

## Obter o projeto

```bash
git clone https://github.com/joao01020/Hurtip.git
cd Hurtip
```

## Compilar

Na raiz do projeto, execute:

```bash
cmake -S . -B build
cmake --build build
```

## Executar um programa

O interpretador recebe o caminho de um arquivo `.hurtip` como argumento:

```bash
./build/hurtip examples/program.hurtip
```

## Criar um primeiro programa

Crie um arquivo chamado `hello.hurtip`:

```hurtip
create name = "Hurtip"

view("Olá, " + name)
```

Execute:

```bash
./build/hurtip hello.hurtip
```

### Utilizando loops e incremento

A Hurtip permite executar repetições utilizando `for` e incrementar variáveis com o operador `++`.

```hurtip
for (create i = 0; i < 5; i++) {
    view(i)
}
```

## Executar os testes

Para executar toda a suíte automatizada:

```bash
ctest --test-dir build --output-on-failure
```

Para mais informações, consulte [Testes](testing.md).
