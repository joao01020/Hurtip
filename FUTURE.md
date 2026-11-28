# Hurtip — Future

## Sobre este documento

Este documento apresenta a direção de desenvolvimento da Hurtip, reunindo os
recursos, sistemas, ferramentas e objetivos planejados para sua evolução.

Ele serve como referência para orientar decisões técnicas, organizar prioridades
e acompanhar a expansão da linguagem.

O documento contempla desde melhorias na sintaxe e no ambiente de execução até
recursos avançados de programação, integração com hardware e expansão do
ecossistema.

**Importante:** os itens apresentados representam possibilidades e objetivos de
desenvolvimento, não compromissos de implementação imediata. Algumas
funcionalidades dependem de avaliações técnicas e decisões arquiteturais.

---

# 1. Fundamentos da Linguagem

## 1.1 Recursos da linguagem

**Objetivo:** ampliar a expressividade da Hurtip, mantendo uma sintaxe simples,
consistente e acessível.

- [ ] Laços `for`
- [ ] Laços `do-while`
- [ ] Estruturas `switch` / `case`
- [ ] Operador ternário
- [ ] Operadores de atribuição composta (`+=`, `-=`, `*=`, `/=`)
- [ ] Operadores de incremento e decremento (`++`, `--`)
- [ ] Expressões de intervalo
- [ ] Operador spread
- [ ] Atribuição por desestruturação
- [ ] Valores opcionais
- [ ] Valor nulo e tratamento de nulos
- [ ] Interpolação de strings
- [ ] Strings multilinha
- [ ] Constantes e variáveis imutáveis
- [ ] Anotações de tipo
- [ ] Melhorias na inferência de tipos

## 1.2 Estruturas de dados

**Objetivo:** oferecer estruturas flexíveis para representar, organizar e
manipular informações.

- [ ] Concatenação de arrays
- [ ] Fatiamento de arrays (slicing)
- [ ] Cópia de arrays
- [ ] Ordenação de arrays
- [ ] Mapeamento e filtragem de arrays
- [ ] Métodos de iteração de arrays
- [ ] Dicionários e mapas
- [ ] Tuplas
- [ ] Conjuntos (sets)
- [ ] Estruturas de dados personalizadas
- [ ] Estruturas (structs)
- [ ] Enumerações
- [ ] Melhorias no uso de estruturas aninhadas

## 1.3 Funções e paradigmas de programação

**Objetivo:** ampliar as possibilidades de composição e reutilização de código.

- [ ] Valores padrão para parâmetros
- [ ] Argumentos nomeados
- [ ] Funções com quantidade variável de argumentos
- [ ] Funções anônimas
- [ ] Expressões lambda
- [ ] Closures
- [ ] Funções de ordem superior
- [ ] Sobrecarga de funções
- [ ] Melhorias na recursividade
- [ ] Programação orientada a objetos
- [ ] Classes e objetos
- [ ] Construtores e destrutores
- [ ] Herança
- [ ] Interfaces
- [ ] Traits ou mixins
- [ ] Encapsulamento e modificadores de acesso

## 1.4 Sistema de tipos

**Objetivo:** estabelecer um sistema de tipos previsível, seguro e capaz de
acompanhar o crescimento da linguagem.

- [ ] Verificação estática de tipos
- [ ] Inferência de tipos
- [ ] Conversão e coerção de tipos
- [ ] Tipos personalizados
- [ ] Tipos genéricos
- [ ] Restrições de tipos
- [ ] Tipos de união
- [ ] Tipos anuláveis
- [ ] Apelidos de tipos (type aliases)
- [ ] Maior segurança e consistência de tipos

---

# 2. Runtime e Arquitetura

## 2.1 Tratamento de erros

**Objetivo:** tornar os erros mais claros, previsíveis e úteis durante o
desenvolvimento e a execução de programas.

- [ ] Estruturas `try` / `catch`
- [ ] Instrução `throw`
- [ ] Exceções personalizadas
- [ ] Tipos de erro
- [ ] Melhorias nos diagnósticos de execução
- [ ] Identificação de linha e coluna no código-fonte
- [ ] Rastreamento da pilha de execução (stack trace)
- [ ] Recuperação de erros
- [ ] Padronização das mensagens de erro

## 2.2 Memória e ambiente de execução

**Objetivo:** definir um modelo de memória consistente, eficiente e adequado
tanto para aplicações gerais quanto para sistemas de baixo nível.

