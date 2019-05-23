COV_DIR=coverage
LCOV_OUT=$COV_DIR/app.info

make test
./bin/test
gcov -b -c test_runner.cc
mkdir -p $COV_DIR
mv *.gcno $COV_DIR/
mv *.gcda $COV_DIR/
lcov --directory $COV_DIR --capture --output-file $LCOV_OUT
genhtml $LCOV_OUT --output-directory $COV_DIR
