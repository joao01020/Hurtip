# Acessibilidade

A Hurtip busca ser uma linguagem de programação acessível, compreensível e
utilizável pelo maior número possível de pessoas.

Acreditamos que as ferramentas de desenvolvimento devem reduzir barreiras, e não
criar novas dificuldades para quem deseja aprender, utilizar ou contribuir com
uma linguagem de programação.

Este documento apresenta os princípios de acessibilidade do projeto, as
expectativas para contribuições, as formas de relatar barreiras e o compromisso
de melhorar continuamente a experiência de uso da Hurtip.

As práticas descritas abrangem o site, a documentação, as ferramentas de
desenvolvimento, a extensão para editores e as interfaces de interação com a
linguagem.

## Prioridades

O desenvolvimento da Hurtip deve considerar a acessibilidade desde o
planejamento até a implementação de novas funcionalidades.

Nossas principais prioridades são:

- **Clareza:** utilizar textos, instruções e mensagens que sejam compreensíveis.
- **Navegação:** permitir que as interfaces possam ser utilizadas por diferentes
  métodos de interação, incluindo teclado.
- **Compatibilidade:** considerar tecnologias assistivas e diferentes ambientes
  de utilização.
- **Legibilidade:** manter contraste adequado, hierarquia visual consistente e
  textos fáceis de acompanhar.
- **Documentação:** fornecer instruções organizadas, exemplos claros e conteúdo
  acessível.
- **Diagnósticos:** apresentar mensagens de erro compreensíveis, com informações
  suficientes para ajudar na identificação dos problemas.
- **Inclusão:** evitar barreiras desnecessárias para pessoas com diferentes
  necessidades e níveis de experiência.

Sempre que aplicável, o projeto utilizará as Diretrizes de Acessibilidade para
Conteúdo Web (WCAG) como referência para orientar melhorias no site e em suas
interfaces.

Essas referências representam objetivos de desenvolvimento e não uma declaração
de conformidade já verificada.

## Expectativas para contribuidores

Contribuições que introduzam ou modifiquem interfaces, documentação ou
ferramentas devem considerar seus possíveis impactos na acessibilidade.

Esperamos que os contribuidores:

- Utilizem linguagem clara e objetiva na documentação.
- Mantenham uma estrutura organizada de títulos e seções.
- Forneçam textos alternativos para imagens informativas.
- Evitem utilizar apenas cores para transmitir informações importantes.
- Considerem a navegação por teclado em interfaces interativas.
- Mantenham indicações visíveis de foco nos elementos interativos.
- Utilizem nomes e descrições compreensíveis em botões, campos e controles.
- Considerem leitores de tela ao desenvolver interfaces.
- Evitem animações, efeitos visuais ou elementos que possam dificultar a
  utilização.
- Atualizem a documentação quando uma alteração modificar a experiência de uso.

Quando uma contribuição introduzir uma interface visual, é recomendável incluir
informações sobre os testes realizados e eventuais limitações conhecidas.

O projeto poderá incorporar verificações automatizadas e manuais de
acessibilidade conforme suas ferramentas e processos de desenvolvimento
evoluírem.

## Relato de problemas de acessibilidade

Se você encontrar uma barreira que dificulte ou impeça a utilização da Hurtip,
poderá relatá-la por meio do GitHub Issues:

https://github.com/joao01020/Hurtip/issues

Também é possível utilizar as discussões do projeto para apresentar sugestões e
conversar sobre melhorias:

https://github.com/joao01020/Hurtip/discussions

Ao relatar um problema, procure informar:

- Qual funcionalidade ou página foi afetada.
- Qual tarefa você estava tentando realizar.
- O que aconteceu e qual comportamento era esperado.
- O sistema operacional utilizado.
- O navegador ou editor, quando aplicável.
- A tecnologia assistiva utilizada, caso seja relevante.
- Uma possível forma de reproduzir o problema.

Capturas de tela e gravações podem ajudar na investigação, mas são opcionais.

Não é necessário informar qualquer diagnóstico ou condição pessoal para relatar
uma dificuldade de acessibilidade.

### Severidade

Os problemas poderão ser classificados conforme o impacto na experiência de
utilização.

