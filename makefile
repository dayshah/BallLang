
CC=g++ -std=c++17
CFLAGS=-I.

ODIR="obj"

DEPS = lexer.h abstract_syntax_tree.h

_OBJ = lexer.o abstract_syntax_tree.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ball: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
	rm -f ball
