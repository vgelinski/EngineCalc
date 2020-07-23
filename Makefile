ODIR=obj
TEST_ODIR=tobj
GTESTDIR=test/googletest/googletest
BIN=bin
LIBDIR=lib

CC=g++
CFLAGS=-std=c++17 -Wall -pthread -Ofast
DEPS=.

TEST_CFLAGS=-std=c++17 -Wall -pthread -fprofile-arcs -ftest-coverage -pg -g

ifdef FULL_TEST
      TEST_CFLAGS += -DFULL_TEST
endif

LDFLAGS=-lstdc++fs
TEST_LDFLAGS=-lgcov -pg -no-pie -lstdc++fs

PROJECT_SRCS=src/math/constant.cc\
src/math/custom_function.cc\
src/math/differential.cc\
src/math/extremum_calculator.cc\
src/math/function.cc\
src/math/identity.cc\
src/math/implicit_function.cc\
src/math/integral.cc\
src/model/engine/common_engines.cc\
src/model/engine/engine.cc\
src/model/transmission/tyre.cc\
src/physics/unit_definitions.cc\
src/physics/common_units.cc\
src/physics/units.cc\
src/physics/value.cc\
src/tools/engine/engine_power_calculator.cc\
src/tools/suspension/suspension_calculator.cc\
src/util/exceptions/illegal_argument_exception.cc\
src/util/files/file_io.cc\
src/util/plot/data_calculator_2d.cc\
src/util/plot/plot_builder_2d.cc\
src/util/plot/simple_2d_plotter.cc

SRCS=$(PROJECT_SRCS)\
src/main.cc

TEST_SRCS=$(PROJECT_SRCS)\
test/test_runner.cc\
test/math/constant_test.cc\
test/math/custom_function_test.cc\
test/math/differential_test.cc\
test/math/extremum_calculator_test.cc\
test/math/function_test.cc\
test/math/identity_test.cc\
test/math/implicit_function_test.cc\
test/math/integral_test.cc\
test/model/engine/common_engines_test.cc\
test/model/transmission/tyre_test.cc\
test/physics/units_test.cc\
test/physics/value_test.cc\
test/util/plot/data_calculator_2d_test.cc

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

test: create_dirs gtest testRunner
	@echo DONE

testRunner: $(TEST_OBJ)
	$(CC) $(TEST_CFLAGS) -isystem ${GTESTDIR}/include \
            -o $(BIN)/$@ $^ $(LIBDIR)/libgtest.a $(LIBS) $(TEST_LDFLAGS)


clean:
	rm -rf $(BIN) $(ODIR) $(TEST_ODIR) $(LIBDIR) *.gcno *.gcda
