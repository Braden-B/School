import java.util.*;
import java.util.concurrent.Semaphore;


public class Main {

    public static List<Semaphore> chopsticks = new ArrayList<>();
    public static boolean mutex = false;
    public static Queue<Integer> meals = new LinkedList<>();
    public static boolean validateInteger(String testValue, boolean mealFlag){
        if (!testValue.matches("\\d{1,4}")){ // Originally I used a try catch statement with parseInt() but the exception crashed everything. Proud of this solution, as it also limits characters
            return false;
        }
        if (!mealFlag) {
            return Integer.parseInt(testValue) <= 1;
        }
        else {
            return Integer.parseInt(testValue) <= 0;
        }
    }

    public static void main(String[] args) {
        System.out.println("Hello. How many philosophers should be created? (1-9999): ");
        Scanner sc = new Scanner(System.in);
        String input = sc.nextLine();
        while(validateInteger(input, false)){
            System.out.println("Invalid Input. Use a whole number of range 1-9999.");
            System.out.println("Hello. How many philosophers should be created?: ");
            input = sc.nextLine();
        }
        int numPhilosophers = Integer.parseInt(input);
        System.out.println("How many meals should they get? (2-9999): ");
        input = sc.nextLine();
        while(validateInteger(input, true)){
            System.out.println("Invalid Input. Use a whole number of range 0-9999.");
            System.out.println("How many meals should they get?: ");
            input = sc.nextLine();
        }
        int numMeals = Integer.parseInt(input);
        for (int i = 1; i <= numPhilosophers; i++) {
            chopsticks.add(new Semaphore(1));
        }
        for (int i = 0; i < numMeals; i++) {
            meals.add(1);
        }
        System.out.println("Creating philosophers...");
        for(int i = 0; i < numPhilosophers; i++){
            Thread thread = new Thread(new Philosopher(i, numPhilosophers), "Philosopher " + i + ": ");
            thread.start();
        }
    }
}