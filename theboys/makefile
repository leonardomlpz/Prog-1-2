# makefile The Boys
# Carlos Maziero - DINF/UFPR, 2024/2

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g -std=c99
LDLIBS  = -lm
MAIN    = theboys
ENTREGA = $(MAIN)

# lista de arquivos de cabeçalho (a completar)
HDR = fila.h fprio.h conjunto.h mundo.h eventos.h estruturas.h

# lista de arquivos-objeto (a completar)
# não inclua conjunto.o, senão ele será removido com "make clean"
OBJ = fila.o fprio.o theboys.o mundo.o eventos.o

# construir o executável
$(MAIN): $(MAIN).o $(OBJ) conjunto.o

# construir os arquivos-objeto (a completar)
$(MAIN).o: $(MAIN).c $(HDR)

# construir os TADs
fila.o: fila.c fila.h
fprio.o: fprio.c fprio.h
eventos.o: eventos.c eventos.h
mundo.o: mundo.c mundo.h

# executar
run: $(MAIN)
	./$(MAIN)

# testar no Valgrind
valgrind: $(MAIN)
	valgrind --leak-check=full --track-origins=yes ./$(MAIN)

# gerar arquivo TGZ para entregar
tgz: clean
	-mkdir -p /tmp/$(USER)/$(ENTREGA)
	chmod 0700 /tmp/$(USER)/$(ENTREGA)
	cp *.c *.h conjunto.o makefile /tmp/$(USER)/$(ENTREGA)
	tar czvf $(ENTREGA).tgz -C /tmp/$(USER) $(ENTREGA)
	rm -rf /tmp/$(USER)
	@echo "Arquivo $(ENTREGA).tgz criado para entrega"

# limpar arquivos temporários
clean:
	rm -f *~ $(OBJ) $(MAIN) /tmp/$(USER)/$(ENTREGA) $(ENTREGA).tgz

