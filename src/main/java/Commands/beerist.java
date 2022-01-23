package Commands;

import discord4j.core.event.domain.interaction.ChatInputInteractionEvent;
import discord4j.core.spec.EmbedCreateSpec;
import discord4j.rest.util.Color;
import reactor.core.publisher.Mono;

public class beerist {
    public static Mono<Void> exec(ChatInputInteractionEvent event){
        event.getClient().getSelf().subscribe(user -> {
            EmbedCreateSpec embed = EmbedCreateSpec.builder()
                    .image(user.getAvatarUrl())
                    .color(Color.MOON_YELLOW)
                    .build();
            event.editReply().withEmbeds(embed).subscribe();
        });
        return event.deferReply();
    }
}
