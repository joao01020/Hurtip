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
- [ ] Arrays e listas
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
- [ ] Biblioteca padrão

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
- [ ] Mensagens padronizadas para fim de linha e fim de arquivo
- [x] Testes de erros léxicos
- [x] Testes de erros sintáticos
- [ ] Testes de erros em tempo de execução
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
- [x] 23 testes registrados e aprovados pelo CTest

## Biblioteca e ferramentas

- [ ] Biblioteca padrão
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

**Legenda:**

- `[x]` Implementado e validado por testes realizados.
- `[ ]` Pendente de implementação ou validação.

**Estado atual:**

A Hurtip já possui um núcleo funcional, com controle de fluxo, funções,
recursividade, escopos e sistema inicial de módulos.

O Lexer e o Parser possuem testes unitários, e a suíte automatizada está
integrada ao CTest. Atualmente, são 40 verificações unitárias do Parser e 23
testes registrados no CTest, todos aprovados.

O foco atual é continuar fortalecendo o Parser e melhorar a confiabilidade dos
diagnósticos. Testes avançados de resistência e fuzz testing ficam planejados
para uma etapa posterior, sem impedir a evolução dos recursos da linguagem.
