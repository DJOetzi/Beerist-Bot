package Commands;

import com.vdurmont.emoji.EmojiParser;
import discord4j.core.event.domain.interaction.ChatInputInteractionEvent;
import discord4j.core.object.command.ApplicationCommandInteractionOption;
import discord4j.core.object.command.ApplicationCommandInteractionOptionValue;
import discord4j.core.object.entity.channel.TextChannel;
import discord4j.core.spec.EmbedCreateSpec;
import discord4j.rest.util.Color;
import reactor.core.publisher.Mono;

import java.io.IOException;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.time.Instant;

import static utils.embedUtils.buildWarningEmbed;
import static utils.redditUtils.buildPost;

public class randommeme {
    public static Mono<Void> exec(ChatInputInteractionEvent event) {
        event.deferReply().subscribe();

        event.getInteraction().getChannel().subscribe(messageChannel -> new Thread(()->{
            String sub = event.getOption("subreddit")
                    .flatMap(ApplicationCommandInteractionOption::getValue)
                    .map(ApplicationCommandInteractionOptionValue::asString)
                    .orElse("memes");
            URI uri = URI.create(String.format("https://meme-api.herokuapp.com/gimme/%s", sub));
            HttpRequest request = HttpRequest.newBuilder(uri).build();
            String content = null;
            try {
                content = HttpClient.newHttpClient().send(request, HttpResponse.BodyHandlers.ofString()).body();
            }
            catch (IOException | InterruptedException e) {
                e.printStackTrace();
            }
            buildPost(content).subscribe(redditPost -> event.getClient().getSelf().subscribe(user -> {
                EmbedCreateSpec embed;
                if(!redditPost.nsfw || ((TextChannel)messageChannel).isNsfw())
                    embed = EmbedCreateSpec.builder()
                            .title(redditPost.title)
                            .url(redditPost.link)
                            .color(Color.MOON_YELLOW)
                            .image(redditPost.url)
                            .footer(EmojiParser.parseToUnicode(String.format("%d:thumbsup: • by %s • from r/%s", redditPost.upvotes, redditPost.author, redditPost.sub)), user.getAvatarUrl())
                            .timestamp(Instant.now())
                            .build();
                else embed = buildWarningEmbed("You need to be in a NSFW-Channel in order to use this Feature!", false);
                event.editReply().withEmbeds(embed).subscribe();
            }));
            return;
        }).start());
        return Mono.empty();
    }
}
