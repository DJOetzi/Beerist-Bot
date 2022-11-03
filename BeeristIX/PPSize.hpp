#pragma once
#include <discordcoreapi/Index.hpp>
#include <fmt/format.h>

#include "GlobalData.hpp"
#include "Colors.hpp"

namespace Beerist::Commands
{
    class PPSize : public DiscordCoreAPI::BaseFunction {
    public:
        PPSize() {
            this->commandName = "pp-size";
            this->helpDescription = "Let the beerist check your PP size!";

            DiscordCoreAPI::EmbedData msgEmbed;
            this->helpEmbed = msgEmbed;
        }

        auto create() -> std::unique_ptr<DiscordCoreAPI::BaseFunction> {
            return std::make_unique<PPSize>();
        }

        virtual auto execute(DiscordCoreAPI::BaseFunctionArguments& args) -> void {
            DiscordCoreAPI::RespondToInputEventData dataPackage{ args.eventData };
            int maxSize = 10;
            std::uniform_int_distribution<> distr(1, maxSize);
            int val = distr(gen);
            DiscordCoreAPI::EmbedData msgEmbed;
            std::string msg = "8";

            for (int i = 0; i < val; i++)
                msg.append("=");

            msg.append("D");

            msgEmbed.addField("Ur PP-Size:", msg);
            msgEmbed.setTimeStamp(DiscordCoreAPI::getTimeAndDate());
            msgEmbed.setColor(DiscordCoreAPI::Colors::MoonYellow);

            dataPackage.addMessageEmbed(msgEmbed);
            dataPackage.setResponseType(DiscordCoreAPI::InputEventResponseType::Interaction_Response);
            DiscordCoreAPI::InputEvents::respondToInputEventAsync(dataPackage);
        }

        static auto returnData(auto guild, auto BotUserId) -> DiscordCoreAPI::CreateGuildApplicationCommandData
        {
            DiscordCoreAPI::CreateGuildApplicationCommandData CommandData{};

            CommandData.guildId = guild;
            CommandData.defaultMemberPermissions = DiscordCoreAPI::Permission::Use_Application_Commands;
            CommandData.dmPermission = true;
            CommandData.applicationId = BotUserId;
            CommandData.type = DiscordCoreAPI::ApplicationCommandType::Chat_Input;
            CommandData.description = "Let the Beerist check your PP-size!";
            CommandData.name = "pp-size";

            return CommandData;
        }
    };
}