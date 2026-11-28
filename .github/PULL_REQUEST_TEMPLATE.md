# Solicitação de Pull Request

## Descrição

Descreva as alterações introduzidas neste Pull Request.

## Motivação

Explique qual problema esta alteração resolve ou qual é o motivo da melhoria
proposta.

## Tipo de alteração

- [ ] Correção de erro
- [ ] Nova funcionalidade da linguagem
- [ ] Melhoria no Parser
- [ ] Melhoria no Interpreter
- [ ] Melhoria na biblioteca padrão
- [ ] Atualização da documentação
- [ ] Adição ou atualização de testes
- [ ] Refatoração
- [ ] Melhoria no sistema de compilação ou ferramentas
- [ ] Outra alteração

## Detalhes da implementação

Descreva as principais decisões de implementação e os detalhes técnicos
relevantes.

## Testes

- [ ] O projeto compila corretamente.
- [ ] Os testes existentes foram executados e passaram.
- [ ] Novos testes foram adicionados quando necessário.
- [ ] Novos exemplos foram testados quando aplicável.

Comandos utilizados:

```bash
cmake -S . -B build
cmake --build build -j$(nproc)
ctest --test-dir build --output-on-failure
```

## Lista de verificação

- [ ] Minhas alterações seguem as diretrizes de contribuição do projeto.
- [ ] Revisei minhas próprias alterações.
- [ ] Atualizei a documentação quando necessário.
- [ ] Não incluí arquivos gerados pela compilação ou alterações sem relação com
      a proposta.
- [ ] Expliquei eventuais alterações incompatíveis com versões anteriores.

## Informações adicionais

Adicione capturas de tela, exemplos de saída ou outras informações relevantes.
