# Extensão para Visual Studio Code

A Hurtip possui uma extensão inicial para o Visual Studio Code, criada para reconhecer a linguagem e facilitar a edição de arquivos `.hurtip`.

## Recursos

- Reconhecimento da extensão `.hurtip`.
- Identificação da linguagem Hurtip.
- Realce de sintaxe.
- Destaque de palavras-chave.
- Destaque da função `view()`.
- Destaque de strings e números.
- Destaque de operadores.
- Fechamento automático de parênteses e aspas.
- Tema de ícones personalizado.

## Identidade visual

O projeto possui uma identidade visual própria, incluindo ícone para a Hurtip e variações em diferentes resoluções.

O ícone dos arquivos `.hurtip` foi integrado ao tema Seti do VS Code, preservando os ícones existentes para os demais tipos de arquivos.

O tema personalizado é identificado como **Seti + Hurtip**.

## Estrutura

```text
vscode-extension/
├── package.json
├── language-configuration.json
├── syntaxes/
│   └── hurtip.tmLanguage.json
└── icons/
    ├── hurtip-file.png
    ├── hurtip-file.svg
    ├── hurtip-icon-theme.json
    └── seti/
        ├── seti-circular-128x128.png
        ├── seti.woff
        ├── vs-seti-icon-theme.json
        └── vs-seti-icon-theme.backup.json
```

## Estado atual

A extensão ainda é experimental e está em desenvolvimento local. Sua publicação em um marketplace ainda não foi realizada.
