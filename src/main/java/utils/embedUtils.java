package utils;

import com.vdurmont.emoji.EmojiParser;
import discord4j.core.spec.EmbedCreateSpec;
import discord4j.rest.util.Color;

import java.time.Instant;

public class embedUtils {
    public static EmbedCreateSpec buildWarningEmbed(String content, Boolean contentUppercase){
        return EmbedCreateSpec.builder()
                .color(Color.RED)
                .addField(EmojiParser.parseToUnicode(":warning:warning!:warning:").toUpperCase(), (contentUppercase)?EmojiParser.parseToUnicode(content).toUpperCase():EmojiParser.parseToUnicode(content), false)
                .timestamp(Instant.now())
                .build();
    }
    public static EmbedCreateSpec buildErrorEmbed(String content, Boolean contentUppercase){
        return EmbedCreateSpec.builder()
                .color(Color.RED)
                .addField(EmojiParser.parseToUnicode(":cross:error!:cross:").toUpperCase(), (contentUppercase)?EmojiParser.parseToUnicode(content).toUpperCase():EmojiParser.parseToUnicode(content), false)
                .timestamp(Instant.now())
                .build();
    }
}
