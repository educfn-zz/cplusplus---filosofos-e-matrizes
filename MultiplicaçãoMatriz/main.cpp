//ALUNO: EDUARDO CARDOSO FERNANDS NETO - 5 SEMESTRE - NUMERO CHAMADA:9197350
#include <iostream>
#include <cstdlib>
#include <cstdbool>
#include <ctime>

typedef struct no_matriz * ptrMatriz;

struct no_matriz
{
    ptrMatriz prox;//proximo
    ptrMatriz ant;//anterior
    ptrMatriz emb;//embaixo
    float valor;
};

class Matriz
{
private:
    ptrMatriz matriz1;
    ptrMatriz matriz2;

public:
    Matriz()
    {
        matriz1=nullptr;
        matriz2=nullptr;
    }

    ptrMatriz getPtrMatriz1()
    {
        return matriz1;
    }

    ptrMatriz getPtrMatriz2()
    {
        return matriz2;
    }

    void criarMatriz(int tam_x,int tam_y)
    {
        srand(time(NULL));

        ptrMatriz p;//vai receber a referencia do ponteiro [0][0] da matriz.
        if(tam_x!=0 && tam_y!=0)
        {
            ptrMatriz q = nullptr;//ponteiro que ira realizar toda a criacao da matriz.
            ptrMatriz aux = nullptr;//ponteiro para o no do inicio da linha.
            ptrMatriz aux_l = nullptr;//ponteiro para o no anterior do ponteiro `q`.
            for(int i=0;i<tam_y;i++)
            {
                for(int j=0;j<tam_x;j++)
                {
                    if(i!=0 && j==0)
                    {
                        if((q = (ptrMatriz) malloc(sizeof(no_matriz)))== nullptr)
                        {
                            std::cout << "Malloc erro: Erro de alocacao de memoria!";
                            exit(-1);
                        }

                        aux->emb = q;
                        aux = aux_l = q;
                        q->ant=nullptr;
                        q->prox=nullptr;
                        q->valor= rand() % 999 + 0;
                    }
                    else if(i==0 && j==0)
                    {
                        if((p = (ptrMatriz) malloc(sizeof(no_matriz)))== nullptr)
                        {
                            std::cout << "Malloc erro: Erro de alocacao de memoria!";
                            exit(-1);
                        }

                        aux = aux_l = p;
                        p->ant=nullptr;
                        p->emb=nullptr;
                        p->prox=nullptr;
                        p->valor= rand() % 999 + 0;
                    }

                }
            }
        }

    }
};

int main()
{
    Matriz m = Matriz();
    std::cout << m.getPtrMatriz1() << std::endl;
    m.criarMatriz(0,0);
    return 0;
}
