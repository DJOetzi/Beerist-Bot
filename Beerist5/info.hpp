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
	namespace info {
		void exec(dpp::cluster& bot, const dpp::interaction_create_t& event, dpp::command_interaction cmd_data, std::string topgg_link) {
			event.reply(dpp::ir_channel_message_with_source, "fetching data...");
			dpp::utility::exec("curl", { "https://raw.githubusercontent.com/Progame03/Beerist-Bot/dev/credits.md" }, [&bot, eventtokenraw = event.command.token, botlink = topgg_link, usrname= event.command.usr.username, avatarurl = event.command.usr.get_avatar_url(), channelid = event.command.channel_id](const std::string& output){
				std::string foutput = output;
				foutput.std::string::erase(0, output.find('#') - 1);
				foutput = std::regex_replace(foutput, std::regex("#"), "> ");
				dpp::embed embed = dpp::embed().
					set_color(0xFFFF00).
					set_title("THANK YOU").
					set_url(botlink).
					set_author(usrname, "", avatarurl).
					add_field("CREDITS:", fmt::format("**{}**", foutput)).
					set_footer(dpp::embed_footer().set_text(u8"huge thanks to all people making the bot what it is 💖").set_icon(bot.me.get_avatar_url())).
					set_timestamp(time(NULL));
				bot.message_create(dpp::message(channelid, embed));
				bot.interaction_response_edit(eventtokenraw, dpp::message().set_content(u8"᲼"));
			});
		}
	}
}
