# Política de Segurança

## Política de Segurança do Hurtip

A segurança é uma parte importante do desenvolvimento e da manutenção do Hurtip.

O Hurtip é uma linguagem de programação experimental desenvolvida com foco em
simplicidade, clareza, expressividade e versatilidade.

Este documento estabelece as diretrizes para identificação, comunicação,
análise, correção e divulgação de vulnerabilidades de segurança relacionadas ao
projeto.

Nosso objetivo é tratar problemas de segurança de maneira responsável,
transparente e organizada, protegendo usuários, contribuidores e a integridade
do projeto.

---

# 1. Nosso compromisso com a segurança

O projeto Hurtip busca desenvolver uma implementação confiável e segura.

Reconhecemos que vulnerabilidades podem surgir durante o desenvolvimento de
qualquer software, especialmente em componentes como:

- Lexer.
- Parser.
- AST.
- Interpretador.
- Compilador.
- Runtime.
- Gerenciamento de memória.
- Sistema de tipos.
- Sistema de arquivos.
- Execução de código.
- Gerenciamento de processos.
- Bibliotecas e dependências.
- Ferramentas de desenvolvimento.
- Sistemas de build.

Incentivamos pesquisadores, desenvolvedores, usuários e contribuidores a
reportarem possíveis vulnerabilidades.

Todos os relatos legítimos serão tratados com seriedade.

---

# 2. Escopo

Esta política se aplica aos componentes oficiais do projeto Hurtip, incluindo:

- Código-fonte.
- Compilador.
- Interpretador.
- Runtime.
- Parser.
- Lexer.
- Bibliotecas oficiais.
- Ferramentas oficiais.
- Scripts de desenvolvimento.
- Sistemas de build.
- Exemplos oficiais, quando apresentarem riscos de segurança.
- Infraestrutura diretamente mantida pelo projeto.

Vulnerabilidades em dependências externas também podem ser comunicadas quando
afetarem diretamente a segurança do Hurtip.

Produtos, serviços ou projetos de terceiros não mantidos pelo Hurtip não estão
automaticamente cobertos por esta política.

---

# 3. Tipos de vulnerabilidades

Os seguintes problemas são exemplos de situações que podem ser considerados
vulnerabilidades de segurança.

## 3.1. Execução arbitrária de código

Situações em que uma pessoa consegue executar código não autorizado por meio do
compilador, interpretador, runtime ou ferramentas do Hurtip.

## 3.2. Corrupção de memória

Problemas relacionados a:

- Buffer overflow.
- Heap overflow.
- Stack overflow.
- Use-after-free.
- Double free.
- Out-of-bounds access.
- Memory corruption.
- Ponteiros inválidos.

## 3.3. Gerenciamento inadequado de memória

Problemas que possam provocar comportamento indefinido, corrupção de dados,
encerramentos inesperados ou comprometimento da execução.

## 3.4. Parsing e processamento de entradas

Vulnerabilidades relacionadas ao processamento de arquivos ou entradas
malformadas, incluindo:

- Parsing incorreto.
- Acesso inválido à memória.
- Consumo excessivo de recursos.
- Recursão descontrolada.
- Entradas especialmente construídas para comprometer o processo.
- Condições que provoquem encerramento inesperado.

## 3.5. Escalada de privilégios

Situações em que uma funcionalidade permite obter permissões superiores às
autorizadas.

## 3.6. Acesso não autorizado

Problemas que possibilitem acessar arquivos, informações, processos ou recursos
sem autorização.

## 3.7. Vazamento de informações

Exposição indevida de:

- Dados privados.
- Informações sensíveis.
- Conteúdo de arquivos.
- Credenciais.
- Tokens.
- Informações internas.
- Dados de memória.

## 3.8. Negação de serviço

Problemas que permitam impedir ou prejudicar significativamente o funcionamento
do software.

Exemplos:

- Consumo excessivo de memória.
- Consumo excessivo de CPU.
- Loops não controlados.
- Recursão excessiva.
- Travamentos.
- Esgotamento de recursos.

## 3.9. Dependências vulneráveis

Vulnerabilidades em bibliotecas, ferramentas ou componentes externos utilizados
pelo projeto.

