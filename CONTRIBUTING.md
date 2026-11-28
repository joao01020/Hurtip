# Guia de Contribuição

Obrigado por considerar contribuir com o **Hurtip**.

O Hurtip é uma linguagem de programação experimental desenvolvida com foco em
**simplicidade, clareza, expressividade e versatilidade**.

Contribuições de diferentes tipos são bem-vindas, incluindo código,
documentação, testes, exemplos, correções de bugs, melhorias de ferramentas,
sugestões de arquitetura e propostas para a evolução da linguagem.

Este documento explica como participar do desenvolvimento do projeto e como
preparar uma contribuição.

---

# 1. Antes de contribuir

Antes de começar uma alteração, recomendamos:

1. Ler o `README.md`.
2. Conhecer a documentação disponível.
3. Verificar o `READMAP.md` para entender a direção atual do projeto.
4. Consultar as issues existentes.
5. Verificar se já existe uma contribuição ou discussão relacionada ao problema
   que você pretende resolver.
6. Entender os comandos disponíveis no `COMMANDS.md`.
7. Ler o `CODE_OF_CONDUCT.md`.

Evite implementar uma alteração grande sem antes discutir sua proposta quando
ela puder afetar a arquitetura ou a direção da linguagem.

---

# 2. Formas de contribuição

Você pode contribuir com o Hurtip de diversas maneiras.

## Código

- lexer;
- parser;
- AST;
- interpretador;
- compilador;
- runtime;
- sistema de tipos;
- tratamento de erros;
- biblioteca padrão;
- ferramentas de desenvolvimento;
- CLI;
- otimizações;
- correções de bugs.

## Testes

- testes unitários;
- testes de integração;
- testes de regressão;
- casos extremos;
- testes de sintaxe;
- testes matemáticos;
- testes de desempenho.

## Documentação

- documentação da linguagem;
- exemplos;
- tutoriais;
- referências;
- guias;
- correções de erros;
- melhorias de clareza.

## Exemplos

Exemplos são especialmente importantes para uma linguagem de programação.

Contribuições podem incluir:

- programas pequenos;
- exemplos de sintaxe;
- exemplos matemáticos;
- demonstrações de funcionalidades;
- programas completos;
- casos de uso.

## Issues

Você também pode contribuir relatando:

- bugs;
- comportamentos inesperados;
- problemas de documentação;
- dificuldades de instalação;
- problemas de compatibilidade;
- sugestões de melhoria.

---

# 3. Requisitos

Para contribuir com o código do Hurtip, você precisará ter um ambiente capaz de
compilar e executar o projeto.

As ferramentas necessárias podem variar conforme a plataforma e o estado atual
do projeto.

Antes de começar, consulte o `README.md` e o `COMMANDS.md` para obter os
comandos e requisitos atualizados.

---

# 4. Obtendo o código

Clone o repositório:

```bash
git clone https://github.com/joao01020/Hurtip
```

Entre no diretório:

```bash
cd Hurtip
```

Confira a situação do repositório:

```bash
git status
```

---

# 5. Branches

Evite trabalhar diretamente na branch principal.

Crie uma branch específica para sua alteração.

Exemplo:

```bash
git checkout -b feature/nova-funcionalidade
```

Ou:

```bash
git switch -c feature/nova-funcionalidade
```

Para correções:

```bash
git switch -c fix/correcao-parser
```

Para documentação:

```bash
git switch -c docs/melhorar-documentacao
```

---

# 6. Nomenclatura de branches

Sempre que possível, utilize nomes claros e objetivos.

### Funcionalidade

```text
feature/nome-da-funcionalidade
```

### Correção

```text
fix/nome-do-problema
```

### Documentação

```text
docs/nome-da-alteracao
```

### Testes

```text
test/nome-do-teste
```

### Refatoração

```text
refactor/nome-da-refatoracao
```

### Ferramentas

```text
chore/nome-da-tarefa
```

Os nomes devem representar o propósito da alteração.

Evite nomes genéricos como:

```text
teste
coisa
mudancas
novo
fix
abc
```

---

# 7. Entendendo a estrutura do projeto

