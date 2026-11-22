# Estado atual do desenvolvimento — Hurtip

## Núcleo da linguagem

- [x] Lexer
- [x] Parser básico
- [x] AST
- [x] Interpreter básico
- [x] Execução de arquivos `.hurtip` por argumento na CLI
- [x] Valores e variáveis no runtime
- [x] Declaração de variáveis com `create`
- [x] Atribuição e atualização de variáveis
- [x] Tipos básicos: strings, números e booleanos
- [x] Expressões
- [x] Operadores aritméticos (`+`, `-`, `*`, `/`)
- [x] Operadores unários (`+`, `-`)
- [x] Precedência matemática
- [x] Agrupamento de expressões com parênteses
- [x] Comentários de linha (`//`)

## Operadores e lógica

- [x] Comparações (`==`, `!=`, `>`, `<`, `>=`, `<=`)
- [x] Operadores lógicos (`and`, `or`, `not`)
- [x] Precedência de operadores lógicos
- [x] Avaliação de curto-circuito
- [x] Validação de valores booleanos nas operações lógicas

## Controle de fluxo

- [x] `if` / `else`
- [x] Decisões aninhadas
- [x] Blocos de código
- [x] Abertura de blocos na mesma linha ou na linha seguinte
- [x] `while`
- [x] `break`
- [x] `continue`
- [x] Loops aninhados
- [x] Escopo próprio para blocos de controle
- [x] Restauração de escopo após `break`, `continue` e `return`
- [ ] `for`

## Funções e escopos

- [x] Funções definidas pelo usuário
- [x] Declaração de parâmetros
- [x] Chamadas de funções
- [x] Valores de retorno
- [x] `return`
- [x] Escopo local e global
- [x] Funções aninhadas
- [x] Recursividade
- [x] Isolamento de variáveis locais entre chamadas
- [ ] Closures

## Arrays

- [x] Estrutura de arrays no runtime
- [x] Criação de arrays
- [x] Arrays vazios
- [x] Arrays numéricos
- [x] Arrays de strings
- [x] Arrays booleanos
- [x] Arrays com diferentes tipos de valores
- [x] Arrays aninhados
- [x] Acesso a elementos por índice
- [x] Acesso encadeado a elementos de arrays aninhados
- [x] Atribuição e modificação de elementos por índice
- [x] Modificação de elementos em arrays aninhados
- [x] Exibição de arrays com `view()`
- [x] Propriedade `length`
- [x] Validação de índices negativos
- [x] Validação de índices fracionários
- [x] Validação de índices fora dos limites
- [x] Validação de objetos que não são arrays
- [x] `push(value)` — adiciona elementos ao final
- [x] `pop()` — remove e retorna o último elemento
- [x] `remove(index)` — remove e retorna um elemento por índice
- [x] `insert(index, value)` — insere um elemento em determinada posição
- [x] `contains(value)` — verifica se um valor existe
- [x] `indexOf(value)` — encontra a posição de um valor
- [x] `clear()` — esvazia o array
- [x] `reverse()` — inverte a ordem dos elementos
- [ ] Iteração de arrays com `for`
- [ ] Concatenação de arrays
- [ ] Comparação estrutural de arrays
- [ ] Definição formal da semântica de cópia e referência
- [ ] Estruturas de dados adicionais

## Sistema de módulos

- [x] Carregamento de arquivos `.hurtip` com `load`
- [x] Alias de módulos com `as`
- [x] Acesso a funções por namespace
- [x] Resolução de caminhos relativos ao arquivo que executa `load`
- [x] Cache de módulos carregados
- [x] Detecção de dependências circulares
- [x] Teste de integração entre módulos
- [ ] Isolamento completo de variáveis por módulo

## Sistema de importação de bibliotecas nativas

