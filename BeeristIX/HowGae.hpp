#pragma once
#include <discordcoreapi/Index.hpp>
#include <fmt/format.h>
#include "MathUtil.hpp"

namespace Beerist::Commands
{
    class HowGae : public DiscordCoreAPI::BaseFunction {
    public:
        HowGae() {
            this->commandName = "howgae";
            this->helpDescription = "Let the beerist check how gay you are!";

            DiscordCoreAPI::EmbedData msgEmbed;
            this->helpEmbed = msgEmbed;
        }

        std::unique_ptr<DiscordCoreAPI::BaseFunction> create() {
            return std::make_unique<HowGae>();
        }

        virtual void execute(DiscordCoreAPI::BaseFunctionArguments& args) {
            DiscordCoreAPI::RespondToInputEventData dataPackage{ args.eventData };

            int val = Utility::File::map_value<float>(rand() % 100, 0, 99, 0, 100);
            DiscordCoreAPI::EmbedData msgEmbed;
            msgEmbed.addField(":rainbow_flag:how gae?:rainbow_flag:", fmt::format("you are :rainbow_flag:{}% gay:rainbow_flag:", val));
            msgEmbed.setTimeStamp(DiscordCoreAPI::getTimeAndDate());
            msgEmbed.setColor("ffff00");
            msgEmbed.setFooter("y r u gae?", args.discordCoreClient->getBotUser().getAvatarUrl());

            dataPackage.addMessageEmbed(msgEmbed);
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