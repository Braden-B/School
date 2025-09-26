
import java.util.Random;

public class Philosopher implements Runnable {
    private boolean holdingLeftChopstick;
    private boolean holdingRightChopstick;
    private final int leftChopstick;
    private final int rightChopstick;
    private final Random random = new Random();
    private int mealsEaten;

    public Philosopher(int position, int numPhilosophers) {
        this.holdingLeftChopstick = false;
        this.holdingRightChopstick = false;
        this.leftChopstick = position;
        this.rightChopstick = (position + 1) % numPhilosophers;

    }

    @Override
    public void run() {
        System.out.println(Thread.currentThread().getName() + "Hello! I shall sit at seat number " + leftChopstick);

        while (Main.sittingFlag) {
            if (Main.resource.peek() == null) {
                if (!Main.chairsMutex) {
                    if (Main.occupiedChairs.size() != 1) {
                        System.out.println(Thread.currentThread().getName() + "A wonderful gathering. I shall wait for my " +
                                "friends to leave.");
                        try {
                            Main.occupiedChairs.remove(Thread.currentThread());
                            Main.activePhilosophers--;
                            Main.occupiedChairs.getLast().join();
                            break;
                        } catch (InterruptedException e) {
                            throw new RuntimeException(e);
                        }
                    }
                }

                if (Main.activePhilosophers == 0) {
                    Main.sittingFlag = false;
                }
                break;
            }
            if (holdingRightChopstick && holdingLeftChopstick) {
                if (Main.mutex) {
                    continue;
                }
                Main.mutex = true;
                Main.semaphores.get(leftChopstick).release();
                holdingLeftChopstick = false;
                Main.semaphores.get(rightChopstick).release();
                holdingRightChopstick = false;
            }
            if (Main.mutex) {
                continue;
            } else {
                Main.mutex = true;
                holdingLeftChopstick = Main.semaphores.get(leftChopstick).tryAcquire();
                if (holdingLeftChopstick) {
                    System.out.println(Thread.currentThread().getName() + "Wonderful! A left chopstick. Now I merely " +
                            "need the right...");
                    holdingRightChopstick = Main.semaphores.get(rightChopstick).tryAcquire();
                    if (!holdingRightChopstick) {
                        System.out.println(Thread.currentThread().getName() + "Oh how rude of me. Please, do eat. I " +
                                "shall wait my turn.");
                        Main.semaphores.get(leftChopstick).release();
                        holdingLeftChopstick = false;
                        Main.mutex = false;
                    }
                } else {
                    System.out.println(Thread.currentThread().getName() + "Oh how rude of me. Please, do eat. I shall " +
                            "wait my turn.");
                    Main.mutex = false;
                    continue;
                }
                Main.mutex = false;
            }
            if (holdingRightChopstick && holdingLeftChopstick) {
                System.out.println(Thread.currentThread().getName() + "Two chopsticks! I simply cannot wait to take " +
                        "a bite.");
                int timer;
                if (Main.resource.poll() != null) {
                    System.out.println(Thread.currentThread().getName() + "Ah! A delectable morsel.");
                    mealsEaten++;
                    timer = (random.nextInt() % 4) + 3;
                    while (timer > 0) {
                        System.out.println(Thread.currentThread().getName() + "is politely enjoying a bite.");
                        timer--;
                    }
                    Main.semaphores.get(leftChopstick).release();
                    System.out.println(Thread.currentThread().getName() + "No need for this left chopstick, I've had " +
                            "my share for now.");
                    holdingLeftChopstick = false;
                    Main.semaphores.get(rightChopstick).release();
                    System.out.println(Thread.currentThread().getName() + "And this right one shall return to the " +
                            "table as well.");
                    holdingRightChopstick = false;
                    System.out.println(Thread.currentThread().getName() + "That was delicious. I shall think upon the " +
                            "flavors.");
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
            System.out.println(Thread.currentThread().getName() + "A wonderful gathering. I shall wait for my " +
                    "friends to leave.");
            if (Main.occupiedChairs.size() != 1 && !Main.chairsMutex) {
                Main.occupiedChairs.remove(Thread.currentThread());
                Main.occupiedChairs.getLast().join();
            }
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        System.out.println(Thread.currentThread().getName() + "I ate " + mealsEaten + " meals. I hope I had a fair " +
                "share. Goodbye all!");
    }
}
