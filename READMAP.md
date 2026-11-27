# Estado atual do desenvolvimento — Hurtip

Este documento acompanha a evolução da linguagem Hurtip, registrando os recursos
implementados, os testes realizados e as funcionalidades que ainda precisam ser
desenvolvidas.

A marcação de um recurso como implementado representa o estágio atual de
desenvolvimento e não significa que todas as situações extremas já foram
validadas.

## Núcleo da linguagem

- [x] Lexer
- [x] Parser básico
- [x] AST
- [x] Interpreter básico
- [x] Execução de arquivos `.hurtip` por argumento na CLI
- [x] Valores e variáveis no runtime
- [x] Declaração de variáveis com `create`
- [x] Atribuição e atualização de variáveis
- [x] Validação de redeclaração de variáveis no mesmo escopo
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
- [ ] Valor nulo (`null`) e sua semântica
- [ ] Sistema de tipos mais abrangente
- [ ] Conversão explícita entre tipos
- [ ] Verificação e compatibilidade de tipos

## Operadores e lógica

- [x] Comparações (`==`, `!=`, `>`, `<`, `>=`, `<=`)
- [x] Operadores lógicos (`and`, `or`, `not`)
- [x] Precedência de operadores lógicos
- [x] Avaliação de curto-circuito
- [x] Validação de valores booleanos nas operações lógicas
- [x] Operador de incremento (`++`)
- [ ] Operador de decremento (`--`)
- [ ] Operadores de atribuição composta (`+=`, `-=`, `*=`, `/=`)
- [ ] Operadores de módulo (`%`)
- [ ] Operadores de potência
- [ ] Operadores de incremento e decremento em expressões, com semântica
      prefixada e pós-fixada

## Controle de fluxo

- [x] `if` / `else`
- [x] Decisões aninhadas
- [x] Blocos de código
- [x] Abertura de blocos na mesma linha ou na linha seguinte
- [x] `while`
- [x] `for`
- [x] Inicialização de variável no cabeçalho do `for`
- [x] Avaliação da condição no cabeçalho do `for`
- [x] Incremento no cabeçalho do `for`
- [x] Incremento com `++`
- [x] `break`
- [x] `continue`
- [x] Loops aninhados
- [x] Escopo próprio para blocos de controle
- [x] Restauração de escopo após `break`, `continue` e `return`
- [x] Testes de integração do `for`
- [x] Testes de loops `for` aninhados
- [x] Testes de `break` e `continue` em loops `for`
- [ ] `try` / `catch`
- [ ] Tratamento de exceções definido pela linguagem
- [ ] Lançamento de exceções com `throw`
- [ ] Bloco `finally`
- [ ] Semântica de propagação e captura de erros

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
- [ ] Shadowing (ocultação de variáveis de escopos externos)
- [ ] Definição formal das regras de shadowing
- [ ] Closures
- [ ] Captura de ambientes léxicos
- [ ] Funções anônimas
- [ ] Parâmetros com valores padrão
- [ ] Verificação de quantidade e tipos de argumentos em funções definidas pelo
      usuário

## Operações e manipulação de strings

- [x] Representação de strings no runtime
- [x] Criação de strings
- [x] Concatenação básica com o operador `+`
- [ ] Acesso a caracteres por índice
- [ ] Propriedade `length`
- [ ] Comparação de strings
- [ ] Interpolação de strings
- [ ] Métodos de manipulação de strings
- [ ] Conversão entre strings e números
- [ ] Conversão entre strings e booleanos
- [ ] Busca de texto dentro de strings
- [ ] Verificação de prefixos e sufixos
- [ ] Substituição de trechos de texto
- [ ] Extração de partes de strings
- [ ] Divisão de strings em arrays
- [ ] Remoção de espaços no início e no final
- [ ] Alteração de maiúsculas e minúsculas
- [ ] Definição de regras para caracteres especiais e Unicode

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
- [ ] Busca de elementos
- [ ] Ordenação de elementos
- [ ] Definição formal da semântica de cópia e referência
- [ ] Estruturas de dados adicionais

## Objetos e estruturas de dados

