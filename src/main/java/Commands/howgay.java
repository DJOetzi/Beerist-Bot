package Commands;

import com.vdurmont.emoji.EmojiParser;
import discord4j.core.event.domain.interaction.ChatInputInteractionEvent;
import discord4j.core.spec.EmbedCreateSpec;
import discord4j.rest.util.Color;
import reactor.core.publisher.Mono;

import java.time.Instant;
import java.util.Random;

public class howgay {
    public static Mono<Void> exec(ChatInputInteractionEvent event, Random rand){
        int gaypercentage = rand.nextInt(0, 100);

        EmbedCreateSpec embed = EmbedCreateSpec.builder()
                .color(Color.MOON_YELLOW)
                .addField(String.format("How gae is %s?", event.getInteraction().getUser().getUsername()), EmojiParser.parseToUnicode(String.format(":rainbow_flag:%s is %d%% gay!:rainbow_flag:", event.getInteraction().getUser().getUsername(), gaypercentage)), false)
                .timestamp(Instant.now())
                .build();
        return event.reply().withEmbeds(embed);
    }
}
