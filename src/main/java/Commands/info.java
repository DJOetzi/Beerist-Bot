package Commands;

import discord4j.core.event.domain.interaction.ChatInputInteractionEvent;
import discord4j.core.spec.EmbedCreateSpec;
import discord4j.rest.util.Color;
import reactor.core.publisher.Mono;
import utils.embedUtils;

import java.time.Instant;

public class info {
    public static Mono<Void> exec(ChatInputInteractionEvent event, Boolean isDebug){
        if(event.getClient().getGatewayClient(0).isPresent()){
            EmbedCreateSpec embed = EmbedCreateSpec.builder()
                    .color(Color.MOON_YELLOW)
                    .title("INFO")
                    .addField("PING", String.format("Ping: %dms", event.getClient().getGatewayClient(0).get().getResponseTime().toMillis()), true)
                    .addField("Discord4J VERSION", "3.2.1", true)
                    .addField("BOT VERSION", "Beerist6 - SNAPSHOT 1", true)
                    .addField("TOTAL MEMORY", String.format("%.2fmb", (Runtime.getRuntime().totalMemory() / (1024.0 * 1024.0))), true)
                    .addField("USED MEMORY", String.format("%.2fmb", (Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory())/ (1024.0 * 1024.0)), true)
                    .addField("FREE MEMORY", String.format("%.2fmb", (Runtime.getRuntime().freeMemory() / (1024.0 * 1024.0))), true)
                    .addField("JRE VERSION", System.getProperty("java.version"), true)
                    .addField("HOST OS", System.getProperty("os.name"), true)
                    .addField("IS DEBUG", isDebug.toString().toUpperCase(), true)
                    .timestamp(Instant.now())
                    .build();
            return event.reply().withEmbeds(embed);
        }
        return event.reply().withEmbeds(embedUtils.buildErrorEmbed("An error occured fetching data!\ntry again later!", true));
    }
}