- [ ] Definição da semântica de valor e referência
- [ ] Comportamento de cópia de arrays e objetos
- [ ] Gerenciamento de referências
- [ ] Estratégia de gerenciamento de memória
- [ ] Avaliação de coleta automática de lixo (garbage collection)
- [ ] Melhorias de desempenho do ambiente de execução
- [ ] Gerenciamento de pilha e heap
- [ ] Gerenciamento de recursos
- [ ] Melhorias na segurança da execução

## 2.3 Compilador e desempenho

**Objetivo:** avaliar e desenvolver estratégias para melhorar o desempenho, a
distribuição e as possibilidades de execução da Hurtip.

- [ ] Avaliação da arquitetura do compilador
- [ ] Geração de bytecode
- [ ] Avaliação de uma máquina virtual
- [ ] Compilação para código nativo
- [ ] Etapas de otimização
- [ ] Avaliação antecipada de constantes
- [ ] Eliminação de código não utilizado
- [ ] Modos de compilação para depuração e produção
- [ ] Compilação cruzada
- [ ] Melhorias no desempenho da compilação

---

# 3. Biblioteca e Ecossistema

## 3.1 Biblioteca padrão

**Objetivo:** fornecer funcionalidades essenciais para que programas possam
realizar tarefas comuns sem depender constantemente de bibliotecas externas.

- [ ] Utilitários para strings
- [ ] Utilitários para arrays
- [ ] Operações com sistema de arquivos
- [ ] Leitura e escrita de arquivos
- [ ] Entrada e saída de dados
- [ ] Data e hora
- [ ] Geração de números aleatórios
- [ ] Funções matemáticas
- [ ] Coleções de dados
- [ ] Variáveis de ambiente
- [ ] Utilitários do sistema operacional
- [ ] Recursos de rede
- [ ] Suporte a JSON
- [ ] Expressões regulares
- [ ] Recursos de concorrência

## 3.2 Módulos e ecossistema de pacotes

**Objetivo:** permitir a organização, distribuição, reutilização e integração de
projetos e bibliotecas desenvolvidos em Hurtip.

- [ ] Gerenciador de pacotes
- [ ] Gerenciamento de dependências
- [ ] Repositório de pacotes
- [ ] Controle de versões de pacotes
- [ ] Controle de visibilidade e acesso entre módulos
- [ ] Distribuição de módulos da biblioteca padrão
- [ ] Melhorias na integração com bibliotecas externas
- [ ] Empacotamento de bibliotecas nativas

## 3.3 Integração com outras linguagens

**Objetivo:** permitir que a Hurtip aproveite bibliotecas e tecnologias já
existentes em outros ecossistemas.

- [ ] Melhorias na integração com C e C++
- [ ] Interface de funções nativas (FFI)
- [ ] Integração com bibliotecas compartilhadas
- [ ] Avaliação de integração com Python
- [ ] Definição de interfaces para extensões externas
- [ ] Sistema de registro e distribuição de extensões

---

# 4. Concorrência e Execução Assíncrona

**Objetivo:** permitir que programas executem múltiplas operações de maneira
eficiente e controlada.

- [ ] Threads
- [ ] Tarefas
- [ ] Sintaxe `async` / `await`
- [ ] Promises ou futures
- [ ] Execução paralela
- [ ] Primitivas de sincronização
- [ ] Mutexes
- [ ] Canais de comunicação
- [ ] Segurança em operações concorrentes

---

# 5. Ferramentas para Desenvolvedores

**Objetivo:** construir ferramentas que facilitem a criação, manutenção, análise
e depuração de programas Hurtip.

- [ ] Terminal interativo (REPL)
- [ ] Depurador
- [ ] Pontos de interrupção (breakpoints)
- [ ] Inspeção de variáveis
- [ ] Analisador de desempenho (profiler)
- [ ] Formatador de código
- [ ] Analisador estático (linter)
- [ ] Protocolo de Servidor de Linguagem (LSP)
- [ ] Autocompletar código
- [ ] Ir para definição
- [ ] Encontrar referências
- [ ] Melhorias no realce de sintaxe
- [ ] Suporte oficial a ambientes de desenvolvimento (IDEs)

---

# 6. Hardware e Sistemas Embarcados

**Objetivo:** desenvolver capacidades de baixo nível que permitam à Hurtip
interagir diretamente com hardware, microcontroladores e dispositivos físicos.

Esta é uma das áreas estratégicas da linguagem, especialmente considerando sua
proposta de combinar simplicidade de sintaxe com controle sobre recursos de
hardware.

## 6.1 Recursos de baixo nível

- [ ] Acesso à memória em baixo nível
- [ ] Suporte a ponteiros
- [ ] Operações bit a bit
- [ ] Acesso direto ao hardware
- [ ] Manipulação de registradores
- [ ] Controle de recursos de memória
- [ ] Interação com interfaces de hardware

