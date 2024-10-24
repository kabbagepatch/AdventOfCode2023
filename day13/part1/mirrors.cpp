#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool isVerticalReflection(vector<string> &pattern, int j1Start, int j2Start) {
  for (int i = 0; i < pattern.size(); i += 1) {
    int j1 = j1Start;
    int j2 = j2Start;
    while(j1 >= 0 && j2 < pattern[0].size()) {
      if (pattern[i][j1] != pattern[i][j2]) {
        return false;
      }
      j1--;
      j2++;
    }
  }
  return true;
}

bool isHorizontalReflection(vector<string> &pattern, int i1Start, int i2Start) {
  for (int j = 0; j < pattern[0].size(); j += 1) {
    int i1 = i1Start;
    int i2 = i2Start;
    while(i1 >= 0 && i2 < pattern.size()) {
      if (pattern[i1][j] != pattern[i2][j]) {
        return false;
      }
      i1--;
      i2++;
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

  vector<vector<string>> patterns;
  vector<string> pattern;
  for (string line : lines) {
    if (line.empty()) {
      patterns.push_back(pattern);
      pattern.clear();
      continue;
    }
    pattern.push_back(line);
  }
  patterns.push_back(pattern);

  int summary = 0;
  for (vector<string> pattern : patterns) {
    // find horizontal line
    bool found = false;
    for (int i = 0; i < pattern.size() - 1; i += 1) {
      if(isHorizontalReflection(pattern, i, i + 1)) {
        summary += 100 * (i + 1);
        found = true;
        break;
      }
    }
    if (found) continue;

    // find vertical line
    for (int j = 0; j < pattern[0].size() - 1; j += 1) {
      if(isVerticalReflection(pattern, j, j + 1)) {
        summary += j + 1;
        break;
      }
    }
  }

  cout << summary << endl;
}
