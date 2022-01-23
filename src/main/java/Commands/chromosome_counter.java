package Commands;

import com.vdurmont.emoji.EmojiParser;
import discord4j.core.event.domain.interaction.ChatInputInteractionEvent;
import discord4j.core.spec.EmbedCreateSpec;
import discord4j.rest.util.Color;
import reactor.core.publisher.Mono;

import java.time.Instant;
import java.util.Random;

public class chromosome_counter {
    public static Mono<Void> exec(ChatInputInteractionEvent event, Random rand){
        int chromosomes = rand.nextInt(45, 52);
        event.getClient().getSelf().subscribe(user -> {
            EmbedCreateSpec embed = EmbedCreateSpec.builder()
                    .addField(EmojiParser.parseToUnicode(":dna: CHROMOSOME COUNTER :dna:"), String.format("You have %d Chromosomes!", chromosomes), false)
                    .footer("I don't know if you should be proud of this...", user.getAvatarUrl())
                    .timestamp(Instant.now())
                    .color(Color.MOON_YELLOW)
                    .build();
            event.editReply().withEmbeds(embed).subscribe();
        });
        return event.deferReply();
    }
}
