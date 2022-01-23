package utils;

import discord4j.common.JacksonResources;
import discord4j.discordjson.json.ApplicationCommandRequest;

import java.io.IOException;

public class slashUtils {
    public static ApplicationCommandRequest buildSlashCommand(String jsonData) throws IOException {
        return JacksonResources.create().getObjectMapper().readValue(jsonData, ApplicationCommandRequest.class);
    }
}
