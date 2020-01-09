#include <string.h>

#include <map>
#include <string>
class envVar {
 private:
  std::string cmdInp;
  size_t map_size;
  std::string varName;
  std::string varValue;
  //out
  size_t firstblank;
  size_t secondblank;
  std::string cmdName;

 public:
  static std::map<std::string, std::string> var_map;
  envVar();
  void setV();
  void expV();
  void revV();
  void setCmdInp(std::string inp) { cmdInp = inp; }
  //out
  bool checkVarInput(char * command);
  bool checkVarName();
  bool replaceVar(char ** args);
  friend class ffosh;
  friend class cmdParser;
};
std::map<std::string, std::string> envVar::var_map;