A estrutura do Hurtip pode evoluir ao longo do desenvolvimento.

Antes de adicionar ou mover arquivos, procure entender a organização existente.

Exemplo conceitual:

```text
Hurtip/
├── src/
├── tests/
├── examples/
├── docs/
├── CMakeLists.txt
├── README.md
├── COMMANDS.md
├── CONTRIBUTING.md
├── CODE_OF_CONDUCT.md
├── SECURITY.md
└── LICENSE
```

A estrutura real do projeto deve ser considerada a fonte de verdade.

Não crie diretórios ou sistemas paralelos sem necessidade.

---

# 8. Ambiente de desenvolvimento

Antes de começar uma alteração, confirme que o projeto compila em seu ambiente.

Exemplo:

```bash
cmake -S . -B build
cmake --build build
```

Quando apropriado, utilize paralelização:

```bash
cmake --build build -j$(nproc)
```

Se o projeto já estiver configurado:

```bash
cmake --build build
```

---

# 9. Executando o Hurtip

Depois de compilar, execute os exemplos ou arquivos `.hurtip` disponíveis.

Exemplo:

```bash
./build/hurtip examples/program.hurtip
```

Exemplo matemático:

```bash
./build/hurtip examples/mathematics/complex_numbers.hurtip
```

A documentação em `COMMANDS.md` deve ser consultada para os comandos disponíveis
no momento da contribuição.

---

# 10. Testes

Toda alteração que possa modificar o comportamento da linguagem deve, quando
possível, possuir testes.

Execute os testes existentes antes e depois da alteração.

Exemplo:

```bash
ctest --test-dir build
```

Ou, dependendo da configuração:

```bash
cd build
ctest
```

Uma contribuição não deve depender apenas de testes manuais quando um
comportamento puder ser coberto automaticamente.

---

# 11. Testes de regressão

Quando corrigir um bug, procure adicionar um teste que reproduza o problema.

O objetivo é evitar que o mesmo problema volte a acontecer no futuro.

Exemplo conceitual:

```text
bug encontrado
        ↓
criar teste que reproduz o bug
        ↓
corrigir implementação
        ↓
executar teste
        ↓
confirmar que o problema foi resolvido
```

Sempre que possível, o teste deve falhar antes da correção e passar depois dela.

---

# 12. Alterações na linguagem

Alterações relacionadas à sintaxe ou semântica do Hurtip devem ser avaliadas com
cuidado.

Antes de modificar:

- palavras-chave;
- operadores;
- tipos;
- regras gramaticais;
- precedência;
- estruturas de controle;
- sistema de tipos;
- comportamento de runtime;
- representação interna;

considere o impacto sobre:

- parser;
- lexer;
- AST;
- testes;
- documentação;
- exemplos existentes;
- compatibilidade;
- futuras extensões da linguagem.

Mudanças que afetam a linguagem devem ser justificadas de maneira clara.

---

# 13. Sintaxe e filosofia do Hurtip

Contribuições devem respeitar os princípios fundamentais do projeto.

Sempre que possível, priorize:

- simplicidade;
- clareza;
- consistência;
- legibilidade;
- previsibilidade;
- facilidade de aprendizado;
- expressividade;
- manutenção.

Uma solução tecnicamente possível não é necessariamente uma boa solução para o
Hurtip.

Evite adicionar complexidade apenas porque uma funcionalidade pode ser
implementada dessa maneira.

---

# 14. Código

Ao escrever código para o Hurtip:

- mantenha as implementações simples;
- evite duplicação desnecessária;
- utilize nomes claros;
- mantenha funções com responsabilidades bem definidas;
- evite abstrações prematuras;
- trate erros de maneira explícita;
- mantenha mudanças relacionadas agrupadas;
- evite alterações não relacionadas ao objetivo da contribuição.

Se o código existente seguir um padrão, procure mantê-lo.

---

# 15. Comentários

Comentários devem explicar **por que** algo existe ou funciona de determinada
maneira quando isso não for evidente pelo próprio código.

Evite comentários que apenas repitam o código.

Prefira:

