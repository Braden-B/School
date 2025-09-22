
import java.util.Random;

public class Philosopher implements Runnable {
    private boolean holdingLeftChopstick;
    private boolean holdingRightChopstick;
    private final int leftChopstick;
    private final int rightChopstick;
    private final Random random = new Random();
    private final int numPhilosophers;

    public Philosopher(int position, int numPhilosophers) {
        this.holdingLeftChopstick = false;
        this.holdingRightChopstick = false;
        this.leftChopstick = position;
        this.rightChopstick = (position + 1) % numPhilosophers;
        this.numPhilosophers = numPhilosophers;

    }

    @Override
    public void run() {
        System.out.println(Thread.currentThread().getName() + "Hello! I shall sit at seat number " + leftChopstick);
        Main.activePhilosophers++;
        if (Main.activePhilosophers != numPhilosophers){
            try {
                Thread.sleep(15000);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }else {
            Thread.currentThread().notifyAll();
        }
        while (Main.meals.peek() != null) {
            if (holdingRightChopstick && holdingLeftChopstick) {
                if (Main.mutex) {
                    continue;
                }
                Main.mutex = true;
                Main.chopsticks.get(leftChopstick).release();
                holdingLeftChopstick = false;
                Main.chopsticks.get(rightChopstick).release();
                holdingRightChopstick = false;
            }
            if (Main.mutex) {
                continue;
            }
            else {
                Main.mutex = true;
                holdingLeftChopstick = Main.chopsticks.get(leftChopstick).tryAcquire();
                if (holdingLeftChopstick) {
                    System.out.println(Thread.currentThread().getName() + "Wonderful! A left chopstick. Now I merely need the right...");
                    holdingRightChopstick = Main.chopsticks.get(rightChopstick).tryAcquire();
                    if (!holdingRightChopstick) {
                        System.out.println(Thread.currentThread().getName() + "Oh how rude of me. Please, do eat. I shall wait my turn.");
                        Main.chopsticks.get(leftChopstick).release();
                        holdingLeftChopstick = false;
                        Main.mutex = false;
                    }
                } else {
                    System.out.println(Thread.currentThread().getName() + "Oh how rude of me. Please, do eat. I shall wait my turn.");
                    Main.mutex = false;
                    continue;
                }
                Main.mutex = false;
            }
            if (holdingRightChopstick && holdingLeftChopstick) {
                System.out.println(Thread.currentThread().getName() + "Two chopsticks! I simply cannot wait to take a bite.");
                int timer;
                if (Main.meals.poll() != null) {
                    System.out.println(Thread.currentThread().getName() + "Ah! A delectable morsel.");
                    timer = (random.nextInt() % 4) + 3;
                    while (timer > 0) {
                        System.out.println(Thread.currentThread().getName() + "is politely enjoying a bite.");
                        timer--;
                    }
                    Main.chopsticks.get(leftChopstick).release();
                    System.out.println(Thread.currentThread().getName() + "No need for this left chopstick, I've had my share for now.");
                    holdingLeftChopstick = false;
                    Main.chopsticks.get(rightChopstick).release();
                    System.out.println(Thread.currentThread().getName() + "And this right one shall return to the table as well.");
                    holdingRightChopstick = false;
                    System.out.println(Thread.currentThread().getName() + "That was delicious. I shall think upon the flavors.");
                } else {
                    try {
                        Thread.currentThread().join();
                    } catch (InterruptedException e) {
                        throw new RuntimeException(e);
                    }
                }
                timer = (random.nextInt() % 4) + 3;
                Main.mutex = false;
                while (timer > 0) {
                    System.out.println(Thread.currentThread().getName() + "is pondering on the various flavors.");
                    timer--;
                }
            }
        }
        try {
            System.out.println(Thread.currentThread().getName() + "No more meals, a sad occurrence. I shall wait for the rest to finish.");
            Thread.currentThread().join();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }
}
