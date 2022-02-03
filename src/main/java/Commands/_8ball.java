package Commands;

import discord4j.core.event.domain.interaction.ChatInputInteractionEvent;
import discord4j.core.object.command.ApplicationCommandInteractionOption;
import discord4j.core.object.command.ApplicationCommandInteractionOptionValue;
import reactor.core.publisher.Mono;

import java.util.Random;

public class _8ball {
    public static Mono<Void> exec(ChatInputInteractionEvent event, Random rand){
        String[] answers = {
            "maybe:tm:",
            "yea",
            "no bro",
            "ask me again bruv",
            "dunno",
        };

        return event.reply().withContent(String.format("> %s\n%s", event.getOption("question").flatMap(ApplicationCommandInteractionOption::getValue).map(ApplicationCommandInteractionOptionValue::asString).orElse("error"), answers[rand.nextInt(answers.length)])).withEphemeral(true);
    }
}
