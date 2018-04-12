package jantarfilosofos;

import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * @author mpiva
 */

public class Jantarfilosofos {

    public static void main(String[] args) {
        int iAmount = 20;
        
        System.out.println("******************************************");
        System.out.println("***                                    ***");
        System.out.println("***    JANTAR ANIMADO COM FILÓSOFOS    ***");
        System.out.println("***                                    ***");
        System.out.println("******************************************");
        System.out.println(""); System.out.println("");
        System.out.println("******************************************");
        System.out.println("* PONDO A MESA E RECEBENDO OS CONVIDADOS *");
        System.out.println("******************************************");
        System.out.println("");
        
        if(args.length > 0)
            iAmount = Integer.parseInt(args[0].trim());
               
        //criando bandeja
        Tray tray = new Tray(1, iAmount);
        
        //criando garfos
        Fork[] forks = new Fork[]{new Fork(1), 
                                  new Fork(2), 
                                  new Fork(3),
                                  new Fork(4),
                                  new Fork(5)};

        /*
         * 1 -> 5, 1 
         * 2 -> 1, 2
         * 3 -> 2, 3
         * 4 -> 3, 4
         * 5 -> 4, 5
         */
                
        //criando filosofos
        Philosopher[] philosophers = new Philosopher[]{new Philosopher(1, tray, forks, 0, 4),
                                                       new Philosopher(2, tray, forks, 1, 0),
                                                       new Philosopher(3, tray, forks, 2, 1),
                                                       new Philosopher(4, tray, forks, 3, 2),
                                                       new Philosopher(5, tray, forks, 4, 3)};
        
        System.out.println(""); System.out.println("");
        System.out.println("******************************************");
        System.out.println("*         O JANTAR ESTÁ SERVIDO          *");
        System.out.println("******************************************");
        System.out.println("");
        
        //iniciando filosofos
        philosophers[0].start();
        philosophers[1].start();
        philosophers[2].start();
        philosophers[3].start();
        philosophers[4].start();
        
        //aguardando o fim do jantar
        try {
            philosophers[0].join();
            philosophers[1].join();
            philosophers[2].join();
            philosophers[3].join();
            philosophers[4].join();
        
            System.out.println(""); System.out.println("");
            System.out.println("******************************************");
            System.out.println("*         FIM DO JANTAR ANIMADO          *");
            System.out.println("******************************************");
            System.out.println("");
        
        } catch (InterruptedException ex) {
            Logger.getLogger(Jantarfilosofos.class.getName()).log(Level.SEVERE, null, ex);
        }
        
    }
}


class Fork {
    private int iId;
    private int iBusy;
    
    public Fork(int _iId){
        this.iId = _iId;
        this.iBusy = 0;
        System.out.println("Garfo " + Integer.toString(iId) + " criado!");
    }
    
    public int getId(){
        return this.iId;
    }
    
    public void setBusy(int _iBusy){
        this.iBusy = _iBusy;
    }
    
    public Boolean isBusy(){
        return (this.iBusy != 0);
    }
    
}

class Tray {
    private int iId;
    private int iAmount;
    
    public Tray(int _iId, int _iAmount){
        this.iId = _iId;
        this.iAmount = _iAmount;
        System.out.println("Bandeja " + Integer.toString(iId) + " criada! - Qtde: " 
                                      + Integer.toString(iAmount) + " porções.");
    }
    
    public int getAmount(){
        return this.iAmount;
    }
    
    public void decreaseAmount(){
        this.iAmount--;
    }
}


class Philosopher extends Thread{
    private int iId;
    private Tray tray;
    private Fork[] forks;
    private int iLeft;
    private int iRight;
    private Boolean bCanEat;
    private int iAmount;
    
    public Philosopher(int _iId, Tray _tray, Fork[] _forks, int _iLeft, int _iRight){
        this.iAmount = 0;
        this.iId = _iId;
        this.tray = _tray;
        this.forks = _forks;
        this.iLeft = _iLeft;
        this.iRight = _iRight;
        this.bCanEat = false;
        System.out.println("> Filósofo " + Integer.toString(iId) + " diz: Cheguei!");       
    }
    
    @Override
    public void run(){
        while(tray.getAmount()>0) {
            this.eat();
            this.think();
        }
        if(this.iAmount > 0)
           System.out.println("* Filósofo " + Integer.toString(iId) + " diz: Xii, acabou o rango! Só comi " 
                                          + Integer.toString(this.iAmount) + " porção(ões).");
        else
           System.out.println("* Filósofo " + Integer.toString(iId) + " diz: Acabou o rango e eu nem comi!");
    }
    
    //garfos e bandeja são compartilhados, então devo sincronizar o uso
    private synchronized void getForks(int _iLeft, int _iRight){
        if(!forks[_iLeft].isBusy() && !forks[_iRight].isBusy()) {
            this.bCanEat = true;
            forks[_iLeft].setBusy(this.iId);
            forks[_iRight].setBusy(this.iId);
            tray.decreaseAmount();
            this.iAmount++;
        }  
    }
    
    //garfos e bandeja são compartilhados, então devo sincronizar o uso
    private synchronized void releaseForks(int _iLeft, int _iRight){
        this.bCanEat = false;
        forks[_iLeft].setBusy(0);
        forks[_iRight].setBusy(0);
    }
    
    private void eat(){
        System.out.println("+ Filósofo " + Integer.toString(iId) + " diz: Vou comer! Será?");
        this.getForks(iLeft, iRight);
        if(this.bCanEat) {
            System.out.println("++ Filósofo " + Integer.toString(iId) + " diz: Finalmente! Que delícia...");
            System.out.println("+++ Filósofo " + Integer.toString(iId) + " pegou o garfo " 
                                               + Integer.toString(forks[iLeft].getId()) 
                                               + " (esquerdo) e o garfo " 
                                               + Integer.toString(forks[iRight].getId())
                                               + " (direito).");
            try {
                Thread.sleep(700);
            } catch (InterruptedException ex) {
                Logger.getLogger(Philosopher.class.getName()).log(Level.SEVERE, null, ex);
            }
            
            this.releaseForks(iLeft, iRight);
            System.out.println("- Filósofo " + Integer.toString(iId) + " diz: Acabei, mas quero mais!");
        } 
    }
    
    private void think(){
        System.out.println("= Filósofo " + Integer.toString(iId) + " diz: Por hora, vou filosofar...");
        try {
            Thread.sleep(500);
        } catch (InterruptedException ex) {
            Logger.getLogger(Philosopher.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public int getAmount(){
        return this.iAmount;
    }    
} 
