#include <cstring>
#include <iostream>

using namespace std;

const string russianVowels = "ауоиэыяюеё";  // Массив с русскими глассными
const int countVowels = (russianVowels.size() / 2);

int cmpVowels(string strInput) {
  int sum = 0;
  int lengthStrInput = strInput.size();
  for (int i = 0; i < lengthStrInput; i++) {
    for (int j = 0; j < countVowels; j++) {
      if (strInput[i] == russianVowels[j]) {
        sum++;
      }
    }
  }
  return sum;
}

int main() {
  setlocale(LC_ALL, "ru");
  string strInput;
  cin >> strInput;
  int sum = 0;
  sum = (cmpVowels(strInput));
  cout << sum;
  return 0;
}