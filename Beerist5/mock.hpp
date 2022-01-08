#include <dpp/dpp.h>
#include <dpp/nlohmann/json.hpp>
#include <dpp/fmt/format.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
#include <time.h>
#include <regex>
#include <locale>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <array>
#define popen _popen
#define pclose _pclose
#endif

namespace beerist::commands {
	namespace mock {
		void exec(dpp::cluster& bot, const dpp::interaction_create_t& event, dpp::command_interaction cmd_data, std::string topgg_link) {
            std::string basetext = std::get<std::string>(event.get_parameter("to-mock"));

            char* text = (char*)calloc(basetext.length(), sizeof(char));
            if (text) {
                strcpy(text, basetext.c_str());

                for (int idx = 0; idx < basetext.length(); idx++) {
                    text[idx] = (idx % 2 != 0) ? toupper(text[idx]) : tolower(text[idx]);
                }

                event.reply(dpp::ir_channel_message_with_source, text);
                free(text);
                //std::cout << "mem cleared";
            }
            else
                event.reply(dpp::ir_channel_message_with_source, fmt::format("Error happened while editing `{}`\n**REPORT THIS TO THE DEV IMMEDIATELY**", basetext));
            /*if (text)
                free(text);*/
		}
   }
}
