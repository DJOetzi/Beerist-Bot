#pragma once
#include <discordcoreapi/Index.hpp>
#include "MathUtil.hpp"

namespace Beerist::Commands
{
    class HowGae : public DiscordCoreAPI::BaseFunction {
    public:
        HowGae() {
            this->commandName = "howgae";
            this->helpDescription = "Let the beerist check how gay you are!";
            int val = Utility::File::map_value<int>(rand() % 100 + 1, 1, 100, 0, 100);

            DiscordCoreAPI::EmbedData msgEmbed;
            msgEmbed.setDescription("------\nSimply enter !test or /test!\n------");
            msgEmbed.setTitle("__**Test Usage:**__");
            msgEmbed.setTimeStamp(DiscordCoreAPI::getTimeAndDate());
            msgEmbed.setColor("FeFeFe");
            this->helpEmbed = msgEmbed;
        }

        std::unique_ptr<DiscordCoreAPI::BaseFunction> create() {
            return std::make_unique<HowGae>();
        }

        virtual void execute(DiscordCoreAPI::BaseFunctionArguments& args) {
            DiscordCoreAPI::RespondToInputEventData dataPackage{ args.eventData };

            dataPackage.addMessageEmbed(this->helpEmbed);
            dataPackage.setResponseType(DiscordCoreAPI::InputEventResponseType::Interaction_Response);
            DiscordCoreAPI::InputEvents::respondToInputEventAsync(dataPackage);
        }

        static auto returnData(auto guild, auto BotUserId) -> DiscordCoreAPI::CreateGuildApplicationCommandData
        {
            DiscordCoreAPI::CreateGuildApplicationCommandData CommandData{};

            CommandData.guildId = guild;
            CommandData.defaultMemberPermissions = DiscordCoreAPI::Permission::Use_Application_Commands;
            CommandData.dmPermission = false;
            CommandData.applicationId = BotUserId;
            CommandData.type = DiscordCoreAPI::ApplicationCommandType::Chat_Input;
            CommandData.description = "Let the beerist check how gay you are!";
            CommandData.name = "howgae";

            return CommandData;
        }
    };
}