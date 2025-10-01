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
            if (!(Main.readCount == maxReaders)){
                continue;
            }
            if(!Main.readerWriterSemaphore.get(0).tryAcquire()){
                continue;
            }
            timer = (random.nextInt() % 4) + 3;
            System.out.println(Thread.currentThread().getName() + "is taking it's turn writing.");
            while (timer > 0) {
                timer--;
            }
            Main.readCount = 0;
            Main.readerWriterSemaphore.get(0).release();
        }
    }
}
