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
    Matriz()//Construtor da Classe Matriz.
    {
        matriz1=nullptr;
        matriz2=nullptr;
    }

    ptrMatriz getPtrMatriz1()//Devolve o ponteiro para a Matriz1.
    {
        return matriz1;
    }

    ptrMatriz getPtrMatriz2()//Devolve o ponteiro para a Matriz2.
    {
        return matriz2;
    }

    ptrMatriz criarMatriz(int tam_x,int tam_y)
    //DESCRICAO DA FUNCAO:
    //-Criar uma matriz atraves de alocacao dinamica ao final devolvendo o ponteiro
    //para o noh [0][0] da matriz.(Caso a funcao retorne 'nullptr',ocorreu um erro
    //durante a criacao da matriz).
    //-Toda linha termina com um noh com a variavel ponteiro 'prox' apontando para nullptr.
    //-A linha final eh aquela que a variavel ponteiro 'emb'(primeiro noh da linha),
    //contiver o valor nullptr.
    //-Eh necessario dois ponteiros para ler esta matriz: um para percorrer todos os nohŽs
    //da linha e outro para apontar para o primeiro noh. Somente com a confirmacao
    //do valor 'nullptr' nas variaveis ponteiro da struct 'ptrMatriz':
    //emb(primeiro noh) e prox(ultimo noh da linha) se pode confirmar que se chegou ao fim da matriz.
    {
        srand(time(NULL));//Semente de tempo para ser usada na geracao de valores aleatorios(rand()).

        ptrMatriz p=nullptr;//vai receber a referencia do ponteiro [0][0] da matriz.

        if(tam_x>0 && tam_y>0)
        {
            ptrMatriz aux_p = nullptr;//Ira segurar ate o final da criacao da matriz a referencia para o ponteiro [0][0].
            //Pois caso ocorra alguma falha que termine abruptamente com a criada da matriz o ponteiro principal permanecera
            //nulo indicando que ocorreu falha na geracao da matriz.
            ptrMatriz q = nullptr;//ponteiro que ira realizar toda a criacao da matriz.
            ptrMatriz aux = nullptr;//ponteiro para o noh do inicio da linha.
            ptrMatriz aux_l = nullptr;//ponteiro para o noh anterior do ponteiro `q`.
            for(int i=0;i<tam_y;i++)
            {
                for(int j=0;j<tam_x;j++)
                {
                    if(i!=0 && j!=0)
                    {
                        if((q = (ptrMatriz) malloc(sizeof(no_matriz)))== nullptr)
                        {
                            std::cout << "Malloc erro: Erro de alocacao de memoria!";
                            exit(-1);
                        }

                        q->ant=aux_l;
                        aux_l->prox=q;
                        aux_l = q;
                        q->prox=nullptr;
                        q->emb=nullptr;
                        q->valor= rand() % 999 + 0;
                        q = nullptr;
                    }
                    else if(i!=0 && j==0)
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
                        q->emb=nullptr;
                        q->valor= rand() % 999 + 0;
                        q=nullptr;
                    }
                    else if(i==0 && j==0)
                    {
                        if((aux_p = (ptrMatriz) malloc(sizeof(no_matriz)))== nullptr)
                        {
                            std::cout << "Malloc erro: Erro de alocacao de memoria!";
                            exit(-1);
                        }

                        aux = aux_l = aux_p;
                        aux_p->ant=nullptr;
                        aux_p->emb=nullptr;
                        aux_p->prox=nullptr;
                        aux_p->valor= rand() % 999 + 0;
                    }

                }//Fim da interacao da linha
            }//Fim da interacao coluna
            p = aux_p;
        }//Fim da criacao da matriz
        else if(tam_x==0 || tam_y==0) std::cout << "Nao pode conter valor 0!" << std::endl;
        else std::cout << "Nao pode ser valor negativo!" << std::endl;
        return p;
    }//Fim da funcao 'criarMatriz()'.

    void exibirMatriz(ptrMatriz m)
    {
        if(m!=nullptr)
        {
            ptrMatriz p=m;
            ptrMatriz aux=p;

            while(p!=nullptr && aux!=nullptr)
            {

            }
        }

    }
};

int main()
{
    Matriz m = Matriz();
    m.criarMatriz(0,0);
    m.criarMatriz(-1,-7);
    m.criarMatriz(1,1);
    return 0;
}
