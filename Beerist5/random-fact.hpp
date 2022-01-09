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
	namespace randomfact {
		void exec(dpp::cluster& bot, const dpp::interaction_create_t& event, dpp::command_interaction cmd_data, std::string topgg_link) {
			event.reply(dpp::ir_channel_message_with_source, "fetching data...");
			dpp::utility::exec("curl", { "https://uselessfacts.jsph.pl/random.json?language=en" }, [&bot, channelid = event.command.channel_id, eventtokenraw = event.command.token, usrname = event.command.usr.username, usravatar = event.command.usr.get_avatar_url(), botlink = topgg_link](const std::string& output){
				std::string foutput = output;
				foutput.std::string::erase(0, output.find('{') - 1);
				//std::cout << foutput;
				nlohmann::json jsonBinary;
                
				jsonBinary = djutils::str_json(foutput);

				dpp::embed embed = dpp::embed().
					set_color(0xFFFF00).
					set_title("USELESS FACT").
					set_url(jsonBinary["permalink"]).
					set_author(usrname, "", usravatar).
					add_field("did you know...", jsonBinary["text"]).
					set_footer(dpp::embed_footer().set_text(u8"straight up facts").set_icon(bot.me.get_avatar_url())).
					set_timestamp(time(NULL));
				std::string response = "straightup facts";
				bot.message_create(dpp::message(channelid, embed));
				bot.interaction_response_edit(eventtokenraw, response);
			});
		}
	}
}
