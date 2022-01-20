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
	namespace urbandict {
		CMD_HEAD {
            event.reply(dpp::ir_channel_message_with_source, "processing request...");
            bot.channel_get(event.command.channel_id, [&bot, eventtoken = event.command.token, request = std::get<std::string>(event.get_parameter("to-search"))](const dpp::confirmation_callback_t& channelcallback) {
                if (std::get<dpp::channel>(channelcallback.value).is_nsfw())
                    bot.interaction_response_edit(eventtoken, dpp::message().set_content(fmt::format("https://www.urbandictionary.com/define.php?term={}", std::regex_replace(djutils::str_tolower(request), std::regex(" "), "%20"))).set_flags(dpp::m_ephemeral));
                else
                    bot.interaction_response_edit(eventtoken, dpp::message().set_content("Loads of UrbanDictionary entries are considered NSFW, if you want to search UrbanDict, make sure your Channel is marked as NSFW!").set_flags(dpp::m_ephemeral));
            });
		}
	}
}
