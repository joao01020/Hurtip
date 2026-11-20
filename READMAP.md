## Estado atual do desenvolvimento

### Núcleo da linguagem

- [x] Lexer
- [x] Parser básico
- [x] AST
- [x] Interpreter básico
- [x] Execução de arquivos `.nt` por argumento na CLI
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

### Operadores e lógica

- [x] Comparações (`==`, `!=`, `>`, `<`, `>=`, `<=`)
- [x] Operadores lógicos (`and`, `or`, `not`)
- [x] Precedência de operadores lógicos
- [x] Avaliação de curto-circuito
- [x] Validação de valores booleanos nas operações lógicas

### Controle de fluxo

- [x] `if` / `else`
- [x] Decisões aninhadas
- [x] Blocos de código
- [x] `while`
- [x] `break`
- [x] `continue`
- [x] Loops aninhados
- [ ] `for`

### Diagnósticos e confiabilidade

- [x] Diagnósticos iniciais com identificação de linha
- [ ] Diagnósticos robustos do Parser
- [ ] Rastreamento completo de linha e coluna nos diagnósticos
- [ ] Testes de erros léxicos
- [ ] Testes de erros sintáticos
- [ ] Testes de erros em tempo de execução
- [ ] Tratamento robusto de erros

### Funções e estruturas de dados

- [ ] Funções definidas pelo usuário
- [ ] Parâmetros de funções
- [ ] Valores de retorno
- [ ] `return`
- [ ] Escopo local e global
- [ ] Arrays e listas
- [ ] Estruturas de dados

### Biblioteca e ferramentas

- [ ] Biblioteca padrão
- [ ] Sistema de módulos e importação
- [ ] CLI / tooling avançado
- [ ] Testes automatizados

### Recursos de baixo nível e hardware

- [ ] Controle de memória
- [ ] Tipos de dados de baixo nível
- [ ] Acesso a recursos do sistema
- [ ] Comunicação com microcontroladores
- [ ] Suporte ao ESP32

---

**Legenda:**

- `[x]` Implementado e testado nos exemplos atuais.
- `[ ]` Pendente de implementação ou validação.
