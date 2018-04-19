// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>

std::mutex t_mutex;

void foo()
{
  for(int i=65;i<80;i++)
  {
     std::lock_guard<std::mutex> guard(t_mutex);
     char c = (char) i;
     std::cout << c << std::endl;
  }
}

void bar()
{
    for(int i=97;i<112;i++)
  {
        std::lock_guard<std::mutex> guard(t_mutex);
        char c = (char) i;
        std::cout << c << c <<std::endl;
  }

}



int main()
{
  //std::thread first[5];     // spawn new thread that calls foo()

  std::cout << "main, foo and bar now execute concurrently...\n";

    for(int i=0;i<std::thread::hardware_concurrency();i++)
    {
        std::thread first[5];

        first[i](foo());
        first[i].join();                // pauses until first finishes
        first[i] (bar());
        first[i].join();
    }
                // pauses until second finishes

  std::cout << "\nfoo and bar completed.\n";

  return 0;
}
