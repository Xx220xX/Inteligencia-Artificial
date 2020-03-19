# Desenvolvimento da parte do jogo

### Etapas
 1. [x] Ler entrada de dados dos carrinhos
 2. [x] Calcular saida da rede neural usando as entradas
 3. [x] Aplicar saída da rede neural como força no carrinho
 4. [ ] [Calcular efeitos que a força aplicada causou](efeitos)
 5. [ ] [Movimentar e modificar posição a partir dos calculos](mov)
 
 
 <a name="efeitos"></a>
##### Calcular efeitos que a força aplicada causou
A primeira coisa a fazer é identificar se o carrinho se colidiu com o outro carrinho.
Para isso é desenvolvido a função 
```C
colidiuQuadrado()
```
A qual verifica se os carrinhos se colidiram. A verificação envolve alguns passos:
1. encontrar cantos do carrinho (getConers)
2. transladar para que o carrinho fique com a quina esquerda inferior em (0,0)
3


 <a name="mov"></a>
##### Movimentar e modificar posição a partir dos calculos

 