## 3.10. Comprometimento da cadeia de desenvolvimento

Problemas relacionados a:

- Scripts de build.
- Distribuição de binários.
- Publicação de versões.
- Dependências comprometidas.
- Alterações maliciosas.
- Acesso não autorizado ao repositório.

Esta lista não é exaustiva.

Outros problemas que possam comprometer a segurança do Hurtip também podem ser
reportados.

---

# 4. Como reportar uma vulnerabilidade

Se você identificar uma possível vulnerabilidade, solicitamos que não publique
os detalhes técnicos em uma issue pública antes que o problema seja analisado.

A divulgação pública prematura pode permitir que outras pessoas explorem a
vulnerabilidade antes da disponibilização de uma correção.

## 4.1. Canal de comunicação

Utilize o recurso de comunicação privada de vulnerabilidades do GitHub, caso
esteja habilitado no repositório Hurtip.

Caminho:

Repository → Security → Advisories → Report a vulnerability.

Caso esse recurso não esteja disponível, entre em contato diretamente com os
mantenedores por um canal privado oficial indicado no perfil ou na página do
projeto.

Não utilize uma issue pública para enviar detalhes de uma vulnerabilidade ainda
não corrigida.

## 4.2. Informações recomendadas

Para facilitar a análise, recomendamos incluir:

- Descrição da vulnerabilidade.
- Componente afetado.
- Versão ou commit afetado.
- Sistema operacional.
- Arquitetura, quando relevante.
- Pré-requisitos para reprodução.
- Passos para reproduzir o problema.
- Comportamento esperado.
- Comportamento observado.
- Impacto potencial.
- Código de demonstração, quando necessário.
- Logs ou mensagens de erro relevantes.
- Possível solução, caso exista.

Um relatório não precisa conter todas essas informações para ser considerado
válido.

Relatos incompletos também podem ser analisados.

---

# 5. Modelo de relatório

Para facilitar a comunicação, recomendamos utilizar a seguinte estrutura:

### Título

Descrição breve do problema.

### Componente afetado

Identifique o componente do Hurtip envolvido.

### Versão afetada

Informe a versão ou o commit utilizado.

### Descrição

Explique o comportamento identificado.

### Reprodução

Forneça os passos necessários para reproduzir o problema.

### Impacto

Descreva quais consequências podem ocorrer.

### Evidências

Inclua logs, exemplos ou outras informações relevantes.

### Mitigação

Caso conheça uma maneira de reduzir o risco, descreva-a.

---

# 6. Processo de análise

Após receber um relatório, os mantenedores poderão seguir as seguintes etapas:

1. Receber o relato.
2. Confirmar o recebimento quando possível.
3. Avaliar a validade técnica da informação.
4. Identificar os componentes afetados.
5. Avaliar a gravidade e o impacto.
6. Investigar possíveis causas.
7. Desenvolver uma correção ou mitigação.
8. Realizar testes.
9. Preparar uma atualização de segurança.
10. Coordenar a divulgação responsável.

O processo poderá variar conforme a complexidade e a gravidade da
vulnerabilidade.

---

# 7. Classificação de gravidade

As vulnerabilidades poderão ser classificadas de acordo com seu impacto.

## Crítica

Problemas que permitam comprometimento significativo de sistemas, execução
arbitrária de código em contextos relevantes, exposição grave de informações ou
comprometimento da infraestrutura do projeto.

## Alta

Problemas que possam comprometer significativamente a integridade,
confidencialidade ou disponibilidade do software.

## Média

Problemas que provoquem impactos relevantes, mas que dependam de condições
específicas ou apresentem limitações de exploração.

## Baixa

Problemas de impacto limitado, com consequências restritas ou exploração pouco
significativa.

## Informativa

Problemas que mereçam registro ou investigação, mas que não representem
necessariamente uma vulnerabilidade explorável.

A classificação final será determinada pelos mantenedores considerando o
contexto técnico e o impacto real.

---

# 8. Prazos de resposta

O projeto buscará analisar os relatos dentro de prazos razoáveis.

Como referência:

