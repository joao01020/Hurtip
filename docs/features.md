# Recursos implementados

Esta página apresenta o estado atual das funcionalidades da Hurtip.

A Hurtip é uma linguagem experimental em desenvolvimento. A lista diferencia os recursos que já estão disponíveis, as limitações conhecidas e as funcionalidades que ainda não foram implementadas.

O objetivo é documentar o que o interpretador consegue executar atualmente, sem confundir funcionalidades existentes com objetivos futuros do projeto.

## 1. Interpretador

A Hurtip possui um interpretador funcional desenvolvido em C++17.

Sua arquitetura é composta por quatro etapas principais:

- **Lexer:** realiza a análise léxica e transforma o código-fonte em tokens.
- **Parser:** analisa a estrutura dos tokens e constrói a árvore sintática.
- **AST:** representa a estrutura do programa.
- **Interpreter:** percorre a árvore sintática e executa as instruções.

O interpretador recebe arquivos com a extensão `.hurtip`.

## 2. Variáveis e valores

### Variáveis

A palavra-chave `create` é utilizada para declarar variáveis.

```hurtip
create name = "Hurtip"
create age = 24
create is_active = true
```

Também é possível atualizar o valor de uma variável já declarada.

```hurtip
create counter = 0

counter = counter + 1
counter = counter + 1

view(counter)
```

### Tipos suportados

| Tipo | Exemplo | Representação interna |
|---|---|---|
| Texto | `"Hurtip"` | `std::string` |
| Número | `24` ou `1.5` | `double` |
| Booleano | `true` | `bool` |
| Array | `[10, 20, 30]` | `std::shared_ptr<ArrayValue>` |

Os valores são armazenados utilizando `std::variant`.

```cpp
using RuntimeValue = std::variant<
    std::string,
    double,
    bool,
    std::shared_ptr<ArrayValue>
>;
```

Os arrays utilizam uma estrutura própria chamada `ArrayValue`, que armazena uma coleção de valores `RuntimeValue`. Isso permite representar arrays com diferentes tipos de elementos e arrays aninhados.

O runtime utiliza `double` para representar números. O Lexer reconhece números inteiros e decimais, como `10`, `1.5` e `100.25`.

### Exibição de valores

A função nativa `view()` permite exibir valores no terminal.

```hurtip
view("Hello, Hurtip!")

create language = "Hurtip"
create version = 1

view(language)
view(version)
```

Também aceita múltiplos argumentos.

```hurtip
view("Language:", "Hurtip", "Version:", 1)
```

### Comentários

Comentários de linha podem ser escritos utilizando `//`.

```hurtip
// Este é um comentário

create age = 24 // Comentário na mesma linha

view(age)
```

Os comentários são ignorados durante a execução.

## 3. Operadores e expressões

### Operadores aritméticos

| Operador | Operação | Exemplo |
|---|---|---|
| `+` | Adição | `10 + 5` |
| `-` | Subtração | `10 - 5` |
| `*` | Multiplicação | `10 * 5` |
| `/` | Divisão | `10 / 5` |

### Números decimais

O Lexer reconhece números com parte decimal.

```hurtip
create price = 19.90
create tax = 2.50

create total = price + tax

view(total)
```

Números inteiros e decimais utilizam o tipo interno `double`.

### Precedência matemática

O interpretador respeita a precedência dos operadores matemáticos. Parênteses permitem agrupar expressões.

```hurtip
create result = 10 + 5 * 2
create grouped_result = (10 + 5) * 2

view(result)
view(grouped_result)
```

### Operadores unários

São suportados os operadores unários positivos e negativos.

```hurtip
create negative = -10
create positive = +10

view(negative)
view(positive)
```

### Operador de incremento

O operador `++` permite incrementar uma variável numérica em uma unidade.

```hurtip
create counter = 0

counter++

view(counter)
```

Resultado:

```text
1
```

### Operadores de comparação

| Operador | Significado |
|---|---|
| `==` | Igual |
| `!=` | Diferente |
| `>` | Maior que |
| `<` | Menor que |
| `>=` | Maior ou igual |
| `<=` | Menor ou igual |

As comparações produzem valores booleanos.

### Operadores lógicos

| Operador | Significado |
|---|---|
| `and` | E lógico |
| `or` | OU lógico |
| `not` | Negação lógica |

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

O interpretador considera a precedência entre os operadores lógicos e permite agrupamento com parênteses.

```hurtip
view(true or false and false)
view((true or false) and false)
view(not false and true)
```

### Curto-circuito

