ODIR=obj
GTESTDIR=test/googletest/googletest
BIN=bin
LIBDIR=lib

CC=g++
CFLAGS=-std=c++17 -Wall
DEPS=.

TEST_LDFLAGS=-lgcov -pg

PROJECT_SRCS=src/math/constant.cc\
src/math/function.cc\
src/math/identity.cc\
#src/math/integral.cc

SRCS=$(PROJECT_SRCS)\
src/main.cc

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
	@mkdir -p $(ODIR)/src/math
	@mkdir -p $(BIN)
	@mkdir -p $(LIBDIR)

engineCalc: $(OBJ)
	$(CC) -o $(BIN)/$@ $^ $(CFLAGS) $(LIBS)

gtest: $(GTESTDIR)/src/gtest-all.cc create_dirs
	$(CC) -isystem ${GTESTDIR}/include -I${GTESTDIR} \
            -pthread -c $(CFLAGS) ${GTESTDIR}/src/gtest-all.cc -o $(ODIR)/gtest-all.o
	ar -rv $(LIBDIR)/libgtest.a $(ODIR)/gtest-all.o


test: gtest
	$(CC) -fprofile-arcs -ftest-coverage -pg -isystem ${GTESTDIR}/include -pthread $(CFLAGS) $(TEST_SRCS) $(LIBDIR)/libgtest.a -o $(BIN)/test $(TEST_LDFLAGS)

clean:
	rm -rf $(BIN) $(ODIR) $(LIBDIR) *.gcno *.gcda
