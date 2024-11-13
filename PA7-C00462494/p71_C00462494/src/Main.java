// Braden Begnaud
// C00462494
// CMPS 261
// Program Description: This program is meant to display every word used in "Frankenstein" in ascending order.
// Certificate of Authenticity:
// I certify that the code in the method functions
// including method function main of this project are
// entirely my own work.

import java.io.File;
import java.util.Iterator;
import java.util.Scanner;
import java.util.Set;
import java.util.TreeSet;

public class Main {

    public static void main(String[] args) {
        Set<String> words = new TreeSet<>();
        // Makes a set then just adds every word found in the text document to it. Duplicates aren't added by default
        try (Scanner scanner = new Scanner(new File("fstein.txt"))) {
            while (scanner.hasNextLine()) {
                words.add(scanner.nextLine());
            }
        }
        catch (Exception e) {
            System.out.println("File not found");
        }
        // Creates an interator and prints out everything in the set. 
            Iterator<String> wordsIterator = words.iterator();
            while(wordsIterator.hasNext()) {
                System.out.println(wordsIterator.next());
            }
        }

    }
