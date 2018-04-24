#include <iostream>
#include <cstdlib>
#include <cstdbool>

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
    float* matriz1;
    float* matriz2;

public:
    Matriz()
    {
        matriz1=nullptr;
        matriz2=nullptr;
    }

    void criarMatriz(int tam_x,int tam_y)
    {
        float* p;//vai receber a referencia do ponteiro [0][0].
        if(tam_x!=0 && tam_y!=0)
        {
            for(int i=0;i<tam_y;i++)
            {
                for(int j=0;j<tam_x;j++)
                {
                    if((p = (float*) malloc(sizeof(float)))== nullptr)
                    {
                        std::cout << "Malloc erro: Erro de alocacao de memoria!";
                        exit(-1);
                    }
                }
            }
        }

    }
};

int main()
{
    Matriz m;
    std::cout << "Hello world!" << std::endl;
    //m = new Matriz::Matriz();
    m.criarMatriz(0,0);
    return 0;
}

void exibirMatriz(ptrMatriz m)
{
     ptrMatriz p = m;
     while(1)
     {

          std::cout << "\t[" << p
          << "]";
     }
}



