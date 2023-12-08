#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main () {
  long times[] = { 48938595 };
  long distances[] = { 296192812361391 };
  int nRaces = 1;


  long nWaysProd = 1;
  for (int i = 0; i < nRaces; i += 1) {
    long wayIndex = 0;
    while (wayIndex < ((times[i] + 1) / 2)) {
      if (wayIndex * (times[i] - wayIndex) > distances[i]) {
        break;
      }
      wayIndex += 1;
    }
    long nWays = (((times[i] + 1) / 2) - wayIndex) * 2;
    if (times[i] % 2 == 0) {
      nWays += 1;
    }
    nWaysProd *= nWays;
    cout << nWays << endl;
  }

  cout << nWaysProd << endl;
}
