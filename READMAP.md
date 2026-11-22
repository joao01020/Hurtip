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

### Arrays

- [x] Estrutura inicial de arrays no runtime
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
- [ ] Métodos de manipulação (`push`, `pop`, `remove`, `contains`)
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
- [x] 38 testes registrados no CTest, considerando os 29 anteriores e os 9 novos
      testes de arrays
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
- [x] Testes de regressão para arrays

## Biblioteca e ferramentas

- [ ] Biblioteca padrão completa
- [x] Estrutura inicial de registro centralizado da biblioteca padrão
- [x] Estrutura inicial de CLI
- [ ] CLI / tooling avançado
- [ ] Sistema de documentação
- [ ] Gerenciador de pacotes
- [ ] Ferramentas de depuração

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
integrada ao CTest. São 40 verificações unitárias do Parser e 38 testes
registrados no CTest, considerando a suíte anterior e os nove novos testes de
arrays. Na última execução informada, todos os testes passaram.

### Arrays: estágio atual

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

O sistema já possui validações para índices negativos, fracionários, fora dos
limites e tentativas de acessar elementos em objetos que não são arrays.

Foram adicionados nove testes automatizados específicos para arrays, cobrindo
criação, tipos mistos, estruturas aninhadas, atribuição, tamanho e situações de
erro.

O próximo avanço será desenvolver os métodos de manipulação:

- `push()` — adicionar elementos ao final.
- `pop()` — remover e retornar o último elemento.
- `remove()` — remover um elemento pelo índice.
- `contains()` — verificar se determinado valor está presente.

Depois disso, a evolução poderá avançar para concatenação, comparação estrutural
e iteração com `for`.

## Foco atual do desenvolvimento

O próximo objetivo é fortalecer a confiabilidade do sistema de importação,
especialmente a prevenção de conflitos entre aliases de módulos e bibliotecas
nativas.

Na evolução dos arrays, o próximo passo será implementar os métodos de
manipulação (`push`, `pop`, `remove` e `contains`), mantendo a validação de
tipos e índices e adicionando testes automatizados para cada operação.

Em seguida, o desenvolvimento poderá avançar para a implementação de `for`,
permitindo percorrer arrays e outras estruturas iteráveis.

Outros objetivos importantes são a expansão da biblioteca padrão, a API para
bibliotecas externas e o fortalecimento dos diagnósticos e testes de
resistência.

Os recursos avançados de baixo nível e suporte a microcontroladores continuam
fazendo parte da visão de longo prazo da Hurtip.