## 6.2 Microcontroladores e periféricos

- [ ] Suporte a GPIO
- [ ] Suporte ao ESP32
- [ ] Avaliação de compatibilidade com Arduino
- [ ] Comunicação com periféricos
- [ ] Comunicação UART
- [ ] Comunicação SPI
- [ ] Comunicação I²C
- [ ] Comunicação CAN
- [ ] Tratamento de interrupções
- [ ] Controle de temporizadores
- [ ] Suporte a PWM
- [ ] Integração com sensores e atuadores

## 6.3 Ambiente embarcado

- [ ] Ambiente de execução para sistemas embarcados
- [ ] Camada de abstração de hardware (HAL)
- [ ] Compilação para microcontroladores
- [ ] Controle de consumo de memória
- [ ] Gerenciamento de recursos limitados
- [ ] Inicialização e configuração de dispositivos
- [ ] Ferramentas de gravação e depuração de firmware

---

# 7. Áreas de Aplicação

## 7.1 Inteligência artificial

**Objetivo:** avaliar a utilização da Hurtip em aplicações de inteligência
artificial e aprendizado de máquina.

- [ ] Integração com bibliotecas de inteligência artificial
- [ ] Integração com modelos de aprendizado de máquina
- [ ] Operações matemáticas e matriciais
- [ ] Manipulação de tensores
- [ ] Integração com aceleradores de hardware
- [ ] Ferramentas para desenvolvimento de aplicações de IA

## 7.2 Desenvolvimento de jogos

**Objetivo:** possibilitar a criação de jogos e aplicações interativas
utilizando a Hurtip.

- [ ] Biblioteca gráfica
- [ ] Renderização 2D
- [ ] Renderização 3D
- [ ] Manipulação de imagens
- [ ] Processamento de áudio
- [ ] Entrada de teclado, mouse e controles
- [ ] Física e colisões
- [ ] Integração com motores gráficos
- [ ] Ferramentas para desenvolvimento de jogos

## 7.3 Aplicações gerais

**Objetivo:** ampliar a utilização da Hurtip em diferentes tipos de software.

- [ ] Desenvolvimento de aplicações desktop
- [ ] Desenvolvimento de aplicações web
- [ ] Desenvolvimento de APIs
- [ ] Comunicação em rede
- [ ] Automação de tarefas
- [ ] Ferramentas de linha de comando
- [ ] Aplicações de sistema
- [ ] Aplicações de alto desempenho

---

# 8. Plataformas e Portabilidade

**Objetivo:** ampliar os ambientes nos quais programas Hurtip podem ser
desenvolvidos e executados.

- [ ] Linux
- [ ] Windows
- [ ] macOS
- [ ] Arquitetura ARM
- [ ] Arquiteturas x86 e x86-64
- [ ] Suporte a microcontroladores
- [ ] Compatibilidade entre plataformas
- [ ] Padronização do comportamento entre sistemas
- [ ] Ferramentas de compilação cruzada

---

# 9. Testes, Segurança e Qualidade

**Objetivo:** garantir que a evolução da linguagem seja acompanhada por
confiabilidade, previsibilidade e estabilidade.

- [ ] Ampliar a cobertura de testes automatizados
- [ ] Testes de integração do ambiente de execução
- [ ] Testes da biblioteca padrão
- [ ] Testes de tratamento de erros
- [ ] Testes de desempenho
- [ ] Testes de segurança de memória
- [ ] Testes em diferentes sistemas operacionais
- [ ] Testes de regressão
- [ ] Testes de compatibilidade
- [ ] Testes de compilação cruzada
- [ ] Testes de integração com hardware
- [ ] Verificação de comportamento entre versões

---

# 10. Documentação e Comunidade

**Objetivo:** facilitar o aprendizado, a adoção e a contribuição de
desenvolvedores para o ecossistema Hurtip.

- [ ] Documentação oficial da linguagem
- [ ] Referência completa da sintaxe
- [ ] Referência da biblioteca padrão
- [ ] Guia de instalação
- [ ] Tutoriais para iniciantes
- [ ] Guias avançados de programação
- [ ] Documentação de APIs
- [ ] Projetos de exemplo
- [ ] Diretrizes de contribuição
- [ ] Especificação oficial da linguagem
- [ ] Política de versões e lançamentos
- [ ] Guia de migração entre versões
- [ ] Documentação para desenvolvimento de extensões
- [ ] Exemplos de integração com hardware

---

# 11. Evolução Estratégica

