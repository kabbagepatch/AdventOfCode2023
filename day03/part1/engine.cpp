#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool isNumber(char c) {
  return c >= '0' && c <= '9';
}

bool hasSymbols(vector<string> &lines, int i, int j) {
  if (i > 0) {
    if ((j > 0 && !isNumber(lines[i - 1][j - 1]) && lines[i - 1][j - 1] != '.')
      || (!isNumber(lines[i - 1][j]) && lines[i - 1][j] != '.')
      || (j < lines[0].size() - 1 && !isNumber(lines[i - 1][j + 1]) && lines[i - 1][j + 1] != '.')
    ) {
      return true;
    }
  }

  if ((j > 0 && !isNumber(lines[i][j - 1]) && lines[i][j - 1] != '.')
    || (j < lines[0].size() - 1 && !isNumber(lines[i][j + 1]) && lines[i][j + 1] != '.')
  ) {
    return true;
  }
  
  if (i < lines.size() - 1) {
    if ((j > 0 && !isNumber(lines[i + 1][j - 1]) && lines[i + 1][j - 1] != '.')
      || (!isNumber(lines[i + 1][j]) && lines[i + 1][j] != '.')
      || (j < lines[0].size() - 1 && !isNumber(lines[i + 1][j + 1]) && lines[i + 1][j + 1] != '.')
    ) {
      return true;
    }
  }

  return false;
}

int main () {
  ifstream myfile;
  myfile.open ("../input");
  vector<string> lines;
  if (myfile.is_open()) {
    string lineString;
    while(getline(myfile, lineString)) {
      lines.push_back(lineString);
    }
  }
  myfile.close();

  const int nRows = lines.size();
  const int nCols = lines[0].size();
  int partSum = 0;
  for (int i = 0; i < nRows; i += 1) {
    string number = "";
    bool isPart = false;
    for (int j = 0; j < nCols; j += 1) {
      char c = lines[i][j];
      if (isNumber(c)) {
        number += c;
        if (!isPart) {
          isPart = hasSymbols(lines, i, j);
        }
      } else {
        if (number.size() > 0) {
          if (isPart) {
            partSum += stoi(number);
          }
          number = "";
          isPart = false;
        }
      }
    }
    if (number.size() > 0) {
      if (isPart) {
        partSum += stoi(number);
      }
      number = "";
      isPart = false;
    }
  }

  cout << partSum << '\n';
}
