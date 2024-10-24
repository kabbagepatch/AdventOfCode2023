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

  vector<vector<string> > patterns;
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
    int nRows = pattern.size();
    int nCols = pattern[0].size();
    bool found = false;
    for (int si = 0; si < nRows && !found; si += 1) {
      for (int sj = 0; sj < nCols && !found; sj += 1) {
        // Next smudge
        pattern[si][sj] = pattern[si][sj] == '.' ? '#' : '.';
        // Fix previous smudge
        if (si != 0 && sj == 0) pattern[si - 1][nCols - 1] = pattern[si - 1][nCols - 1] == '.' ? '#' : '.';
        else if (sj != 0) pattern[si][sj - 1] = pattern[si][sj - 1] == '.' ? '#' : '.';

        // Find horizontal line
        for (int i = 0; i < nRows - 1; i += 1) {
          if (isHorizontalReflection(pattern, i, i + 1)) {
            // Check if the smudge is actually on the mirror
            if ((i + 1 > nRows / 2 && si < i)
                || (i + 1 <= nRows / 2 && si > i)) {
              continue;
            }
            summary += 100 * (i + 1);
            found = true;
            break;
          }
        }
        if (found) break;

        // Find horizontal line
        for (int j = 0; j < nCols - 1; j += 1) {
          if (isVerticalReflection(pattern, j, j + 1)) {
            // Check if the smudge is actually on the mirror
            if ((j + 1 > nCols / 2 && sj < j)
                || (j + 1 <= nCols / 2 && sj > j)) {
              continue;
            }
            summary += j + 1;
            found = true;
            break;
          }
        }
        if (found) break;
      }
    }
  }

  cout << summary << endl;
}