As áreas anteriores representam o conjunto de possibilidades para a evolução da
Hurtip. A implementação deverá acontecer gradualmente, respeitando a maturidade
da arquitetura e as necessidades reais do projeto.

A seguinte organização representa uma direção estratégica, não um calendário
fixo.

## Fase 1 — Consolidação da linguagem

- Evolução dos recursos fundamentais da sintaxe.
- Expansão das estruturas de dados.
- Melhorias no sistema de funções.
- Definição do sistema de tipos.
- Padronização do tratamento de erros.
- Definição da semântica de memória e referências.

## Fase 2 — Biblioteca e integração

- Expansão da biblioteca padrão.
- Consolidação do sistema de módulos.
- Integração com bibliotecas externas.
- Desenvolvimento de interfaces para extensões nativas.
- Primeiras ferramentas de distribuição de dependências.

## Fase 3 — Runtime e desempenho

- Avaliação de alternativas para o ambiente de execução.
- Melhorias na eficiência da interpretação.
- Estudos de compilação e geração de código.
- Estratégias de gerenciamento de memória.
- Melhorias de portabilidade.

## Fase 4 — Ferramentas de desenvolvimento

- REPL.
- Depurador.
- Formatador e linter.
- LSP.
- Integração aprimorada com editores e IDEs.

## Fase 5 — Hardware e baixo nível

- Acesso controlado à memória.
- Operações de baixo nível.
- Integração com microcontroladores.
- Suporte ao ESP32.
- Comunicação com periféricos.
- Ambiente de execução embarcado.

## Fase 6 — Expansão do ecossistema

- Concorrência e programação assíncrona.
- Desenvolvimento de jogos.
- Inteligência artificial.
- Aplicações gerais.
- Ecossistema de pacotes e bibliotecas.
- Ampliação das plataformas suportadas.

---

# 12. Decisões Arquiteturais em Avaliação

Nem toda funcionalidade desejável precisa necessariamente ser implementada.
Algumas exigem estudos para determinar se são compatíveis com os objetivos e a
arquitetura da Hurtip.

Entre os temas que exigem avaliação estão:

- Coleta automática de lixo (Garbage Collection).
- Máquina virtual e execução por bytecode.
- Compilação para código nativo.
- Programação orientada a objetos.
- Herança e modelos alternativos de composição.
- Semântica de cópia e referência.
- Sistema estático ou dinâmico de tipos.
- Integração com Python.
- Estratégia de gerenciamento de memória para microcontroladores.
- Modelo de concorrência e execução assíncrona.

Essas decisões deverão considerar simplicidade, desempenho, segurança,
portabilidade e controle sobre o hardware.

---

# 13. Critérios de Evolução

A implementação de novos recursos deverá considerar os seguintes princípios:

1. **Simplicidade:** novos recursos devem preservar a clareza da linguagem.
2. **Consistência:** funcionalidades diferentes devem seguir regras coerentes.
3. **Desempenho:** a arquitetura deve permitir execução eficiente.
4. **Controle:** recursos de baixo nível devem oferecer controle adequado sobre
   hardware e memória.
5. **Portabilidade:** sempre que possível, o comportamento deve ser consistente
   entre plataformas.
6. **Testabilidade:** novos recursos devem possuir testes automatizados.
7. **Documentação:** funcionalidades públicas devem ser documentadas.
8. **Compatibilidade:** alterações incompatíveis devem ser avaliadas e
   registradas.

Uma funcionalidade será considerada concluída quando possuir implementação
funcional, testes apropriados, comportamento definido e documentação
correspondente, quando aplicável.

---

# Visão de Longo Prazo

A Hurtip busca se tornar uma linguagem de programação simples, expressiva e
versátil, capaz de atender diferentes áreas do desenvolvimento de software.

Sua direção de longo prazo inclui:

- Programação de propósito geral.
- Desempenho e execução eficientes.
- Programação de baixo nível.
- Desenvolvimento para hardware e sistemas embarcados.
- Inteligência artificial e aprendizado de máquina.
- Desenvolvimento de jogos.
- Aplicações desktop, web e de sistema.
- Um ecossistema próprio de bibliotecas, ferramentas e extensões.

O objetivo é preservar uma sintaxe clara e acessível, enquanto são incorporados
gradualmente os recursos e a flexibilidade necessários para desenvolver
aplicações cada vez mais complexas.

A Hurtip deverá evoluir sem perder sua proposta central: tornar a programação
mais simples sem limitar aquilo que pode ser construído.

---

_Este documento está em constante evolução. Os tópicos, prioridades e direções
poderão ser reorganizados, ampliados ou removidos conforme a maturidade da
linguagem, as decisões arquiteturais e as necessidades do ecossistema._
