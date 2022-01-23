package Commands;

import com.vdurmont.emoji.EmojiParser;
import discord4j.core.event.domain.interaction.ChatInputInteractionEvent;
import discord4j.core.object.component.ActionRow;
import discord4j.core.object.component.Button;
import discord4j.core.object.reaction.ReactionEmoji;
import reactor.core.publisher.Mono;

public class rockpaperscissors {
    public static Mono<Void> exec(ChatInputInteractionEvent event){
        Button[] buttons = {
                Button.secondary("rock", ReactionEmoji.unicode(EmojiParser.parseToUnicode(":moyai:")), "ROCK"),
                Button.success("paper", ReactionEmoji.unicode(EmojiParser.parseToUnicode(":roll_of_paper:")), "PAPER"),
                Button.primary("scissors", ReactionEmoji.unicode(EmojiParser.parseToUnicode(":crossed_swords:")), "SCISSORS")
        };

        return event.reply().withContent("Choose your Weapon!".toUpperCase()).withComponents(ActionRow.of(buttons));
    }
}
