ODIR=../obj
BIN=../bin

CC=g++
CFLAGS=-std=c++11 -Wall
DEPS=.

SRCS=main.cc\
math/identity.cc\
math/integral.cc

_OBJ=$(SRCS:.cc=.o)

default: create_directories engineCalc
	@echo DONE

OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cc
	$(CC) -c -o $@ $< $(CFLAGS)

create_directories: 
	@mkdir -p $(ODIR)/math
	@mkdir -p $(BIN)

engineCalc: $(OBJ)
	$(CC) -o $(BIN)/$@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -rf $(BIN) $(ODIR)
