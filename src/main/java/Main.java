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
import discord4j.core.object.entity.User;
import discord4j.core.object.presence.ClientActivity;
import discord4j.core.object.presence.ClientPresence;
import discord4j.discordjson.json.ApplicationCommandRequest;
import reactor.core.publisher.Mono;

import java.util.Arrays;
import java.util.Random;

import static utils.fileUtils.getResourceFileAsString;
import static utils.slashUtils.commandLoaderFromResources;

public class Main {
    public static JsonObject config;
    public static Random rand = new Random();

    public static void main(String[] args) throws Exception{
        config = new Gson().fromJson(getResourceFileAsString("config.json"), JsonObject.class);
        final boolean is_debug = config.get("is_debug").getAsBoolean();
        final DiscordClient client = DiscordClient.create((is_debug)?config.get("debug_token").getAsString():config.get("token").getAsString());
        long applicationId=client.getApplicationId().block(), guildId = config.get("debug_guild").getAsLong();

        //region commands
        ApplicationCommandRequest[] commands = commandLoaderFromResources("CommandData/");
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
                        case "info" -> info.exec(event, is_debug);
                        case "mock" -> mock.exec(event);
                        case "beerist" -> beerist.exec(event);
                        case "set-bot-game" -> setbotgame.exec(event);
                        case "chromosome-counter" -> chromosome_counter.exec(event, rand);
                        case "rock-paper-scissors" -> rockpaperscissors.exec(event);
                        case "urbandict" -> urbandict.exec(event);
                        case "random-meme" -> randommeme.exec(event);
                        case "8-ball" -> _8ball.exec(event, rand);
                        case "choose" -> choose.exec(event, rand);
                        case "credits" -> credits.exec(event);
                        case "random-fact" -> randomfact.exec(event);
                        case "joke" -> joke.exec(event);
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