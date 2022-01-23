package utils;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.stream.Collectors;

public class fileUtils {
    public static String readFileAsString(String fileName)throws Exception
    {
        String data;
        if(!Files.exists(Paths.get(fileName))) Files.createFile(Paths.get(fileName));
        data = new String(Files.readAllBytes(Paths.get(fileName)));
        return data;
    }
    public static String getResourceFileAsString(String fileName) throws IOException {
        ClassLoader classLoader = ClassLoader.getSystemClassLoader();
        try (InputStream resourceAsStream = classLoader.getResourceAsStream(fileName)) {
            if (resourceAsStream == null) return null;
            try (InputStreamReader inputStreamReader = new InputStreamReader(resourceAsStream);
                 BufferedReader reader = new BufferedReader(inputStreamReader)) {
                return reader.lines().collect(Collectors.joining(System.lineSeparator()));
            }
        }
    }
}
