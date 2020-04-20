public class ThreadExtend extends Thread {

	public Integer nums;
	public ThreadExtend(Integer name){
		nums = name;
	}
	
	@Override
	public void run(){
		System.out.println(this.nums);	
	}
	public static void main(String args[]){
		ThreadExtend t1 = new ThreadExtend(1);
		ThreadExtend t2 = new ThreadExtend(2);
		ThreadExtend t3 = new ThreadExtend(3);
		ThreadExtend t4 = new ThreadExtend(4);
		ThreadExtend t5 = new ThreadExtend(5);
		ThreadExtend t6 = new ThreadExtend(6);
		ThreadExtend t7 = new ThreadExtend(7);
		ThreadExtend t8 = new ThreadExtend(8);
		t1.start();
		t2.start();
		t3.start();
		t4.start();
		t5.start();
		t6.start();
		t7.start();
		t8.start();
	}
}
