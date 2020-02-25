
all : Simulador
LIB = ..\lib
OUT = out
JNI = ..\..\include
MAIN = Main
Simulador :$(OUT)\$(MAIN).class
	@echo "[MAKE]-> runing Teste.class"
	java -Djava.library.path="$(OUT)" -cp $(OUT) $(MAIN)
	@echo "[MAKE]-> finished"
$(OUT)\$(MAIN).class: $(MAIN).java $(OUT)\Carro.class $(OUT)\RNG.class $(OUT)\Constantes.class $(OUT)\Duplas.class $(OUT)\Carro.dll $(OUT)\RNG.dll
	@echo "[MAKE]-> compilando Teste.class"
	javac $(MAIN).java
	move $(MAIN).class $(OUT)\$(MAIN).class


$(OUT)\Carro.class:Carro.java
	@echo "[MAKE]-> compilando Carro.class"
	javac Carro.java -h $(LIB)
	move Carro.class $(OUT)\Carro.class
	move "Carro$$P.class" "$(OUT)\Carro$$P.class"

$(OUT)\RNG.class:RNG.java
	@echo "[MAKE]-> compilando RNG.class"
	javac RNG.java  -h $(LIB)
	move RNG.class $(OUT)\RNG.class

$(OUT)\Constantes.class:Constantes.java
	@echo "[MAKE]-> compilando Constantes.class"
	javac Constantes.java
	move Constantes.class $(OUT)\Constantes.class

$(OUT)\Duplas.class:Duplas.java
	@echo "[MAKE]-> compilando Duplas.class"
	javac Duplas.java
	move Duplas.class $(OUT)\Duplas.class


$(OUT)\Carro.dll: $(OUT)\Carro.o
	@echo "[MAKE]-> compilando Carro.dll"
	gcc -shared -o $(OUT)\Carro.dll $(OUT)\Carro.o -Wl,--add-stdcall-alias

$(OUT)\Carro.o: $(LIB)\Carro.c
	@echo "[MAKE]-> compilando Carro.c"
	gcc -c -I$(JNI) -I$(JNI)\win32 $(LIB)\Carro.c -o $(OUT)\Carro.o

$(OUT)\RNG.dll: $(OUT)\RNG.o
	@echo "[MAKE]-> compilando RNG.dll"
	gcc -shared -o $(OUT)\RNG.dll $(OUT)\RNG.o -Wl,--add-stdcall-alias

$(OUT)\RNG.o: $(LIB)\RNG.c
	@echo "[MAKE]-> compilando RNG.c"
	gcc -c -I$(JNI) -I$(JNI)\win32 $(LIB)\RNG.c -o $(OUT)\RNG.o


