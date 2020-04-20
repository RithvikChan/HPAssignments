import java.util.Random;
import java.io.*; 
import java.util.*; 

public class Balance implements Runnable{
	private static int balance = 0;
	private int sync = 0;
	public Integer db;
	public Balance(Integer nums){
		db = nums;
	}
	
	@Override
	public void run(){
		if(this.db == 0){
			this.deposit();
		}
		else{
			this.withdraw();
		}
	}

	public void deposit() {
		synchronized (this) {
			Random rand = new Random();
			int rands = rand.nextInt(1000);
			System.out.println("Depositing:"+rands);
			balance += rands;
			System.out.println("Total:"+balance);
						
		}
	}

	public void withdraw() {
		synchronized (this) {
			Random rand = new Random();
			int rands = rand.nextInt(1000);
			System.out.println("Withdrawing:"+rands);
			balance -= rands;
			System.out.println("Total:"+balance);
		}
	}

	public static void main(String[] args) throws InterruptedException {
		Thread d1 = new Thread(new Balance(0), "thread1");
		Thread d2 = new Thread(new Balance(0), "thread2");
		Thread w1 = new Thread(new Balance(1), "thread3");
		Thread w2 = new Thread(new Balance(1), "thread4");
		Thread d3 = new Thread(new Balance(0), "thread5");
		d1.start();
		d2.start();
		w1.start();
		w2.start();
		d3.start();
	}
	
}
