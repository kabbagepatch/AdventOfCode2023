#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool isNumber(char c) {
  return c >= '0' && c <= '9';
}

vector<pair<int, int>> getAdjacentNumbers(vector<string> &lines, int i, int j) {
  vector<pair<int, int>> neighbors;
  if (i > 0) {
    if ((j > 0 && isNumber(lines[i - 1][j - 1]))) {
      neighbors.push_back(make_pair(i - 1, j - 1));
    }
    if ((isNumber(lines[i - 1][j]))) {
      neighbors.push_back(make_pair(i - 1, j));
    }
    if ((j < lines[0].size() - 1 && isNumber(lines[i - 1][j + 1]))) {
      neighbors.push_back(make_pair(i - 1, j + 1));
    }
  }

  if ((j > 0 && isNumber(lines[i][j - 1]))) {
    neighbors.push_back(make_pair(i, j - 1));
  }
  if ((j < lines[0].size() - 1 && isNumber(lines[i][j + 1]))) {
    neighbors.push_back(make_pair(i, j + 1));
  }
  
  if (i < lines.size() - 1) {
    if ((j > 0 && isNumber(lines[i + 1][j - 1]))) {
      neighbors.push_back(make_pair(i + 1, j - 1));
    }
    if ((isNumber(lines[i + 1][j]))) {
      neighbors.push_back(make_pair(i + 1, j));
    }
    if ((j < lines[0].size() - 1 && isNumber(lines[i + 1][j + 1]))) {
      neighbors.push_back(make_pair(i + 1, j + 1));
    }
  }

  return neighbors;
}

struct Number {
  int value;
  int length;
  pair<int, int> startingCoord;
};

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
  Number numbers[nRows][nCols];
  vector<pair<int, int>> potentialGearLocations;
  for (int i = 0; i < nRows; i += 1) {
    string number = "";
    bool isPart = false;
    for (int j = 0; j < nCols; j += 1) {
      char c = lines[i][j];
      if (isNumber(c)) {
        number += c;
      } else {
        if (number.size() > 0) {
          Number n;
          n.value = stoi(number);
          n.length = number.size();
          n.startingCoord = make_pair(i, j - number.size());
          for (int k = j - number.size(); k < j; k += 1) {
            numbers[i][k] = n;
          }
          number = "";
        }
        if (c == '*') {
          potentialGearLocations.push_back(make_pair(i, j));
        }
      }
    }
    if (number.size() > 0) {
      Number n;
      n.value = stoi(number);
      n.length = number.size();
      n.startingCoord = make_pair(i, lines[0].size() - number.size());
      for (int k = lines[0].size() - number.size(); k < lines[0].size(); k += 1) {
        numbers[i][k] = n;
      }
      number = "";
    }
  }

  int gearRatioSum = 0;
  for (int i = 0; i < potentialGearLocations.size(); i += 1) {
    pair<int, int> potentialGear = potentialGearLocations[i];
    vector<pair<int, int>> numericalNeighborsCoords = getAdjacentNumbers(lines, potentialGear.first, potentialGear.second);
    if (numericalNeighborsCoords.size() > 1) {
      vector<Number> uniqueNeighbors;
      for (pair<int, int> neighborCoords : numericalNeighborsCoords) {
        Number neighbor = numbers[neighborCoords.first][neighborCoords.second];
        bool exists = false;
        for (int j = 0; j < uniqueNeighbors.size(); j += 1) {
          if (
            neighbor.value == uniqueNeighbors[j].value
            && neighbor.startingCoord == uniqueNeighbors[j].startingCoord
          ) {
            exists = true;
            break;
          }
        }
        if (!exists) {
          uniqueNeighbors.push_back(neighbor);
        }
      }
      if (uniqueNeighbors.size() == 2) {
        gearRatioSum += uniqueNeighbors[0].value * uniqueNeighbors[1].value;
      }
    }
  }

  cout << gearRatioSum << endl;
}
