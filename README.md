# EngineCalc
Application for calculating different parameters of internal combustion engine.

## Dependencies

Here is a list of dependencies you need to install to build/run this project

  * `build-essential` - tool that is used to compile the project
  * `lcov` - tool for generating code coverage
  * `doxygen` - tool for generating documentation
  * `graphviz` - tool, required by `doxygen` to draw class hierarchy

## How to use

### Build

  * run `make test` to compile the unit tests, thant run `./bin/test` to run them
  * run `make` to build the main program

### Coverage

Run `coverage.sh` to generate the code coverage. It will also execute all tests. Than open `coverage/index.html` in any modern browser.

### Documentation

Run `doxygen Doxyfile` to generate HTML and LaTeX documentation. Then open `docs/html/index.html` in any modern browser. LaTeX documentation needs to be compiled, but may give compile errors for now.


