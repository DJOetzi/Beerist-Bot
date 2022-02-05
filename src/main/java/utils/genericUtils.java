package utils;

import java.util.List;

public class genericUtils {
    public static String characterListToString(List<Character> characterList){
        return characterList.toString().replace("[", "").replace(",","").replace("]", "").replace(" ", "");
    }
}
