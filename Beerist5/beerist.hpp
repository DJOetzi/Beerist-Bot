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

namespace beerist::commands{
	namespace beerist_cmd {
		void exec(dpp::cluster& bot, const dpp::interaction_create_t& event, dpp::command_interaction cmd_data, std::string topgg_link) {
            dpp::embed embed = dpp::embed().
                set_color(0xFFFF00).
                set_title("the Beerist").
                set_url(topgg_link).
                set_author(event.command.usr.username, "", event.command.usr.get_avatar_url()).
                set_image("https://cdn.discordapp.com/emojis/697110203249983628.png?v=1").
                set_footer(dpp::embed_footer().set_text("an epic image of the Beerist because you asked so kindly").set_icon(event.command.member.get_avatar_url())).
                set_timestamp(time(NULL));

            bot.message_create(dpp::message(event.command.channel_id, embed).set_reference(event.command.id));
            event.reply(dpp::ir_channel_message_with_source, "enjoy");
		}
	}
}