- [x] Palavra-chave `import` no Lexer
- [x] Token `Import`
- [x] Token `As` para aliases
- [x] Análise sintática de declarações `import`
- [x] Importação de bibliotecas nativas por nome
- [x] Importação com alias
- [x] Acesso a funções nativas por namespace
- [x] Registro de funções nativas no Interpreter
- [x] Registro centralizado das bibliotecas padrão
- [x] Estrutura inicial para cadastro de novas bibliotecas
- [x] Biblioteca nativa `math`
- [x] Função matemática `math.sum()`
- [x] Validação de quantidade de argumentos
- [x] Validação de tipos dos argumentos
- [x] Detecção de bibliotecas inexistentes
- [x] Detecção de funções inexistentes em bibliotecas
- [x] Tratamento de erros em funções nativas
- [ ] Testes automatizados de conflitos entre aliases de módulos e bibliotecas
- [ ] Carregamento dinâmico de bibliotecas externas
- [ ] API pública para desenvolvimento de bibliotecas por terceiros
- [ ] Documentação da API de bibliotecas nativas

## Parser, diagnósticos e confiabilidade

- [x] Diagnósticos iniciais com identificação de linha
- [x] Identificação de linha e coluna nos erros sintáticos testados
- [x] Detecção de blocos sem abertura `{`
- [x] Detecção de blocos sem fechamento `}`
- [x] Detecção de parênteses não fechados em condições
- [x] Detecção de chamadas de função incompletas
- [x] Detecção de argumentos ausentes
- [x] Detecção de vírgula sobrando nos argumentos
- [x] Detecção de expressões incompletas
- [x] Detecção de operadores inválidos em expressões
- [x] Validação de lista de tokens vazia
- [x] Validação da presença do token `EndOfFile`
- [x] Reconhecimento de números decimais no Lexer
- [ ] Mensagens padronizadas para fim de linha e fim de arquivo
- [x] Testes de erros léxicos
- [x] Testes de erros sintáticos
- [ ] Testes abrangentes de erros em tempo de execução
- [ ] Tratamento robusto e padronizado de erros
- [ ] Testes de recuperação do parser
- [ ] Testes de resistência com entradas extremas
- [ ] Testes de expressões profundamente aninhadas
- [ ] Fuzz testing do Lexer e Parser

## Testes e organização do projeto

- [x] Organização dos exemplos em `examples/`
- [x] Separação dos testes em `tests/`
- [x] Organização dos testes por categoria
- [x] Organização dos testes de arrays em subpastas (`basics`, `indexing`,
      `mutation` e `search`)
- [x] Testes manuais de regressão
- [x] Testes de escopos
- [x] Testes de funções e recursividade
- [x] Testes de módulos
- [x] Testes de sintaxe válida e inválida
- [x] Integração inicial do CTest no `CMakeLists.txt`
- [x] Cadastro dos testes no `tests/CMakeLists.txt`
- [x] Execução automatizada da suíte com CTest
- [x] Testes automatizados de mensagens de erro
- [x] Testes unitários do Lexer
- [x] Testes unitários do Parser
- [x] 40 verificações unitárias do Parser aprovadas
- [x] Testes de importação de bibliotecas nativas
- [x] Testes de importação com alias
- [x] Testes de bibliotecas e funções inexistentes
- [x] Testes de argumentos e tipos inválidos em funções nativas
- [x] Testes automatizados de criação de arrays
- [x] Testes de arrays numéricos, strings e valores mistos
- [x] Testes de arrays aninhados
- [x] Testes de acesso por índice
- [x] Testes de atribuição e modificação de elementos
- [x] Testes da propriedade `length`
- [x] Testes de índices negativos e fracionários
- [x] Testes de índices fora dos limites
- [x] Testes de acesso a objetos que não são arrays
- [x] Testes de `push()`, `pop()`, `remove()` e `insert()`
- [x] Testes de `contains()`, `indexOf()`, `clear()` e `reverse()`
- [x] Testes de argumentos inválidos nos métodos de arrays
- [x] Testes de regressão para arrays
- [x] 55 testes registrados no CTest
- [x] 55 testes aprovados na última execução confirmada

## Biblioteca e ferramentas

- [ ] Biblioteca padrão completa
- [x] Estrutura inicial de registro centralizado da biblioteca padrão
- [x] Estrutura inicial de CLI
- [ ] CLI / tooling avançado
- [ ] Sistema de documentação
- [ ] Gerenciador de pacotes
- [ ] Ferramentas de depuração
- [x] Extensão experimental para VS Code
- [x] Syntax highlighting para arquivos `.hurtip`
- [x] Configuração inicial do IntelliSense para o projeto

## Recursos de baixo nível e hardware

