import java.util.Random;

public class Reader implements Runnable {
    private final Random random = new Random();

    public Reader() {

    }


    @Override
    public void run() {
        int timer;
        System.out.println(Thread.currentThread().getName() + "I can't wait to start reading!");
        try {
            Main.countdownMutex.acquire();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        Main.activeReaders.add(this);
        Main.countdownMutex.release();
        while (true) {
            try {
                if (Main.activeReaders.contains(this)) {
                    Main.readerWriterSemaphore.get(1).acquire();
                    if (Main.countdownMutex.tryAcquire()) {
                        timer = (random.nextInt() % 4) + 3;
                        System.out.println(Thread.currentThread().getName() + "is taking it's turn reading.");
                        while (timer > 0) {
                            timer--;
                        }
                        Main.activeReaders.remove(this);
                        Main.waitingReaders.add(this);
                        System.out.println(Thread.currentThread().getName() + "Countdown decremented.");
                        Main.countdownMutex.release();
                        System.out.println(Thread.currentThread().getName() + "What a nice section. I can't wait to see more.");
                    }
                    Main.readerWriterSemaphore.get(1).release();
                }
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }

        }
    }
}


