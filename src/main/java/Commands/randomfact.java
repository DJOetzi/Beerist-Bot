package Commands;

import com.google.gson.Gson;
import com.google.gson.JsonObject;
import discord4j.core.event.domain.interaction.ChatInputInteractionEvent;
import discord4j.core.spec.EmbedCreateSpec;
import discord4j.rest.util.Color;
import reactor.core.publisher.Mono;

import java.io.IOException;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.time.Instant;

public class randomfact {
    public static Mono<Void> exec(ChatInputInteractionEvent event){
        event.deferReply().subscribe();

        new Thread(() ->{
            URI uri = URI.create("https://uselessfacts.jsph.pl/random.json?language=en");

            HttpRequest request = HttpRequest.newBuilder(uri).build();
            String content = null;
            try {
                content = HttpClient.newHttpClient().send(request, HttpResponse.BodyHandlers.ofString()).body();
            }
            catch (IOException | InterruptedException e) {
                e.printStackTrace();
            }

            JsonObject responseData = new Gson().fromJson(content, JsonObject.class);

            EmbedCreateSpec embed = EmbedCreateSpec.builder()
                    .title("useless fact for ya".toUpperCase())
                    .color(Color.MOON_YELLOW)
                    .url(responseData.get("permalink").getAsString())
                    .addField("did you know...", responseData.get("text").getAsString(), false)
                    .timestamp(Instant.now())
                    .build();
            event.editReply().withEmbeds(embed).subscribe();
        }).start();

        return Mono.empty();
    }
}
