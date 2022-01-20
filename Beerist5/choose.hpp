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
		CMD_HEAD {
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

			nlohmann::json optiondmp = djutils::str_json(event.raw_event)["d"]["data"]["options"];
			std::string result = std::get<std::string>(event.get_parameter(optiondmp[rand() % optiondmp.size()]["name"]));
			if (djutils::string_contains(result, "@everyone") || djutils::string_contains(result, "@here"))
				event.reply(dpp::ir_channel_message_with_source, dpp::message().set_content(fmt::format("I chose: **{}**!", result)));
			else
				event.reply(dpp::ir_channel_message_with_source, dpp::message().set_content("I chose: **You are trying to exploit bots!**").set_flags(dpp::m_ephemeral));
		}
	}
}
