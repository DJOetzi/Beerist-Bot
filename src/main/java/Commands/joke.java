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

public class joke {
    public static Mono<Void> exec(ChatInputInteractionEvent event){
        event.deferReply().subscribe();

        new Thread(() ->{
            URI uri = URI.create("https://v2.jokeapi.dev/joke/Programming,Miscellaneous,Pun,Spooky,Christmas?blacklistFlags=nsfw,religious,racist,sexist&safe-mode");

            HttpRequest request = HttpRequest.newBuilder(uri).build();
            String content = null;
            try {
                content = HttpClient.newHttpClient().send(request, HttpResponse.BodyHandlers.ofString()).body();
            }
            catch (IOException | InterruptedException e) {
                e.printStackTrace();
            }

            JsonObject responseData = new Gson().fromJson(content, JsonObject.class);

            String joke = (!responseData.get("type").getAsString().equals("single")) ? String.format("%s\n||%s||", responseData.get("setup").getAsString(), responseData.get("delivery").getAsString()) : String.format("%s", responseData.get("joke").getAsString());

            EmbedCreateSpec embed = EmbedCreateSpec.builder()
                    .color(Color.MOON_YELLOW)
                    .addField(String.format("Category: %s", responseData.get("category").getAsString()), joke, false)
                    .timestamp(Instant.now())
                    .build();
            event.editReply().withEmbeds(embed).subscribe();
        }).start();

        return Mono.empty();
    }
}
