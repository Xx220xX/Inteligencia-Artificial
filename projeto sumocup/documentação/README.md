#  Documentação 

O projeto é composto por 3 partes. A primeira parte é feita em c, por ser uma parte com grande processamento, que é a simulação do jogo e calculo da rede neural. A segunda parte é feita em java que cria N jogos com N redes neurais e chama as funções em c. E por fim a terceira parte que esta aberto a qualquer linguagem, atualmente esta em javascrip, é responsavel por mostrar visualmente na tela o jogo entre os carrinhos.




### Rede neural
 Foi criado uma biblioteca otimizada para a rede neural tanto em tamanho de codigo e memoria, quanto em processamento. Na pasta "rng_optimize" se encontra 9 arquivos ".h" que contém todas a funções relacionadas a rede neural. 

 Desta forma não é necessario carregar na memória funçoes que nao serão utilizadas.(O motivo disso é por usar a JNI como interface entre java e c).

### Simulação e fisica do jogo
#### Padronização de codigo
 Todas as funções e bibliotecas usadas para a fisica estarão na pasta "src/c/fisica_lib" com mascros em "fisica.h" de tal forma que facilite a edição das funções relacionadas a fisica

# Visualiação do jogo