| Nível    | Descrição                                                                                                              |
| -------- | ---------------------------------------------------------------------------------------------------------------------- |
| Crítico  | Uma barreira impede completamente o acesso ou a utilização de uma funcionalidade essencial, sem alternativa conhecida. |
| Alto     | Uma barreira compromete significativamente uma tarefa importante ou dificulta o acesso a informações essenciais.       |
| Moderado | Uma dificuldade prejudica a experiência, mas existe uma alternativa razoável para concluir a tarefa.                   |
| Baixo    | Uma melhoria desejável que não impede a utilização normal do recurso.                                                  |

A classificação definitiva será realizada durante a análise do relato pelos
responsáveis pelo projeto.

Não é necessário que quem relata o problema determine sua severidade.

### Como respondemos

Os relatos serão analisados conforme sua gravidade, impacto e disponibilidade de
recursos para investigação e correção.

Sempre que possível, os responsáveis pelo projeto procurarão:

1. Confirmar o recebimento do relato.
2. Compreender e reproduzir a barreira identificada.
3. Avaliar seu impacto na experiência de utilização.
4. Informar o andamento da investigação.
5. Identificar possíveis alternativas temporárias.
6. Desenvolver e avaliar uma correção.
7. Atualizar o relato com o resultado da análise.

Não estabelecemos prazos fixos de resolução neste momento. O tempo necessário
poderá variar conforme a complexidade técnica e a gravidade do problema.

Quando uma correção estiver disponível, contribuições de quem identificou a
barreira poderão ajudar a verificar se o problema foi resolvido.

## Responsabilidade e manutenção

A responsabilidade pela acessibilidade da Hurtip pertence à manutenção do
projeto.

O responsável pela manutenção deverá:

- Considerar a acessibilidade durante o desenvolvimento de novas
  funcionalidades.
- Avaliar relatos e sugestões relacionados a barreiras de utilização.
- Incentivar práticas acessíveis nas contribuições.
- Identificar limitações conhecidas.
- Atualizar este documento conforme as práticas do projeto evoluírem.

Este documento deverá ser revisado periodicamente e sempre que mudanças
significativas nas ferramentas, interfaces ou processos de desenvolvimento
justificarem uma atualização.

Caso a responsabilidade pela manutenção seja transferida, as práticas e os
registros relacionados à acessibilidade deverão acompanhar essa transição.

## Ambientes suportados

A Hurtip está em desenvolvimento e seus ambientes de utilização ainda estão em
processo de expansão e avaliação.

Atualmente, o projeto possui como foco:

- Ambientes Linux para desenvolvimento e execução.
- Compilação com C++17.
- Ferramentas baseadas em CMake e GCC/G++.
- Utilização por terminal.
- Integração experimental com Visual Studio Code.
- Site e documentação disponibilizados pelo GitHub Pages.

A compatibilidade com diferentes sistemas operacionais, navegadores, métodos de
entrada e tecnologias assistivas deverá ser avaliada progressivamente.

Não declaramos suporte ou compatibilidade de acessibilidade para combinações de
dispositivos e tecnologias assistivas que ainda não tenham sido verificadas.

## Limitações conhecidas

A acessibilidade do projeto ainda não passou por uma avaliação abrangente.

Por esse motivo, não é possível afirmar que todas as interfaces, ferramentas e
documentos atendam a todos os requisitos de acessibilidade.

Entre os aspectos que ainda precisam ser avaliados estão:

- Navegação completa do site utilizando apenas teclado.
- Compatibilidade do site com leitores de tela.
- Contraste e legibilidade dos elementos visuais.
- Acessibilidade dos formulários e componentes interativos.
- Experiência de utilização da extensão para Visual Studio Code.
- Clareza e consistência das mensagens de erro da linguagem.
- Acessibilidade dos exemplos e materiais de documentação.

Limitações identificadas deverão ser documentadas e acompanhadas por meio dos
canais de contribuição do projeto.

## Feedback e melhorias

A Hurtip reconhece que a acessibilidade é um processo contínuo e que diferentes
pessoas podem encontrar barreiras distintas durante a utilização das
ferramentas.

Sugestões para melhorar este documento ou as práticas de acessibilidade do
projeto são bem-vindas.

Para apresentar sugestões gerais, utilize o GitHub Discussions:

https://github.com/joao01020/Hurtip/discussions

Para relatar uma barreira específica, utilize o processo descrito na seção de
relato de problemas.

Todas as contribuições que ajudem a tornar a Hurtip mais acessível,
compreensível e inclusiva são bem-vindas.

---

_A acessibilidade faz parte do compromisso de tornar a Hurtip uma linguagem de
programação acessível não apenas em sua sintaxe, mas também em suas ferramentas,
documentação e comunidade._
