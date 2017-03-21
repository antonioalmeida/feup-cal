# feup-cal

## 1ª Fase
- n camiões
- dividir o grafo em n sub-grafos, cada camião cobre um sub-grafo
- camiões têm limite fixo de carga
- calcular todas as rotas possíveis para todos os pontos da camada mais distante da BFS, escolhendo a rota que, simultaneamente:
    - maximize o número de nodes (pontos de entrega) que passa
    - não ultrapasse a carga do camião 
