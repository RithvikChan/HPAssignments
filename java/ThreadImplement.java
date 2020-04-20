public class ThreadImplement implements Runnable{

	public Integer tnum;
	public ThreadImplement(Integer name){
		tnum = name;
	}
	public void run(){
		System.out.println(this.tnum);
	}

	public static void main(String[] args) throws InterruptedException {
		Thread t1 = new Thread(new ThreadImplement(1), "thread1");
		Thread t2 = new Thread(new ThreadImplement(2), "thread2");
		Thread t3 = new Thread(new ThreadImplement(3), "thread3");
		Thread t4 = new Thread(new ThreadImplement(4), "thread4");
		Thread t5 = new Thread(new ThreadImplement(5), "thread5");
		t1.start();
		t2.start();
		t3.start();
		t4.start();
		t5.start();
		
	}
}
