#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

const string OPEN_LEFT = "-J7S";
const string OPEN_TOP = "|JLS";
const string OPEN_RIGHT = "-FLS";
const string OPEN_DOWN = "|F7S";

pair<int, int> getNextPath(vector<string> &pipes, pair<int, int> curPos, pair<int, int> prevPos) {
  int i = curPos.first;
  int j = curPos.second;
  char curPipe = pipes[i][j];

  if (i > 0) {
    pair<int, int> topPath = make_pair(i - 1, j);
    char topPipe = pipes[topPath.first][topPath.second];
    if (prevPos != topPath && OPEN_TOP.find(curPipe) != string::npos && OPEN_DOWN.find(topPipe) != string::npos) {
      return topPath;
    }
  }

  if (i < pipes.size() - 1) {
    pair<int, int> downPath = make_pair(i + 1, j);
    char downPipe = pipes[downPath.first][downPath.second];
    if (prevPos != downPath && OPEN_DOWN.find(curPipe) != string::npos && OPEN_TOP.find(downPipe) != string::npos) {
      return downPath;
    }
  }

  if (j > 0) {
    pair<int, int> leftPath = make_pair(i, j - 1);
    char leftPipe = pipes[leftPath.first][leftPath.second];
    if (prevPos != leftPath && OPEN_LEFT.find(curPipe) != string::npos && OPEN_RIGHT.find(leftPipe) != string::npos) {
      return leftPath;
    }
  }

  pair<int, int> rightPath = make_pair(i, j + 1);
  return rightPath;
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

  int nRows = lines.size();
  int nCols = lines[0].size();
  pair<int, int> curPos;
  for (int i = 0; i < nRows; i += 1) {
    for (int j = 0; j < nCols; j += 1) {
      if (lines[i][j] == 'S') {
        curPos = make_pair(i, j);
      }
    }
  }

  pair<int, int> prevPos = curPos;
  int nSteps = 0;
  do {
    pair<int, int> nextPath = getNextPath(lines, curPos, prevPos);
    char prevPipe = lines[prevPos.first][prevPos.second];
    char curPipe = lines[curPos.first][curPos.second];
    char nextPipe = lines[nextPath.first][nextPath.second];
    prevPos = curPos;
    curPos = nextPath;
    nSteps += 1;
  } while (lines[curPos.first][curPos.second] != 'S');

  cout << nSteps / 2 << endl;
}
