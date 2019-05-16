ODIR=obj
GTESTDIR=test/googletest/googletest
BIN=bin
LIBDIR=lib

CC=g++
CFLAGS=-std=c++11 -Wall
DEPS=.

PROJECT_SRCS=math/identity.cc\
math/integral.cc

SRCS=$(PROJECT_SRCS)\
main.cc

TEST_SRCS=$(PROJECT_SRCS)\
test/test_runner.cc\
test/math/*_test.cc

_OBJ=$(SRCS:.cc=.o)

default: create_dirs engineCalc
	@echo DONE

OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cc
	$(CC) -c -o $@ $< $(CFLAGS)

create_dirs: 
	@mkdir -p $(ODIR)/math
	@mkdir -p $(BIN)
	@mkdir -p $(LIBDIR)

engineCalc: $(OBJ)
	$(CC) -o $(BIN)/$@ $^ $(CFLAGS) $(LIBS)

gtest: $(GTESTDIR)/src/gtest-all.cc create_dirs
	g++ -isystem ${GTESTDIR}/include -I${GTESTDIR} \
            -pthread -c ${GTESTDIR}/src/gtest-all.cc -o $(ODIR)/gtest-all.o
	ar -rv $(LIBDIR)/libgtest.a $(ODIR)/gtest-all.o


test: gtest
	g++ -isystem ${GTESTDIR}/include -pthread $(TEST_SRCS) $(LIBDIR)/libgtest.a -o $(BIN)/test

clean:
	rm -rf $(BIN) $(ODIR) $(LIBDIR)
