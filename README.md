# EngineCalc
Application for calculating different parameters of internal combustion engine.

## Dependencies

Here is a list of dependencies you need to install to build/run this project

  * `build-essential` - tool that is used to compile the project
  * `cmake` (>= 3.26) - build system
  * `lcov` - tool for generating code coverage
  * `doxygen` - tool for generating documentation
  * `graphviz` - tool, required by `doxygen` to draw class hierarchy
  * `texlive-latex-base` - provides `pdflatex`, required to compile the plot output (`plot/**/plot.tex` → `plot.pdf`)
  * `texlive-pictures` - provides `pgfplots` and `tikz`, required by the plot `.tex` files

## How to use

### Build

  * `cmake -B build` to configure the build tree
  * `cmake --build build` to compile `engineCalc` and the test runner
  * `./build/engineCalc` to run the main program
  * `./build/testRunner` (or `ctest --test-dir build`) to run the unit tests

### Plots

`engineCalc` writes plot data (CSV) into `plot/`. To render a PDF, run `pdflatex` against the matching `.tex` from inside the directory that holds the CSV:

  * Option 1 (engine power by rod length) — `cd plot && pdflatex sandbox.tex` → `sandbox.pdf`
  * Option 4 (momentum and power by rpm) — `cd plot/engine_momentum_power_by_rpm && pdflatex plot.tex` → `plot.pdf`
  * Option 5 (power by speed) — `cd plot/engine_power_by_speed && pdflatex plot.tex` → `plot.pdf`

### Coverage

Run `coverage.sh` to generate the code coverage. It will also execute all tests. Than open `coverage/index.html` in any modern browser.

### Documentation

Run `doxygen Doxyfile` to generate HTML and LaTeX documentation. Then open `docs/html/index.html` in any modern browser. LaTeX documentation needs to be compiled, but may give compile errors for now.