```cpp
// Mantemos o token atual para permitir que o parser
// reporte a posição correta em caso de erro.
```

em vez de:

```cpp
// Incrementa o token.
token++;
```

Comentários também devem ser mantidos atualizados.

---

# 16. Tratamento de erros

Mensagens de erro fazem parte da experiência da linguagem.

Sempre que possível, erros devem:

- informar o problema;
- indicar a localização;
- utilizar linguagem clara;
- evitar mensagens vagas;
- ajudar o usuário a corrigir o código.

Exemplo conceitual:

```text
Erro: expressão inválida na linha 4, coluna 12.
```

é preferível a:

```text
Erro.
```

---

# 17. Documentação

Alterações que introduzam ou modifiquem funcionalidades devem atualizar a
documentação correspondente quando necessário.

Isso pode incluir:

- `README.md`;
- documentação da linguagem;
- exemplos;
- `COMMANDS.md`;
- `READMAP.md`;
- comentários técnicos;
- documentação de APIs.

Uma funcionalidade que existe no código, mas não pode ser descoberta ou
compreendida pela documentação, está incompleta.

---

# 18. Exemplos

Novas funcionalidades importantes devem, quando apropriado, possuir exemplos.

Os exemplos devem:

- ser pequenos quando possível;
- demonstrar claramente a funcionalidade;
- utilizar sintaxe válida;
- possuir nomes compreensíveis;
- ser mantidos conforme a linguagem evolui.

Evite exemplos desnecessariamente complexos para demonstrar conceitos simples.

---

# 19. Compatibilidade

Ao alterar uma funcionalidade existente, considere se a mudança quebra programas
que já funcionavam.

Quando uma mudança incompatível for necessária, ela deve ser discutida e
documentada.

Não altere silenciosamente o significado de uma construção da linguagem sem
considerar suas consequências.

---

# 20. Dependências

Novas dependências devem ser adicionadas somente quando houver uma justificativa
razoável.

Antes de adicionar uma dependência, considere:

- necessidade real;
- tamanho;
- manutenção;
- licença;
- segurança;
- compatibilidade;
- impacto no processo de build;
- possibilidade de implementar a funcionalidade sem ela.

Dependências desnecessárias aumentam a complexidade do projeto.

---

# 21. Segurança

Não envie informações sensíveis para o repositório.

Nunca faça commit de:

- senhas;
- tokens;
- chaves privadas;
- credenciais;
- arquivos `.env` contendo segredos;
- informações pessoais;
- dados de acesso.

Antes de abrir um Pull Request, revise as alterações:

```bash
git diff
```

E também:

```bash
git status
```

Vulnerabilidades devem ser reportadas conforme as instruções do `SECURITY.md`.

---

# 22. Formatação

Mantenha o estilo de código existente.

Evite reformatações gigantescas que não estejam relacionadas à contribuição.

Uma alteração funcional deve, sempre que possível, modificar somente o
necessário.

Isso facilita:

- revisão;
- manutenção;
- identificação de bugs;
- compreensão do histórico;
- futuros cherry-picks ou reversões.

---

# 23. Commits

Os commits devem representar mudanças coerentes.

Evite um único commit contendo alterações completamente diferentes.

Por exemplo, prefira:

```text
docs: add contributing guide
```

e:

```text
fix: correct parser error handling
```

em vez de:

```text
update everything
```

---

# 24. Mensagens de commit

Recomenda-se utilizar mensagens curtas, claras e descritivas.

Formato sugerido:

```text
tipo: descrição
```

Exemplos:

```text
feat: add string interpolation
```

```text
fix: correct complex number parsing
```

```text
test: add parser regression tests
```

```text
docs: add contributing guide
```

```text
refactor: simplify lexer token handling
```

```text
chore: update build configuration
```

---

# 25. Tipos de commit

Os seguintes tipos podem ser utilizados:

| Tipo       | Uso                                        |
| ---------- | ------------------------------------------ |
| `feat`     | Nova funcionalidade                        |
| `fix`      | Correção de bug                            |
| `docs`     | Documentação                               |
| `test`     | Testes                                     |
| `refactor` | Refatoração                                |
| `perf`     | Melhoria de desempenho                     |
| `build`    | Alterações no sistema de build             |
| `chore`    | Manutenção                                 |
| `style`    | Alterações de estilo sem mudança funcional |

