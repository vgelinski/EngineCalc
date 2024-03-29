COV_DIR=coverage
LCOV_OUT=$COV_DIR/app.info

make -j64 test
./bin/testRunner
gcov -b -c tobj/test/test_runner.cc
mkdir -p $COV_DIR
find tobj/|grep gcno|while read FILE; do cp $FILE coverage/; done
find tobj/|grep gcda|while read FILE; do cp $FILE coverage/; done
pwd
ls
lcov --directory $COV_DIR --capture --output-file $LCOV_OUT -b `pwd`
genhtml $LCOV_OUT --output-directory $COV_DIR
