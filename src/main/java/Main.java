import Commands.*;
import Interactions.rps_interaction;
import com.google.gson.Gson;
import com.google.gson.JsonObject;
import discord4j.core.DiscordClient;
import discord4j.core.GatewayDiscordClient;
import discord4j.core.event.domain.interaction.ButtonInteractionEvent;
import discord4j.core.event.domain.interaction.ChatInputInteractionEvent;
import discord4j.core.event.domain.lifecycle.ReadyEvent;
import discord4j.core.event.domain.message.MessageCreateEvent;
import discord4j.core.object.command.ApplicationCommandOption;
import discord4j.core.object.entity.User;
import discord4j.core.object.presence.ClientActivity;
import discord4j.core.object.presence.ClientPresence;
import discord4j.discordjson.json.ApplicationCommandOptionData;
import discord4j.discordjson.json.ApplicationCommandRequest;
import reactor.core.publisher.Mono;

import java.util.Arrays;
import java.util.Random;

import static utils.fileUtils.readFileAsString;

public class Main {
    public static JsonObject config;
    public static Random rand = new Random();

    public static void main(String[] args) throws Exception{
        config = new Gson().fromJson(readFileAsString("src/config.json"), JsonObject.class);
        final boolean is_debug = config.get("is_debug").getAsBoolean();
        final DiscordClient client = DiscordClient.create((is_debug)?config.get("debug_token").getAsString():config.get("token").getAsString());
        long applicationId=client.getApplicationId().block(), guildId = config.get("debug_guild").getAsLong();

        //region commands
        ApplicationCommandRequest[] commands = {
                ApplicationCommandRequest.builder()
                        .name("info")
                        .description("displays various info about the bot")
                        .build(),
                ApplicationCommandRequest.builder()
                        .name("mock")
                        .description("mock dumb things your friends say")
                        .addOption(ApplicationCommandOptionData.builder()
                                .name("to-mock")
                                .description("stuff you want to mock")
                                .type(ApplicationCommandOption.Type.STRING.getValue())
                                .required(true)
                                .build()
                        )
                        .build(),
                ApplicationCommandRequest.builder()
                        .name("beerist")
                        .description("Show the Beerist to the world!")
                        .build(),
                ApplicationCommandRequest.builder()
                        .name("chromosome-counter")
                        .description("Let Beerist count your chromosomes")
                        .build(),
                ApplicationCommandRequest.builder()
                        .name("rock-paper-scissors")
                        .description("Play Rock Paper Scissors with the Beerist")
                        .build()
        };
        //endregion

        //region register commands
        if(config.get("is_debug").getAsBoolean())
            client.getApplicationService()
                    .bulkOverwriteGuildApplicationCommand(applicationId, guildId, Arrays.asList(commands))
                    .subscribe();
        else
            client.getApplicationService()
                    .bulkOverwriteGlobalApplicationCommand(applicationId, Arrays.asList(commands))
                    .subscribe();
        //endregion

        //region events
        Mono<Void> login = client.withGateway((GatewayDiscordClient gateway) -> {
            Mono<Void> onStartEvent = gateway.on(ReadyEvent.class, event ->
                    Mono.fromRunnable(() -> {
                                final User self = event.getSelf();
                                System.out.printf("Logged in as %s#%s%n", self.getUsername(), self.getDiscriminator());
                                gateway.updatePresence(ClientPresence.idle(ClientActivity.watching("my creator doing things to me..."))).subscribe();
                            }
                    )
            ).then();

            Mono<Void> onMsgEvent = gateway.on(MessageCreateEvent.class, event -> Mono.empty()).then();

            Mono<Void> onInteractionEvent = gateway.on(ChatInputInteractionEvent.class, event ->
                    switch (event.getCommandName()) {
                        case "info" -> info.exec(event);
                        case "mock" -> mock.exec(event);
                        case "beerist" -> beerist.exec(event);
                        case "set-bot-game" -> setbotgame.exec(event);
                        case "chromosome-counter" -> chromosome_counter.exec(event, rand);
                        case "rock-paper-scissors" -> rockpaperscissors.exec(event);
                        default -> Mono.empty();
                    }
            ).then();

            Mono<Void> onButtonEvent = gateway.on(ButtonInteractionEvent.class, event ->
                    switch (event.getCustomId()){
                        case "rock", "paper", "scissors" -> rps_interaction.exec(event, rand);
                        default -> Mono.empty();
                    }
            ).then();

            return onStartEvent.and(onMsgEvent.and(onInteractionEvent.and(onButtonEvent)));
        });
        //endregion

        login.block();
    }
}
