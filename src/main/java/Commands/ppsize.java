package Commands;

import discord4j.core.event.domain.interaction.ChatInputInteractionEvent;
import discord4j.core.spec.EmbedCreateSpec;
import discord4j.rest.util.Color;
import reactor.core.publisher.Mono;
import utils.genericUtils;

import java.time.Instant;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;

public class ppsize {
    public static Mono<Void> exec(ChatInputInteractionEvent event, Random rand){
       int size = rand.nextInt(1, 6);
       List<Character> response = new LinkedList<>();

       for (int i = 0; i < size; i++) {
          response.add(0, '=');
       }
       response.add(0, '8');
       response.add('D');

        EmbedCreateSpec embed = EmbedCreateSpec.builder()
                .color(Color.MOON_YELLOW)
                .addField(String.format("%s's PP-Size:", event.getInteraction().getUser().getUsername()), genericUtils.characterListToString(response), false)
                .timestamp(Instant.now())
                .build();

        return event.reply().withEmbeds(embed);
    }
}