| Etapa                         | Prazo desejado                    |
| ----------------------------- | --------------------------------- |
| Confirmação de recebimento    | Até 3 dias úteis                  |
| Avaliação inicial             | Até 7 dias úteis                  |
| Atualização sobre o andamento | Quando houver progresso relevante |
| Correção                      | Conforme gravidade e complexidade |

Esses prazos são objetivos de atendimento, não garantias.

Vulnerabilidades complexas podem exigir investigação adicional.

Quando possível, o responsável pelo relato será informado sobre atrasos
relevantes.

---

# 9. Divulgação responsável

O Hurtip adota o princípio da divulgação responsável de vulnerabilidades.

Isso significa que os detalhes técnicos de uma vulnerabilidade devem ser
tratados de maneira coordenada, permitindo que os mantenedores tenham a
oportunidade de investigar e disponibilizar uma correção antes da divulgação
pública.

Solicitamos que pesquisadores:

- Não divulguem publicamente vulnerabilidades não corrigidas sem coordenação.
- Não publiquem dados privados obtidos durante uma investigação.
- Não explorem vulnerabilidades para causar danos.
- Não comprometam sistemas de terceiros.
- Não realizem testes destrutivos.
- Não utilizem a vulnerabilidade para obter acesso não autorizado.

Após a disponibilização de uma correção, os detalhes poderão ser divulgados de
maneira coordenada, respeitando os interesses de segurança dos usuários.

---

# 10. Testes de segurança

Testes de segurança são incentivados quando realizados de maneira responsável.

Pesquisadores devem limitar seus testes ao ambiente necessário para reproduzir o
problema.

Não é permitido:

- Comprometer sistemas de terceiros.
- Destruir ou modificar dados sem autorização.
- Interromper serviços intencionalmente.
- Acessar informações privadas sem autorização.
- Utilizar vulnerabilidades para obter vantagens indevidas.
- Realizar testes que possam prejudicar usuários ou infraestrutura.

Sempre que possível, utilize ambientes isolados e dados de teste.

---

# 11. Correções de segurança

Correções devem priorizar:

- Eliminação da causa da vulnerabilidade.
- Preservação do comportamento esperado.
- Testes de regressão.
- Prevenção de problemas semelhantes.
- Compatibilidade, quando possível.
- Documentação adequada.

Uma correção não deve simplesmente ocultar uma mensagem de erro ou impedir uma
demonstração específica sem resolver a causa do problema.

Quando necessário, poderão ser implementadas medidas temporárias de mitigação
até que uma correção definitiva esteja disponível.

---

# 12. Atualizações de segurança

Quando uma vulnerabilidade for corrigida, os mantenedores poderão publicar
informações contendo:

- Identificação do problema.
- Componentes afetados.
- Versões afetadas.
- Versões corrigidas.
- Impacto.
- Recomendações de atualização.
- Referência à correção.
- Créditos ao pesquisador, quando autorizado.

Os usuários devem acompanhar as atualizações oficiais do projeto e utilizar
versões corrigidas sempre que disponíveis.

---

# 13. Versões suportadas

Como o Hurtip é um projeto em desenvolvimento, a política de suporte a versões
poderá evoluir.

Salvo indicação diferente em uma publicação oficial:

- A versão mais recente disponibilizada será a principal referência para
  atualizações.
- Versões antigas poderão deixar de receber correções.
- Versões experimentais poderão apresentar limitações de segurança.
- Alterações de arquitetura poderão modificar requisitos e comportamentos.

Não presuma que uma versão antiga continuará recebendo atualizações de
segurança.

---

# 14. Segurança durante o desenvolvimento

Contribuidores devem considerar a segurança em todas as etapas do
desenvolvimento.

Recomendamos:

- Validar entradas externas.
- Evitar acessos inválidos à memória.
- Verificar limites de arrays e buffers.
- Tratar erros adequadamente.
- Evitar comportamentos indefinidos.
- Revisar operações com ponteiros.
- Utilizar ferramentas de análise quando disponíveis.
- Manter dependências atualizadas.
- Evitar permissões desnecessárias.
- Testar entradas malformadas.
- Revisar alterações sensíveis antes de integrá-las.

Segurança não deve ser considerada apenas uma etapa final do desenvolvimento.

---

# 15. Dependências

