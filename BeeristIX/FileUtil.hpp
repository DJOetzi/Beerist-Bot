#pragma once
#include <fstream>
#include <nlohmann/json.hpp>

namespace Utility::File
{
    inline auto read_file(const std::string& filename) -> nlohmann::json {
        std::ifstream configfile(filename);
        nlohmann::json conf_doc;
        configfile >> conf_doc;
        configfile.close();

        return conf_doc;
    }
}