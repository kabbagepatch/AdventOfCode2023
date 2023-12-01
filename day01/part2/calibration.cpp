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

  string digits[9] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

  int calibrationTotal = 0;
  for (string line : lines) {
    int leftDigitIndex = -1;
    int leftDigit = 0;
    for (int i = 0; i < line.length(); i++) {
      char c = line[i];
      if (c >= '0' && c <= '9') {
        int digit = c - '0';
        leftDigitIndex = i;
        leftDigit = digit;
        break;
      }
    }

    int rightDigitIndex = -1;
    int rightDigit = 0;
    for (int i = line.length() - 1; i >= 0; i--) {
      char c = line[i];
      if (c >= '0' && c <= '9') {
        int digit = c - '0';
        rightDigitIndex = i;
        rightDigit = digit;
        break;
      }
    }

    for (int i = 0; i < 9; i++) {
      string digit = digits[i];
      int firstFoundIndex = line.find(digit);
      if (firstFoundIndex != std::string::npos) {
        if ((firstFoundIndex < leftDigitIndex || leftDigitIndex == -1)) {
          leftDigitIndex = firstFoundIndex;
          leftDigit = i + 1;
        }
      }
      int lastFoundIndex = line.find(digit);
      if (lastFoundIndex != std::string::npos) {
        int prevLastFoundIndex;
        while (lastFoundIndex != string::npos) {
          prevLastFoundIndex = lastFoundIndex;
          lastFoundIndex = line.find(digit, prevLastFoundIndex + digit.length());
        }
        lastFoundIndex = prevLastFoundIndex;
        if ((lastFoundIndex > rightDigitIndex || rightDigitIndex == -1)) {
          rightDigitIndex = lastFoundIndex;
          rightDigit = i + 1;
        }
      }
    }

    calibrationTotal += 10 * leftDigit + rightDigit;
  }

  cout << calibrationTotal << '\n';

  myfile.close();
}
