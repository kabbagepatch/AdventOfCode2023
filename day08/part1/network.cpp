#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
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
  myfile.close();

  map<string, pair<string, string>> network;
  for (int i = 2; i < lines.size(); i += 1) {
    string line = lines[i];
    string start = line.substr(0, 3);
    string left = line.substr(7, 3);
    string right = line.substr(12, 3);

    network[start] = make_pair(left, right);
  }

  int nSteps = 0;
  string curPos = "AAA";
  int instructionInd = 0;
  while (curPos != "ZZZ") {
    curPos = lines[0][instructionInd] == 'L' ? network[curPos].first : network[curPos].second;
    nSteps += 1;
    instructionInd += 1;
    instructionInd %= lines[0].size();
  }

  cout << nSteps << endl;
}