Não é obrigatório utilizar todos os tipos em todos os casos.

O mais importante é que a mensagem seja clara e represente corretamente a
alteração.

---

# 26. Antes do commit

Antes de criar um commit, execute:

```bash
git status
```

Confira as diferenças:

```bash
git diff
```

Se necessário, confira também as alterações staged:

```bash
git diff --cached
```

Certifique-se de que não existem:

- arquivos temporários;
- credenciais;
- arquivos de build indevidos;
- alterações não relacionadas;
- modificações acidentais.

---

# 27. Fazendo o commit

Adicione somente os arquivos relacionados:

```bash
git add caminho/do/arquivo
```

Ou, quando todas as alterações forem intencionais:

```bash
git add .
```

Depois:

```bash
git commit -m "tipo: descrição"
```

---

# 28. Enviando a branch

Depois de criar o commit:

```bash
git push
```

Na primeira publicação de uma branch:

```bash
git push -u origin nome-da-branch
```

Evite fazer push diretamente para a branch principal, exceto quando o fluxo
oficial do projeto permitir.

---

# 29. Pull Requests

Quando a contribuição estiver pronta, abra um Pull Request.

O Pull Request deve explicar:

- o que foi alterado;
- por que a alteração foi necessária;
- como a alteração foi implementada;
- como foi testada;
- possíveis impactos;
- limitações conhecidas.

Um bom Pull Request facilita a revisão.

---

# 30. Checklist antes de abrir um Pull Request

Antes de abrir o Pull Request, confirme:

- [ ] A branch está atualizada.
- [ ] O código compila.
- [ ] Os testes passam.
- [ ] Novos comportamentos possuem testes quando necessário.
- [ ] A documentação foi atualizada quando necessário.
- [ ] Os exemplos funcionam.
- [ ] Não existem credenciais no commit.
- [ ] Não existem arquivos temporários.
- [ ] As alterações estão relacionadas ao objetivo do Pull Request.
- [ ] O código segue o padrão do projeto.
- [ ] A mensagem dos commits é clara.
- [ ] O Pull Request possui uma descrição adequada.

---

# 31. Revisão do Pull Request

Durante uma revisão, podem ser solicitadas alterações.

Isso faz parte do processo normal de desenvolvimento.

Responda às revisões de maneira objetiva e mantenha a discussão focada no
código.

Quando discordar de uma sugestão, explique tecnicamente sua posição.

Uma revisão não deve ser interpretada como crítica pessoal.

---

# 32. Alterações solicitadas

Se alterações forem solicitadas no Pull Request, faça novos commits quando
apropriado.

Evite reescrever o histórico ou utilizar `force push` sem necessidade,
especialmente quando outras pessoas estiverem trabalhando na mesma branch.

Quando for necessário atualizar a branch:

```bash
git push
```

---

# 33. Pull Requests pequenos

Sempre que possível, prefira Pull Requests focados.

Um Pull Request que resolve um problema específico normalmente é mais fácil de:

- entender;
- testar;
- revisar;
- aprovar;
- corrigir;
- reverter.

Evite misturar, por exemplo:

```text
novo parser
+
refatoração completa do lexer
+
mudança visual da documentação
+
remoção de arquivos antigos
```

sem uma relação clara entre as alterações.

---

# 34. Mudanças arquiteturais

Alterações que possam afetar significativamente a arquitetura do Hurtip devem
ser discutidas antes da implementação, quando possível.

Exemplos:

- mudança do modelo de execução;
- novo sistema de tipos;
- alteração importante da AST;
- mudança significativa no parser;
- novo sistema de módulos;
- mudanças no runtime;
- mudanças incompatíveis na linguagem;
- nova infraestrutura de build.

Para propostas maiores, explique:

1. problema;
2. solução proposta;
3. alternativas consideradas;
4. vantagens;
5. desvantagens;
6. impacto;
7. possíveis riscos.

---

# 35. Novas funcionalidades

