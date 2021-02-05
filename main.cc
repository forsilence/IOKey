# include<iostream>
# include<string>
# include"../include/IOFoSilence.h"
int main(){
  std::vector<std::string> discribtions{"L1dis","L2dis","L3dis","L4dis","L5dis"};
  IO::OutBase ob(5,discribtions);
  IO::OutBase ob2(5,discribtions,"../data/outbase");
  ob2.setOutType(IO::OutBase::outToFile);
  ob2.setOutFileTail(".csv");
  IO::OutBase::level l = 0;
  for(int i=0; i<100; ++i){
    if(i%25==0){
      l += 1;
    }
    ob.Out(std::to_string(i),l);
    ob2.Out(std::to_string(i),l);
  }
  return 0;
}