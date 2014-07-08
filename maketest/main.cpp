#include <iostream>
#include <fstream>
#include <string>
#include <random>

int main(int narg,char** arg)
{
  if(narg != 3)
  {
    std::cout << "maketest [number of processes] [test file]" << std::endl;
    return -1;
  }

  int nproc = std::stoi(arg[1]);
  std::ofstream file(arg[2],std::ios_base::trunc);
  std::default_random_engine rand;

  //pid burst arrival priority
  for(int i=0; i<nproc; ++i)
  {
    file << i << '\t'
      << std::uniform_int_distribution<>(1,100)(rand) << '\t'
      << std::uniform_int_distribution<>(0,25*nproc)(rand) << '\t'
      << std::uniform_int_distribution<>(0,99)(rand) << std::endl;
  }
}
