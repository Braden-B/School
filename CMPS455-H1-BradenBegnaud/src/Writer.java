import java.util.Random;

public class Writer implements Runnable {
    private final int maxReaders;
    private final Random random = new Random();

    public Writer(int maxReaders) {
        this.maxReaders = maxReaders;
    }


    @Override
    public void run() {
        int timer;
        System.out.println(Thread.currentThread().getName() + " I can't wait to begin writing!");
        while (true) {
            if (Main.activeReaders.isEmpty() && Main.readerWriterSemaphore.get(1).availablePermits() == maxReaders) {
                if (Main.readerWriterSemaphore.getFirst().availablePermits() == 1) {
                    if (Main.readerWriterSemaphore.getFirst().tryAcquire()) {
                        System.out.println(Thread.currentThread().getName() + "Writer check success!");
                        timer = (random.nextInt() % 4) + 3;
                        while (timer > 0) {
                            System.out.println(Thread.currentThread().getName() + "is taking it's turn writing.");
                            timer--;
                        }
                        Main.activeReaders = Main.waitingReaders;
                        Main.waitingReaders.clear();
                        Main.readerWriterSemaphore.getFirst().release();
                    }
                }
                }
            }
        }
    }
