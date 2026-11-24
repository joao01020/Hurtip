# Sistema de diagnóstico

A Hurtip possui mecanismos de identificação e apresentação de erros em diferentes etapas do processamento e da execução de um programa.

O objetivo é ajudar a identificar problemas no código e indicar, quando possível, a localização em que ocorreram.

## 1. Localização dos erros

Os tokens produzidos pelo Lexer armazenam informações sobre sua posição no código-fonte:

- `line`: linha em que o token começa.
- `column`: coluna em que o token começa.

Essas informações formam a base para diagnósticos mais precisos.

## 2. Erros de sintaxe

O Parser identifica diferentes estruturas sintáticas inválidas.

### Bloco sem abertura

Código:

```hurtip
if (true)
    view("Hello")
```

Resultado ilustrativo:

```text
Hurtip Error: Line 2, column 5: Expected '{' to begin block
```

### Bloco sem fechamento

Código:

```hurtip
if (true) {
    view("Hello")
```

Resultado ilustrativo:

```text
Hurtip Error: Line 3, column 1: Expected '}' to close block
```

### Argumento inválido

Código:

```hurtip
view(10, )
```

Resultado ilustrativo:

```text
Hurtip Error: Line 1, column 10: Expected an expression, got: )
```

### Operador inválido

Código:

```hurtip
create result = 10 + * 5
```

Resultado ilustrativo:

```text
Hurtip Error: Line 1, column 22: Expected an expression, got: *
```

Os exemplos apresentam formatos ilustrativos de mensagens de erro.

## 3. Situações de sintaxe identificadas

Os testes do Parser contemplam situações como:

- Blocos sem abertura `{`.
- Blocos sem fechamento `}`.
- Condições com parênteses incompletos.
- Chamadas de função incompletas.
- Argumentos ausentes.
- Vírgulas sobrando.
- Expressões incompletas.
- Sequências inválidas de operadores.

O Lexer também possui testes para situações como caracteres inválidos e strings não terminadas.

## 4. Erros de bibliotecas nativas

O sistema de importação de bibliotecas nativas possui tratamento para:

- Bibliotecas inexistentes.
- Funções não registradas.
- Quantidade inválida de argumentos.
- Tipos inválidos de argumentos.

## 5. Erros de módulos

O carregamento de módulos contempla tratamento para:

- Arquivos inexistentes.
- Dependências ausentes.
- Conflitos de namespace.
- Dependências circulares.
- Falhas durante a execução de um módulo.

Quando o carregamento falha, o interpretador possui mecanismos para restaurar o contexto anterior e limpar registros temporários do módulo malsucedido.

## 6. Erros de arrays

O acesso a arrays possui validações para:

- Índices negativos.
- Índices fracionários.
- Índices fora dos limites.
- Índices que não são numéricos.
- Tentativas de acessar índices em valores que não são arrays.

## 7. Cobertura dos testes

Os testes relacionados a diagnósticos estão distribuídos entre:

- Testes unitários do Lexer.
- Testes unitários do Parser.
- Testes de integração de sintaxe inválida.
- Testes de importação de bibliotecas nativas.
- Testes de falhas no carregamento de módulos.
- Testes de validação de arrays.

Consulte [Testes](testing.md) para conhecer a organização da suíte e os comandos de execução.

## 8. Limitações

A cobertura dos diagnósticos ainda está em evolução. A existência de mensagens de erro para determinadas situações não significa que todos os erros possíveis sejam identificados com localização precisa.

Novos diagnósticos podem ser adicionados conforme o Lexer, o Parser e o Interpreter evoluírem.