Antes de implementar uma nova funcionalidade, considere:

- ela resolve um problema real?
- ela está alinhada com a filosofia do Hurtip?
- sua sintaxe é simples?
- seu comportamento é previsível?
- existe uma alternativa mais simples?
- ela aumenta significativamente a complexidade?
- ela precisa ser adicionada agora?
- ela pode ser implementada futuramente sem bloquear outras funcionalidades?

O objetivo não é adicionar o maior número possível de recursos.

O objetivo é construir uma linguagem coerente.

---

# 36. Propostas de sintaxe

Propostas que alterem a sintaxe do Hurtip devem apresentar exemplos claros.

Por exemplo:

```hurtip
create name = "Hurtip"
```

deve ser comparado com alternativas quando a alteração envolver uma decisão de
design.

A proposta deve explicar não apenas **como** a sintaxe funcionaria, mas também
**por que** ela deveria existir.

---

# 37. Testes manuais

Testes manuais continuam sendo úteis, especialmente durante o desenvolvimento
inicial da linguagem.

Ao testar manualmente uma funcionalidade, registre:

- entrada utilizada;
- saída esperada;
- saída obtida;
- comportamento em casos inválidos;
- comportamento em casos extremos.

Quando o comportamento estiver estabilizado, considere transformá-lo em um teste
automatizado.

---

# 38. Performance

Alterações de desempenho devem, quando possível, apresentar evidências.

Evite afirmar que algo é "mais rápido" sem uma medição ou justificativa técnica.

Quando apropriado, documente:

- cenário utilizado;
- tamanho da entrada;
- método de medição;
- resultado anterior;
- resultado posterior.

Otimizações não devem comprometer desnecessariamente:

- clareza;
- segurança;
- corretude;
- manutenção.

---

# 39. Código experimental

O Hurtip está em desenvolvimento e algumas partes da implementação podem ser
experimentais.

Experimentação é permitida e incentivada quando contribui para descobrir
soluções melhores.

Entretanto, código experimental deve ser claramente identificado quando
necessário.

Experimentos não devem ser incorporados como comportamento oficial sem avaliação
adequada.

---

# 40. Issues de bugs

Ao reportar um bug, tente fornecer um exemplo mínimo.

Exemplo:

```hurtip
create value = ...
```

Depois descreva:

```text
Esperado:
...

Obtido:
...
```

Se houver erro do programa, inclua a mensagem completa.

Evite informações desnecessárias que dificultem a reprodução.

---

# 41. Issues de funcionalidades

Ao sugerir uma funcionalidade, explique:

### Problema

Qual problema está sendo resolvido?

### Proposta

Como a funcionalidade poderia funcionar?

### Exemplo

Como seria utilizada?

### Motivação

Por que isso seria útil?

### Impacto

O que mudaria na linguagem?

Isso ajuda a transformar uma ideia em uma discussão técnica.

---

# 42. Issues duplicadas

Antes de abrir uma nova issue, procure por issues existentes.

Se uma issue semelhante já existir, considere participar da discussão existente
em vez de criar uma duplicata.

Isso ajuda a manter o projeto organizado.

---

# 43. Contribuições de documentação

Documentação deve priorizar clareza.

Evite presumir conhecimento que o leitor pode não possuir.

Quando possível:

- explique termos;
- forneça exemplos;
- mantenha instruções atualizadas;
- evite ambiguidades;
- mantenha os exemplos executáveis.

---

# 44. Traduções

Contribuições de tradução são bem-vindas quando fizerem sentido para o projeto.

Traduções devem preservar o significado técnico do conteúdo original.

Quando um termo técnico não possuir uma tradução adequada, pode ser preferível
manter o termo original em vez de criar uma tradução confusa.

---

# 45. Licenciamento

Ao contribuir com código ou documentação, você deve possuir os direitos
necessários para disponibilizar sua contribuição sob a licença aplicável ao
projeto.

Não envie código de terceiros sem verificar a licença correspondente.

Quando uma contribuição depender de código externo, informe sua origem e os
requisitos de licença quando necessário.

---

# 46. Contribuições assistidas por IA

