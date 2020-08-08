#include "file_io.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#define FIO FileIO

using namespace std;
using namespace std::filesystem;
using namespace engc::util;

void FIO::writeToFile(const std::string& filename, const std::string& content) {
    auto fstream = ofstream(current_path() /= filename);
    fstream << content << endl;
    fstream.close();
}
