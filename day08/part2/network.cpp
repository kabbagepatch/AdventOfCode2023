#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <numeric>
using namespace std;

bool isEnd(vector<string> &nodes) {
  for (string node : nodes) {
    if (node[2] != 'Z') {
      return false;
    }
  }

  return true;
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

  map<string, pair<string, string>> network;
  vector<string> startNodes;
  vector<string> curNodes;
  for (int i = 2; i < lines.size(); i += 1) {
    string line = lines[i];
    string start = line.substr(0, 3);
    string left = line.substr(7, 3);
    string right = line.substr(12, 3);

    network[start] = make_pair(left, right);
    if (start[2] == 'A') {
      startNodes.push_back(start);
      curNodes.push_back(start);
    }
  }

  vector<int> stepsToReachZ;
  for (int i = 0; i < curNodes.size(); i += 1) {
    int nSteps = 0;
    int instructionInd = 0;
    while (curNodes[i][2] != 'Z') {
      curNodes[i] = lines[0][instructionInd] == 'L' ? network[curNodes[i]].first : network[curNodes[i]].second;

      nSteps += 1;
      instructionInd += 1;
      instructionInd %= lines[0].size();
    }

    stepsToReachZ.push_back(nSteps);
  
    cout << nSteps << endl;
  }

  cout << "Find LCM of the above numbers" << endl;
}
