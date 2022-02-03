package Commands;

import discord4j.core.event.domain.interaction.ChatInputInteractionEvent;
import discord4j.core.object.command.ApplicationCommandInteractionOptionValue;
import reactor.core.publisher.Mono;

import java.util.Random;

public class choose {
    public static Mono<Void> exec(ChatInputInteractionEvent event, Random rand){
        String response = "";
        response = event.getOptions().get(rand.nextInt(event.getOptions().size())).getValue().map(ApplicationCommandInteractionOptionValue::asString).orElse("error");
        if(response.contains("@everyone") || response.contains("@here")){
            return event.reply().withContent("I chose: **You are trying to exploit bots!**").withEphemeral(true);
        }

        return event.reply().withContent(String.format("I choose: **%s**!", response));
    }
}
