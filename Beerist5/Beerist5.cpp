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
#pragma endregion

#pragma region namespaces
using json = nlohmann::json;
#pragma endregion

#pragma region global variables
std::string bot_link_topgg = "https://top.gg/bot/846722660523180042";
#pragma endregion

#pragma region prototypes
short evaluateWinner(const char* player, const char* bot);
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
        bot.set_presence(dpp::presence(dpp::ps_idle, dpp::at_custom, "Beerist5 in the works!"));
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
            )
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
                {"8-ball", beerist::commands::_8ball::exec}
            };
            command_table[cmd_data.name](bot, event, cmd_data, bot_link);
        }
    });

    bot.on_button_click([&bot](const dpp::button_click_t& event) {
        if (event.custom_id == "rock" || event.custom_id == "paper" || event.custom_id == "scissors") {
            dpp::message msgobj;
            short botchoice = rand() % 3;
            std::string choices[] =
            {
                "rock",
                "paper",
                "scissors"
            };
            short winner = evaluateWinner(event.custom_id.c_str(), choices[botchoice].c_str());
            std::string reply;

            switch (winner)
            {
               case 0:
                   reply = "DRAW!\nI'm the better winner though";
                   break;
               case 1:
                   reply = "YOU WIN!\nUAGH how could that happen????";
                   break;
               case 2:
                   reply = "I WIN!\nHAHAHAHAHA UR SUCH A NOOB!!!!";
                   break;
            }

            msgobj.set_flags(dpp::m_ephemeral);
            msgobj.content = reply;

            event.reply(dpp::ir_channel_message_with_source, msgobj);
        }
    });
 
    bot.start(false);
    return 0;
}

short evaluateWinner(const char* player, const char* bot) //0=none, 1=player, 2=bot, -1=error
{
    if (!strcmp(player, bot))
    {
        return 0;
    }
    else if (!strcmp(player, "rock"))
    {
        if (!strcmp(bot, "paper"))
            return 2;
        else if (!strcmp(bot, "scissors"))
            return 1;
    }
    else if (!strcmp(player, "paper"))
    {
        if (!strcmp(bot, "rock"))
            return 1;
        else if (!strcmp(bot, "scissors"))
            return 2;
    }
    else if (!strcmp(player, "scissors"))
    {
        if (!strcmp(bot, "rock"))
            return 2;
        else if (!strcmp(bot, "paper"))
            return 1;
    }
    return -1;
}