#ifndef FILE_IO_H
#define FILE_IO_H

#include <string>

namespace engc::util {
class FileIO {
public:
    static void writeToFile(const std::string& filename, const std::string& content);
};
};
#endif //FILE_IO_H
