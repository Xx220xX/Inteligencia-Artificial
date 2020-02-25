# Gabriela aprendendo a jogar sumocup

  - [ESTRATEGIA](estrategia)
  
  
  
<a name="estrategia"/>

#### Estrategia
  O projeto consiste em três partes
  1. Controle de jogo
  2. Cálculo da rede 
  3. mostrar na tela
  
  O controle do jogo é feito em java pela facilidade de gerenciar threads,
  assim possuira **N** duplas de carrinhos. Com uma estrategia de Dados enfileirados,
  vai utilizar threads para fazer os calculos das redes neurais de cada um ganhando velocidade no processo.
  
  O Cálculo da rede é feito em c puro (ANCI C), possibilitando grande velocidade de processamento,
  os dados sao passados por meio da JNI.
  
  Para mostrar na tela é usado um programado separado com stream de arquivos lendo e atualizando as posicoes dos 
  Carrinhos. Este é feito em processing python;
  