- [ ] Estrutura de objetos no runtime
- [ ] Criação de objetos
- [ ] Propriedades e valores
- [ ] Acesso a propriedades por notação de ponto
- [ ] Acesso a propriedades por chaves dinâmicas
- [ ] Atribuição e modificação de propriedades
- [ ] Objetos aninhados
- [ ] Verificação da existência de propriedades
- [ ] Remoção de propriedades
- [ ] Métodos associados a objetos
- [ ] Definição de estruturas de dados personalizadas
- [ ] Definição de tipos personalizados
- [ ] Regras de cópia e referência para objetos
- [ ] Testes de criação, acesso e modificação de objetos

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
- [ ] Testes automatizados abrangentes de conflitos entre aliases de módulos e
      bibliotecas
- [ ] Carregamento dinâmico de bibliotecas externas
- [ ] API pública para desenvolvimento de bibliotecas por terceiros
- [ ] Documentação da API de bibliotecas nativas

## Biblioteca padrão

- [x] Estrutura inicial de registro das bibliotecas padrão
- [x] Biblioteca `math`
- [x] Função `math.sum()`
- [ ] Biblioteca de manipulação de strings
- [ ] Biblioteca de manipulação de arrays
- [ ] Biblioteca de conversão de tipos
- [ ] Biblioteca de entrada e saída
- [ ] Biblioteca de arquivos e diretórios
- [ ] Biblioteca de datas e horários
- [ ] Biblioteca de operações com números
- [ ] Biblioteca de utilidades gerais
- [ ] Funções para geração de números aleatórios
- [ ] Padronização das interfaces das bibliotecas
- [ ] Documentação das funções disponíveis
- [ ] Testes automatizados das bibliotecas padrão

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
- [x] Reconhecimento da palavra-chave `for`
- [x] Reconhecimento do operador `++`
- [x] Reconhecimento de ponto e vírgula (`;`)
- [x] Análise sintática do cabeçalho do `for`
- [x] Detecção de redeclaração de variáveis no mesmo escopo
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
- [x] Testes de integração de loops `for`
- [x] Testes de loops `for` aninhados
- [x] Testes de `break` e `continue` em loops `for`
- [x] Testes de redeclaração de variáveis
- [x] Teste básico de declaração e chamada de funções
- [ ] Testes de shadowing
- [ ] Testes de operações e manipulação de strings
- [ ] Testes de `try` / `catch`
- [ ] Testes de criação e manipulação de objetos
- [ ] Cobertura automatizada completa do runtime
- [ ] Testes de resistência e fuzz testing

**Observação sobre contagem:** a quantidade de testes registrados no CTest pode
mudar conforme novos casos são adicionados. Consulte a execução atual do CTest
para obter o total exato. As 13 verificações do Lexer e as 40 do Parser são
contagens de verificações unitárias, não necessariamente o número de testes
registrados no CTest.

O teste básico de declaração e chamada de funções foi adicionado em
`tests/functions/basic/`, mas ainda não estava registrado no CTest na última
verificação. Portanto, sua existência não deve ser contabilizada como um novo
teste executado pela suíte automatizada.

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
- [ ] Documentação completa da biblioteca padrão
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
- [ ] Cobertura completa de syntax highlighting para todos os recursos da
      linguagem
- [ ] Destaque de funções definidas pelo usuário
- [ ] Destaque de parâmetros e variáveis
- [ ] Destaque de bibliotecas e namespaces
- [ ] Publicação em marketplace
- [ ] Diagnósticos integrados ao editor
- [ ] Autocomplete
- [ ] Sugestões de palavras-chave e estruturas da linguagem
- [ ] Sugestões de funções e parâmetros
- [ ] Informações ao passar o mouse sobre símbolos
- [ ] Navegação para definições
- [ ] Formatação automática de código

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

A Hurtip possui um núcleo funcional desenvolvido em C++17, composto por Lexer,
Parser, AST e Interpreter.

A linguagem oferece declaração e atualização de variáveis, expressões,
operadores aritméticos e lógicos, estruturas de controle, funções,
recursividade, escopos e arrays.

O sistema de variáveis possui validação de redeclaração no mesmo escopo,
evitando que uma nova declaração sobrescreva silenciosamente uma variável já
existente naquele ambiente. O comportamento de shadowing, que permite ocultar
variáveis de escopos externos, ainda precisa ser definido e implementado.

O controle de fluxo inclui `if`, `else`, `while` e `for`. O loop `for` permite
declarar uma variável, definir uma condição e executar um incremento no próprio
cabeçalho. A linguagem também oferece `break`, `continue` e suporte a loops
aninhados.