Dependências externas devem ser avaliadas considerando:

- Origem.
- Licença.
- Histórico de manutenção.
- Vulnerabilidades conhecidas.
- Compatibilidade.
- Necessidade real.
- Impacto na superfície de ataque.

Dependências vulneráveis devem ser avaliadas e atualizadas quando apropriado.

A inclusão de uma nova dependência deve possuir justificativa técnica.

---

# 16. Segurança do repositório

O acesso ao repositório Hurtip deve ser concedido somente a pessoas autorizadas.

Recomendamos:

- Utilizar autenticação multifator.
- Evitar compartilhamento de credenciais.
- Revisar permissões periodicamente.
- Proteger branches importantes.
- Revisar Pull Requests.
- Evitar execução de código não confiável em ambientes privilegiados.
- Não armazenar segredos no código-fonte.
- Manter tokens e chaves de acesso protegidos.

Credenciais comprometidas devem ser revogadas ou substituídas imediatamente.

---

# 17. Segurança dos usuários

Usuários devem executar programas Hurtip somente quando compreenderem sua origem
e finalidade.

Arquivos de código podem conter operações potencialmente perigosas, dependendo
dos recursos disponibilizados pela implementação.

Recomendamos:

- Não executar arquivos desconhecidos sem avaliação.
- Utilizar ambientes isolados para testar código não confiável.
- Manter o software atualizado.
- Evitar executar ferramentas com privilégios administrativos sem necessidade.
- Verificar a origem de binários e dependências.
- Não compartilhar credenciais em arquivos de configuração.

---

# 18. Relatos de boa-fé

O projeto valoriza pesquisadores e contribuidores que ajudam a identificar
problemas de segurança.

Relatos realizados de boa-fé serão tratados com respeito.

Não serão considerados comportamentos inadequados simplesmente por uma pessoa:

- identificar uma vulnerabilidade;
- demonstrar um problema;
- apresentar evidências;
- questionar decisões de segurança;
- sugerir melhorias;
- comunicar um risco legítimo.

O objetivo é incentivar a identificação responsável de problemas.

---

# 19. Reconhecimento de pesquisadores

Quando uma vulnerabilidade for confirmada e corrigida, os mantenedores poderão
reconhecer publicamente a contribuição do pesquisador.

O reconhecimento poderá ocorrer em:

- comunicado de segurança;
- histórico de alterações;
- publicação de correção;
- documentação;
- créditos oficiais.

A identificação pública dependerá da autorização do pesquisador.

O projeto não divulgará informações pessoais sem autorização.

---

# 20. Limitações de responsabilidade

O Hurtip é um projeto de software em desenvolvimento.

Apesar dos esforços para identificar e corrigir vulnerabilidades, não é possível
garantir que o software esteja completamente livre de falhas de segurança.

Os usuários devem avaliar os riscos antes de utilizar o software em ambientes
críticos ou com informações sensíveis.

Esta política não substitui práticas de segurança adequadas, auditorias
independentes ou requisitos legais aplicáveis.

---

# 21. Atualizações desta política

Esta política poderá ser atualizada conforme o crescimento e a evolução do
Hurtip.

Alterações poderão considerar:

- Novas funcionalidades.
- Mudanças arquiteturais.
- Novos componentes.
- Novas ameaças.
- Melhorias no processo de desenvolvimento.
- Experiências com incidentes de segurança.
- Necessidades da comunidade.

As atualizações relevantes serão documentadas no repositório.

---

# 22. Contato

Para comunicar vulnerabilidades, utilize preferencialmente o sistema privado de
reporte de vulnerabilidades do GitHub, caso esteja habilitado no repositório.

Se esse recurso não estiver disponível, procure um canal privado oficial dos
mantenedores.

Não publique detalhes de vulnerabilidades ainda não corrigidas em canais
públicos.

---

# 23. Compromisso final

A segurança é uma responsabilidade compartilhada.

O Hurtip busca evoluir continuamente, identificando riscos, corrigindo falhas e
adotando práticas que contribuam para um desenvolvimento mais confiável.

Agradecemos a todos que ajudam a tornar o projeto mais seguro.

**Hurtip — simplicidade, clareza, versatilidade e segurança.**