Os operadores `and` e `or` possuem avaliação de curto-circuito.

A segunda parte de uma expressão pode não ser avaliada quando o resultado já pode ser determinado pela primeira parte.

```hurtip
view(false and missing == 1)
view(true or missing == 1)
```

Nesses exemplos, a variável `missing` não precisa ser avaliada.

## 4. Estruturas de controle

### Condicionais

A linguagem oferece `if` e `else`.

```hurtip
create age = 24

if (age >= 18) {
    view("Maior de idade")
} else {
    view("Menor de idade")
}
```

Também são suportadas decisões aninhadas e estruturas `if` sem `else`.

### Blocos de código

As instruções podem ser agrupadas utilizando chaves `{}`.

A abertura do bloco pode ficar na mesma linha da declaração ou na linha seguinte.

```hurtip
if (true)
{
    view("Bloco executado")
}
```

Cada bloco possui seu próprio ambiente de variáveis, permitindo isolamento de declarações locais.

### Repetição

A estrutura `while` executa um bloco enquanto sua condição permanecer verdadeira.

```hurtip
create counter = 0

while (counter < 5) {
    view(counter)
    counter = counter + 1
}
```

### Loop `for`

A estrutura `for` permite executar um bloco de código com inicialização, condição e incremento definidos em seu cabeçalho.

```hurtip
for (create i = 0; i < 5; i++) {
    view(i)
}
```

O cabeçalho possui três partes:

- Inicialização: executada antes da primeira iteração.
- Condição: determina se o loop deve continuar.
- Incremento: executado ao final de cada iteração.

### Controle de loops

- `break`: encerra o loop em que está inserido.
- `continue`: interrompe a iteração atual e passa para a próxima.

Exemplo:

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

É possível utilizar loops dentro de outros loops.

O comportamento de `break` em loops aninhados foi testado para garantir que a interrupção do loop interno não encerre automaticamente o loop externo.

### Estado dos recursos de controle

| Recurso | Estado |
|---|---|
| `if` | Implementado |
| `else` | Implementado |
| Decisões aninhadas | Implementadas |
| Blocos de código | Implementados |
| Escopo próprio para blocos de controle | Implementado |
| `while` | Implementado |
| `break` | Implementado |
| `continue` | Implementado |
| Loops aninhados | Implementados |
| `for` | Implementado |

## 5. Funções e escopos

### Declaração de funções

A palavra-chave `function` permite declarar funções.

```hurtip
function greet()
{
    view("Hello, Hurtip!")
}

greet()
```

### Parâmetros e retorno

As funções podem receber parâmetros e retornar valores com `return`.

```hurtip
function sum(a, b)
{
    return a + b
}

view(sum(10, 20))
```

### Chamadas entre funções

Uma função pode chamar outras funções.

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

Uma função pode chamar a si mesma.

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

**Limitação conhecida:** closures e captura de ambientes léxicos ainda não foram implementados. O sistema de escopos das funções também não oferece todos os recursos de um modelo lexical completo.

## 6. Arrays

A Hurtip possui uma implementação funcional de arrays integrada ao Parser, à AST e ao runtime.

### Recursos disponíveis

- Criação de arrays vazios.
- Criação de arrays preenchidos.
- Arrays numéricos.
- Arrays de strings.
- Arrays booleanos.
- Arrays com diferentes tipos de valores.
- Arrays aninhados.
- Acesso por índice.
- Acesso encadeado a arrays aninhados.
- Atribuição por índice.
- Modificação de elementos de arrays aninhados.
- Propriedade `length`.
- Exibição de arrays completos com `view()`.

### Exemplos

```hurtip
create numbers = [10, 20, 30, 40, 50]
create names = ["Ana", "João", "Maria"]
create states = [true, false, true]
create mixed = [10, "Hurtip", true, false]
create empty_array = []
```

Acesso por índice:

```hurtip
create numbers = [10, 20, 30]

view(numbers[0])
view(numbers[1])
view(numbers[2])
```

Atribuição por índice:

```hurtip
create numbers = [10, 20, 30]

numbers[0] = 50

view(numbers)
```

Arrays aninhados:

```hurtip
create matrix = [
    [1, 2],
    [3, 4]
]

matrix[1][0] = 99

view(matrix)
```

Propriedade `length`:

```hurtip
create numbers = [10, 20, 30, 40]

view(numbers.length)
```

### Validação de índices

O interpretador verifica:

- Índices negativos.
- Índices fracionários.
- Índices fora dos limites do array.
- Tentativas de acessar índices em valores que não são arrays.
- Índices que não são numéricos.

