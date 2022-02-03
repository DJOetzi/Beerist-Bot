package Commands;

import discord4j.core.event.domain.interaction.ChatInputInteractionEvent;
import discord4j.core.spec.EmbedCreateSpec;
import discord4j.rest.util.Color;
import reactor.core.publisher.Mono;

import java.time.Instant;

public class credits {
    public static Mono<Void> exec(ChatInputInteractionEvent event){
        EmbedCreateSpec embed = EmbedCreateSpec.builder()
                                   .title("the Beerist")
                                   .url("https://github.com/Progame03/Beerist-Bot")
                                   .addField("Beerist6 created and maintained by DJ::Ötzi and its contributors!", "- Version: Beerist6 rev. 1\n" + "- Discord4J-Version: 3.2.1", false)
                                   .color(Color.MOON_YELLOW)
                                   .timestamp(Instant.now())
                                   .build();
        return event.reply().withEmbeds(embed);
    }
}
