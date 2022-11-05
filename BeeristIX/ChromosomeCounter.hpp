#pragma once

#include <discordcoreapi/Index.hpp>

namespace Beerist::Commands
{
    class ChromosomeCounter : public DiscordCoreAPI::BaseFunction {
    public:
        ChromosomeCounter() {
            this->commandName = "chromosome-counter";
            this->helpDescription = "Let the Beerist count your chromosomes!";

            DiscordCoreAPI::EmbedData msgEmbed;
            this->helpEmbed = msgEmbed;
        }

        auto create() -> std::unique_ptr<DiscordCoreAPI::BaseFunction> {
            return std::make_unique<ChromosomeCounter>();
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
            CommandData.description = "Let the Beerist count your chromosomes!";
            CommandData.name = "chromosome-counter";

            return CommandData;
        }
    };
}
