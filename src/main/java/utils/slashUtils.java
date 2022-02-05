package utils;

import com.google.gson.JsonArray;
import discord4j.common.JacksonResources;
import discord4j.discordjson.json.ApplicationCommandRequest;

import java.io.IOException;

import static utils.fileUtils.getResourceFileAsString;
import static utils.fileUtils.readFileAsString;

public class slashUtils {
    public static ApplicationCommandRequest buildSlashCommand(String jsonData) throws IOException {
        return JacksonResources.create().getObjectMapper().readValue(jsonData, ApplicationCommandRequest.class);
    }
    public static ApplicationCommandRequest buildSlashCommandFromResource(String filePath) throws IOException{
        return buildSlashCommand(getResourceFileAsString(filePath));
    }
    public static ApplicationCommandRequest[] commandLoaderFromResources(String path, JsonArray commandRegistry) throws Exception {
        ApplicationCommandRequest[] commands = new ApplicationCommandRequest[commandRegistry.size()];
        for(int i=0; i<commandRegistry.size(); i++){
            commands[i] = buildSlashCommandFromResource(String.format("%s%s", path, commandRegistry.get(i).getAsString()));
        }
        return commands;
    }
}
