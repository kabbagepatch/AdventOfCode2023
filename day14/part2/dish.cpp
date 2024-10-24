#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
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

bool isNumber(char c) {
  return c >= '0' && c <= '9';
}

void print(vector<string> stuff) {
  for (string t : stuff) {
    cout << t << endl;
  }
  cout << endl;
  cout << endl;
}

int main () {
  ifstream myfile;
  myfile.open ("../input");
  vector<string> rocks;
  if (myfile.is_open()) {
    string lineString;
    while(getline(myfile, lineString)) {
      rocks.push_back(lineString);
    }
  }
  myfile.close();

  int rows = rocks.size();
  int cols = rocks[0].size();

  // print(rocks);

  int nCycles = 300;
  vector<int> loads;
  loads.push_back(-1);
  unordered_map<int, vector<int> > seenPositions;
  for (int c = 1; c < nCycles + 1; c += 1) {

    for (int d = 0; d < 4; d += 1) {
      for (int i = 1; i < rows; i += 1) {
        for (int j = 0; j < cols; j += 1) {
          if (rocks[i][j] == 'O') {
            for (int k = i - 1; k >= -1; k -= 1) {
              if (k == -1 || rocks[k][j] != '.') {
                rocks[i][j] = '.';
                rocks[k + 1][j] = 'O';
                break;
              }
            }
          }
        }
      }

      vector<string> rotated(cols, string(rows, ' '));
      for (int i = 0; i < rows; i += 1) {
        for (int j = 0; j < cols; j += 1) {
          rotated[j][rows - i - 1] = rocks[i][j];
        }
      }
      rocks = rotated;
    }

    int load = 0;
    for (int i = 0; i < rows; i += 1) {
      for (int j = 0; j < cols; j += 1) {
        if (rocks[i][j] == 'O') {
          load += rocks.size() - i;
        }
      }
    }

    loads.push_back(load);
    seenPositions[load].push_back(c);
    int patternStart = 0;
    int patternLength = 0;
    bool patternFound = false;
    if (seenPositions[load].size() > 2) {
      for (int i = 0; i < seenPositions[load].size() - 2; i += 1) {
        patternStart = seenPositions[load][i];
        for (int j = i + 1; j < seenPositions[load].size() - 1; j += 1) {
          int patternStart2 = seenPositions[load][j];
          patternLength = patternStart2 - patternStart;

          if (patternLength <= 1) {
            continue;
          }
        
          patternFound = true;
          for (int k = 0; k < patternLength; k += 1) {
            if (loads[patternStart + k] != loads[patternStart2 + k]) {
              patternFound = false;
              break;
            }
          }
        }

        if (patternFound) {
          break;
        }
      }
    }

    if (patternFound) {
      cout << c << " " << patternStart << " " << patternLength << endl;
      cout << loads[patternStart + (1000000000 - patternStart) % patternLength] << endl;
      break;
    }
  }
}
