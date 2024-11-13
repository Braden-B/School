// Braden Begnaud
// C00462494
// CMPS 261
// Program Description: This program accesses a website to pull data from, depending on year, gender, and the name all given
// by the user. It puts these in a map, then lets you search for a name and its ranking in terms of usage.
// Certificate of Authenticity:
//        I certify that the code in the method functions
//        including method function main of this project are
//        entirely my own work.

import java.net.URL;
import java.util.Map;
import java.util.Scanner;
import java.util.TreeMap;

public class Main {

    public static void main(String[] args) {
        int position = 0;
        String boyName;
        String girlName;
        TreeMap[] boysArr = new TreeMap[10];
        TreeMap[] girlsArr = new TreeMap[10];
        TreeMap<String, Integer> boysMap = new TreeMap<>();
        TreeMap<String, Integer> girlsMap = new TreeMap<>();
        Scanner userInput = new Scanner(System.in);
        int year = 0;
        // The loop here makes sure the year is between 2000 and 2011
        while (year < 2001 || year > 2010) {
            System.out.println("Which year are you searching in [2001-2010]: ");
            year = userInput.nextInt();
            if (year > 2000 && year < 2011) {
                break;
            } else
                System.out.println("Please enter a valid year.");
        }
        int yearAdd = 2001;
        String website = "https://liveexample.pearsoncmg.com/data/babynameranking" + yearAdd + ".txt";

        System.out.println("Loading names...");
        // This set of loops and a try statement assigns the names to the maps for the appropriate year. It then adds them all to an array to be searched.

        while (yearAdd < 2010) {
            try (Scanner input = new Scanner(new java.net.URL(website).openStream())) {
                while (input.hasNextLine()) {
                    input.next();
                    position++;
                    boyName = input.next();
                    input.next();
                    girlName = input.next();
                    input.next();
                    boysMap.put(boyName, position);
                    girlsMap.put(girlName, position);

                }
                // This switch statement assigns the map to the appropriate year to be added to the array. I couldn't figure out how to reuse one and copy
                // it to array indices so this mess was created.
                switch (yearAdd) {
                    case 2001:
                        TreeMap<String, Integer> boysMap2001 = new TreeMap<String, Integer>();
                        boysMap2001.putAll(boysMap);
                        TreeMap<String, Integer> girlsMap2001 = new TreeMap<String, Integer>();
                        girlsMap2001.putAll(girlsMap);
                        boysArr[yearAdd - 2001] = boysMap2001;
                        girlsArr[yearAdd - 2001] = girlsMap2001;
                        break;
                    case 2002:
                        TreeMap<String, Integer> boysMap2002 = new TreeMap<String, Integer>();
                        boysMap2002.putAll(boysMap);
                        TreeMap<String, Integer> girlsMap2002 = new TreeMap<String, Integer>();
                        girlsMap2002.putAll(girlsMap);
                        boysArr[yearAdd - 2001] = boysMap2002;
                        girlsArr[yearAdd - 2001] = girlsMap2002;
                        break;
                    case 2003:
                        TreeMap<String, Integer> boysMap2003 = new TreeMap<String, Integer>();
                        boysMap2003.putAll(boysMap);
                        TreeMap<String, Integer> girlsMap2003 = new TreeMap<String, Integer>();
                        girlsMap2003.putAll(girlsMap);
                        boysArr[yearAdd - 2001] = boysMap2003;
                        girlsArr[yearAdd - 2001] = girlsMap2003;
                        break;
                    case 2004:
                        TreeMap<String, Integer> boysMap2004 = new TreeMap<String, Integer>();
                        boysMap2004.putAll(boysMap);
                        TreeMap<String, Integer> girlsMap2004 = new TreeMap<String, Integer>();
                        girlsMap2004.putAll(girlsMap);
                        boysArr[yearAdd - 2001] = boysMap2004;
                        girlsArr[yearAdd - 2001] = girlsMap2004;
                        break;
                    case 2005:
                        TreeMap<String, Integer> boysMap2005 = new TreeMap<String, Integer>();
                        boysMap2005.putAll(boysMap);
                        TreeMap<String, Integer> girlsMap2005 = new TreeMap<String, Integer>();
                        girlsMap2005.putAll(girlsMap);
                        boysArr[yearAdd - 2001] = boysMap2005;
                        girlsArr[yearAdd - 2001] = girlsMap2005;
                        break;
                    case 2006:
                        TreeMap<String, Integer> boysMap2006 = new TreeMap<String, Integer>();
                        boysMap2006.putAll(boysMap);
                        TreeMap<String, Integer> girlsMap2006 = new TreeMap<String, Integer>();
                        girlsMap2006.putAll(girlsMap);
                        boysArr[yearAdd - 2001] = boysMap2006;
                        girlsArr[yearAdd - 2001] = girlsMap2006;
                        break;
                    case 2007:
                        TreeMap<String, Integer> boysMap2007 = new TreeMap<String, Integer>();
                        boysMap2007.putAll(boysMap);
                        TreeMap<String, Integer> girlsMap2007 = new TreeMap<String, Integer>();
                        girlsMap2007.putAll(girlsMap);
                        boysArr[yearAdd - 2001] = boysMap2007;
                        girlsArr[yearAdd - 2001] = girlsMap2007;
                        break;
                    case 2008:
                        TreeMap<String, Integer> boysMap2008 = new TreeMap<String, Integer>();
                        boysMap2008.putAll(boysMap);
                        TreeMap<String, Integer> girlsMap2008 = new TreeMap<String, Integer>();
                        girlsMap2008.putAll(girlsMap);
                        boysArr[yearAdd - 2001] = boysMap2008;
                        girlsArr[yearAdd - 2001] = girlsMap2008;
                        break;
                    case 2009:
                        TreeMap<String, Integer> boysMap2009 = new TreeMap<String, Integer>();
                        boysMap2009.putAll(boysMap);
                        TreeMap<String, Integer> girlsMap2009 = new TreeMap<String, Integer>();
                        girlsMap2009.putAll(girlsMap);
                        boysArr[yearAdd - 2001] = boysMap2009;
                        girlsArr[yearAdd - 2001] = girlsMap2009;
                        break;
                    case 2010:
                        TreeMap<String, Integer> boysMap2010 = new TreeMap<String, Integer>();
                        boysMap2010.putAll(boysMap);
                        TreeMap<String, Integer> girlsMap2010 = new TreeMap<String, Integer>();
                        girlsMap2010.putAll(girlsMap);
                        boysArr[yearAdd - 2001] = boysMap2010;
                        girlsArr[yearAdd - 2001] = girlsMap2010;
                        break;
                }
                if (yearAdd < 2010) yearAdd++;
                position = 0;
                website = "https://liveexample.pearsoncmg.com/data/babynameranking" + yearAdd + ".txt";
                boysMap.clear();
                girlsMap.clear();
            } catch (Exception e) {
                System.out.println("Uh-oh.");
            }
        }
            System.out.println("What is the gender of the name you want to search for? (Boy or Girl)");
            String gender = userInput.next().toLowerCase();
            userInput.nextLine();
            System.out.println("What name would you like to search for? (Ensure spelling and capitals are correct)");
            String nameSearch = userInput.next();
            int ranking = 0;
            // These if statements select the appropriate gender and year to search.
            if (gender.equals("boy")) {

                if (boysArr[year - 2001].containsKey(nameSearch)) {
                    ranking = (int) boysArr[year - 2001].get(nameSearch);
                    System.out.println("That name is at place " + ranking);
                } else
                    System.out.println("That name is not in the selected year");
            } else if (gender.equals("girl")) {
                if (girlsArr[year - 2001].containsKey(nameSearch)) {
                    ranking = (int) girlsArr[year - 2001].get(nameSearch);
                    System.out.println("That name is at place " + ranking);
                } else
                    System.out.println("That name is not in the selected year");
            }


        }
    }


