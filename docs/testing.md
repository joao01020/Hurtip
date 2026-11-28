# Testes

A Hurtip possui uma estrutura de testes organizada por responsabilidade, separando testes unitários e programas de integração.

## Organização

```text
tests/
├── CMakeLists.txt
├── run_test.cmake
├── arrays/
├── environment/
├── functions/
├── import/
├── lexer/
├── modules/
├── parser/
└── scopes/
```

## Áreas cobertas

A suíte contempla verificações para:

- Declaração e atualização de variáveis.
- Escopos locais e globais.
- Isolamento de variáveis em blocos.
- Comportamento de `if` e `else`.
- Loops, `break` e `continue`.
- Inicialização, condição e incremento de loops `for`.
- Incrementos de variáveis com o operador `++`.
- Funções, parâmetros e recursividade.
- Sistema de módulos.
- Isolamento de ambientes entre módulos.
- Persistência de estado dos módulos.
- Reutilização de módulos com aliases.
- Dependências aninhadas e circulares.
- Falhas durante o carregamento de módulos.
- Recuperação do interpretador após erros.
- Importação de bibliotecas nativas.
- Aliases de bibliotecas.
- Bibliotecas e funções inexistentes.
- Argumentos e tipos inválidos.
- Erros léxicos e sintáticos.
- Criação, acesso e atribuição em arrays.
- Arrays com diferentes tipos e arrays aninhados.
- Índices inválidos e fora dos limites.

## Testes unitários

O Lexer possui 13 verificações unitárias, cobrindo palavras reservadas, identificadores, valores, operadores, delimitadores, comentários, posições dos tokens e erros léxicos.

O Parser possui 40 verificações unitárias, cobrindo declarações, expressões, precedência, funções, estruturas de controle, sintaxe inválida e validação da entrada de tokens.

Essas verificações são executadas pelos respectivos executáveis de testes unitários, não necessariamente como casos independentes do CTest.

## Testes de arrays

A suíte inclui testes específicos para:

| Teste | Validação |
|---|---|
| `array_creation` | Criação de arrays |
| `array_mixed` | Elementos de diferentes tipos |
| `array_nested` | Arrays aninhados |
| `array_assignment` | Modificação de elementos |
| `array_length` | Propriedade `length` |
| `array_negative_index` | Índice negativo |
| `array_fractional_index` | Índice fracionário |
| `array_out_of_range` | Índice fora dos limites |
| `array_invalid_object` | Acesso a objeto que não é array |

## Testes de módulos

A suíte de módulos cobre:

| Área | Validação |
|---|---|
| Isolamento | Separação dos ambientes dos módulos |
| Estado | Persistência de variáveis entre chamadas |
| Aliases | Associação e reutilização de aliases |
| Dependências aninhadas | Carregamento de dependências |
| Dependências circulares | Identificação de ciclos |
| Dependências ausentes | Tratamento de arquivos inexistentes |
| Falhas de execução | Erros durante a inicialização |
| Recuperação | Restauração do estado após falhas |

## Integração com CTest

O projeto integra os testes ao CMake:

```cmake
include(CTest)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
```

O arquivo `tests/CMakeLists.txt` cadastra os testes de integração e os executáveis unitários.

## Executar os testes

Compile o projeto:

```bash
cmake -S . -B build
cmake --build build
```

Execute toda a suíte:

```bash
ctest --test-dir build --output-on-failure
```

Execute testes de arrays:

```bash
ctest --test-dir build -R array --output-on-failure
```

Execute testes de módulos:

```bash
ctest --test-dir build -R module --output-on-failure
```

Execute os testes unitários individualmente:

```bash
./build/tests/lexer_tests
./build/tests/parser_tests
```

Os comandos acima pressupõem que os executáveis estejam sendo gerados nesses caminhos pela configuração atual do CMake.