Ferramentas de inteligência artificial podem ser utilizadas como auxílio durante
o desenvolvimento.

Entretanto, a pessoa que envia a contribuição continua sendo responsável por
ela.

Isso inclui verificar:

- funcionamento;
- qualidade;
- segurança;
- licença;
- compatibilidade;
- testes;
- documentação;
- possíveis efeitos colaterais.

Não envie código simplesmente porque uma ferramenta de IA o produziu.

A contribuição deve ser compreendida e revisada por quem a está submetendo.

---

# 47. Segurança das contribuições

Contribuidores devem considerar possíveis impactos de segurança antes de enviar
código.

Particular atenção deve ser dada a:

- entrada do usuário;
- parsing;
- execução de código;
- acesso a arquivos;
- memória;
- processos;
- comandos externos;
- rede;
- dependências;
- serialização;
- tratamento de erros.

Quando uma contribuição introduzir uma nova superfície de ataque, isso deve ser
considerado durante a revisão.

---

# 48. Não introduza código malicioso

É estritamente proibido utilizar o processo de contribuição para introduzir
deliberadamente:

- malware;
- backdoors;
- mecanismos de acesso não autorizado;
- coleta indevida de dados;
- código destrutivo;
- comportamento oculto malicioso.

Questões de segurança devem seguir o `SECURITY.md`.

---

# 49. Respeito às decisões do projeto

Nem toda proposta será aceita.

Uma contribuição pode ser recusada porque:

- não está alinhada com a direção do projeto;
- aumenta complexidade;
- possui problemas de manutenção;
- introduz riscos;
- não resolve uma necessidade suficientemente importante;
- existe uma solução melhor;
- ainda não é o momento adequado.

A recusa de uma proposta não representa uma rejeição pessoal ao contribuidor.

---

# 50. Disputas técnicas

Quando houver discordância sobre uma decisão técnica:

1. apresente argumentos;
2. forneça evidências quando possível;
3. considere alternativas;
4. mantenha o respeito;
5. evite repetir o mesmo argumento indefinidamente;
6. respeite a decisão final dos responsáveis pelo projeto quando a discussão for
   encerrada.

Discussões produtivas podem levar a decisões melhores.

Discussões sem fim não ajudam o projeto.

---

# 51. Mantendo o histórico limpo

Evite commits desnecessários como:

```text
fix
fix2
fix final
fix final 2
agora vai
teste
teste2
```

Quando apropriado, organize os commits de maneira lógica antes de abrir o Pull
Request.

Entretanto, não reescreva o histórico compartilhado de outras pessoas sem
coordenação.

---

# 52. Desenvolvimento local

Durante o desenvolvimento, é normal criar arquivos temporários ou builds locais.

Esses arquivos não devem ser adicionados ao repositório quando não forem
necessários.

Antes do commit:

```bash
git status
```

verifique cuidadosamente o que será enviado.

---

# 53. Atualizando sua branch

Se a branch principal tiver avançado durante o desenvolvimento, atualize sua
branch conforme o fluxo adotado pelo projeto.

Antes de integrar mudanças, certifique-se de que os testes continuam passando.

Em caso de conflitos, resolva-os cuidadosamente e execute novamente os testes.

---

# 54. Conflitos de merge

Não resolva conflitos simplesmente escolhendo automaticamente uma das versões.

Analise:

- o que mudou;
- por que mudou;
- se ambas as alterações são necessárias;
- se o comportamento esperado foi preservado.

Depois de resolver:

```bash
git status
```

e execute novamente os testes.

---

# 55. Checklist para código

Antes de enviar uma alteração de código:

- [ ] O código é necessário?
- [ ] A solução é simples?
- [ ] Os nomes são claros?
- [ ] A implementação segue os padrões existentes?
- [ ] Erros são tratados adequadamente?
- [ ] Não há duplicação desnecessária?
- [ ] Não foram adicionadas dependências sem necessidade?
- [ ] Não há dados sensíveis?
- [ ] A funcionalidade foi testada?
- [ ] Casos extremos foram considerados?

---

# 56. Checklist para documentação

