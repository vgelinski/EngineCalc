# EngineCalc
Application for calculating different parameters of internal combustion engine.

## Dependencies

Here is a list of dependencies you need to install to build/run this project

  * `build-essential` - tool that is used to compile the project
  * `cmake` (>= 3.26) - build system
  * `lcov` - tool for generating code coverage
  * `doxygen` - tool for generating documentation
  * `graphviz` - tool, required by `doxygen` to draw class hierarchy

## How to use

### Build

  * `cmake -B build` to configure the build tree
  * `cmake --build build` to compile `engineCalc` and the test runner
  * `./build/engineCalc` to run the main program
  * `./build/testRunner` (or `ctest --test-dir build`) to run the unit tests

### Coverage

Run `coverage.sh` to generate the code coverage. It will also execute all tests. Than open `coverage/index.html` in any modern browser.

### Documentation

Run `doxygen Doxyfile` to generate HTML and LaTeX documentation. Then open `docs/html/index.html` in any modern browser. LaTeX documentation needs to be compiled, but may give compile errors for now.


