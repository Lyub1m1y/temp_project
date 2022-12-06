#include <cstring>
#include <iostream>

using namespace std;

int counterWord(int n, string strInput) {
  int sum = 0;
  int length = strInput.size();
  for (int i = 0, j = 0; i < length; i++) {md
    if (strInput.at(i) != ' ') {
      if (j < n && strInput.at(j + 1) == (' ' || strInput.at(length))) {
        sum++;
        j++;
      } else {
        j = 0;
      }
    }
  }
  return sum;
}

int main() {
  int n = 0;
  string strInput;
  cin >> n;
  cin >> strInput;
  int sum = 0;
  sum = (counterWord(n, strInput));
  cout << sum << endl;
  return 0;
}
