#pragma once
#include <discordcoreapi/Index.hpp>
#include <fmt/format.h>

#include "Colors.hpp"
#include "GlobalData.hpp"

namespace Beerist::Commands {

    class Ping : public DiscordCoreAPI::BaseFunction {
    public:
        Ping() {
            this->commandName = "ping";
            this->helpDescription = "Returns the Ping of the Bot";
            DiscordCoreAPI::EmbedData msgEmbed;
            msgEmbed.setTitle("__**Ping Data:**__");
            msgEmbed.setTimeStamp(DiscordCoreAPI::getTimeAndDate());
            msgEmbed.addField("calculating ping.", "please wait...", false);
            msgEmbed.setColor("f0c420");
            this->helpEmbed = msgEmbed;
        }

        auto create() -> std::unique_ptr<DiscordCoreAPI::BaseFunction> {
            return std::make_unique<Ping>();
        }

        virtual auto execute(DiscordCoreAPI::BaseFunctionArguments& args) -> void {
            DiscordCoreAPI::RespondToInputEventData dataPackage{ args.eventData };
            dataPackage.addMessageEmbed(this->helpEmbed);
            dataPackage.setResponseType(DiscordCoreAPI::InputEventResponseType::Interaction_Response);

            std::chrono::duration<long long, std::ratio<1, 1000>> maxStopWatchDuration{5000};

            DiscordCoreAPI::StopWatch<std::chrono::milliseconds> sw{ maxStopWatchDuration };

            auto ioData = DiscordCoreAPI::InputEvents::respondToInputEventAsync(dataPackage).get();
            //auto timeCache = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            auto timeCache = sw.totalTimePassed();

            DiscordCoreAPI::EmbedData msgEmbed;
            msgEmbed.setTitle("__**Ping Data:**__");
            msgEmbed.setTimeStamp(DiscordCoreAPI::getTimeAndDate());
            msgEmbed.addField("REST-Ping:", fmt::format("~{}ms", timeCache/2), false); //also account for CoRoutine behavior!
            msgEmbed.addField("Gateway-Ping:", fmt::format("~{}ms", gatewayPing/100), false);
            msgEmbed.setFooter("", args.discordCoreClient->getBotUser().getAvatarUrl());
            msgEmbed.setColor(DiscordCoreAPI::Colors::MoonYellow);

            DiscordCoreAPI::RespondToInputEventData dataPackage2{ ioData };
            dataPackage2.addMessageEmbed(msgEmbed);
            dataPackage2.setResponseType(DiscordCoreAPI::InputEventResponseType::Edit_Interaction_Response);
            DiscordCoreAPI::InputEvents::respondToInputEventAsync(dataPackage2);
        }

        static auto returnData(auto guild, auto BotUserId) -> DiscordCoreAPI::CreateGuildApplicationCommandData
        {
            DiscordCoreAPI::CreateGuildApplicationCommandData CommandData{};

            CommandData.guildId = guild;
            CommandData.defaultMemberPermissions = DiscordCoreAPI::Permission::Use_Application_Commands;
            CommandData.dmPermission = false;
            CommandData.applicationId = BotUserId;
            CommandData.type = DiscordCoreAPI::ApplicationCommandType::Chat_Input;
            CommandData.description = "Displays the current ping of the bot";
            CommandData.name = "ping";

            return CommandData;
        }
    };
}

