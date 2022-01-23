package Commands;

import discord4j.core.DiscordClient;
import discord4j.core.DiscordClientBuilder;
import discord4j.core.event.domain.interaction.ChatInputInteractionEvent;
import discord4j.core.spec.EmbedCreateSpec;
import discord4j.rest.util.Color;
import reactor.core.publisher.Mono;
import discord4j.common.GitProperties;

import java.time.Instant;

public class info {
    public static Mono<Void> exec(ChatInputInteractionEvent event){
        long startSend = System.currentTimeMillis();
        event.reply().withContent("beep boop...").subscribe();

        event.getReply().subscribe(message -> {
            long restPing = message.getTimestamp().toEpochMilli() - startSend;

            EmbedCreateSpec embed = EmbedCreateSpec.builder()
                    .color(Color.MOON_YELLOW)
                    .title("INFO")
                    .addField("PING", String.format("REST Ping: %dms", restPing), true)
                    .addField("Discord4J VERSION", "3.2.1", true)
                    .addField("JRE VERSION", System.getProperty("java.version"), true)
                    .addField("BOT VERSION", "Beerist6 - SNAPSHOT 1", true)
                    .timestamp(Instant.now())
                    .build();
            event.editReply("ㅤ").withEmbeds(embed).subscribe();
        });
        return Mono.empty();
    }
}
