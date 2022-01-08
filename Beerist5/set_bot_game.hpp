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
	namespace set_bot_game {
		void exec(dpp::cluster& bot, const dpp::interaction_create_t& event, dpp::command_interaction cmd_data, std::string topgg_link) {
			event.reply(dpp::ir_channel_message_with_source, "```DEPRECATED FEATURE```");
		}
	}
}
