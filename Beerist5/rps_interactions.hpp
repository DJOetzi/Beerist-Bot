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

namespace beerist::button_interactions {
	namespace rockpaperscissors {
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

		void exec(dpp::cluster& bot, const dpp::button_click_t& event, std::string topgg_link) {
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
	}
}
