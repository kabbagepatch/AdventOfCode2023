#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void print(vector<string> stuff) {
  for (string t : stuff) {
    cout << t << endl;
  }
  cout << endl;
  cout << endl;
}

vector<string> expandUniverse(vector<string> universe) {
  int nRows = universe.size();
  int nEmptyRows = 0;
  bool isEmptyRow[nRows];
    for (int i = 0; i < nRows; i += 1) {
    string line = universe[i];
    isEmptyRow[i] = true;
    for (char c : line) {
      if (c == '#') {
        isEmptyRow[i] = false;
        break;
      }
    }
    if (isEmptyRow[i]) nEmptyRows += 1;
  }

  int nCols = universe[0].size();
  int nEmptyCols = 0;
  bool isEmptyCol[nCols];
  for (int j = 0; j < nCols; j += 1) {
    isEmptyCol[j] = true;
    for (int i = 0; i < nRows; i += 1) {
      char c = universe[i][j];
      if (c == '#') {
        isEmptyCol[j] = false;
        break;
      }
    }
    if (isEmptyCol[j]) nEmptyCols += 1;
  }

  vector<string> newUniverse;
  string emptyRow(nCols + nEmptyCols, '.');
  for (int i = 0; i < nRows; i += 1) {
    string newRow = "";
    for (int j = 0; j < nCols; j += 1) {
      newRow += universe[i][j];
      if (isEmptyCol[j]) newRow += '.';
    }
    newUniverse.push_back(newRow);
    if (isEmptyRow[i]) newUniverse.push_back(emptyRow);
  }

  return newUniverse;
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

  vector<string> universe = expandUniverse(lines);
  vector<pair<int, int>> galaxies;
  for (int i = 0; i < universe.size(); i += 1) {
    for (int j = 0; j < universe[0].size(); j += 1) {
      if (universe[i][j] == '#') {
        galaxies.push_back(make_pair(i, j));
      }
    }
  }

  int distanceSum = 0;
  for (int i = 0; i < galaxies.size(); i += 1) {
    for (int j = i + 1; j < galaxies.size(); j += 1) {
      distanceSum += abs(galaxies[i].first - galaxies[j].first) + abs(galaxies[i].second - galaxies[j].second);
    }
  }

  cout << distanceSum << endl;
}