Antes de enviar uma alteração de documentação:

- [ ] A informação está correta?
- [ ] Os exemplos funcionam?
- [ ] A linguagem está clara?
- [ ] Os links estão corretos?
- [ ] Não existem instruções desatualizadas?
- [ ] O documento está no local apropriado?
- [ ] A documentação está consistente com o código?

---

# 57. Checklist para uma nova funcionalidade

Antes de propor ou implementar uma nova funcionalidade:

- [ ] O problema está claramente definido.
- [ ] A funcionalidade está alinhada ao Hurtip.
- [ ] A sintaxe é simples.
- [ ] O comportamento é previsível.
- [ ] O impacto foi considerado.
- [ ] Existem testes planejados.
- [ ] A documentação foi considerada.
- [ ] Possíveis incompatibilidades foram avaliadas.

---

# 58. Após a contribuição

Depois que uma contribuição for integrada:

- acompanhe possíveis problemas;
- responda a relatos relacionados;
- corrija regressões quando necessário;
- atualize a documentação caso algo mude;
- continue colaborando com a comunidade.

Contribuir não termina necessariamente no momento em que o Pull Request é
aceito.

---

# 59. Primeiras contribuições

Se você está contribuindo pela primeira vez, não é necessário começar com uma
grande mudança.

Boas primeiras contribuições podem incluir:

- corrigir documentação;
- melhorar um exemplo;
- adicionar um teste;
- corrigir uma mensagem de erro;
- reproduzir um bug;
- melhorar um comentário;
- corrigir um pequeno problema;
- ajudar a responder uma questão técnica.

Pequenas contribuições são uma ótima maneira de conhecer o projeto.

---

# 60. Como escolher uma tarefa

Se você não sabe por onde começar, procure:

- issues abertas;
- problemas de documentação;
- testes ausentes;
- bugs reproduzíveis;
- exemplos que podem ser melhorados;
- tarefas marcadas como adequadas para novos contribuidores.

Se uma tarefa não estiver claramente disponível, você também pode abrir uma
issue descrevendo uma proposta.

---

# 61. Comunicação

A comunicação deve ser:

- objetiva;
- respeitosa;
- técnica quando necessário;
- aberta a diferentes opiniões;
- orientada à solução.

Evite transformar discussões técnicas em disputas pessoais.

Consulte também o `CODE_OF_CONDUCT.md`.

---

# 62. Filosofia de contribuição

O Hurtip não busca apenas aumentar a quantidade de código.

Uma boa contribuição é aquela que melhora o projeto.

Isso pode significar:

- remover código desnecessário;
- simplificar uma implementação;
- melhorar uma mensagem de erro;
- adicionar um teste;
- melhorar a documentação;
- corrigir uma inconsistência;
- tornar uma funcionalidade mais previsível.

**Mais código não significa necessariamente um projeto melhor.**

---

# 63. Princípio da menor mudança necessária

Quando resolver um problema, procure fazer a menor alteração capaz de resolver
corretamente o problema.

Evite modificar partes não relacionadas do projeto apenas porque elas poderiam
ser melhoradas.

Melhorias independentes podem ser propostas separadamente.

Isso torna o desenvolvimento mais previsível e facilita as revisões.

---

# 64. Qualidade antes de velocidade

O desenvolvimento do Hurtip deve priorizar soluções sustentáveis.

Uma implementação rápida, mas difícil de manter, pode gerar mais trabalho
posteriormente.

Sempre que possível, priorize:

```text
corretude
    ↓
clareza
    ↓
testabilidade
    ↓
manutenção
    ↓
desempenho
```

O equilíbrio pode variar conforme o problema, mas a corretude deve permanecer
fundamental.

---

# 65. Encerramento

Obrigado por contribuir com o Hurtip.

Cada contribuição ajuda a construir uma linguagem mais consistente, acessível e
capaz.

Seja uma linha de código, um teste, uma documentação, uma correção de bug ou uma
ideia, sua contribuição pode fazer parte da evolução do projeto.

**Construa. Teste. Documente. Compartilhe.**

**Hurtip — simplicidade, clareza e versatilidade.**
