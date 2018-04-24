//ALUNO:EDUARDO CARDOSO FERNANDES NETO - 5º-SEMESTRE - Nº:9197350 - CIENCIA DA COMPUTACAO

#include <iostream>
#include <cstdio>
#include <cstdbool>
#include <thread>
#include <mutex>
#include <chrono>
#include <string>

//CLASSES

class Fork {
private:
    int iId;
    int iBusy;

public:
    Fork(int _iId){
        this->iId = _iId;
        this->iBusy = 0;
        std::cout << "Garfo " << iId << " criado!" << std::endl;
    }

    int getId(){
        return this->iId;
    }

    void setBusy(int _iBusy){
        this->iBusy = _iBusy;
    }

    bool isBusy(){
        return (this->iBusy != 0);
    }

};

class Tray {
private:
    int iId;
    int iAmount;

public:
    Tray(int _iId, int _iAmount){
        this->iId = _iId;
        this->iAmount = _iAmount;
        std::cout << "Bandeja " << iId << " criada! - Qtde: "
        << iAmount << " porções." << std::endl;
    }

    int getAmount(){
        return this->iAmount;
    }

    void decreaseAmount(){
        this->iAmount--;
    }
};

class Philosopher {
private:
    int iId;
    Tray * tray;
    Fork * forks;
    int iLeft;
    int iRight;
    bool bCanEat;
    int iAmount;

     //garfos e bandeja são compartilhados, então devo sincronizar o uso
    void getForks(int _iLeft, int _iRight){
        if(!forks[_iLeft].isBusy() && !forks[_iRight].isBusy()) {
            this->bCanEat = true;
            forks[_iLeft].setBusy(this->iId);
            forks[_iRight].setBusy(this->iId);
            tray->decreaseAmount();
            this->iAmount++;
        }
    }

    //garfos e bandeja são compartilhados, então devo sincronizar o uso
    void releaseForks(int _iLeft, int _iRight){
        this->bCanEat = false;
        forks[_iLeft].setBusy(0);
        forks[_iRight].setBusy(0);
    }

    void eat(){
        std::cout << "+ Filósofo " << iId << " diz: Vou comer! Será?" << std::endl;
        this->getForks(iLeft, iRight);
        if(this->bCanEat) {
            std::cout << "++ Filósofo " << iId << " diz: Finalmente! Que delícia..." << std::endl
            << "+++ Filósofo " << iId << " pegou o garfo "
            << forks[iLeft].getId() << " (esquerdo) e o garfo " << forks[iRight].getId()
            << " (direito)." << std::endl;
            try {
                std::this_thread::sleep_for(std::chrono::milliseconds(700));
            } catch (int err) {
                 std::cout << err << ":Erro do filosofo " << iId << "durante a tentativa de sleep." << std::endl;
            }

            this->releaseForks(iLeft, iRight);
            std::cout << "- Filósofo " << iId << " diz: Acabei, mas quero mais!" << std::endl;
        }
    }

    void think(){
        std::cout << "= Filósofo " << iId << " diz: Por hora, vou filosofar..." << std::endl;
        try {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        } catch (int err) {
                 std::cout << err << ":Erro do filosofo " << iId << "durante a tentativa de sleep." << std::endl;
        }
    }

public:
    Philosopher(int _iId, Tray * _tray, Fork * _forks, int _iLeft, int _iRight){
        this->iAmount = 0;
        this->iId = _iId;
        this->tray = &(*_tray);
        this->forks = &(*_forks);
        this->iLeft = _iLeft;
        this->iRight = _iRight;
        this->bCanEat = false;
        std::cout << "> Filósofo " << iId << " diz: Cheguei!" << std::endl;
    }

    void run(){
        while(tray->getAmount()>0) {
            this->eat();
            this->think();
        }
        if(this->iAmount > 0)
           std::cout << "* Filósofo " << iId << " diz: Xii, acabou o rango! Só comi "
            << this->iAmount << " porção(ões)." << std::endl;
        else
           std::cout << "* Filósofo " << iId << " diz: Acabou o rango e eu nem comi!" << std::endl;
    }

    void request_run(Philosopher philosopher)
    {
        philosopher.run();
    }

    int getAmount(){
        return this->iAmount;
    }
};

//FIM DAS CLASSES


//MAIN

int main(int argc, char *argv[])
{
    int iAmount=20;

        std :: cout <<("******************************************")<< std::endl
        <<("***                                    ***")<<std::endl
        <<("***    JANTAR ANIMADO COM FILÓSOFOS    ***")<<std::endl
        <<("***                                    ***")<<std::endl
        <<("******************************************")<<std::endl
        <<std::endl
        <<std::endl
        <<("******************************************")<<std::endl
        <<("* PONDO A MESA E RECEBENDO OS CONVIDADOS *")<<std::endl
        <<("******************************************")<<std::endl;

        /*if(argc > 1)
            iAmount =  std::stoi(argv[1],nullptr,0);*/ //somente para compilador GCC atualizado.

        //criando bandeja
        Tray tray(1, iAmount);

        //criando garfos
        Fork forks []= {Fork(1),
                        Fork(2),
                        Fork(3),
                        Fork(4),
                        Fork(5)};

        /*
         * 1 -> 5, 1
         * 2 -> 1, 2
         * 3 -> 2, 3
         * 4 -> 3, 4
         * 5 -> 4, 5
         */

         //criando filosofos
        Philosopher philosophers []= {Philosopher(1, &tray, forks, 0, 4),
                                      Philosopher(2, &tray, forks, 1, 0),
                                      Philosopher(3, &tray, forks, 2, 1),
                                      Philosopher(4, &tray, forks, 3, 2),
                                      Philosopher(5, &tray, forks, 4, 3)};

        std::cout <<std::endl << std::endl
        << "******************************************" << std::endl
        << "*         O JANTAR ESTÁ SERVIDO          *" << std::endl
        << "******************************************" << std::endl
        << "" << std::endl;

        //iniciando filosofos
        std::thread primeira (&Philosopher::run,philosophers[0]);
        //std::thread  segunda (philosophers[1].run());
        //std::thread  terceira (philosophers[2].run());
        //philosophers[3];
        //philosophers[4];

        //aguardando o fim do jantar
        try {
            /*primeira.join();
            segunda.join();
            terceira.join();
            quarta.join();
            quinta.join();*/

            std::cout << std::endl << std::endl
            <<("******************************************")<< std::endl
            <<("*         FIM DO JANTAR ANIMADO          *")<< std::endl
            <<("******************************************")<< std::endl
            << std::endl;

        } catch (int err) {
            std::cout << err << ":Erro na Main() durante o .join() de alguma thread" << std::endl;
        }



    return 0;
}

//FIM DA MAIN
