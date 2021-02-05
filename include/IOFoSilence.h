# if !defined(_IO_FOSILENCE_H)
# define _IO_FOSILENCE_H
# include<string>
# include<vector>
# include<set>
namespace IO{
class Levels{
  public:
  typedef int level;
  Levels(): MaxLevel(9),MaxLevelAllowed(1),LevelDiscribtion(){}
  Levels(level maxLevelAllowed): MaxLevel(9),MaxLevelAllowed(maxLevelAllowed>0?(maxLevelAllowed<=9?maxLevelAllowed:9):1),LevelDiscribtion(){}
  Levels(level maxLevelAllowed,std::vector<std::string> Discribtion): MaxLevel(9),MaxLevelAllowed(maxLevelAllowed>0?(maxLevelAllowed<=9?maxLevelAllowed:9):1),LevelDiscribtion(Discribtion){}
  void setLevelDiscribtion(const std::vector<std::string>& Discribtions);
  protected:
  bool thisLevelBaned(level CurrentLevel);
  bool eligibleLevel(level CurrentLevel);
  std::string LevelToString(level CurrentLevel);
  std::vector<std::string> LevelDiscribtion;
  level MaxLevelAllowed;
  level MaxLevel;
};
class StringPool{
  public:
  StringPool():realPool(std::vector<std::string>()),MaxSize(20){}
  StringPool(std::size_t size_):realPool(std::vector<std::string>()),MaxSize(size_){}
  std::string& operator[](std::size_t loc);
  const std::string& operator[](std::size_t loc) const;
  StringPool& reset();
  StringPool& pushToPool(std::string str);
  StringPool& setSize(std::size_t loc);
  std::ostream& PoolOutPut(std::ostream& PrintOut);
  bool PoolFull() const;
  private:
  std::size_t MaxSize;
  std::vector<std::string> realPool;
};
class OutBase: public Levels{
  public:
  enum OutType{outToFile,OutToScreen};
  OutBase():Levels(),LevelPools(MaxLevelAllowed),BaseFileName(""),outType(OutToScreen),outFileTail(""){}
  OutBase(level maxLevelAllowed,std::vector<std::string> Discribtion):
    Levels(maxLevelAllowed,Discribtion),
    LevelPools(MaxLevel),
    BaseFileName(""),
    outType(OutToScreen),
    outFileTail(""){}
  OutBase(level maxLevelAllowed,std::vector<std::string> Discribtion,std::string baseFileName):
    Levels(maxLevelAllowed,Discribtion),
    LevelPools(MaxLevel),
    BaseFileName(baseFileName),
    outType(OutToScreen),
    outFileTail(""){}
  OutBase& Out(std::string str,level l);
  OutBase& setOutType(OutType outType_);
  std::size_t levelToStringPoolLocation(level l);
  level PoolLocationToLevel(std::size_t loc);
  void StrToPool(std::string str,std::size_t loc);
  OutBase& setOutFileTail(std::string str);
  private:
  std::string outFileTail;
  OutType outType; 
  std::vector<StringPool> LevelPools;
  std::string BaseFileName;
};
} // IO
# endif