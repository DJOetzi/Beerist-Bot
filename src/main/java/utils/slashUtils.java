package utils;

import discord4j.common.JacksonResources;
import discord4j.discordjson.json.ApplicationCommandRequest;

import java.io.File;
import java.io.IOException;

import static utils.fileUtils.*;

public class slashUtils {
    public static ApplicationCommandRequest buildSlashCommand(String jsonData) throws IOException {
        return JacksonResources.create().getObjectMapper().readValue(jsonData, ApplicationCommandRequest.class);
    }
    public static ApplicationCommandRequest buildSlashCommandFromResource(String filePath) throws IOException{
        return buildSlashCommand(getResourceFileAsString(filePath));
    }
    public static ApplicationCommandRequest[] commandLoaderFromResources(String path) throws IOException {
        File[] commandData = getResourceFolderFiles(path);
        ApplicationCommandRequest[] commands = new ApplicationCommandRequest[commandData.length];
        for(int i=0; i<commandData.length; i++){
            commands[i] = buildSlashCommand(readFromFile(commandData[i]));
        }
        return commands;
    }
}
