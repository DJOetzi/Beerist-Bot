#pragma once
#include <discordcoreapi/Index.hpp>

namespace Beerist::Commands
{
    class CommandTemplate : public DiscordCoreAPI::BaseFunction {
    public:
        CommandTemplate() {
            this->commandName = "";
            this->helpDescription = "";

            DiscordCoreAPI::EmbedData msgEmbed;
            this->helpEmbed = msgEmbed;
        }

        auto create() -> std::unique_ptr<DiscordCoreAPI::BaseFunction> {
            return std::make_unique<CommandTemplate>();
        }

        virtual auto execute(DiscordCoreAPI::BaseFunctionArguments& args) -> void {
            DiscordCoreAPI::RespondToInputEventData dataPackage{ args.eventData };
            
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
            CommandData.description = "";
            CommandData.name = "";

            return CommandData;
        }
    };
}
