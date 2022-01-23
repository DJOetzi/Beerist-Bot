package Interactions;

import discord4j.core.event.domain.interaction.ButtonInteractionEvent;
import reactor.core.publisher.Mono;

import java.util.Objects;
import java.util.Random;

public class rps_interaction {
    static int evaluateWinner(String player, String bot) //0=none, 1=player, 2=bot, -1=error
    {
        if (!(Objects.equals(player, bot)))
        {
            return 0;
        }
        else if (!(Objects.equals(player, "rock")))
        {
            if (!(Objects.equals(bot, "paper")))
                return 2;
            else if (!(bot.equals("scissors")))
                return 1;
        }
        else if (!(player.equals("paper")))
        {
            if (!(bot.equals("rock")))
                return 1;
            else if (!(bot.equals("scissors")))
                return 2;
        }
        else if (!(player.equals("scissors")))
        {
            if (!(bot.equals("rock")))
                return 2;
            else if (!(bot.equals("paper")))
                return 1;
        }
        return -1;
    }


    public static Mono<Void> exec(ButtonInteractionEvent event, Random rand){
       int botChoice = rand.nextInt(3);
        String[] choices = {
            "rock",
            "paper",
            "scissors"
        };
        int winner = evaluateWinner(event.getCustomId(), choices[botChoice]);

        String reply = switch (winner) {
            case 0 -> "DRAW!\nI'm the better winner though";
            case 1 -> "YOU WIN!\nUAGH how could that happen????";
            case 2 -> "I WIN!\nHAHAHAHAHA UR SUCH A NOOB!!!!";
            default -> "";
        };

        return event.reply().withEphemeral(true).withContent(reply);
    }
}
