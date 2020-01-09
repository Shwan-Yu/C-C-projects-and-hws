#include "envVar.h"

#include <bits/stdc++.h>
#include <string.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

envVar::envVar() : map_size(0), firstblank(0), secondblank(0) {
  int count = 0;
  while (environ[count]) {
    count++;
  }
  for (int i = 0; i < count; i++) {
    std::string temp(environ[i]);
    size_t equal = temp.find("=");
    std::string key = temp.substr(0, equal);
    std::string value = temp.substr(equal + 1);
    var_map[key] = value;
  }
}

void envVar::setV() {
  var_map[varName] = varValue;
  std::cout << var_map[varName] << std::endl;
}

void envVar::expV() {
  std::cout << varName << std::endl;
  std::cout << varValue << std::endl;
  std::cout << var_map[varName] << std::endl;
  if (setenv(varName.c_str(), var_map[varName].c_str(), 1) != 0) {
    perror("Fail to export this variable");
    return;
  }
  else {
    std::cout << "Variable exported" << std::endl;
  }
}

void envVar::revV() {
  reverse(varValue.begin(), varValue.end());
  var_map[varName] = varValue;
  return;
}

bool envVar::checkVarInput(char * command) {
  if (strcmp(command, "set") == 0) {
    firstblank = cmdInp.find_first_of(" ");
    if (firstblank == std::string::npos || firstblank == cmdInp.length() - 1) {
      cmdName = cmdInp;
      varName.assign("null");
      varValue.assign("null");
      std::cout << "Invalid variable name and value" << std::endl;
      return false;
    }
    else {
      cmdName = cmdInp.substr(0, firstblank);
      cmdInp.erase(0, firstblank + 1);
      secondblank = cmdInp.find_first_of(" ");
      if (secondblank == std::string::npos || secondblank == cmdInp.length() - 1) {
        varName = cmdInp;
        varValue.assign("null");
        std::cout << "Invalid variable value" << std::endl;
        return false;
      }
      else {
        varName = cmdInp.substr(0, secondblank);
        cmdInp.erase(0, secondblank + 1);
        varValue = cmdInp;
      }
    }
    return true;
  }

  if (strcmp(command, "export") == 0 || strcmp(command, "inc") == 0) {
    firstblank = cmdInp.find_first_of(" ");
    if (firstblank == std::string::npos || firstblank == cmdInp.length() - 1) {
      std::cout << "No variable name found" << std::endl;
      return false;
    }
    else {
      cmdName = cmdInp.substr(0, firstblank);
      cmdInp.erase(0, firstblank + 1);
      varName = cmdInp;
      secondblank = cmdInp.find_first_of(" ");
      if (secondblank == cmdInp.length() - 1) {
        cmdInp.erase(secondblank, cmdInp.length());
        varName = cmdInp;
        return true;
      }
      if (secondblank != std::string::npos) {
        std::cout << "Too many arguements" << std::endl;
        return false;
      }
    }
  }
  return true;
}
bool envVar::checkVarName() {
  size_t found = varName.find_first_not_of(
      "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz1234567890_");
  if (found != std::string::npos) {
    std::cout << "Variable name invalid" << std::endl;
    return false;
  }
  return true;
}

bool envVar::replaceVar(char ** args) {
  for (int i = 0; args[i] != NULL; i++) {
    std::string argsi(args[i]);
    size_t found = argsi.find("$");
    int k = 1;

    while (found != std::string::npos) {
      do {
        std::string sub = argsi.substr(found + 1, found + k);
        std::map<std::string, std::string>::iterator it = var_map.find(sub);
        std::cout << var_map["var"] << std::endl;

        if (it != var_map.end()) {  //found the variable in map
          std::cout << "found" << std::endl;
          argsi.replace(found, k + 1, it->second);
          std::cout << it->second << std::endl;
          args[i] = strdup(argsi.c_str());  //replace the varname
          found = argsi.find("$");
          break;
        }
        k++;
      } while (found + k < argsi.length() && args[i][found + k] != '$');
      if (!(found + k < argsi.length() && args[i][found + k] != '$')) {
        std::cout << "No existed variable matched" << std::endl;
        return false;
      }
    }
  }

  return true;
}
