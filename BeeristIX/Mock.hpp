#pragma once
#include <discordcoreapi/Index.hpp>

namespace Beerist::Commands
{
    class Mock : public DiscordCoreAPI::BaseFunction {
    public:
        Mock() {
            this->commandName = "mock";
            this->helpDescription = "Mock dumb things your friends say!";
        }

        std::unique_ptr<DiscordCoreAPI::BaseFunction> create() {
            return std::make_unique<Mock>();
        }

        virtual void execute(DiscordCoreAPI::BaseFunctionArguments& args) {
            DiscordCoreAPI::RespondToInputEventData dataPackage{ args.eventData };

            std::string text = args.optionsArgs.values["to-mock"].value;

            int idx = 0;
            for (char& chr : text) {
                chr = (idx % 2 != 0) ? toupper(chr) : tolower(chr);
                idx++;
            }

            dataPackage.addContent(text);
            dataPackage.setResponseType(DiscordCoreAPI::InputEventResponseType::Interaction_Response);
            DiscordCoreAPI::InputEvents::respondToInputEventAsync(dataPackage);
        }

        static auto returnData(auto guild, auto BotUserId) -> DiscordCoreAPI::CreateGuildApplicationCommandData
        {
            DiscordCoreAPI::ApplicationCommandOptionData MockOption{};
            MockOption.type = DiscordCoreAPI::ApplicationCommandOptionType::String;
            MockOption.name = "to-mock";
            MockOption.description = "The crap you want to mock";
            MockOption.required = true;

            DiscordCoreAPI::CreateGuildApplicationCommandData CommandData{};

            CommandData.guildId = guild;
            CommandData.defaultMemberPermissions = DiscordCoreAPI::Permission::Use_Application_Commands;
            CommandData.dmPermission = false;
            CommandData.applicationId = BotUserId;
            CommandData.type = DiscordCoreAPI::ApplicationCommandType::Chat_Input;
            CommandData.description = "Mock dumb shit your friends say!";
            CommandData.name = "mock";
            CommandData.options.emplace_back(MockOption);

            return CommandData;
        }
    };
}