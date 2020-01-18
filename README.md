# Inteligencia-Artificial
Uma biblioteca em  C para inteligência artificial 
# RNG - REDE NEURAL + ALGORITIMO GENÉTICO

 Esta biblioteca é genérica para que possa ser implementada ao seu gosto.

 * Vantagens de usar esta biblioteca

  > * Por usar pouca abstração ganha-se velocidade nos treinamentos.
  > 
  > * Facil implementação

##### Observação
  Veja o arquivo **RNACONFIG.h**, nele contem grande parte dos parametros ajustáveis, como função de ativação, o valor min e max do numero sorteado, etc.

------

### TABLE OF CONTENTES

* [Documentação](doc)
* [Exemplos](exemplo)

------
<a name="doc"/>

```c
typedef struct{
	double *dna;//pesos
	int dna_len;
	int *arquitetura;
	int arquitetura_len;
	
	void *p;// usado para atribuir uma strutura para modelagem
	double pontuacao;
}RNG;
```
Esta strutura empacota toda informação da rede neural (RNA).

A **arquitetura** é um vetor que representa quantos neuronios cada camada possui, deve possuir tamanho maior que 2, a biblioteca não checa por razões de otimização. Exemplo de rede com 3 neuronios de entrada 2 de saida com 2 camadas ocultas com 7 e 6 neuronios respectivamente {3,7,6,2} .

**dna** guarda todos os pesos da rede incluindo o bias. O seu tamanho é calculado automaticamente ao criar uma rede neural, veja [**newRNG**](newrng).

o ponteiro ***p** é para atribuir uma strutura contendo mais informações sobre o individuo. Use na modelagem do seu problema. Veja [**freeRNG**](frerng)

-----
<a name="newrng"/>
#### newRNG

```c
RNG newRNG(const int *arquitetura,int len);
```
  Retorna uma strutura RNG  de acordo com a arquitetura passada, o vetor arquitetura sera apenas copiado.
  A função calcula a quantidade de pesos que a rede terá.

-----
#### loadRNG
```c
RNG loadRNG(const char * fileToload)
```
  retorna uma RNG contida em um arquivo. 

-----
#### salveRNG

```c
void salveRNG(RNG r,const char * fileToSave);
```
  Salva a rede em um arquivo.

  **ATENÇÃO** tenha certeza que o diretório exista.

----
#### freeRNG
<a name="frerng"/>

```c
 void freeRNG(RNG r);
```
  Toda Rede criada por **newRNG** e **loadRNG** deve ser liberada ao final do programa.

----
#### randomMutation
```c
void randomMutation(RNG *redes,int len,double *rangeMutation);
```
  Esta função é a responsavel pela rede aprender, chame-a após pontuas a rede. A função reseta a pontuacao a 0 quando chamada.


-----
#### eval

```c
void eval(RNG r,double *input,double *output);
```

Essa função aplica a entrada na rede neural e ao final o vetor saida conterá o resultado fornecido pela rede. A entrada deve ter o mesmo tamanho que o primeiro elemento do vetor arquitetura e a saída o mesmo tamanho do ultimo elemento da arquitetura.

Use para avaliar o desempenho da rede.

..
