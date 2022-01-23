package Commands;

import discord4j.core.event.domain.interaction.ChatInputInteractionEvent;
import reactor.core.publisher.Mono;

public class setbotgame {
    public static Mono<Void> exec(ChatInputInteractionEvent event){
        return event.reply().withContent("```deprecated feature```");
    }
}
