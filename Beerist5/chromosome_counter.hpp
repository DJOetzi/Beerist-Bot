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
	namespace chromosome_counter {
		void exec(dpp::cluster& bot, const dpp::interaction_create_t& event, dpp::command_interaction cmd_data, std::string topgg_link) {
            short chromosome_count = (rand() % 7) + 45; //45 is the lowest amount and 51 the highest amount of chromosomes a living being can have

            dpp::embed embed = dpp::embed().
                set_color(0xFFFF00).
                set_title("THE CHROMOSOME COUNTER").
                set_url(topgg_link).
                set_author(event.command.usr.username, "", event.command.usr.get_avatar_url()).
                add_field(
                    "Your Chromosome Count:",
                    fmt::format("You have a whopping {} Chromosomes!", chromosome_count)
                ).
                set_footer(dpp::embed_footer().set_text("I don't know if you should be proud of this...").set_icon(event.command.member.get_avatar_url())).
                set_timestamp(time(NULL));

            bot.message_create(dpp::message(event.command.channel_id, embed).set_reference(event.command.id));
            event.reply(dpp::ir_channel_message_with_source, "**CONGRATULATIONS!**");
		}
	}
}
