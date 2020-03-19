#ifndef MACRO_NEURAL
#define MACRO_NEURAL


#define COPIA_VETOR(x,y,len)\
  do{\
  	int i___iisksbysoagsoka;\
  	for(i___iisksbysoagsoka=0;i___iisksbysoagsoka<len;i___iisksbysoagsoka++)\
  	 x[i___iisksbysoagsoka]=y[i___iisksbysoagsoka];\
  }while(0)


#define PRINT_VETOR(x,len)\
  do{\
  	int i;\
  	printf("[");\
  	if(len>0)\
  	printf("%g",(double)x[0]);\
  	for(i=1;i<len;i++) printf(", %g",(double)x[i]);\
  	printf("]\n");\
  }while(0)

 #define SWAP(TYPE,a,b)\
  do{TYPE c = a;a=b;b=c;}while(0);
  
  #define FORI(var,beg,end,acao)\
  do{ int var;for(var=beg;var<end;var++){\
  	acao;\
  	}}while(0)
  	
 #endif
