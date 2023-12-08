#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<int> split(string s, string delimiter) {
  vector<int> results;
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

  int colonPos = lines[0].find_first_of(':');
  int barPos = lines[0].find_first_of('|');
  int nCards = lines.size();
  int scratchcardCounts[nCards] = { 0 };
  for (int i = 0; i < nCards; i += 1) {
    string line = lines[i];
    scratchcardCounts[i] += 1;
    int nMatches = 0;
    vector<int> winningNumbers = split(line.substr(colonPos + 2, barPos - 1 - (colonPos + 2)), " ");
    bool winningNumberExists[100] = { false };
    for (int number : winningNumbers) {
      winningNumberExists[number] = true;
    }
    vector<int> ticketNumbers = split(line.substr(barPos + 2), " ");
    for (int number : ticketNumbers) {
      if (winningNumberExists[number]) {
        nMatches += 1;
        scratchcardCounts[i + nMatches] += scratchcardCounts[i];
      }
    }
  }

  int nTotalScratchcards = 0;
  for (int nScartchCards : scratchcardCounts) {
    nTotalScratchcards += nScartchCards;
  }

  cout << nTotalScratchcards << endl;
}
