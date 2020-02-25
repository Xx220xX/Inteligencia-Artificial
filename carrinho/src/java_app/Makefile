
all : Simulador
LIB = C:\Users\PC\Desktop\Henrique\Inteligencia-Artificial\carrinho\src\lib
SRC = C:\Users\PC\Desktop\Henrique\Inteligencia-Artificial\carrinho\src\java_app
JNI =C:\Users\PC\Desktop\Henrique\Inteligencia-Artificial\carrinho\include
MAIN = Teste

Simulador :$(MAIN).class
	@echo "[MAKE]-> runing Teste.class"
	java $(MAIN)
	@echo "[MAKE]-> finished"
$(MAIN).class: $(MAIN).java Carro.class RNG.class Constantes.class Carro.dll RNG.dll
	@echo "[MAKE]-> compilando Teste.class"
	javac $(MAIN).java

Carro.class:Carro.java
	@echo "[MAKE]-> compilando Carro.class"
	javac Carro.java -h $(LIB)

RNG.class:RNG.java
	@echo "[MAKE]-> compilando RNG.class"
	javac RNG.java  -h $(LIB)

Constantes.class:Constantes.java
	@echo "[MAKE]-> compilando Constantes.class"
	javac Constantes.java


Carro.dll: Carro.o
	@echo "[MAKE]-> compilando Carro.dll"
	gcc -shared -o Carro.dll Carro.o -Wl,--add-stdcall-alias
Carro.o: $(LIB)\Carro.c
	@echo "[MAKE]-> compilando Carro.c"
	gcc -c -I$(JNI) -I$(JNI)\win32 $(LIB)\Carro.c -o Carro.o
RNG.dll: RNG.o
	@echo "[MAKE]-> compilando RNG.dll"
	gcc -shared -o RNG.dll RNG.o -Wl,--add-stdcall-alias
RNG.o: $(LIB)\RNG.c
	@echo "[MAKE]-> compilando RNG.c"
	gcc -c -I$(JNI) -I$(JNI)\win32 $(LIB)\RNG.c -o RNG.o


