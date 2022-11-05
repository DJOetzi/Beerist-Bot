// BeeristIX.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <vector>
#include <chrono>
#include <discordcoreapi/Index.hpp>
#include <nlohmann/json.hpp>

#include "CommandRegister.hpp"
#include "GlobalData.hpp"

#include "MacroUtil.hpp"
#include "FileUtil.hpp"

auto onBoot00(DiscordCoreAPI::DiscordCoreClient* args) -> DiscordCoreAPI::CoRoutine<void>;
auto onGatewayPing(DiscordCoreAPI::OnGatewayPingData args) -> DiscordCoreAPI::CoRoutine<void>;

DiscordCoreAPI::Snowflake debugGuild;
nlohmann::json confDoc;

//TODO:: fix random stuff
auto main() -> int
{
    confDoc = Utility::File::read_file("./data/config.json");

    std::vector<DiscordCoreAPI::RepeatedFunctionData> functionVector{};
    DiscordCoreAPI::RepeatedFunctionData function01{};
    function01.function = &onBoot00;
    function01.intervalInMs = 100;
    function01.repeated = false;
    functionVector.push_back(function01);

    DiscordCoreAPI::DiscordCoreClientConfig clientConfig{};
    clientConfig.botToken = (confDoc["isDebug"] ? confDoc["debugToken"] : confDoc["token"]);
    debugGuild = DiscordCoreAPI::Snowflake(confDoc["debugGuild"].get<uint64_t>());

    DiscordCoreAPI::ShardingOptions shardOptions{};
    shardOptions.numberOfShardsForThisProcess = 1;
    shardOptions.startingShard = 0;
    shardOptions.totalNumberOfShards = 1;
    DiscordCoreAPI::LoggingOptions logOptions{};
    logOptions.logFFMPEGErrorMessages = true;
    logOptions.logGeneralErrorMessages = true;
    logOptions.logHttpsErrorMessages = true;
    logOptions.logHttpsSuccessMessages = true;
    logOptions.logWebSocketErrorMessages = true;
    logOptions.logWebSocketSuccessMessages = true;

    clientConfig.logOptions = logOptions;
    clientConfig.shardOptions = shardOptions;
    clientConfig.intents = DiscordCoreAPI::GatewayIntents::Default_Intents;
    clientConfig.functionsToExecute = functionVector;

    std::vector<DiscordCoreAPI::ActivityData> activities{};
    DiscordCoreAPI::ActivityData activity{};
    activity.name = "with ur mom!";
    activity.type = DiscordCoreAPI::ActivityType::Game;
    activities.push_back(activity);

    clientConfig.presenceData.activities = activities;
    clientConfig.presenceData.afk = false;
    clientConfig.presenceData.since = 0;
    clientConfig.presenceData.status = "online";

    auto bot = std::make_unique<DiscordCoreAPI::DiscordCoreClient>(clientConfig);
    //bot->getEventManager().onGatewayPingEvent(gatewayData);
    bot->getEventManager().onGatewayPing(&onGatewayPing);

    bot->runBot();

    return 0;
}

auto onBoot00(DiscordCoreAPI::DiscordCoreClient* args) -> DiscordCoreAPI::CoRoutine<void>
{
    co_await DiscordCoreAPI::NewThreadAwaitable<void>();
    std::cout << "registering commands..." << std::endl;

    while (args->getBotUser().id == 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds{ 1 });
    }

    std::vector<DiscordCoreAPI::CreateGuildApplicationCommandData> commands{};
    std::vector<DiscordCoreAPI::CreateGlobalApplicationCommandData> global_commands;

    CR("ping", Ping, 0);
    CR("mock", Mock, 1);
    CR("howgae", HowGae, 2);
    CR("choose", Choose, 3);
    CR("pp-size", PPSize, 4);


    DiscordCoreAPI::BulkOverwriteGuildApplicationCommandsData dataPackage;
    dataPackage.responseData = commands;
    dataPackage.guildId = 776156232557264896;
    dataPackage.applicationId = args->getBotUser().id;

    /*DiscordCoreAPI::BulkOverwriteGlobalApplicationCommandsData dataPackageGlobal;
    dataPackageGlobal.responseData = global_commands;
    dataPackageGlobal.applicationId = args->getBotUser().id;*/

    auto ret = DiscordCoreAPI::ApplicationCommands::bulkOverwriteGuildApplicationCommandsAsync(dataPackage).get();
    //auto ret_glob = DiscordCoreAPI::ApplicationCommands::bulkOverwriteGlobalApplicationCommandsAsync(dataPackageGlobal).get();

    co_return;
}

auto onGatewayPing(DiscordCoreAPI::OnGatewayPingData args) -> DiscordCoreAPI::CoRoutine<void>
{
    co_await DiscordCoreAPI::NewThreadAwaitable<void>();

    //std::cout << args.timeUntilNextPing;
    gatewayPing = args.timeUntilNextPing;

    co_return;
}
