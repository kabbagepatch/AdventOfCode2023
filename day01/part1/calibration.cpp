#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

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

  int calibrationTotal = 0;
  for (string line : lines) {
    int calibrationValue = 0;
    for (int i = 0; i < line.length(); i++) {
      char c = line[i];
      if (c >= '0' && c <= '9') {
        int digit = c - '0';
        calibrationValue = digit * 10;
        break;
      }
    }
    for (int i = line.length() - 1; i >= 0; i--) {
      char c = line[i];
      if (c >= '0' && c <= '9') {
        int digit = c - '0';
        calibrationValue += digit;
        break;
      }
    }
    calibrationTotal += calibrationValue;
  }

  cout << calibrationTotal << '\n';

  myfile.close();
}
