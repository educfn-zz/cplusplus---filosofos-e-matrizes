/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package messagesystem;

/**
 *
 * @author mpiva
 */

import java.util.ArrayList;
import java.util.List;

class MessageQueue {
    
    //the size of the buffer
    private int bufferSize;
    
    //the buffer list of the message, assuming the string message format
    private List<String> buffer = new ArrayList<>();
    
    //construct the message queue with given buffer size
    public MessageQueue(int bufferSize){
        if(bufferSize<=0)
            throw new IllegalArgumentException("Size is illegal.");
        this.bufferSize = bufferSize;
    }
    
    //check whether the buffer is full
    public synchronized boolean isFull() {
        return buffer.size() == bufferSize;
    }
    
    //check whether the buffer is empty
    public synchronized boolean isEmpty() {
        return buffer.isEmpty();
    }
    
    //put an income message into the queue, called by message producer
    public synchronized void put(String message) {
        //wait until the queue is not full
        while (isFull()) {
        
            System.out.println("Queue is full.");
            try{
                //set the current thread to wait
                wait();
            }catch(InterruptedException ex){

            //someone wake me up.
            }
        }
        
        buffer.add(message);
        System.out.println("Queue receives message ‘"+message+"’");

        //wakeup all the waiting threads to proceed
        notifyAll();
    }
    
    //get a message from the queue, called by the message consumer
    public synchronized String get(){
        String message;
        //wait until the queue is not empty
        while(isEmpty()){
            System.out.println("There is no message in queue.");
            try{
                //set the current thread to wait
                wait();
            }catch(InterruptedException ex){
            
            //someone wake me up.
            }
        }
        
        //consume the first message in the queue
        message = buffer.remove(0);
        
        //wakeup all the waiting thread to proceed
        notifyAll();
        return message;
    }
} //end MessageQueue class

class Producer extends Thread{
    private static int count = 0;

    private MessageQueue queue = null;
    
    public Producer(MessageQueue queue){
        this.queue = queue;
    }
    
    @Override
    public void run(){
        for(int i=0;i<10;i++){
            queue.put(generateMessage());
        }
    }
    
    private synchronized String generateMessage(){
        String msg = "MSG#"+ count;
        count++;
        return msg;
    }
    
} //end Producer class

class Consumer extends Thread {
    private MessageQueue queue = null;
    
    public Consumer(MessageQueue queue){
        this.queue = queue;
    }
    
    @Override
    public void run(){
        for(int i=0;i<10;i++){
            System.out.println("Consumer downloads "+queue.get()+ " from the queue.");
        }
    }
} //end Consumer class


public class MessageSystem {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        MessageQueue queue = new MessageQueue(5);
        new Producer(queue).start();
        new Producer(queue).start();
        new Producer(queue).start();
        new Consumer(queue).start();
        new Consumer(queue).start();
        new Consumer(queue).start();        
    }
}
