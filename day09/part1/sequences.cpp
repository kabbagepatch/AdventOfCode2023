#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void print(vector<long> stuff) {
  for (long t : stuff) {
    cout << t << " ";
  }
  cout << endl;
}

long sum(vector<long> stuff) {
  long sum = 0;
  for (long t : stuff) {
    sum += t;
  }
  return sum;
}

vector<long> split(string s, string delimiter) {
  vector<long> results;
  size_t pos = 0;
  string token;
  while ((pos = s.find(delimiter)) != string::npos) {
      token = s.substr(0, pos);
      if (token.length() > 0) {
        results.push_back(stoi(token));
      }
      s.erase(0, pos + delimiter.length());
  }
  if (s.length() > 0) {
    results.push_back(stoi(s));
  }
  return results;
}

bool isNumber(char c) {
  return c >= '0' && c <= '9';
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

  long extrapolatedSum = 0;
  for (string line : lines) {
    vector<long> values = split(line, " ");
    long extrapolatedValue = 0;
    while(!(all_of(values.begin(), values.end(), [](int i) { return i == 0; }))) {
      extrapolatedValue += values[values.size() - 1];

      vector<long> newValues;
      for (long i = 0; i < values.size() - 1; i += 1) {
        newValues.push_back(values[i + 1] - values[i]);
      }
      values = newValues;
    }
    // cout << extrapolatedValue << endl;
    extrapolatedSum += extrapolatedValue;
  }

  cout << endl << extrapolatedSum << endl;
}
