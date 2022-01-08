#include <ctype.h>
#include <iostream>
#include <string.h>

#ifdef _WIN32
#define popen _popen
#define pclose _pclose
#endif

namespace djutils {
    typedef struct {
        std::string author, title, url, link, sub;
        bool nsfw;
        unsigned int upvotes;
    }redditpost;

    typedef void (*command) (dpp::cluster& bot, const dpp::interaction_create_t& event, dpp::command_interaction cmd_data, std::string topgg_link);

    std::string str_tolower(std::string str) {
        for (char& c : str)
        {
            c = tolower(c);
        }

        return str;
    }
    std::string str_toupper(std::string str) {
        for (char& c : str)
        {
            c = toupper(c);
        }
    }
    bool string_contains(std::string s1, std::string s2) {
        return s1.find(s2) != std::string::npos;
    }

    std::string exec_cmd_blocking(std::string command) {
        char buffer[128];
        std::string result = "";

        FILE* pipe = popen(command.c_str(), "r");
        if (!pipe) {
            return "popen failed!";
        }
        // read till end of process:
        while (!feof(pipe)) {
            // use buffer to read and add to result
            if (fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }
        pclose(pipe);
        return result;
    }
}