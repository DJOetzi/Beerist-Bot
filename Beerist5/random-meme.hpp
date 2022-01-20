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
	namespace randommeme {
		CMD_HEAD {
            event.reply(dpp::ir_channel_message_with_source, "Fetching your meme...");
            std::string sub;

            if (json::parse(event.raw_event)["d"]["data"]["options"].is_null()) sub = "memes";
            else sub = std::get<std::string>(event.get_parameter("subreddit"));
            sub = std::regex_replace(djutils::str_tolower(sub), std::regex(" "), "_");
            dpp::utility::exec("curl", { fmt::format("https://meme-api.herokuapp.com/gimme/{}", sub) }, [&bot, channelid = event.command.channel_id, eventtokenraw = event.command.token, usrname = event.command.usr.username, usravatar = event.command.usr.get_avatar_url()](const std::string& output) {
                if (djutils::string_contains(output, "url")) {
                    bot.channel_get(channelid, [&bot, eventtoken = eventtokenraw, rawjson = output, channel_id = channelid, name = usrname, avatar = usravatar](const dpp::confirmation_callback_t& channelcallback) {
                        std::string formatted = rawjson;
                        formatted.std::string::erase(0, rawjson.find('{') - 1);

                        json jsonBinary;
                        jsonBinary = djutils::str_json(formatted);

                        djutils::redditpost post = {
                            jsonBinary["author"],
                            jsonBinary["title"],
                            jsonBinary["url"],
                            jsonBinary["postLink"],
                            jsonBinary["subreddit"],
                            jsonBinary["nsfw"],
                            jsonBinary["ups"]
                        };

                        dpp::embed embed = dpp::embed().
                            set_color(0xFFFF00).
                            set_title(post.title).
                            set_url(post.link).
                            set_author(name, "", avatar).
                            set_image(post.url).
                            set_footer(dpp::embed_footer().set_text(fmt::format(u8"{}👍 • by {} • from {}", post.upvotes, post.author, fmt::format("r/{}", post.sub))).set_icon(bot.me.get_avatar_url())).
                            set_timestamp(time(NULL));

                        if (!post.nsfw) {
                            bot.interaction_response_edit(eventtoken, dpp::message(channel_id, embed));
                        }
                        else if (std::get<dpp::channel>(channelcallback.value).is_nsfw() && post.nsfw) {
                            bot.interaction_response_edit(eventtoken, dpp::message(channel_id, embed));
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
}