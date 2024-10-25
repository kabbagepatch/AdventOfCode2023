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
  vector<string> lines;
  if (myfile.is_open()) {
    string lineString;
    while(getline(myfile, lineString)) {
      lines.push_back(lineString);
    }
  }
  myfile.close();

  vector<string> steps = split(lines[0], ",");
  vector<pair<string, int> > lenses[256];
  for (string step : steps) {
    string label = "";
    int hash = 0;
    char operation;
    int focalLength = 0;
    for (int i = 0; i < step.length(); i += 1) {
      char c = step[i];
      if (c == '-' || c == '=') {
        operation = c;
        if (c == '=') focalLength = (int)step[i + 1] - '0';
        break;
      }
      label += c;
      hash += (int)c;
      hash *= 17;
      hash %= 256;
    }

    int existingIndex = -1;
    for (int j = 0; j < lenses[hash].size(); j += 1) {
      pair<string, int> lens = lenses[hash][j];
      if (lens.first == label) {
        existingIndex = j;
        break;
      }
    }

    if (existingIndex == -1) {
      if (operation == '=') {
        lenses[hash].push_back(make_pair(label, focalLength));
      }
    } else {
      if (operation == '=') {
        lenses[hash][existingIndex].second = focalLength;
      } else {
        lenses[hash].erase(lenses[hash].begin() + existingIndex);
      }
    }
  }

  int power = 0;
  for (int i = 0; i < 256; i += 1) {
    if (!lenses[i].empty()) {
      for (int j = 0; j < lenses[i].size(); j += 1) {
        power += (i + 1) * (j + 1) * lenses[i][j].second;
      }
    }
  }

  cout << power << endl;
}
