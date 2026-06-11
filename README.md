Sistema de Dicionário com Tabela Hash em C

Este projeto consiste em um sistema de dicionário desenvolvido na linguagem C utilizando a estrutura de dados de Tabela Hash com tratamento de colisões por meio de Listas Encadeadas.

Tecnologias e Conceitos Implementados
Linguagem C: Construção limpa e modular.
Alocação Dinâmica: Uso estratégico de `malloc()` e `free()` para gerenciar nós na memória.
Ponteiros e Structs: Estruturação dos dados da palavra, definição e encadeamentos de referências.
Encadeamento Separado: Resolução eficiente de colisões em tempo de execução.

Funcionalidades do Sistema
1. Inserir palavras e definições**: Adiciona termos ao dicionário. Se a palavra já existir, atualiza sua definição.
2. Buscar palavras: Localização rápida utilizando a indexação direta do cálculo hash.
3. Remover palavras: Remove o nó da memória dinâmica e costura as referências dos ponteiros adjacentes.
4. Exibir tabela: Uma visão gráfica textual mostrando o estado atual das posições (índices) da tabela.
5. Estatísticas Completas:
   Total de elementos inseridos.
   Total de colisões mapeadas.
   Fator de carga da tabela ($\alpha = \frac{\text{elementos}}{\text{tamanho}}$).
   Tamanho da maior lista encadeada encontrada.
