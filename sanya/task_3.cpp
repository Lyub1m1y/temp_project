#include <cstring>
#include <iostream>

using namespace std;

const string russianVowels = "aouiey";
const int countVowels = russianVowels.size();

int cmpVowels(string strInput) {
  int sum = 0;
  int lengthStrInput = strInput.size();
  for (int i = 0; i < lengthStrInput; i++) {
    for (int j = 0; j < countVowels; j++) {
      if (strInput.at(i) == russianVowels.at(j)) {
        sum++;
      }
    }
  }
  return sum;
}

int main() {
  string strInput;
  cin >> strInput;
  int sum = 0;
  sum = (cmpVowels(strInput));
  cout << sum;
  return 0;
}