#include <ctype.h>
#include <iostream>
#include <string.h>
#include <dpp/nlohmann/json.hpp>

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
    typedef void (*button_interactions) (dpp::cluster& bot, const dpp::button_click_t& event, std::string topgg_link);

    nlohmann::json str_json(std::string str) {
        nlohmann::json jsonBinary;
        try
        {
            jsonBinary = nlohmann::json::parse(str);
        }
        catch (nlohmann::json::parse_error& e)
        {
            std::cout << "message: " << e.what() << '\n'
                << "exception id: " << e.id << '\n'
                << "byte position of error: " << e.byte << std::endl;
        }
        return jsonBinary;
    }
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
    std::string format_curl_output(std::string output) {
        std::string foutput = output;
        foutput.std::string::erase(0, output.find('{') - 1);
        return foutput;
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

    int map_value(int value, int fromLow, int fromHigh, int toLow, int toHigh)
    {
        return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
    }
}
