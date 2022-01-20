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
	namespace _8ball {
		CMD_HEAD {
            std::vector<std::string> answers{
                        "maybe:tm:",
                        "yea",
                        "no bro",
                        "ask me again bruv",
                        "dunno",
            };

            event.reply(dpp::ir_channel_message_with_source, dpp::message().set_content(fmt::format("> {}\n{}", std::get<std::string>(event.get_parameter("question")), answers[rand() % answers.size()])).set_flags(dpp::m_ephemeral));
        }
	}
}
