#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

void readFile(std::istream & istr) {
  std::string l_buf;
  std::vector<std::string> lines;
  while (getline(istr, l_buf)) {
    lines.push_back(l_buf);
  }
  std::sort(lines.begin(), lines.end());
  //Print the result
  for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); ++it)
    std::cout << *it << std::endl;
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    readFile(std::cin);
  }
  else {
    for (int i = 1; i < argc; i++) {
      std::ifstream ifstr(argv[i]);
      if (!ifstr) {
        perror("Could not open file\n");
        return EXIT_FAILURE;
      }
      readFile(ifstr);
      ifstr.close();
    }
  }
  return EXIT_SUCCESS;
}
