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

#include "djutils.hpp"

#ifdef _WIN32
  #define popen _popen
  #define pclose _pclose
#endif

#pragma region commands
#include "set_bot_game.hpp"
#include "mock.hpp"
#include "beerist.hpp"
#include "chromosome_counter.hpp"
#include "rockpaperscissors.hpp"
#include "ping.hpp"
#include "urbandict.hpp"
#include "random-meme.hpp"
#include "8-ball.hpp"
#include "choose.hpp"
#include "info.hpp"
#include "random-fact.hpp"
#include "joke.hpp"
#include "pp-size.hpp"
#include "howgay.hpp"
#pragma endregion

#pragma region button interactions
#include "rps_interactions.hpp"
#pragma endregion

#pragma region namespaces
using json = nlohmann::json;
#pragma endregion

#pragma region global variables
std::string bot_link_topgg = "https://top.gg/bot/846722660523180042";
#pragma endregion

int main() {
    json configdocument;
    std::ifstream configfile("./data/setup/baseconfig.json");
    configfile >> configdocument;
    configfile.close();

    bool isDbg = configdocument["is_debug"];
    std::string token;
    if (!isDbg) {
        token = configdocument["token"];
    }
    else {
        token = configdocument["debug_token"];
    }

    dpp::cluster bot(token);
    dpp::snowflake dbgGuild = configdocument["debug_guild"];

    bot.on_ready([&bot, dbgMode = isDbg, guild=dbgGuild](const auto& event) {
        #pragma region system setup
        srand(time(NULL));
        #pragma endregion

        #pragma region presetup
        std::cout << fmt::format("Logged in as {}!\n", bot.me.username);
        bot.set_presence(dpp::presence(dpp::ps_online, dpp::at_custom, "ur mom"));
        #pragma endregion

        #pragma region slash command setup
        std::vector<dpp::slashcommand> cmdlist{ 
            dpp::slashcommand().set_name("mock")
            .set_description("mock dumb things your friends say")
            .set_application_id(bot.me.id)
            .add_option(
                dpp::command_option(dpp::co_string, "to-mock", "stuff you want to mock", true)
            ),
            dpp::slashcommand().set_name("beerist")
            .set_description("Show the Beerist to the world!")
            .set_application_id(bot.me.id),
            dpp::slashcommand().set_name("ping")
            .set_description("Calculate ping of the bot")
            .set_application_id(bot.me.id),
            dpp::slashcommand().set_name("chromosome-counter")
            .set_description("Let beerist count your chromosomes")
            .set_application_id(bot.me.id),
            dpp::slashcommand().set_name("rock-paper-scissors")
            .set_description("Play Rock Paper Scissors with the Beerist")
            .set_application_id(bot.me.id),
            dpp::slashcommand().set_name("urbandict")
            .set_description("Search for stuff on urbandict")
            .set_application_id(bot.me.id)
            .add_option(
                dpp::command_option(dpp::co_string, "to-search", "the stuff to search", true)
            ),
            dpp::slashcommand().set_name("random-meme")
            .set_description("Show a random meme from reddit")
            .set_application_id(bot.me.id)
            .add_option(
                dpp::command_option(dpp::co_string, "subreddit", "the subreddit to fetch the meme from", false)
            ),
            dpp::slashcommand().set_name("8-ball")
            .set_description("Ask the Beerist a question and he'll give you an yes/no answer!")
            .set_application_id(bot.me.id)
            .add_option(
                dpp::command_option(dpp::co_string, "question", "The Question you want to ask the Beerist", true)
            ),
            dpp::slashcommand().set_name("choose")
            .set_description("let the Beerist choose for you")
            .set_application_id(bot.me.id)
            .add_option(
                dpp::command_option(dpp::co_string, "1st", "first option to choose from", true)
            )
            .add_option(
                dpp::command_option(dpp::co_string, "2nd", "second option to choose from", true)
            )
            .add_option(
                dpp::command_option(dpp::co_string, "3rd", "third option to choose from", false)
            )
            .add_option(
                dpp::command_option(dpp::co_string, "4th", "fourth option to choose from", false)
            )
            .add_option(
                dpp::command_option(dpp::co_string, "5th", "fifth option to choose from", false)
            )
            .add_option(
                dpp::command_option(dpp::co_string, "6th", "sixth option to choose from", false)
            )
            .add_option(
                dpp::command_option(dpp::co_string, "7th", "seventh option to choose from", false)
            )
            .add_option(
                dpp::command_option(dpp::co_string, "8th", "eighth option to choose from", false)
            )
            .add_option(
                dpp::command_option(dpp::co_string, "9th", "ninth option to choose from", false)
            )
            .add_option(
                dpp::command_option(dpp::co_string, "10th", "tenth option to choose from", false)
            ),
            dpp::slashcommand().set_name("info")
            .set_description("Info about the Bot")
            .set_application_id(bot.me.id),
            dpp::slashcommand().set_name("random-fact")
            .set_description("Beerist spittin' da random facts")
            .set_application_id(bot.me.id),
            dpp::slashcommand().set_name("joke")
            .set_description("let the Beerist tell you a joke")
            .set_application_id(bot.me.id),
            dpp::slashcommand().set_name("pp-size")
            .set_description("Let the Beerist check your PP-Size")
            .set_application_id(bot.me.id),
            dpp::slashcommand().set_name("how-gay")
            .set_description("Let the Beerist check how gay you are")
            .set_application_id(bot.me.id)
        };

        if (dbgMode) {
            bot.guild_bulk_command_create(cmdlist, guild);
        }
        else {
            bot.global_bulk_command_create(cmdlist);
        }
        #pragma endregion 
    });

    bot.on_interaction_create([&bot, bot_link = bot_link_topgg](const dpp::interaction_create_t& event) {
        if (event.command.type == dpp::it_application_command) {
            dpp::command_interaction cmd_data = std::get<dpp::command_interaction>(event.command.data);

            std::map<std::string, djutils::command> command_table{ 
                {"mock", beerist::commands::mock::exec},
                {"set-bot-game", beerist::commands::set_bot_game::exec },
                {"beerist", beerist::commands::beerist_cmd::exec },
                {"chromosome-counter", beerist::commands::chromosome_counter::exec},
                {"rock-paper-scissors", beerist::commands::rockpaperscissors::exec },
                {"ping", beerist::commands::ping::exec },
                {"urbandict", beerist::commands::urbandict::exec},
                {"random-meme", beerist::commands::randommeme::exec },
                {"8-ball", beerist::commands::_8ball::exec},
                {"choose", beerist::commands::choose::exec},
                {"info", beerist::commands::info::exec},
                {"random-fact", beerist::commands::randomfact::exec},
                {"joke", beerist::commands::joke::exec},
                {"pp-size", beerist::commands::ppsize::exec},
                {"how-gay", beerist::commands::howgay::exec}
            };
            command_table[cmd_data.name](bot, event, cmd_data, bot_link);
        }
    });

    bot.on_button_click([&bot, bot_link = bot_link_topgg](const dpp::button_click_t& event) {
        std::map<std::string, djutils::button_interactions> interaction_table{
            {"rock", beerist::button_interactions::rockpaperscissors::exec},
            {"paper", beerist::button_interactions::rockpaperscissors::exec},
            {"scissors", beerist::button_interactions::rockpaperscissors::exec}
        };
        interaction_table[event.custom_id](bot, event, bot_link);
    });
 
    bot.start(false);
    return 0;
}