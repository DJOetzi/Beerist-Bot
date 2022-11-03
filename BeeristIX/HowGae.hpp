#pragma once
#include <discordcoreapi/Index.hpp>
#include <fmt/format.h>

#include "Colors.hpp"
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

        auto create() -> std::unique_ptr<DiscordCoreAPI::BaseFunction> {
            return std::make_unique<HowGae>();
        }

        virtual auto execute(DiscordCoreAPI::BaseFunctionArguments& args) -> void {
            DiscordCoreAPI::RespondToInputEventData dataPackage{ args.eventData };
            std::uniform_int_distribution<> distr(0, 100);
            int val = distr(gen);
            DiscordCoreAPI::EmbedData msgEmbed;
            msgEmbed.addField(":rainbow_flag:how gae?:rainbow_flag:", fmt::format("you are :rainbow_flag:{}% gay:rainbow_flag:", val));
            msgEmbed.setTimeStamp(DiscordCoreAPI::getTimeAndDate());
            msgEmbed.setColor(DiscordCoreAPI::Colors::MoonYellow);
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
            CommandData.dmPermission = true;
            CommandData.applicationId = BotUserId;
            CommandData.type = DiscordCoreAPI::ApplicationCommandType::Chat_Input;
            CommandData.description = "Let the beerist check how gay you are!";
            CommandData.name = "howgae";

            return CommandData;
        }
    };
}