- [ ] Controle de memória
- [ ] Tipos de dados de baixo nível
- [ ] Ponteiros e referências
- [ ] Acesso a recursos do sistema
- [ ] Interação com bibliotecas C/C++
- [ ] Comunicação com microcontroladores
- [ ] Suporte ao ESP32

---

## Legenda

- `[x]` Implementado e validado conforme o estágio indicado.
- `[ ]` Pendente de implementação ou validação.

**Observação:** os itens marcados como implementados representam os recursos que
já foram desenvolvidos e testados no estágio atual. Isso não significa que todas
as suas possíveis aplicações e situações extremas já foram validadas.

## Estado atual

A Hurtip já possui um núcleo funcional desenvolvido em C++17, com Lexer, Parser,
AST e Interpreter integrados.

A linguagem oferece variáveis, expressões, operadores, controle de fluxo,
funções, recursividade, escopos e um sistema inicial de módulos.

O sistema de importação de bibliotecas nativas também foi implementado. Já é
possível importar bibliotecas pelo nome, utilizar aliases e chamar funções
nativas através de namespaces. A biblioteca `math` é a primeira implementação
desse sistema.

A arquitetura de registro das bibliotecas foi centralizada em
`standard_library`, evitando que o `main.cpp` precise registrar individualmente
cada biblioteca.

O projeto possui testes unitários do Lexer e Parser e uma suíte automatizada
integrada ao CTest. São 40 verificações unitárias do Parser e 55 testes
registrados no CTest. Na última execução informada, todos os 55 testes passaram.

## Arrays: estágio atual

A Hurtip já possui uma implementação funcional de arrays integrada ao AST,
Parser e runtime.

É possível criar arrays vazios, numéricos, de strings, booleanos, mistos e
aninhados. Também é possível acessar elementos por índice, modificar seus
valores, acessar estruturas aninhadas e exibir arrays completos com `view()`.

A propriedade `length` permite consultar a quantidade de elementos de um array.

Exemplo:

```hurtip
create numbers = [10, 20, 30, 40]

view(numbers)
view(numbers[0])
view(numbers.length)

create matrix = [
    [1, 2],
    [3, 4]
]

view(matrix[1][0])
```

Também é possível modificar elementos diretamente por índice:

```hurtip
create numbers = [10, 20, 30]

numbers[0] = 50

view(numbers)
```

A linguagem possui oito métodos de arrays implementados:

```hurtip
create numbers = [10, 20, 30]

numbers.push(40)
view(numbers)

view(numbers.pop())

view(numbers.contains(20))
view(numbers.indexOf(20))

numbers.insert(1, 15)
view(numbers)

view(numbers.remove(0))

numbers.reverse()
view(numbers)

view(numbers.clear())
view(numbers)
```

Os métodos contam com validações de quantidade de argumentos e, quando
aplicável, de índices.

A suíte automatizada também cobre os comportamentos principais desses métodos,
incluindo argumentos inválidos.

Os testes de arrays foram organizados em quatro categorias:

- `basics/` — criação, tipos, atribuição, tamanho e arrays aninhados.
- `indexing/` — acesso e validação de índices.
- `mutation/` — inserção, remoção, limpeza e inversão.
- `search/` — busca e localização de elementos.

## Foco atual do desenvolvimento

Com os principais métodos de arrays implementados, o próximo passo é ampliar as
capacidades da linguagem e fortalecer sua arquitetura.

As prioridades sugeridas são:

1. Implementar `for`, começando pela iteração de arrays.
2. Desenvolver métodos adicionais de arrays, como `concat()` e `slice()`.
3. Expandir as funcionalidades de strings.
4. Fortalecer os diagnósticos e o tratamento de erros em tempo de execução.
5. Desenvolver mais funções para a biblioteca padrão.
6. Investigar e testar conflitos entre aliases de módulos e bibliotecas nativas.
7. Avançar na definição da semântica de cópia e referência dos arrays.

Em paralelo, continuam como objetivos de longo prazo a criação de uma API para
bibliotecas externas, o desenvolvimento de ferramentas de depuração e a
preparação da arquitetura para programação de baixo nível e microcontroladores.

Os recursos de hardware, especialmente o suporte ao ESP32, permanecem parte da
visão de longo prazo da Hurtip.
