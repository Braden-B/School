import java.util.Random;

public class Reader implements Runnable {
    private final Random random = new Random();
    private final int maxReaders;

    public Reader(int maxReaders) {
        this.maxReaders = maxReaders;
    }

    @Override
    public void run() {
        int timer;
        System.out.println(Thread.currentThread().getName() + "I can't wait to start reading!");
        while (true) {
            try {
                Main.countdownMutex.acquire();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }

            if (!Main.readerWriterSemaphore.get(1).tryAcquire()) {
                Main.countdownMutex.release();
                continue;
            }

            if (Main.readCount == maxReaders) {
                Main.countdownMutex.release();
                Main.readerWriterSemaphore.get(1).release();
                continue;
            }

            Main.readCount++;
            Main.countdownMutex.release();
            timer = (random.nextInt() % 4) + 3;
            System.out.println(Thread.currentThread().getName() + "is taking it's turn reading.");
            while (timer > 0) {
                timer--;
            }
            Main.readerWriterSemaphore.get(1).release();
        }
    }
}
