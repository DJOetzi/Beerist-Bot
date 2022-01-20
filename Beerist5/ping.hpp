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
	namespace ping {
		CMD_HEAD {
            int gping = event.from->websocket_ping * 1000, rping = bot.rest_ping * 1000;

            dpp::embed embed = dpp::embed().
                set_color(0xFFFF00).
                set_title("PING INFORMATION").
                set_url(topgg_link).
                set_author(event.command.usr.username, "", event.command.usr.get_avatar_url()).
                add_field(
                    "Gateway Ping:",
                    fmt::format("{}ms", gping)
                )
                .add_field(
                    "REST Ping:",
                    fmt::format("{}ms", rping)
                ).
                set_footer(dpp::embed_footer().set_text("ping pong").set_icon(event.command.member.get_avatar_url())).
                set_timestamp(time(NULL));

            event.reply(dpp::ir_channel_message_with_source, dpp::message(event.command.channel_id, embed));
		}
	}
}
