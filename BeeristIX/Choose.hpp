#pragma once
#include <discordcoreapi/Index.hpp>
#include <fmt/format.h>

#include "StringUtil.hpp"

namespace Beerist::Commands
{
    std::vector<std::string> availableOptions{ "first","second","third","fourth","fifth","sixth","seventh","eighth","ninth","tenth" };

    class Choose : public DiscordCoreAPI::BaseFunction {
    public:
        Choose() {
            this->commandName = "choose";
            this->helpDescription = "Let the Beerist choose for you!";
        }

        auto create() -> std::unique_ptr<DiscordCoreAPI::BaseFunction> {
            return std::make_unique<Choose>();
        }

        virtual auto execute(DiscordCoreAPI::BaseFunctionArguments& args) -> void {
            DiscordCoreAPI::RespondToInputEventData dataPackage{ args.eventData };
            int selection = std::rand() % args.optionsArgs.values.size();
            std::cout << availableOptions.size(); // TODO: Debug Behavior of selection!
            std::string response = args.optionsArgs.values[availableOptions[selection]].value;

            response = fmt::format("I choose: **{}**", response);
            dataPackage.setResponseType(DiscordCoreAPI::InputEventResponseType::Interaction_Response);

            if (Utility::String::str_contains(response, "@everyone") || Utility::String::str_contains(response, "@here"))
            {
	            response = "I choose: **You are trying to exploit bots!**";
                dataPackage.setResponseType(DiscordCoreAPI::InputEventResponseType::Ephemeral_Interaction_Response);
            }

            dataPackage.addContent(response);
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
            CommandData.description = "Let the Beerist choose for you!";
            CommandData.name = "choose";
            CommandData.options = buildOptionData();

            return CommandData;
        }

        static auto buildOptionData() -> std::vector<DiscordCoreAPI::ApplicationCommandOptionData>
        {
            std::vector<DiscordCoreAPI::ApplicationCommandOptionData> OptionData;

            for(int i=0; i<availableOptions.size(); i++)
            {
                DiscordCoreAPI::ApplicationCommandOptionData tmpOption{};
                tmpOption.type = DiscordCoreAPI::ApplicationCommandOptionType::String;
                tmpOption.name = availableOptions[i];
                tmpOption.description = fmt::format("The {} option to choose from", availableOptions[i]);
                tmpOption.required = !(i >= 2);

                OptionData.emplace_back(tmpOption);
            }

            return OptionData;
        }
    };
}