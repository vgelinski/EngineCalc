ODIR=obj
TEST_ODIR=tobj
GTESTDIR=lib/googletest/googletest
BIN=bin
LIBDIR=$(BIN)/lib

CC=g++
CFLAGS=-std=c++20 -Wall -pthread -Ofast
DEPS=.

TEST_CFLAGS=-std=c++20 -Wall -pthread -fprofile-arcs -ftest-coverage -pg -g

ifdef FULL_TEST
      TEST_CFLAGS += -DFULL_TEST
endif

LDFLAGS=-lstdc++fs
TEST_LDFLAGS=-lgcov -pg -no-pie -lstdc++fs

PROJECT_SRCS=$(shell find src -name "*.cc"|grep -v main.cc)

SRCS=$(PROJECT_SRCS)\
src/main.cc

TEST_SRCS=$(PROJECT_SRCS)\
$(shell find test -name "*_test.cc")\
test/test_runner.cc

_OBJ=$(SRCS:.cc=.o)
_TEST_OBJ=$(TEST_SRCS:.cc=.o)

default: create_dirs engineCalc
	@echo DONE

OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))
TEST_OBJ=$(patsubst %,$(TEST_ODIR)/%,$(_TEST_OBJ))

$(ODIR)/%.o: %.cc
	$(CC) -c -o $@ $< $(CFLAGS)

$(TEST_ODIR)/%.o: %.cc
	$(CC) -isystem ${GTESTDIR}/include -c -o $@ $< $(TEST_CFLAGS) 

create_dirs: 
	@find src -type d -links 2 -exec mkdir -p $(ODIR)/{} \;
	@cp -r $(ODIR) $(TEST_ODIR)
	@cp -r $(TEST_ODIR)/src $(TEST_ODIR)/test
	@mkdir -p $(BIN)
	@mkdir -p $(LIBDIR)

engineCalc: $(OBJ)
	$(CC) -o $(BIN)/$@ $^ $(CFLAGS) $(LIBS) $(LDFLAGS)


gtest: $(GTESTDIR)/src/gtest-all.cc create_dirs
	$(CC) -isystem ${GTESTDIR}/include -I${GTESTDIR} \
            -c $(TEST_CFLAGS) ${GTESTDIR}/src/gtest-all.cc -o $(ODIR)/gtest-all.o
	ar -rv $(LIBDIR)/libgtest.a $(ODIR)/gtest-all.o

test: create_dirs
	$(MAKE) gtest && $(MAKE) testRunner
	@echo DONE

testRunner: $(TEST_OBJ)
	$(CC) $(TEST_CFLAGS) -isystem ${GTESTDIR}/include \
            -o $(BIN)/$@ $^ $(LIBDIR)/libgtest.a $(LIBS) $(TEST_LDFLAGS)


clean:
	rm -rf $(BIN) $(ODIR) $(TEST_ODIR) $(LIBDIR) coverage *.gcov
