# Estado atual do desenvolvimento — Hurtip

Este documento acompanha a evolução da linguagem Hurtip, registrando os recursos implementados, os testes realizados e as funcionalidades que ainda precisam ser desenvolvidas.

A marcação de um recurso como implementado representa o estágio atual de desenvolvimento e não significa que todas as situações extremas já foram validadas.

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
- [x] Reconhecimento de números decimais
- [x] Representação de valores com `RuntimeValue`
- [x] Suporte a arrays na representação de valores do runtime

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
- [x] Busca de variáveis em ambientes ancestrais
- [x] Atualização de variáveis existentes em ambientes superiores
- [x] Ambientes locais independentes para chamadas de funções
- [ ] Closures
- [ ] Captura de ambientes léxicos

## Arrays

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
- [x] Testes automatizados de criação e acesso
- [x] Testes de arrays com tipos mistos
- [x] Testes de arrays aninhados
- [x] Testes de atribuição e modificação
- [x] Testes da propriedade `length`
- [x] Testes de índices inválidos
- [x] Testes de regressão para arrays
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
- [x] Normalização de caminhos
- [x] Identificação consistente de módulos carregados
- [x] Cache de módulos carregados
- [x] Reutilização de módulos já carregados
- [x] Associação de aliases a módulos registrados
- [x] Ambientes persistentes por módulo
- [x] Preservação de estado entre chamadas de funções do módulo
- [x] Separação dos ambientes de diferentes módulos
- [x] Acesso ao ambiente global quando necessário
- [x] Carregamento de dependências aninhadas
- [x] Detecção de dependências circulares
- [x] Tratamento de conflitos entre aliases
- [x] Restauração do contexto após falhas de carregamento
- [x] Limpeza de registros de módulos que falharam durante a inicialização
- [x] Testes de integração entre módulos
- [x] Testes de dependências aninhadas
- [x] Testes de dependências circulares
- [x] Testes de isolamento entre módulos
- [x] Testes de persistência de estado
- [x] Testes de reutilização e aliases
- [x] Testes de recuperação após falhas
- [ ] Isolamento completo de variáveis por módulo, com semântica formal
- [ ] Testes abrangentes de conflitos entre aliases de módulos e bibliotecas

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
- [x] Separação do registro das bibliotecas em relação ao `main.cpp`
- [x] Função centralizada `registerStandardLibraries()`
- [ ] Testes automatizados abrangentes de conflitos entre aliases de módulos e bibliotecas
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
- [x] Testes de erros léxicos
- [x] Testes de erros sintáticos
- [x] Testes de erros em carregamento de módulos
- [x] Testes de erros em importações nativas
- [x] Testes de argumentos e tipos inválidos em funções nativas
- [x] Testes de validação de índices de arrays
- [ ] Mensagens padronizadas para fim de linha e fim de arquivo
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
- [x] Cadastro dos testes em `tests/CMakeLists.txt`
- [x] Execução automatizada da suíte com CTest
- [x] Testes automatizados de mensagens de erro
- [x] Testes unitários do Lexer
- [x] Testes unitários do Parser
- [x] 13 verificações unitárias do Lexer
- [x] 40 verificações unitárias do Parser
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
- [x] Testes de recuperação após falhas de módulos
- [x] Testes de dependências circulares
- [x] Testes de dependências ausentes
- [x] Testes de dependências aninhadas
- [x] Testes de isolamento entre módulos
- [x] Testes de persistência de estado entre chamadas
- [x] Testes de reutilização de módulos com aliases
- [x] Testes de falhas durante execução de módulos
- [ ] Cobertura automatizada completa do runtime
- [ ] Testes de resistência e fuzz testing

**Observação sobre contagem:** a quantidade de testes registrados no CTest pode mudar conforme novos casos são adicionados. Consulte a execução atual do CTest para obter o total exato. As 13 verificações do Lexer e as 40 do Parser são contagens de verificações unitárias, não necessariamente o número de testes registrados no CTest.

