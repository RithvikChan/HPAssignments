public class InterruptThread implements Runnable {
	int name;
	public InterruptThread(int num){
		name = num;
	}
    public void run() {
        try {
            Thread.sleep(10000);
        } catch (InterruptedException e) {
            System.out.println("Interrupting thread"+ this.name);
        }
    }
    public static void main(String[] args) throws InterruptedException {
        Thread myThread = new Thread(new InterruptThread(1), "myThread");
        myThread.start();

        System.out.println("Sleeping in main thread for 2s...");
        Thread.sleep(2000);

        myThread.interrupt();
    }
}
