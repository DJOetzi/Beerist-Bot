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
		CMD_HEAD {
            std::string text = std::get<std::string>(event.get_parameter("to-mock"));
            int idx = 0;
            for (char& chr : text) {
               chr = (idx % 2 != 0) ? toupper(chr) : tolower(chr);
               idx++;
            }

            event.reply(dpp::ir_channel_message_with_source, text);
		}
   }
}
