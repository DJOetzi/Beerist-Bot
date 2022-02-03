package utils;

import com.google.gson.Gson;
import com.google.gson.JsonObject;
import reactor.core.publisher.Mono;

public class redditUtils {
    public static class redditPost {
       public String author, title, url, link, sub;
       public Boolean nsfw;
       public int upvotes;
    }

    public static Mono<String> buildString(redditPost post){
        String template = """
                {
                  "author": "%s",
                  "title": "%s",
                  "url": "%s",
                  "postLink": "%s",
                  "subreddit": "%s",
                  "nsfw": "%s",
                  "ups": "%d"
                }""";
        return Mono.just(String.format(template, post.author, post.title, post.url, post.link, post.sub, post.nsfw, post.upvotes));
    }

    public static Mono<redditPost> buildPost(String source){
        JsonObject parsed = new Gson().fromJson(source, JsonObject.class);
        redditPost post = new redditPost();

        post.author = parsed.get("author").getAsString();
        post.title = parsed.get("title").getAsString();
        post.url = parsed.get("url").getAsString();
        post.link = parsed.get("postLink").getAsString();
        post.sub = parsed.get("subreddit").getAsString();
        post.nsfw = parsed.get("nsfw").getAsBoolean();
        post.upvotes = parsed.get("ups").getAsInt();

        return Mono.just(post);
    }
}