## Documentação e ferramentas

- [x] README principal do projeto
- [x] Documentação de primeiros passos
- [x] Referência da linguagem
- [x] Documentação de arrays
- [x] Documentação do sistema de módulos
- [x] Documentação da arquitetura
- [x] Documentação de testes
- [x] Documentação da extensão para VS Code
- [x] Catálogo de recursos implementados e pendentes
- [x] Documentação inicial de diagnósticos
- [ ] Documentação completa da API de bibliotecas nativas
- [ ] Documentação de contribuição e desenvolvimento completa
- [ ] Biblioteca padrão completa
- [x] Estrutura inicial de CLI
- [ ] CLI / tooling avançado
- [ ] Gerenciador de pacotes
- [ ] Ferramentas de depuração

## Extensão para Visual Studio Code

- [x] Reconhecimento da extensão `.hurtip`
- [x] Identificador da linguagem Hurtip
- [x] Gramática inicial de sintaxe
- [x] Destaque de palavras-chave
- [x] Destaque de strings
- [x] Destaque de números
- [x] Destaque de operadores
- [x] Destaque da função `view()`
- [x] Fechamento automático de parênteses e aspas
- [x] Integração do ícone Hurtip ao tema Seti
- [x] Tema de ícones personalizado Seti + Hurtip
- [ ] Publicação em marketplace
- [ ] Recursos avançados de linguagem, como diagnóstico integrado e autocomplete

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

- `[x]` Implementado no estágio atual.
- `[ ]` Pendente de implementação ou validação.

## Estado atual

A Hurtip possui um núcleo funcional desenvolvido em C++17, composto por Lexer, Parser, AST e Interpreter.

A linguagem oferece variáveis, expressões, operadores aritméticos e lógicos, estruturas de controle, funções, recursividade, escopos e arrays.

O sistema de módulos permite carregar arquivos `.hurtip`, utilizar aliases e namespaces, resolver dependências aninhadas, detectar dependências circulares e manter ambientes persistentes associados aos módulos.

Também foram desenvolvidos mecanismos de recuperação após falhas no carregamento, incluindo restauração do contexto de execução e limpeza de registros temporários de módulos que não conseguiram ser inicializados.

O sistema de importação de bibliotecas nativas permite importar bibliotecas pelo nome, utilizar aliases e chamar funções por namespace. A biblioteca `math` é a primeira implementação desse sistema, com a função `math.sum()`.

O registro das bibliotecas padrão é centralizado por meio de `registerStandardLibraries()`, mantendo a inicialização das bibliotecas separada do `main.cpp`.

A implementação de arrays permite criar estruturas vazias, numéricas, de strings, booleanas, mistas e aninhadas. Também oferece acesso e atribuição por índice, acesso encadeado, exibição com `view()` e a propriedade `length`.

O sistema possui validações para índices negativos, fracionários, fora dos limites e tentativas de acessar índices em valores que não são arrays.

A suíte de testes contempla verificações unitárias do Lexer e Parser, além de testes de integração para arrays, funções, escopos, importações e módulos. O projeto utiliza CTest para execução automatizada.

## Foco atual do desenvolvimento

Os próximos avanços estão concentrados em:

1. Fortalecer a confiabilidade do sistema de módulos e dos conflitos entre aliases.
2. Implementar métodos de manipulação de arrays: `push()`, `pop()`, `remove()` e `contains()`.
3. Implementar o loop `for` e sua integração com arrays.
4. Evoluir os diagnósticos e a recuperação de erros do Parser.
5. Expandir a biblioteca padrão.
6. Projetar uma API pública para bibliotecas externas.
7. Melhorar as ferramentas de desenvolvimento e depuração.

Os recursos de baixo nível e o suporte a microcontroladores continuam como objetivos de longo prazo. Eles ainda não representam funcionalidades disponíveis na implementação atual.
