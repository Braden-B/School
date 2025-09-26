import java.util.*;
import java.util.concurrent.Semaphore;


public class Main {

    public static List<Semaphore> semaphores = new ArrayList<>();
    public static boolean mutex = false;
    public static boolean chairsMutex = false;
    public static Queue<Integer> resource = new LinkedList<>();
    public static int activePhilosophers = 0;
    public static boolean sittingFlag = false;
    public static ArrayList<Thread> occupiedChairs = new ArrayList<>();
    public static Scanner sc = new Scanner(System.in);
    public static String input;

    public static ArrayList<Reader> activeReaders = new ArrayList<>();
    public static ArrayList<Reader> waitingReaders = new ArrayList<>();
    public static List<Semaphore>  readerWriterSemaphore = new ArrayList<>();
    public static Semaphore countdownMutex = new Semaphore(1);

    public static boolean validateInteger(String testValue, boolean singleFlag) {
        if (!testValue.matches("\\d{1,4}")) { // Originally I used a try catch statement with parseInt() but the exception crashed everything. Proud of this solution, as it also limits characters
            return true;
        }
        if (!singleFlag) {
            return Integer.parseInt(testValue) <= 1;
        } else {
            return Integer.parseInt(testValue) <= 0;
        }
    }

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: java Main <input> (acceptable values are 1 or 2)");
            input = sc.nextLine();
        }
        else {
            while (!args[0].equals("1") && !args[0].equals("2")) {
                System.out.println("Your argument was incorrect. It must match \"1\" or \"2\". Not matching these " +
                        "will not allow the program to run.");
                System.out.println("Enter the argument to use: ");
                input = sc.nextLine();
                args[0] = input;
            }
        }
        if (args[0].equals("1")) {

            System.out.println("Hello. How many philosophers should be created? (2-9999): ");
            input = sc.nextLine();
            while (validateInteger(input, false)) {
                System.out.println("Invalid Input. Use a whole number of range 2-9999.");
                System.out.println("Hello. How many philosophers should be created?: ");
                input = sc.nextLine();
            }
            int numPhilosophers = Integer.parseInt(input);
            System.out.println("How many meals should they get? (1-9999): ");
            input = sc.nextLine();
            while (validateInteger(input, true)) {
                System.out.println("Invalid Input. Use a whole number of range 1-9999.");
                System.out.println("How many meals should they get?: ");
                input = sc.nextLine();
            }
            int numMeals = Integer.parseInt(input);
            long start_time = System.currentTimeMillis();
            for (int i = 1; i <= numPhilosophers; i++) {
                semaphores.add(new Semaphore(1));
            }
            for (int i = 0; i < numMeals; i++) {
                resource.add(1);
            }
            System.out.println("Creating philosophers...");
            for (int i = 0; i < numPhilosophers; i++) {
                Thread thread = new Thread(new Philosopher(i, numPhilosophers), "Philosopher " + i + ": ");
                occupiedChairs.add(thread);
            }
            for (Thread occupiedChair : occupiedChairs) {
                sittingFlag = true;
                occupiedChair.start();
                activePhilosophers++;
            }
            while(!occupiedChairs.isEmpty()) {
            }
            long end_time = System.currentTimeMillis();
            System.out.println("Time taken: " + (end_time - start_time) + " ms");
        }
        if (args[0].equals("2")) {
            System.out.println("Hello. How many readers should be created? (1-9999): ");
            input = sc.nextLine();
            while (validateInteger(input, true)) {
                System.out.println("Invalid Input. Use a whole number of range 1-9999.");
                System.out.println("How many readers should be created?: ");
                input = sc.nextLine();
            }
            int numReaders = Integer.parseInt(input);
            System.out.println("How many writers should be created? (1-9999): ");
            input = sc.nextLine();
            while (validateInteger(input, true)) {
                System.out.println("Invalid Input. Use a whole number of range 1-9999.");
                System.out.println("How many writers should be created?: ");
                input = sc.nextLine();
            }
            int numWriters = Integer.parseInt(input);
            System.out.println("How many readers should be able to read simultaneously?: ");
            input = sc.nextLine();
            while (validateInteger(input, true)) {
                System.out.println("Invalid Input. Use a whole number of range 1-9999.");
                System.out.println("How many readers should be able to read simultaneously?: ");
                input = sc.nextLine();
            }
            int maxReaders = Integer.parseInt(input);
            readerWriterSemaphore.add(new Semaphore(1));
            readerWriterSemaphore.add(new Semaphore(maxReaders));
            for (int i = 0; i < numWriters; i++) {
                Thread thread = new Thread(new Writer(maxReaders), "Writer " + i + ": ");
                thread.start();
            }
            for (int i = 0; i < numReaders; i++) {
                Thread thread = new Thread(new Reader(), "Reader " + i + ": ");
                thread.start();
            }
        }
    }
}