### Estado dos arrays

| Recurso | Estado |
|---|---|
| Estrutura de arrays no runtime | Implementada |
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
| `push()` | Não implementado |
| `pop()` | Não implementado |
| `remove()` | Não implementado |
| `contains()` | Não implementado |
| Iteração com `for` | Não implementada |
| Concatenação de arrays | Não implementada |
| Comparação estrutural | Não implementada |

## 7. Sistema de módulos

A Hurtip possui um mecanismo para carregar arquivos da própria linguagem utilizando `load`.

### Carregamento de arquivos

A instrução `load` carrega outros arquivos `.hurtip`.

```hurtip
load "modules/greeting.hurtip"

view("O módulo foi carregado com sucesso!")
```

### Aliases e namespaces

O alias `as` permite associar um nome ao módulo.

```hurtip
load "modules/math.hurtip" as math

view(math.sum(10, 20))
```

O namespace permite acessar funções registradas no módulo sem misturar seus nomes diretamente com as funções globais.

### Ambientes persistentes

Cada módulo carregado possui um ambiente persistente associado ao seu caminho de identificação.

As funções pertencentes a um módulo utilizam o ambiente correspondente como ambiente ancestral. Cada chamada ainda cria seu próprio ambiente local para parâmetros e variáveis da função.

Essa estrutura permite:

- Separar o estado de diferentes módulos.
- Preservar variáveis do módulo entre chamadas.
- Acessar valores do ambiente global quando necessário.
- Reutilizar o ambiente de um módulo já carregado.

### Resolução de caminhos

Os caminhos informados em `load` podem ser relativos ao arquivo que contém a instrução.

O sistema utiliza normalização e, quando possível, canonicalização para identificar módulos de maneira consistente.

### Reutilização de módulos

O interpretador mantém um registro dos módulos carregados.

Quando um módulo já carregado é solicitado novamente, sua estrutura registrada pode ser reutilizada, evitando uma nova execução do arquivo.

O alias utilizado na nova chamada é associado ao módulo já registrado.

### Dependências

O sistema permite carregar módulos que dependem de outros módulos.

Também contempla:

- Resolução de dependências aninhadas.
- Detecção de dependências circulares.
- Verificação de conflitos entre aliases.
- Separação dos ambientes de diferentes módulos.

### Recuperação após falhas

Quando uma operação de carregamento falha, o interpretador possui tratamento para restaurar o contexto anterior.

Isso inclui informações como:

- Caminho do arquivo atualmente executado.
- Namespace atual.
- Ambiente de execução anterior.
- Estado de carregamento do módulo.

Quando a inicialização de um módulo falha, os registros temporários são limpos para evitar que um módulo parcialmente carregado permaneça registrado como válido.

### Estado do sistema de módulos

| Recurso | Estado |
|---|---|
| `load` de arquivos `.hurtip` | Implementado |
| Alias de módulos com `as` | Implementado |
| Namespace de módulos | Implementado |
| Resolução de caminhos relativos | Implementada |
| Normalização de caminhos | Implementada |
| Reutilização de módulos carregados | Implementada |
| Ambientes persistentes por módulo | Implementados |
| Preservação de estado entre chamadas | Implementada |
| Resolução de dependências aninhadas | Implementada |
| Detecção de dependências circulares | Implementada |
| Recuperação após falhas de carregamento | Implementada |

## 8. Bibliotecas nativas

A instrução `import` permite incorporar bibliotecas nativas registradas no interpretador.

Diferentemente de `load`, que carrega arquivos `.hurtip`, o `import` atual utiliza um sistema de registro de funções implementadas em C++.

### Importação

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

### Biblioteca math

A primeira biblioteca nativa implementada é `math`.

| Função | Descrição | Exemplo |
|---|---|---|
| `math.sum(a, b)` | Soma dois valores numéricos | `math.sum(10, 20)` |

Resultado do exemplo:

```text
30
```

A função valida a quantidade e os tipos dos argumentos recebidos. Quando a chamada é inválida, o interpretador apresenta uma mensagem de erro.

### Registro de bibliotecas

As bibliotecas nativas são registradas no interpretador por meio de uma interface interna.

O registro centralizado é realizado por `registerStandardLibraries()`, mantendo a inicialização das bibliotecas separada do arquivo principal da aplicação.

### Estado das bibliotecas

