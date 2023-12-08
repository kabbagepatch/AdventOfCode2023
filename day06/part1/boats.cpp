#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main () {
  int times[] = { 48, 93, 85, 95 };
  int distances[] = { 296, 1928, 1236, 1391 };
  int nRaces = 4;

  int nWaysProd = 1;
  for (int i = 0; i < nRaces; i += 1) {
    int wayIndex = 0;
    while (wayIndex < ((times[i] + 1) / 2)) {
      if (wayIndex * (times[i] - wayIndex) > distances[i]) {
        break;
      }
      wayIndex += 1;
    }
    int nWays = (((times[i] + 1) / 2) - wayIndex) * 2;
    if (times[i] % 2 == 0) {
      nWays += 1;
    }
    nWaysProd *= nWays;
    cout << nWays << endl;
  }

  cout << nWaysProd << endl;
}
