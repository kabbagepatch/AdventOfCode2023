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

  int load = 0;
  for (int i = 0; i < rows; i += 1) {
    for (int j = 0; j < cols; j += 1) {
      if (rocks[i][j] == 'O') {
        load += rocks.size() - i;
      }
    }
  }

  cout << load << endl;
}
