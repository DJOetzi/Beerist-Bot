package Commands;

import discord4j.core.event.domain.interaction.ChatInputInteractionEvent;
import discord4j.core.object.command.ApplicationCommandInteractionOption;
import discord4j.core.object.command.ApplicationCommandInteractionOptionValue;
import reactor.core.publisher.Mono;

public class mock {
    public static Mono<Void> exec(ChatInputInteractionEvent event){
        String baseText = event.getOption("to-mock")
                .flatMap(ApplicationCommandInteractionOption::getValue)
                .map(ApplicationCommandInteractionOptionValue::asString)
                .orElse("error");
        char[] formattedText = baseText.toCharArray();

        for(int i=0; i<formattedText.length; i++){
            formattedText[i] = (i%2==0)?Character.toLowerCase(formattedText[i]) : Character.toUpperCase(formattedText[i]);
        }
        return event.reply().withContent(new String(formattedText));
    }
}