Um exemplo da sintaxe atualmente implementada:

```hurtip
for(create i = 0; i < 10; ++i) {
    view(i)
}
```

O sistema de funções permite declarar parâmetros, realizar chamadas, retornar
valores, utilizar funções aninhadas e executar funções recursivas. Os ambientes
locais são independentes entre chamadas, com busca de variáveis em ambientes
ancestrais e atualização de variáveis existentes em ambientes superiores.
Closures e captura de ambientes léxicos ainda não foram implementadas.

As strings já possuem representação no runtime e permitem concatenação básica
com o operador `+`. Operações mais avançadas, como busca, substituição, extração
e interpolação de texto, ainda estão pendentes.

O sistema de módulos permite carregar arquivos `.hurtip`, utilizar aliases e
namespaces, resolver dependências aninhadas, detectar dependências circulares e
manter ambientes persistentes associados aos módulos.

Também foram desenvolvidos mecanismos de recuperação após falhas no
carregamento, incluindo restauração do contexto de execução e limpeza de
registros temporários de módulos que não conseguiram ser inicializados.

O sistema de importação de bibliotecas nativas permite importar bibliotecas pelo
nome, utilizar aliases e chamar funções por namespace. A biblioteca `math` é a
primeira implementação desse sistema, com a função `math.sum()`.

O registro das bibliotecas padrão é centralizado por meio de
`registerStandardLibraries()`, mantendo a inicialização das bibliotecas separada
do `main.cpp`. A biblioteca padrão ainda precisa ser expandida.

A implementação de arrays permite criar estruturas vazias, numéricas, de
strings, booleanas, mistas e aninhadas. Também oferece acesso e atribuição por
índice, acesso encadeado, exibição com `view()` e a propriedade `length`.

O sistema possui validações para índices negativos, fracionários, fora dos
limites e tentativas de acessar índices em valores que não são arrays. Métodos
de manipulação e iteração de arrays com `for` ainda estão pendentes.

Objetos e estruturas de dados personalizadas ainda não fazem parte dos recursos
implementados.

A extensão para Visual Studio Code possui reconhecimento de arquivos `.hurtip`,
gramática inicial, destaque de palavras-chave, strings, números e operadores,
além de fechamento automático de parênteses e aspas. Recursos mais avançados,
como autocomplete, diagnósticos integrados e formatação automática, ainda
precisam ser desenvolvidos.

A suíte de testes contempla verificações unitárias do Lexer e Parser, além de
testes de integração para arrays, funções, escopos, importações, módulos e
estruturas de controle. O projeto utiliza CTest para execução automatizada.

Na última execução registrada, 54 testes do CTest passaram. Esse número
corresponde à execução anterior à inclusão do teste básico de funções, que ainda
não estava registrado na suíte automatizada. A contagem atual deve ser
confirmada em uma nova execução.

## Foco atual do desenvolvimento

Os próximos avanços estão concentrados em:

1. Fortalecer a confiabilidade do sistema de módulos e ampliar os testes de
   conflitos entre aliases de módulos e bibliotecas.
2. Implementar shadowing e definir suas regras de escopo.
3. Desenvolver operações e métodos de manipulação de strings.
4. Implementar métodos de manipulação de arrays: `push()`, `pop()`, `remove()` e
   `contains()`.
5. Implementar a iteração de arrays com `for`.
6. Projetar e implementar objetos e estruturas de dados.
7. Desenvolver o tratamento de exceções com `try` / `catch`.
8. Expandir a biblioteca padrão.
9. Evoluir os diagnósticos e a recuperação de erros do Parser.
10. Projetar uma API pública para bibliotecas externas.
11. Desenvolver closures e captura de ambientes léxicos.
12. Evoluir a extensão para VS Code, incluindo syntax highlighting mais
    completo, autocomplete e diagnósticos integrados.
13. Melhorar as ferramentas de desenvolvimento e depuração.

Os recursos de baixo nível e o suporte a microcontroladores continuam como
objetivos de longo prazo. Eles ainda não representam funcionalidades disponíveis
na implementação atual.

---

**Este documento representa o estágio atual de desenvolvimento da Hurtip e deve
ser atualizado conforme novas funcionalidades, testes e mudanças na arquitetura
forem implementados.**
