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
	namespace rockpaperscissors {
		CMD_HEAD {
            event.reply(dpp::ir_channel_message_with_source, dpp::message(event.command.channel_id, "Choose your Weapon!")
                .add_component(
                    dpp::component()
                    .add_component(
                        dpp::component().set_label("ROCK")
                        .set_type(dpp::cot_button)
                        .set_emoji(u8"🗿")
                        .set_style(dpp::cos_secondary)
                        .set_id("rock")
                    )
                    .add_component(
                        dpp::component().set_label("PAPER")
                        .set_type(dpp::cot_button)
                        .set_emoji(u8"🧻")
                        .set_style(dpp::cos_success)
                        .set_id("paper")
                    )
                    .add_component(
                        dpp::component().set_label("SCISSORS")
                        .set_type(dpp::cot_button)
                        .set_emoji(u8"⚔")
                        .set_style(dpp::cos_primary)
                        .set_id("scissors")
                    )
                )
            );
		}
	}
}
