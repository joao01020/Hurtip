# Arrays

A Hurtip possui uma implementação de arrays integrada ao Parser, à AST e ao runtime.

Os arrays permitem armazenar coleções de valores em uma única variável. Podem conter números, textos, booleanos e diferentes tipos na mesma estrutura. Também podem armazenar outros arrays.

## Criação

Arrays são declarados utilizando colchetes `[]`, com elementos separados por vírgulas:

```hurtip
create numbers = [10, 20, 30, 40, 50]
create names = ["Ana", "João", "Maria"]
create states = [true, false, true]
create empty_array = []
```

## Diferentes tipos

Um mesmo array pode armazenar valores de tipos diferentes:

```hurtip
create mixed = [10, "Hurtip", true, false]

view(mixed)
```

## Acesso por índice

O primeiro elemento ocupa o índice `0`:

```hurtip
create numbers = [10, 20, 30]

view(numbers[0])
view(numbers[1])
view(numbers[2])
```

## Atribuição por índice

É possível modificar diretamente um elemento:

```hurtip
create numbers = [10, 20, 30]

numbers[0] = 50

view(numbers)
```

Resultado:

```text
[50, 20, 30]
```

## Arrays aninhados

Um array pode armazenar outros arrays:

```hurtip
create matrix = [
    [1, 2],
    [3, 4]
]

view(matrix[0])
view(matrix[1])
view(matrix[0][0])
view(matrix[1][0])
```

Também é possível modificar elementos internos:

```hurtip
matrix[1][0] = 99

view(matrix)
```

## Propriedade length

A propriedade `length` consulta a quantidade de elementos:

```hurtip
create numbers = [10, 20, 30, 40]

view(numbers.length)
```

Resultado:

```text
4
```

Também funciona com arrays vazios e arrays aninhados:

```hurtip
create empty = []
create matrix = [[1, 2], [3, 4]]

view(empty.length)
view(matrix.length)
view(matrix[0].length)
```

## Exibição

A função `view()` permite exibir arrays completos, incluindo estruturas aninhadas:

```hurtip
create numbers = [10, 20, 30]
create matrix = [[1, 2], [3, 4]]

view(numbers)
view(matrix)
```

## Validação de índices

O interpretador valida o acesso aos arrays. Atualmente, são tratados:

- Índices negativos.
- Índices fracionários.
- Índices fora dos limites.
- Tentativas de acessar índices em valores que não são arrays.
- Índices que não são numéricos.

## Estado dos recursos

| Recurso | Estado |
|---|---|
| Criação de arrays | Implementada |
| Arrays vazios | Implementados |
| Arrays numéricos | Implementados |
| Arrays de strings | Implementados |
| Arrays booleanos | Implementados |
| Arrays com diferentes tipos | Implementados |
| Arrays aninhados | Implementados |
| Acesso por índice | Implementado |
| Acesso encadeado | Implementado |
| Atribuição por índice | Implementada |
| Modificação de arrays aninhados | Implementada |
| Propriedade `length` | Implementada |
| Exibição com `view()` | Implementada |
| Validação de índices | Implementada |
| `push()`, `pop()`, `remove()` e `contains()` | Não implementados |
| Iteração com `for` | Não implementada |
| Concatenação de arrays | Não implementada |
| Comparação estrutural | Não implementada |

## Próximas funcionalidades

- `push()` — adicionar elementos ao final.
- `pop()` — remover e retornar o último elemento.
- `remove()` — remover um elemento pelo índice.
- `contains()` — verificar se determinado valor está presente.
- Concatenação de arrays.
- Comparação estrutural.
- Iteração com `for`.
