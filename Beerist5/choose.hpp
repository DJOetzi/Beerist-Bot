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
#include <array>

#ifdef _WIN32
#define popen _popen
#define pclose _pclose
#endif

namespace beerist::commands {
	namespace choose{
		void exec(dpp::cluster& bot, const dpp::interaction_create_t& event, dpp::command_interaction cmd_data, std::string topgg_link) {
			bool valid_options = true;
			std::vector<std::string> options{
				"1st",
				"2nd",
				"3rd",
				"4th",
				"5th",
				"6th",
				"7th",
				"8th",
				"9th",
				"10th"
			};

			int lastParam = json::parse(event.raw_event)["d"]["data"]["options"].size();
			for (int i = 0; i < lastParam; i++) {
				if (djutils::string_contains(std::get<std::string>(event.get_parameter(options[i])), "@everyone") || djutils::string_contains(std::get<std::string>(event.get_parameter(options[i])), "@here")) {
					valid_options = false;
				}
			}
			if (valid_options)
				event.reply(dpp::ir_channel_message_with_source, dpp::message().set_content(fmt::format("I chose: **{}**!", std::get<std::string>(event.get_parameter(options[rand() % lastParam])))));
			else
				event.reply(dpp::ir_channel_message_with_source, dpp::message().set_content("Annoying other People and trying to exploit Bots isn't nice :(").set_flags(dpp::m_ephemeral));
		}
	}
}
