import java.util.Random; 

public class ThreadJoin implements Runnable {

    int num;
    ThreadJoin(int numb){
		num = numb;	
	}
	@Override
    public void run() 
    {
		System.out.println("Doing thread"+this.num);
          
    }


    public static void main(String[] args) throws InterruptedException
    {
        Thread[] threads = new Thread[5];
        
        for(int i=0; i<5; i++) {
            threads[i] = new Thread(new ThreadJoin(i+1), "Thread "+i);
        }


        for(int i=0; i<5; i++) {
            threads[i].start();
        }
        
        for(int i=0; i<5; i++) 
        {
            threads[i].join();
        }
        
        System.out.println("All threads done");
    }

}
