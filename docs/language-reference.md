# Referência da linguagem

Este documento apresenta os recursos fundamentais da sintaxe da Hurtip.

## Variáveis

A palavra-chave `create` é utilizada para declarar variáveis:

```hurtip
create name = "Hurtip"
create age = 24
create is_active = true
```

As variáveis podem armazenar valores e ser utilizadas em expressões, operações, funções e decisões.

## Atribuição

É possível atualizar o valor de uma variável já declarada:

```hurtip
create counter = 0

counter = counter + 1
counter = counter + 1

view(counter)
```

## Exibição de valores

A função nativa `view()` exibe valores no terminal:

```hurtip
view("Hello, Hurtip!")

create language = "Hurtip"
create version = 1

view(language)
view(version)
view("Language:", language, "Version:", version)
```

Atualmente, `view()` aceita múltiplos argumentos.

## Tipos suportados

| Tipo | Exemplo | Representação interna |
|---|---|---|
| Texto | `"Hurtip"` | `std::string` |
| Número | `24` ou `1.5` | `double` |
| Booleano | `true` | `bool` |
| Array | `[10, 20, 30]` | `std::shared_ptr<ArrayValue>` |

Os valores são armazenados utilizando `std::variant`. Os arrays utilizam uma estrutura própria chamada `ArrayValue`, que armazena uma coleção de valores `RuntimeValue`.

O runtime utiliza `double` para representar números. O Lexer reconhece números inteiros e decimais.

## Comentários

Comentários de linha começam com `//`:

```hurtip
// Este é um comentário

create age = 24 // Comentário na mesma linha

view(age)
```

Os comentários são ignorados durante a execução.

## Operadores aritméticos

| Operador | Operação |
|---|---|
| `+` | Adição |
| `-` | Subtração |
| `*` | Multiplicação |
| `/` | Divisão |

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

A precedência matemática é respeitada. Parênteses podem ser utilizados para agrupar expressões.

```hurtip
create result = 10 + 5 * 2
create grouped_result = (10 + 5) * 2
```

A Hurtip também possui operadores unários positivos e negativos:

```hurtip
create negative = -10
create positive = +10
```

### Operador de incremento

O operador `++` incrementa uma variável numérica em uma unidade.

```hurtip
create counter = 0
counter++
view(counter)
```

Resultado: `1`

## Operadores de comparação

| Operador | Significado |
|---|---|
| `==` | Igual |
| `!=` | Diferente |
| `>` | Maior que |
| `<` | Menor que |
| `>=` | Maior ou igual |
| `<=` | Menor ou igual |

As comparações produzem valores booleanos.

## Operadores lógicos

| Operador | Significado |
|---|---|
| `and` | E lógico |
| `or` | OU lógico |
| `not` | Negação lógica |

Exemplo:

```hurtip
view(true and true)
view(true or false)
view(not true)
```

O interpretador respeita a precedência lógica e permite agrupamento com parênteses.

### Avaliação de curto-circuito

Os operadores `and` e `or` utilizam avaliação de curto-circuito. A segunda parte de uma expressão pode não ser avaliada quando o resultado já pode ser determinado pela primeira parte.

```hurtip
view(false and missing == 1)
view(true or missing == 1)
```

## Estruturas condicionais

A estrutura `if` executa instruções dependendo de uma condição:

```hurtip
create age = 24

if (age >= 18) {
    view("Maior de idade")
} else {
    view("Menor de idade")
}
```

Também é possível utilizar decisões aninhadas e `if` sem `else`.

## Blocos de código

As instruções podem ser agrupadas utilizando chaves `{}`:

```hurtip
if (true)
{
    view("Bloco executado")
}
```

Cada bloco possui seu próprio ambiente de variáveis.

## Loops

O `while` executa um bloco enquanto sua condição permanecer verdadeira:

```hurtip
create counter = 0

while (counter < 5) {
    view(counter)
    counter = counter + 1
}
```

### Loop `for`

O `for` permite executar repetições com inicialização, condição e incremento definidos em seu cabeçalho.

```hurtip
for (create i = 0; i < 5; i++) {
    view(i)
}
```

### Break e continue

`break` encerra o loop em que está inserido.

`continue` interrompe a repetição atual e passa para a próxima iteração.

A Hurtip também permite loops aninhados.

## Funções

A palavra-chave `function` declara uma função:

```hurtip
function greet()
{
    view("Hello, Hurtip!")
}

greet()
```

### Parâmetros e retorno

```hurtip
function sum(a, b)
{
    return a + b
}

view(sum(10, 20))
```

A instrução `return` devolve um resultado para quem chamou a função.

### Recursividade

Uma função pode chamar a si mesma:

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

## Escopos

A Hurtip utiliza ambientes para armazenar variáveis e controlar sua visibilidade.

Atualmente, o sistema oferece:

- Ambiente global.
- Ambientes locais de funções.
- Ambientes próprios para blocos.
- Busca de variáveis nos ambientes ancestrais.
- Atualização de variáveis existentes em ambientes superiores.
- Restauração do ambiente anterior após a execução de blocos.
- Isolamento de variáveis locais entre chamadas de funções.
- Ambientes persistentes associados aos módulos carregados.

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

### Limitações atuais

Closures e captura de ambientes léxicos ainda não foram implementados. O sistema de escopos das funções também não oferece todos os recursos de um modelo lexical completo.

## Recursos ainda não implementados

- Closures.
- Captura completa de ambientes léxicos.
- Métodos avançados para arrays.

Consulte [Arrays](arrays.md) para os recursos específicos de coleções e [Sistema de módulos](modules.md) para carregamento de arquivos e bibliotecas.
