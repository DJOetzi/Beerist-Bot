package Commands;

import discord4j.core.event.domain.interaction.ChatInputInteractionEvent;
import discord4j.core.object.command.ApplicationCommandInteractionOption;
import discord4j.core.object.command.ApplicationCommandInteractionOptionValue;
import discord4j.core.object.entity.channel.TextChannel;
import reactor.core.publisher.Mono;

import java.util.Objects;

import static utils.embedUtils.buildWarningEmbed;

public class urbandict {
    public static Mono<Void> exec(ChatInputInteractionEvent event){
        event.getInteraction().getChannel().subscribe(messageChannel -> {
            if(((TextChannel)messageChannel).isNsfw()){
               event.editReply(String.format("https://www.urbandictionary.com/define.php?term=%s", Objects.requireNonNull(event.getOption("to-search"))
                       .flatMap(ApplicationCommandInteractionOption::getValue)
                       .map(ApplicationCommandInteractionOptionValue::asString)
                       .orElse("error").toLowerCase().replace(" ", "%20")))
                .subscribe();
            }
            else{
                event.editReply().withEmbeds(buildWarningEmbed("You need to be in a NSFW-Channel in order to use this Feature!", false)).subscribe();
            }
        });

        return event.deferReply();
    }
}
