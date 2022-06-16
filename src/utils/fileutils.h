//
// Created by maxga on 16.06.2022.
//

#ifndef BEERIST7_FILEUTILS_H
#define BEERIST7_FILEUTILS_H
#include <dpp/nlohmann/json.hpp>

class fileutils {
public:
    static auto read_file(const std::string& filename) -> nlohmann::json;
};


#endif //BEERIST7_FILEUTILS_H
