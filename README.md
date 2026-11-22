# Hurtip — Sistema de Módulos

O sistema de módulos da Hurtip é responsável por permitir a organização,
reutilização e integração de diferentes arquivos dentro de um mesmo projeto.

A branch `feature/module-system` é dedicada ao desenvolvimento de um sistema de
módulos que permita dividir programas em arquivos independentes, estabelecer
relações entre eles e reutilizar funcionalidades de maneira simples e
organizada.

O objetivo é tornar a organização de projetos na Hurtip mais flexível,
facilitando o desenvolvimento de aplicações pequenas e grandes.

## Objetivo

Construir um sistema de módulos consistente, previsível e fácil de utilizar,
permitindo que diferentes arquivos `.hurtip` trabalhem em conjunto.

O sistema deve priorizar:

- Simplicidade na importação de módulos.
- Organização e reutilização de código.
- Resolução previsível de caminhos.
- Separação entre módulos.
- Controle de dependências.
- Prevenção de carregamentos duplicados.
- Facilidade de manutenção.
- Possibilidade de expansão futura.

## Funcionalidades implementadas

Os seguintes recursos já estão implementados.

### Carregamento de módulos

- Carregamento de arquivos `.hurtip` utilizando `load`.
- Execução de módulos externos.
- Resolução de caminhos relativos ao arquivo que realiza o carregamento.

### Aliases

- Utilização de `as` para definir aliases.
- Acesso aos módulos através de seus aliases.

### Namespaces

- Organização de módulos em namespaces.
- Acesso a funcionalidades através de seus respectivos namespaces.
- Separação entre identificadores de diferentes módulos.

### Gerenciamento de dependências

- Cache de módulos carregados.
- Detecção de dependências circulares.
- Controle do processo de carregamento de módulos.

## Funcionalidades planejadas

Os seguintes recursos poderão ser desenvolvidos para ampliar o sistema.

### Organização de módulos

- Suporte a estruturas de diretórios mais complexas.
- Organização de módulos em subdiretórios.
- Padronização da resolução de módulos.
- Melhor gerenciamento de caminhos.
- Definição de regras para localização de módulos.

### Importação seletiva

- Possibilidade de carregar funcionalidades específicas de um módulo.
- Importação de múltiplos identificadores.
- Definição de aliases para identificadores individuais.
- Controle de visibilidade dos elementos exportados.

### Exportação de funcionalidades

- Definição explícita de elementos públicos.
- Separação entre elementos públicos e privados.
- Controle sobre quais funções e variáveis podem ser acessadas externamente.
- Organização das interfaces públicas dos módulos.

### Gerenciamento de dependências

- Melhor visualização das relações entre módulos.
- Diagnósticos detalhados de dependências.
- Identificação de dependências não utilizadas.
- Melhor tratamento de erros durante o carregamento.
- Controle de versões de módulos, caso necessário.

### Resolução avançada de módulos

- Definição de diretórios de busca.
- Suporte a caminhos absolutos e relativos.
- Regras de prioridade na localização de módulos.
- Possibilidade de bibliotecas locais reutilizáveis.
- Padronização do comportamento em diferentes sistemas operacionais.

### Melhorias futuras

- Sistema de pacotes.
- Gerenciamento de dependências externas.
- Estrutura de projetos com configuração própria.
- Distribuição e reutilização de módulos.
- Ferramentas para análise da estrutura de dependências.

## Arquitetura

O sistema de módulos utiliza os componentes fundamentais do interpretador da
Hurtip.

| Componente    | Responsabilidade                                            |
| ------------- | ----------------------------------------------------------- |
| Lexer         | Reconhece os tokens utilizados na sintaxe dos módulos.      |
| Parser        | Analisa as instruções de carregamento e seus aliases.       |
| AST           | Representa as instruções relacionadas aos módulos.          |
| Interpreter   | Coordena a execução e o carregamento dos módulos.           |
| Environment   | Gerencia os ambientes e namespaces.                         |
| Module System | Controla a resolução, o carregamento e o cache dos módulos. |

A implementação deve manter uma separação clara entre o sistema de módulos e o
núcleo da linguagem.

## Exemplo de utilização

Considere a seguinte estrutura:

```text
project/
├── main.hurtip
└── modules/
    ├── calculator.hurtip
    └── messages.hurtip
```

Um arquivo principal poderá carregar módulos utilizando `load`:

```hurtip
load "modules/calculator.hurtip" as calculator
load "modules/messages.hurtip" as messages
```

As funcionalidades dos módulos poderão ser acessadas através de seus respectivos
namespaces, conforme os recursos já disponíveis na linguagem.

Exemplo conceitual:

```hurtip
view(calculator.sum(10, 20))
view(messages.greeting())
```

## Tratamento de erros

O sistema deverá fornecer diagnósticos claros para situações como:

- Arquivo de módulo não encontrado.
- Caminho inválido.
- Falha durante o carregamento.
- Dependências circulares.
- Namespace inexistente.
- Identificador não encontrado.
- Conflitos de nomes.
- Erros de execução dentro de módulos.

As mensagens devem facilitar a identificação do arquivo e da origem do problema.

## Testes

O sistema deve possuir testes automatizados para validar seu comportamento.

A cobertura deve incluir:

- Carregamento de módulos.
- Carregamento com aliases.
- Acesso através de namespaces.
- Resolução de caminhos relativos.
- Carregamento de módulos em subdiretórios.
- Cache de módulos.
- Detecção de dependências circulares.
- Arquivos inexistentes.
- Erros durante o carregamento.
- Dependências entre múltiplos módulos.

Novos recursos devem ser acompanhados de testes para evitar regressões.

## Diretrizes de desenvolvimento

O desenvolvimento nesta branch deve seguir os seguintes princípios:

1. Manter a sintaxe simples e intuitiva.
2. Evitar complexidade desnecessária na importação de módulos.
3. Garantir comportamento previsível na resolução de caminhos.
4. Evitar carregamentos duplicados.
5. Manter o isolamento e a organização dos namespaces.
6. Fornecer diagnósticos claros.
7. Preservar a compatibilidade com o núcleo da linguagem.
8. Desenvolver testes automatizados para cada novo recurso.

## Escopo da branch

A `feature/module-system` é responsável exclusivamente pelo sistema de módulos
da Hurtip.

Seu desenvolvimento deve permitir que programas sejam divididos em arquivos
independentes, organizados em estruturas reutilizáveis e integrados de maneira
consistente.

O objetivo final é oferecer uma infraestrutura de módulos que acompanhe o
crescimento da linguagem, sem comprometer sua simplicidade.

---

**Hurtip — Uma linguagem de programação construída em torno da simplicidade,
clareza e versatilidade.**
