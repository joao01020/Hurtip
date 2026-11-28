# Sistema de módulos e bibliotecas

A Hurtip possui mecanismos separados para carregar arquivos da própria linguagem e importar bibliotecas nativas.

Essa separação utiliza duas instruções: `load` e `import`.

## 1. Load — arquivos Hurtip

A instrução `load` carrega outros arquivos `.hurtip`:

```hurtip
load "modules/greeting.hurtip"

view("O módulo foi carregado com sucesso!")
```

O alias `as` permite associar um nome ao módulo:

```hurtip
load "modules/math.hurtip" as math

view(math.sum(10, 20))
```

### Utilização de bibliotecas escritas em Hurtip

O mecanismo `load` também permite utilizar bibliotecas desenvolvidas na própria linguagem, desde que estejam disponíveis como arquivos `.hurtip`.

Isso permite que funcionalidades adicionais sejam implementadas e reutilizadas sem necessariamente modificar o interpretador em C++.

Exemplo:

```hurtip
load "libraries/Objetos.hurtip" as obj

create person = obj.objectCreate(["name", "age"], ["João", 24])
```

## Ambientes persistentes

Cada módulo carregado possui um ambiente persistente associado ao seu caminho de identificação.

Variáveis declaradas durante a execução do módulo continuam disponíveis nas chamadas posteriores de suas funções.

As funções pertencentes a um módulo utilizam o ambiente correspondente como ambiente ancestral. Cada chamada cria seu próprio ambiente local para parâmetros e variáveis da função.

Essa estrutura separa o estado de diferentes módulos, mantendo a possibilidade de acessar valores do ambiente global por meio da relação entre os ambientes.

Exemplo conceitual:

```hurtip
load "modules/counter.hurtip" as counter

view(counter.increment())
view(counter.increment())
view(counter.value())
```

O estado mantido pelo módulo pode ser reutilizado entre chamadas.

## Aliases e namespaces

Os módulos podem receber aliases utilizando `as`:

```hurtip
load "modules/math.hurtip" as mathematics

view(mathematics.sum(10, 20))
```

O namespace permite acessar funções do módulo sem misturar seus nomes diretamente com as funções globais.

O interpretador também controla conflitos entre aliases de módulos e bibliotecas nativas.

## Resolução de caminhos

Os caminhos informados em `load` podem ser relativos ao arquivo que contém a instrução:

```hurtip
load "modules/math.hurtip"
```

Os caminhos são normalizados e, quando possível, canonicalizados para identificar módulos de maneira consistente.

## Reutilização de módulos

O interpretador mantém um registro dos módulos carregados.

Quando um módulo já carregado é solicitado novamente, sua estrutura registrada pode ser reutilizada, evitando uma nova execução do arquivo.

Um alias adicional pode ser associado ao módulo já registrado.

## Dependências entre módulos

Um módulo pode carregar outros módulos, permitindo organizar dependências em diferentes níveis.

Exemplo de organização:

```text
modules/
├── services/
│   └── math_service.hurtip
├── helpers/
│   └── calculator.hurtip
└── application.hurtip
```

O interpretador detecta dependências circulares para evitar ciclos de carregamento indefinidos.

## Recuperação após falhas

Quando uma operação de carregamento falha, o interpretador restaura o contexto anterior.

Isso inclui informações como:

- Caminho do arquivo atualmente executado.
- Namespace atual.
- Ambiente de execução anterior.
- Estado de carregamento do módulo.

Quando a inicialização falha, registros temporários são limpos para evitar que um módulo parcialmente carregado permaneça registrado como válido.

## Recursos de load

- Carregamento de arquivos `.hurtip`.
- Aliases com `as`.
- Registro de funções por namespace.
- Chamadas de funções utilizando namespace.
- Resolução de caminhos relativos.
- Normalização e canonicalização de caminhos.
- Reutilização de módulos carregados.
- Ambientes persistentes por módulo.
- Separação dos ambientes de diferentes módulos.
- Preservação do estado entre chamadas.
- Resolução de dependências aninhadas.
- Detecção de dependências circulares.
- Verificação de conflitos entre aliases.
- Restauração do contexto após falhas.
- Limpeza de registros temporários em carregamentos malsucedidos.

## 2. Import — bibliotecas nativas

A instrução `import` incorpora bibliotecas nativas registradas no interpretador.

Diferentemente de `load`, que carrega arquivos `.hurtip`, o `import` utiliza funções implementadas em C++.

Exemplo:

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

## Biblioteca math

A primeira biblioteca nativa implementada é `math`.

| Função | Descrição | Exemplo |
|---|---|---|
| `math.sum(a, b)` | Soma dois valores numéricos | `math.sum(10, 20)` |

A função valida a quantidade e os tipos dos argumentos recebidos.

## Registro de bibliotecas

As bibliotecas nativas são registradas no interpretador por meio de uma interface interna.

O registro centralizado é realizado por `registerStandardLibraries()`, mantendo a inicialização das bibliotecas separada do ponto de entrada da aplicação.

## Diferença entre load e import

| Instrução | Finalidade | Origem |
|---|---|---|
| `load` | Carregar módulos e arquivos do projeto | Arquivos `.hurtip` |
| `import` | Importar bibliotecas nativas registradas | Implementações em C++ |

## Estado atual

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
| Dependências aninhadas | Implementadas |
| Detecção de dependências circulares | Implementada |
| Recuperação após falhas | Implementada |
| `import` de bibliotecas nativas | Implementado |
| Importação com alias | Implementada |
| Registro de funções nativas | Implementado |
| Registro centralizado de bibliotecas | Implementado |
| Biblioteca nativa `math` | Implementada |
| Função `math.sum()` | Implementada |
| Carregamento dinâmico de bibliotecas | Não implementado |
| API pública para bibliotecas de terceiros | Não implementada |
