LCOV_OUT=app.info

make test
./bin/test
gcov -b -c test_runner.cc
lcov --directory . --capture --output-file $LCOV_OUT
genhtml $LCOV_OUT --output-directory coverage
