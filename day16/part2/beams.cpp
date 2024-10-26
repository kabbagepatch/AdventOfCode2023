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

struct Beam {
  int x;
  int y;
  char direction;
  bool exitedOrLooping;
};

int getNEnergizedCells(Beam initialBeam, vector<string> &grid, vector<vector<string> > beamArrivalDirections, int nRows, int nCols) {
  vector<Beam> beams;
  beams.push_back(initialBeam);

  bool allBeamsExitedOrLooping = false;
  while(!allBeamsExitedOrLooping) {
    allBeamsExitedOrLooping = true;
    int nBeams = beams.size();
    for (int b = 0; b < nBeams; b += 1) {
      Beam beam = beams[b];
      if (!beam.exitedOrLooping) {
        for (int i = 0; i < beamArrivalDirections[beam.x][beam.y].length(); i += 1) {
          if (beamArrivalDirections[beam.x][beam.y][i] == beam.direction) {
            beam.exitedOrLooping = true;
            break;
          }
        }
        if (beam.exitedOrLooping) {
          beams[b] = beam;
          continue;
        }

        allBeamsExitedOrLooping = false;
        beamArrivalDirections[beam.x][beam.y] += beam.direction;

                char curTile = grid[beam.x][beam.y];
        switch (curTile) {
          case '.': 
            break;
          case '\\':
            if (beam.direction == 'U') beam.direction = 'L';
            else if (beam.direction == 'D') beam.direction = 'R';
            else if (beam.direction == 'L') beam.direction = 'U';
            else if (beam.direction == 'R') beam.direction = 'D';
            break;
          case '/':
            if (beam.direction == 'U') beam.direction = 'R';
            else if (beam.direction == 'D') beam.direction = 'L';
            else if (beam.direction == 'L') beam.direction = 'D';
            else if (beam.direction == 'R') beam.direction = 'U';
            break;
          case '-':
            if (beam.direction == 'U' || beam.direction == 'D') {
              beam.direction = 'L';
              beams.push_back((Beam){beam.x, beam.y, 'R', false});
            }
            break;
          case '|':
            if (beam.direction == 'L' || beam.direction == 'R') {
              beam.direction = 'U';
              beams.push_back((Beam){beam.x, beam.y, 'D', false});
            }
            break;
        }

        int newX = beam.x;
        int newY = beam.y;
        switch (beam.direction) {
          case 'U': newX = beam.x - 1; break;
          case 'D': newX = beam.x + 1; break;
          case 'L': newY = beam.y - 1; break;
          case 'R': newY = beam.y + 1; break;
        }
        beam.x = newX;
        beam.y = newY;
        if (newY < 0 || newY >= nCols || newX < 0 || newX >= nRows) {
          beam.exitedOrLooping = true;
          beams[b] = beam;
          continue;
        }
      }
      beams[b] = beam;
    }
  }

  int nEnergized = 0;
  for (vector<string> row : beamArrivalDirections) {
    for (string s : row) {
      if (!s.empty()) {
        nEnergized += 1;
      }
    }
  }

  return nEnergized;
}

int main () {
  ifstream myfile;
  myfile.open ("../input");
  vector<string> grid;
  vector<vector<string> > beamArrivalDirections;
  if (myfile.is_open()) {
    string lineString;
    while(getline(myfile, lineString)) {
      grid.push_back(lineString);
      vector<string> empty;
      for (char c : lineString) {
        empty.push_back("");
      }
      beamArrivalDirections.push_back(empty);
    }
  }
  myfile.close();

  int nRows = grid.size();
  int nCols = grid[0].size();

  int maxNEnergized = -1;
  for (int i = 0; i < nCols; i += 1) {
    Beam initialBeam = { 0, i, 'D', false };
    int nEnergized = getNEnergizedCells(initialBeam, grid, beamArrivalDirections, nRows, nCols);
    if (nEnergized > maxNEnergized) {
      maxNEnergized = nEnergized;
    }

    initialBeam = (Beam){ nRows - 1, i, 'U', false };
    nEnergized = getNEnergizedCells(initialBeam, grid, beamArrivalDirections, nRows, nCols);
    if (nEnergized > maxNEnergized) {
      maxNEnergized = nEnergized;
    }
  }

  for (int i = 0; i < nRows; i += 1) {
    Beam initialBeam = { i, 0, 'R', false };
    int nEnergized = getNEnergizedCells(initialBeam, grid, beamArrivalDirections, nRows, nCols);
    if (nEnergized > maxNEnergized) {
      maxNEnergized = nEnergized;
    }

    initialBeam = (Beam){ i, nCols - 1, 'L', false };
    nEnergized = getNEnergizedCells(initialBeam, grid, beamArrivalDirections, nRows, nCols);
    if (nEnergized > maxNEnergized) {
      maxNEnergized = nEnergized;
    }
  }

  cout << maxNEnergized << endl;
}
