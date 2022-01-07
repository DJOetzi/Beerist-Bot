#include <dpp/dpp.h>
#include <dpp/nlohmann/json.hpp>
#include <dpp/fmt/format.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
#include <time.h>
#include <regex>
#include <locale>

#ifdef _WIN32
  #include <array>
  #include <stdio.h>
  #include <stdlib.h>
  #define popen _popen
  #define pclose _pclose
#endif

#pragma region datatypes
typedef struct {
    std::string author, title, url, link, sub;
    bool nsfw;
    unsigned int upvotes;
}redditpost;
#pragma endregion

#pragma region namespaces
using json = nlohmann::json;
#pragma endregion

#pragma region global variables
std::string bot_link_topgg = "https://top.gg/bot/846722660523180042";
#pragma endregion

#pragma region prototypes
short evaluateWinner(const char* player, const char* bot);

namespace djutils {
    std::string str_tolower(std::string str);
    bool stringContains(std::string s1, std::string s2);
}
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
        std::cout << "Logged in as " << bot.me.username << "!\n";
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
            )
        };

        if (dbgMode) {
            for (int idx = 0; idx < cmdlist.size(); idx++) {
                bot.guild_command_create(cmdlist[idx], guild);
            }
        }
        else {
            for (int idx = 0; idx < cmdlist.size(); idx++) {
                bot.global_command_create(cmdlist[idx]);
            }
        }
        #pragma endregion 
    });

    bot.on_interaction_create([&bot, bot_link = bot_link_topgg](const dpp::interaction_create_t& event) {
        if (event.command.type == dpp::it_application_command) {
            dpp::command_interaction cmd_data = std::get<dpp::command_interaction>(event.command.data);

            if (cmd_data.name == "mock") {
                std::string basetext = std::get<std::string>(event.get_parameter("to-mock"));

                char* text = (char*)calloc(basetext.length(), sizeof(char));
                if (text) {
                    strcpy(text, basetext.c_str());

                    for (int idx = 0; idx < basetext.length(); idx++) {
                        text[idx] = (idx % 2 != 0) ? toupper(text[idx]) : tolower(text[idx]);
                    }

                    event.reply(dpp::ir_channel_message_with_source, text);
                    free(text);
                    //std::cout << "mem cleared";
                }
                else
                    event.reply(dpp::ir_channel_message_with_source, fmt::format("Error happened at editing `{}`\n**REPORT THIS TO THE DEV IMMEDEATELY**", basetext));
                if (text)
                    free(text);
            }

            else if (cmd_data.name == "set-bot_game") {
                event.reply(dpp::ir_channel_message_with_source, "```DEPRECATED FEATURE```");
            }

            else if (cmd_data.name == "beerist") {
                dpp::embed embed = dpp::embed().
                    set_color(0xFFFF00).
                    set_title("the Beerist").
                    set_url(bot_link).
                    set_author(event.command.usr.username, "", event.command.usr.get_avatar_url()).
                    set_image("https://cdn.discordapp.com/emojis/697110203249983628.png?v=1").
                    set_footer(dpp::embed_footer().set_text("an epic image of the Beerist because you asked so kindly").set_icon(event.command.member.get_avatar_url())).
                    set_timestamp(time(NULL));

                /* reply with the created embed */
                bot.message_create(dpp::message(event.command.channel_id, embed).set_reference(event.command.id));
                event.reply(dpp::ir_channel_message_with_source, "enjoy");
            }

            else if (cmd_data.name == "chromosome-counter") {
                short chromosome_count = (rand() % 7) + 45;

                dpp::embed embed = dpp::embed().
                    set_color(0xFFFF00).
                    set_title("THE CHROMOSOME COUNTER").
                    set_url(bot_link).
                    set_author(event.command.usr.username, "", event.command.usr.get_avatar_url()).
                    add_field(
                        "Your Chromosome Count:",
                        fmt::format("You have a whopping {} Chromosomes!", chromosome_count)
                    ).
                    set_footer(dpp::embed_footer().set_text("I don't know if you should be proud of this...").set_icon(event.command.member.get_avatar_url())).
                    set_timestamp(time(NULL));

                /* reply with the created embed */
                bot.message_create(dpp::message(event.command.channel_id, embed).set_reference(event.command.id));
                event.reply(dpp::ir_channel_message_with_source, "**CONGRATULATIONS!**");
            }

            else if (cmd_data.name == "rock-paper-scissors") {
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

            else if (cmd_data.name == "ping") {
                int gping = event.from->websocket_ping * 1000, rping = bot.rest_ping * 1000;

                dpp::embed embed = dpp::embed().
                    set_color(0xFFFF00).
                    set_title("PING INFORMATION").
                    set_url(bot_link).
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

                /* reply with the created embed */
                bot.message_create(dpp::message(event.command.channel_id, embed).set_reference(event.command.id));
                event.reply(dpp::ir_channel_message_with_source, ":ping_pong: ping pong :ping_pong:");
            }

            else if (cmd_data.name == "urbandict") {
                event.reply(dpp::ir_channel_message_with_source, "processing request...");
                bot.channel_get(event.command.channel_id, [&bot, eventtoken = event.command.token, request = std::get<std::string>(event.get_parameter("to-search"))](const dpp::confirmation_callback_t& channelcallback) {
                    if (std::get<dpp::channel>(channelcallback.value).is_nsfw())
                        bot.interaction_response_edit(eventtoken, dpp::message().set_content(fmt::format("https://www.urbandictionary.com/define.php?term={}", std::regex_replace(djutils::str_tolower(request), std::regex(" "), "%20"))).set_flags(dpp::m_ephemeral));
                    else
                        bot.interaction_response_edit(eventtoken, dpp::message().set_content("Loads of UrbanDictionary entries are considered NSFW, if you want to search UrbanDict, make sure your Channel is marked as NSFW!").set_flags(dpp::m_ephemeral));
                });
            }

            else if (cmd_data.name == "random-meme") {
                event.reply(dpp::ir_channel_message_with_source, "Fetching your meme...");
                std::string sub;

                if (json::parse(event.raw_event)["d"]["data"]["options"].is_null()) sub = "memes";
                else sub = std::get<std::string>(event.get_parameter("subreddit"));
                sub = std::regex_replace(djutils::str_tolower(sub), std::regex(" "), "_");
                dpp::utility::exec("curl", { fmt::format("https://meme-api.herokuapp.com/gimme/{}", sub) }, [&bot, channelid = event.command.channel_id, eventtokenraw = event.command.token, usrname = event.command.usr.username, usravatar = event.command.usr.get_avatar_url()](const std::string& output) {
                    if (djutils::stringContains(output, "url")) {
                        bot.channel_get(channelid, [&bot, eventtoken = eventtokenraw, rawjson = output, channel_id = channelid, name = usrname, avatar = usravatar](const dpp::confirmation_callback_t& channelcallback) {
                            std::string formatted = rawjson;
                            formatted.std::string::erase(0, rawjson.find('{') - 1);

                            json jsonBinary;
                            try
                            {
                                jsonBinary = json::parse(formatted);
                            }
                            catch (json::parse_error& e)
                            {
                                std::cout << "message: " << e.what() << '\n'
                                    << "exception id: " << e.id << '\n'
                                    << "byte position of error: " << e.byte << std::endl;
                            }

                            redditpost post = {
                                jsonBinary["author"],
                                jsonBinary["title"],
                                jsonBinary["url"],
                                jsonBinary["postLink"],
                                jsonBinary["subreddit"],
                                jsonBinary["nsfw"],
                                jsonBinary["ups"]
                            };

                            std::string response = "enjoy your meme";
                            dpp::embed embed = dpp::embed().
                                set_color(0xFFFF00).
                                set_title(post.title).
                                set_url(post.link).
                                set_author(name, "", avatar).
                                set_image(post.url).
                                set_footer(dpp::embed_footer().set_text(fmt::format(u8"{}👍 • by {} • from {}", post.upvotes, post.author, fmt::format("r/{}", post.sub))).set_icon(bot.me.get_avatar_url())).
                                set_timestamp(time(NULL));

                            if (!post.nsfw) {
                                bot.interaction_response_edit(eventtoken, response);
                                bot.message_create(dpp::message(channel_id, embed));
                            }
                            else if (std::get<dpp::channel>(channelcallback.value).is_nsfw() && post.nsfw) {
                                bot.interaction_response_edit(eventtoken, response);
                                bot.message_create(dpp::message(channel_id, embed));
                            }
                            else {
                                bot.interaction_response_edit(eventtoken, dpp::message().set_content("OOPS!\nYou tried to send a NSFW-Meme in a non-NSFW Channel!\nMake sure your Channel is marked as NSFW to receive such memes!").set_flags(dpp::m_ephemeral));
                            }
                        });
                    }
                    else {
                        bot.interaction_response_edit(eventtokenraw, dpp::message().set_content("OOPS!\nSeems like something went wrong!\nMake sure your Subreddit exists and you spelled it right!").set_flags(dpp::m_ephemeral));
                    }
                });
            }
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

namespace djutils {
    std::string str_tolower(std::string str) {
        for (auto& c : str)
        {
            c = tolower(c);
        }

        return str;
    }
    bool stringContains(std::string s1, std::string s2) {
        return s1.find(s2) != std::string::npos;
    }
}