| Recurso | Estado |
|---|---|
| `import` de bibliotecas nativas | Implementado |
| Importação com alias | Implementada |
| Registro de funções nativas | Implementado |
| Registro centralizado de bibliotecas | Implementado |
| Biblioteca nativa `math` | Implementada |
| Função `math.sum()` | Implementada |
| Carregamento dinâmico de bibliotecas | Não implementado |
| API pública para bibliotecas de terceiros | Não implementada |

## 9. Diagnósticos e erros

A Hurtip possui mecanismos de identificação e apresentação de erros em diferentes etapas da execução.

Os diagnósticos contemplam:

- Erros léxicos.
- Erros sintáticos.
- Erros durante a execução.
- Variáveis não declaradas.
- Erros de importação.
- Funções nativas inexistentes.
- Quantidade ou tipos inválidos de argumentos.
- Arquivos de módulos inexistentes.
- Dependências ausentes.
- Conflitos de namespace.
- Dependências circulares.
- Falhas durante a inicialização de módulos.
- Índices inválidos em arrays.

Os tokens armazenam informações de linha e coluna, que servem de base para diagnósticos de localização.

Consulte [Diagnósticos](diagnostics.md) para exemplos.

## 10. Ferramentas de desenvolvimento

### Extensão para Visual Studio Code

A Hurtip possui uma extensão inicial para o Visual Studio Code.

Recursos disponíveis:

- Reconhecimento da extensão `.hurtip`.
- Identificação da linguagem Hurtip.
- Realce de sintaxe.
- Destaque de palavras-chave.
- Destaque da função `view()`.
- Destaque de strings e números.
- Destaque de operadores.
- Fechamento automático de parênteses e aspas.
- Tema de ícones personalizado.

O projeto possui uma identidade visual própria. O ícone dos arquivos `.hurtip` foi integrado ao tema Seti do VS Code, preservando os ícones existentes para os demais tipos de arquivos.

O tema personalizado é identificado como **Seti + Hurtip**.

A extensão ainda é experimental e está em desenvolvimento local. Sua publicação em um marketplace ainda não foi realizada.

Consulte [Extensão para VS Code](vscode-extension.md).

## 11. Testes automatizados

A Hurtip possui uma estrutura de testes organizada por responsabilidade.

A suíte contempla verificações de:

- Declaração e atualização de variáveis.
- Escopos locais e globais.
- Isolamento de variáveis em blocos.
- Comportamento de `if` e `else`.
- Loops, `break` e `continue`.
- Funções, parâmetros e recursividade.
- Sistema de módulos.
- Isolamento de ambientes entre módulos.
- Persistência do estado dos módulos.
- Reutilização de módulos com aliases.
- Resolução de dependências aninhadas.
- Detecção de dependências circulares.
- Falhas durante o carregamento de módulos.
- Recuperação após erros.
- Importação de bibliotecas nativas.
- Arrays e indexação.
- Erros léxicos e sintáticos.

O Lexer possui 13 verificações unitárias e o Parser possui 40 verificações unitárias, conforme a documentação atual do projeto.

Essas verificações são executadas pelos respectivos executáveis de testes unitários, não necessariamente como casos independentes do CTest.

O projeto possui integração com CTest.

Para executar a suíte:

```bash
ctest --test-dir build --output-on-failure
```

Consulte [Testes](testing.md) para a organização e os comandos disponíveis.

## 12. Limitações e recursos futuros

Os itens abaixo não devem ser confundidos com funcionalidades já implementadas.

### Arrays

- Métodos `push()`, `pop()`, `remove()` e `contains()`.
- Iteração com `for`.
- Concatenação de arrays.
- Comparação estrutural.

### Funções e escopos

- Closures.
- Captura de ambientes léxicos.
- Modelo lexical completo de escopos.

### Bibliotecas

- Carregamento dinâmico de bibliotecas.
- API pública para bibliotecas de terceiros.

### Estruturas de controle
### Objetivos de evolução

A Hurtip também possui objetivos de pesquisa e desenvolvimento relacionados a:

- Exploração de interpretação e compilação.
- Integração com bibliotecas externas.
- Recursos de baixo nível.
- Possíveis aplicações em sistemas embarcados.
- Eficiência e simplicidade de implementação.

Esses objetivos representam direções futuras do projeto e não significam que o suporte a hardware ou dispositivos embarcados já esteja disponível.

## 13. Documentação relacionada

- [Primeiros passos](getting-started.md)
- [Referência da linguagem](language-reference.md)
- [Arrays](arrays.md)
- [Sistema de módulos](modules.md)
- [Arquitetura](architecture.md)
- [Diagnósticos](diagnostics.md)
- [Testes](testing.md)
- [Extensão para VS Code](vscode-extension.md)
