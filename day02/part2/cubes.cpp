#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<string> split(string s, string delimiter) {
  vector<string> results;
  size_t pos = 0;
  string token;
  while ((pos = s.find(delimiter)) != string::npos) {
      token = s.substr(0, pos);
      results.push_back(token);
      s.erase(0, pos + delimiter.length());
  }
  results.push_back(s);
  return results;
}

int getGamePower(string game) {
  int startInd = game.find(':') + 2;
  int maxBlue = 0;
  int maxRed = 0;
  int maxGreen = 0;
  int curBalls = 0;
  char curColour = 'z';
  for (int i = startInd; i < game.length(); i += 1) {
    char c = game[i];
    if (c >= '0' && c <= '9') {
      if (curBalls > 0) {
        curBalls = curBalls * 10;
      }
      curBalls += c - '0';
    }
    if (c == ' ') {
      curColour = game[i + 1];
      if (curColour == 'b' && curBalls > maxBlue) {
        maxBlue = curBalls;
      }
      if (curColour == 'r' && curBalls > maxRed) {
        maxRed = curBalls;
      }
      if (curColour == 'g' && curBalls > maxGreen) {
        maxGreen = curBalls;
      }
      curColour = 'z';
      curBalls = 0;
    }
  }

  return maxBlue * maxRed * maxGreen;
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

  int powerSum = 0;
  for (int i = 0; i < lines.size(); i += 1) {
    powerSum += getGamePower(lines[i]);
  }

  cout << powerSum << '\n';
}
