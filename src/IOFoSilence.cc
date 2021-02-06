# include"../include/IOFoSilence.h" 
# include<iostream>
# include<fstream>
namespace IO{
bool Levels::thisLevelBaned(level CurrentLevel){
  if(CurrentLevel > 0 && CurrentLevel <= MaxLevelAllowed){
    return false;
  }
  return true;
}
bool Levels::eligibleLevel(level CurrentLevel){
  if(CurrentLevel > 0 && CurrentLevel <= MaxLevel){
    return true;
  }
  return false;
}

std::string Levels::LevelToString(level CurrentLevel){
  if(eligibleLevel(CurrentLevel) ){
    if(CurrentLevel<=LevelDiscribtion.size()){
      return LevelDiscribtion[CurrentLevel-1] + "-L" + std::to_string(CurrentLevel);
    }else{
      return "level-"+std::to_string(CurrentLevel);
    }
  }else{
    throw "in LevelToString - level not eligible";
  }
}

void Levels::setLevelDiscribtion(const std::vector<std::string>& Discribtion){
  LevelDiscribtion = Discribtion;
}

std::string& StringPool::operator[](std::size_t loc){
  return realPool[loc];
}
const std::string& StringPool::operator[](std::size_t loc) const {
  return realPool[loc];
}

StringPool& StringPool::reset(){
  realPool.clear();
  return *this;
}

StringPool& StringPool::pushToPool(std::string str){
  realPool.push_back(str);
  return *this;
}

inline 
StringPool& StringPool::setSize(std::size_t size_){
  MaxSize = size_;
  return *this;
}

std::ostream& StringPool::PoolOutPut(std::ostream& PrintOut,std::string Header=""){
  for(auto str:realPool){
    PrintOut << Header + str << std::endl;
  }
  return PrintOut;
}

bool StringPool::PoolFull() const{
  if(realPool.size()<MaxSize){
    return false;
  }else{
    return true;
  }
}
bool StringPool::empty() const{
  return realPool.empty();
}

OutBase& OutBase::Out(std::string str,level l){
  if(!thisLevelBaned(l)){
    std::string levelHead = "[" + LevelToString(l) + "]:";
    levelHead += str;
    switch (outType)
    {
    case outToFile:
      StrToPool(str,levelToStringPoolLocation(l));
      break;
    case OutToScreen:
    default:
      std::cout << levelHead << std::endl;
      break;
    }
  }
  return *this;
}

OutBase& OutBase::setOutType(OutType outType_){
  outType = outType_;
  return *this;
}

inline
std::size_t OutBase::levelToStringPoolLocation(level l){
  return l - 1;
}
inline
OutBase::level OutBase::PoolLocationToLevel(std::size_t loc){
  return loc + 1;
}
void OutBase::StrToPool(std::string str,std::size_t loc){
  switch (outType)
  {
    case outToFile:
      if(LevelPools[loc].PoolFull()){
        std::string outFileName = BaseFileName+LevelToString(PoolLocationToLevel(loc)) + outFileTail;
        std::ofstream outFile(outFileName,std::ofstream::ate);
        if(outFile){
          LevelPools[loc].PoolOutPut(outFile);
          LevelPools[loc].reset();
        }else{
          goto ToScreenLabel;
        }
      }else{
        LevelPools[loc].pushToPool(str);
      }
      break;
    ToScreenLabel:
    case OutToScreen:
    default:
      LevelPools[loc].PoolOutPut(std::cout,"["+LevelToString(PoolLocationToLevel(loc))+"]");
      LevelPools[loc].reset();
      break;
  }
}

OutBase& OutBase::setOutFileTail(std::string str){
  outFileTail = str;
  return *this;
}

OutBase::~OutBase(){
  for(int pool=0 ; pool<LevelPools.size(); ++pool){
    if(!LevelPools[pool].empty()){
      std::string outFileName = BaseFileName+LevelToString(PoolLocationToLevel(pool)) + outFileTail;
      std::ofstream outFile(outFileName,std::ofstream::ate);
      LevelPools[pool].PoolOutPut(outFile,"");
    }
  }
  outFileTail.~basic_string();
  LevelPools.~vector();
  BaseFileName.~basic_string();
}
} // IO