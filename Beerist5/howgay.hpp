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
#include <math.h>

#ifdef _WIN32
#define popen _popen
#define pclose _pclose
#endif

namespace beerist::commands {
	namespace howgay {
		void exec(dpp::cluster& bot, const dpp::interaction_create_t& event, dpp::command_interaction cmd_data, std::string topgg_link) {
			int howGayPercent = djutils::map_value((rand()%100)+1, 0, 99, 0, 100);

			dpp::embed embed = dpp::embed().
				set_color(0xFFFF00).
				set_author(event.command.usr.username, "", event.command.usr.get_avatar_url()).
				add_field(u8"🏳️‍🌈how gae?🏳️‍🌈", fmt::format(u8"you are 🏳️‍🌈{}% gay🏳️‍🌈", howGayPercent)).
				set_footer(dpp::embed_footer().set_text(u8"y r u gae?").set_icon(bot.me.get_avatar_url())).
				set_timestamp(time(NULL));
			event.reply(dpp::ir_channel_message_with_source, dpp::message(event.command.channel_id, embed));
		}
	}
}