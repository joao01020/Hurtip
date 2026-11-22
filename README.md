# Hurtip — Importação de Bibliotecas

O sistema de importação de bibliotecas da Hurtip permite integrar
funcionalidades externas ao interpretador, ampliando as capacidades da linguagem
sem precisar implementar tudo diretamente em sua sintaxe.

A branch `feature/external-import` é dedicada ao desenvolvimento de um sistema
de integração entre a Hurtip e bibliotecas nativas, permitindo que
funcionalidades desenvolvidas em C++ sejam disponibilizadas aos programas
escritos na linguagem.

O objetivo é tornar a Hurtip extensível, permitindo adicionar novos recursos de
maneira organizada, modular e consistente.

## Objetivo

Construir um sistema de importação flexível e confiável, capaz de conectar a
linguagem a funcionalidades implementadas fora do seu núcleo.

O sistema deve priorizar:

- Simplicidade na importação de bibliotecas.
- Integração com código nativo em C++.
- Extensibilidade da linguagem.
- Organização das bibliotecas.
- Separação entre o núcleo e os recursos adicionais.
- Reutilização de funcionalidades.
- Segurança e previsibilidade na execução.
- Facilidade para desenvolver novas bibliotecas.

## Funcionalidades implementadas

Os seguintes recursos já estão implementados.

### Importação de bibliotecas

- Instrução `import` para carregar bibliotecas nativas.
- Integração entre o interpretador e bibliotecas desenvolvidas em C++.
- Registro centralizado de bibliotecas através do sistema `standard_library`.

### Aliases e namespaces

- Importação utilizando aliases com `as`.
- Acesso às funcionalidades através de namespaces.
- Organização dos identificadores importados.

### Biblioteca padrão

A Hurtip já possui uma biblioteca nativa chamada `math`.

Atualmente, ela disponibiliza:

- `math.sum(a, b)` para somar dois valores.

### Integração com o interpretador

- Registro de funções nativas.
- Execução de funções disponibilizadas pelas bibliotecas.
- Integração com o sistema de chamadas de funções do interpretador.

## Funcionalidades planejadas

Os seguintes recursos estão previstos para ampliar o sistema de bibliotecas.

### Expansão da biblioteca padrão

Desenvolvimento de novas bibliotecas nativas para disponibilizar funcionalidades
comuns.

Possíveis bibliotecas:

| Biblioteca | Finalidade                             |
| ---------- | -------------------------------------- |
| `math`     | Operações e funções matemáticas.       |
| `string`   | Manipulação e processamento de textos. |
| `array`    | Operações e manipulação de arrays.     |
| `file`     | Leitura e escrita de arquivos.         |
| `time`     | Datas, horários e medição de tempo.    |
| `system`   | Informações e operações do sistema.    |
| `random`   | Geração de valores aleatórios.         |
| `io`       | Operações de entrada e saída.          |

Essas bibliotecas representam possibilidades de expansão, não funcionalidades já
disponíveis.

### Desenvolvimento de bibliotecas personalizadas

- Criação de bibliotecas nativas independentes.
- Padronização da interface entre bibliotecas e interpretador.
- Registro de novas funções nativas.
- Reutilização de bibliotecas em diferentes projetos.
- Organização de bibliotecas em módulos independentes.

### Integração com C++

- Melhorias na comunicação entre C++ e Hurtip.
- Conversão entre tipos nativos e valores da linguagem.
- Suporte ampliado a diferentes tipos de retorno.
- Tratamento consistente de parâmetros.
- Interfaces padronizadas para funções nativas.
- Possibilidade de integração com bibliotecas C e C++.

### Gerenciamento de bibliotecas

- Organização das bibliotecas disponíveis.
- Verificação de bibliotecas inexistentes.
- Diagnósticos para erros de importação.
- Controle de nomes e namespaces.
- Prevenção de conflitos entre bibliotecas.
- Melhor gerenciamento do registro de funções nativas.

### Extensibilidade

- Interfaces para criação de novas bibliotecas.
- Possibilidade de adicionar funcionalidades sem modificar diretamente o núcleo
  do interpretador.
- Integração futura com bibliotecas externas.
- Suporte a diferentes áreas de aplicação.

## Arquitetura

O sistema de importação utiliza componentes do interpretador e uma estrutura
centralizada para registrar as bibliotecas nativas.

| Componente       | Responsabilidade                                      |
| ---------------- | ----------------------------------------------------- |
| Lexer            | Reconhece os tokens utilizados na instrução `import`. |
| Parser           | Analisa as instruções de importação.                  |
| AST              | Representa as instruções relacionadas à importação.   |
| Interpreter      | Executa as chamadas das funções nativas.              |
| Standard Library | Centraliza o registro das bibliotecas disponíveis.    |
| Native Libraries | Implementam funcionalidades nativas em C++.           |

A arquitetura deve permitir que novas bibliotecas sejam adicionadas sem
comprometer o funcionamento das funcionalidades já existentes.

## Exemplo de utilização

Uma biblioteca pode ser importada utilizando a instrução `import`.

```hurtip
import math
```

Depois da importação, suas funcionalidades podem ser acessadas através do
namespace correspondente:

```hurtip
import math

view(math.sum(10, 20))
```

Resultado:

```text
30
```

Também é possível utilizar aliases:

```hurtip
import math as mathematics

view(mathematics.sum(10, 20))
```

## Tratamento de erros

O sistema deve fornecer diagnósticos claros para situações como:

- Biblioteca inexistente.
- Identificador não encontrado.
- Função nativa inexistente.
- Quantidade incorreta de argumentos.
- Tipos de argumentos incompatíveis.
- Falhas durante a execução de funções nativas.
- Conflitos entre namespaces.
- Erros na integração entre C++ e Hurtip.

As mensagens devem facilitar a identificação da origem do problema.

## Testes

O sistema deve possuir testes automatizados para validar o comportamento das
bibliotecas nativas.

A cobertura deve incluir:

- Importação de bibliotecas.
- Importação com aliases.
- Acesso através de namespaces.
- Registro de bibliotecas.
- Execução de funções nativas.
- Biblioteca `math`.
- Validação de argumentos.
- Tratamento de funções inexistentes.
- Erros de importação.
- Compatibilidade com o interpretador.

Novas bibliotecas e funcionalidades devem ser acompanhadas de testes
automatizados.

## Diretrizes de desenvolvimento

O desenvolvimento nesta branch deve seguir os seguintes princípios:

1. Manter a importação simples e intuitiva.
2. Separar as bibliotecas do núcleo da linguagem.
3. Padronizar a integração entre C++ e Hurtip.
4. Evitar dependências desnecessárias.
5. Manter os namespaces organizados.
6. Garantir compatibilidade com o sistema de tipos da linguagem.
7. Desenvolver testes para novas funcionalidades.
8. Facilitar a criação de bibliotecas independentes.

## Escopo da branch

A `feature/external-import` é responsável pelo sistema de importação e
integração de bibliotecas nativas da Hurtip.

Seu desenvolvimento deve permitir que a linguagem amplie suas capacidades
através de funcionalidades implementadas externamente, mantendo o núcleo
simples, organizado e independente.

O objetivo final é construir uma infraestrutura extensível que permita à Hurtip
integrar recursos de diferentes áreas, desde operações básicas até aplicações
mais avançadas envolvendo hardware, sistemas e outras tecnologias.

---

**Hurtip — Uma linguagem de programação construída em torno da simplicidade,
clareza e versatilidade.**
