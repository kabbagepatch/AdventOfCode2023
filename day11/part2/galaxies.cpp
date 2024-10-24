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

vector<int> findEmptyRows(vector<string> &universe) {
  int nRows = universe.size();
  vector<int> emptyRows;
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
    if (isEmptyRow[i]) emptyRows.push_back(i);
  }
  
  return emptyRows;
}

vector<int> findEmptyCols(vector<string> universe) {
  int nRows = universe.size();
  int nCols = universe[0].size();
  vector<int> emptyCols;
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
    if (isEmptyCol[j]) emptyCols.push_back(j);
  }

  return emptyCols;
}

int main () {
  ifstream myfile;
  myfile.open ("../input");
  vector<string> universe;
  if (myfile.is_open()) {
    string lineString;
    while(getline(myfile, lineString)) {
      universe.push_back(lineString);
    }
  }
  myfile.close();

  vector<int> emptyRows = findEmptyRows(universe);
  vector<int> emptyCols = findEmptyCols(universe);
  vector<pair<int, int> > galaxies;
  for (int i = 0; i < universe.size(); i += 1) {
    for (int j = 0; j < universe[0].size(); j += 1) {
      if (universe[i][j] == '#') {
        galaxies.push_back(make_pair(i, j));
      }
    }
  }

  int nExpansions = 1000000 - 1;

  long distanceSum = 0;
  for (int i = 0; i < galaxies.size(); i += 1) {
    for (int j = i + 1; j < galaxies.size(); j += 1) {
      distanceSum += abs(galaxies[i].first - galaxies[j].first) + abs(galaxies[i].second - galaxies[j].second);
      for (int emptyRow : emptyRows) {
        if ((galaxies[i].first < emptyRow && emptyRow < galaxies[j].first) || (galaxies[j].first < emptyRow && emptyRow < galaxies[i].first)) {
          distanceSum += nExpansions;
        }
      }
      for (int emptyCol : emptyCols) {
        if ((galaxies[i].second < emptyCol && emptyCol < galaxies[j].second) || (galaxies[j].second < emptyCol && emptyCol < galaxies[i].second)) {
          distanceSum += nExpansions;
        }
      }
    }
  }

  cout << distanceSum << endl;
}
