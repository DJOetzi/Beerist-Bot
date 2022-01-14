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
	namespace joke {
		void exec(dpp::cluster& bot, const dpp::interaction_create_t& event, dpp::command_interaction cmd_data, std::string topgg_link) {
			event.reply(dpp::ir_channel_message_with_source, "fetching data...");
			dpp::utility::exec("curl", { "https://v2.jokeapi.dev/joke/Programming,Miscellaneous,Pun,Spooky,Christmas?blacklistFlags=nsfw,religious,racist,sexist&safe-mode" }, [&bot, channelid = event.command.channel_id, eventtokenraw = event.command.token, usrname = event.command.usr.username, usravatar = event.command.usr.get_avatar_url(), botlink = topgg_link](const std::string& output){
				std::string foutput = output;
				foutput.std::string::erase(0, output.find('{') - 1);
				nlohmann::json jsonBinary = djutils::str_json(foutput);

				std::string joke;
				if (jsonBinary["type"] != "single")
					joke = fmt::format("{}\n||{}||", jsonBinary["setup"], jsonBinary["delivery"]);
				else
					joke = jsonBinary["joke"];

				dpp::embed embed = dpp::embed().
					set_color(0xFFFF00).
					set_title("little joke for ya").
					set_url(botlink).
					set_author(usrname, "", usravatar).
					add_field(fmt::format("Category: {}", jsonBinary["category"]), joke).
					set_footer(dpp::embed_footer().set_text(u8"funni innit").set_icon("https://cdn.discordapp.com/emojis/874721784816087100.webp?size=96&quality=lossless")).
					set_timestamp(time(NULL));
				bot.interaction_response_edit(eventtokenraw, dpp::message(channelid, embed));
			});
		}
	}
}
