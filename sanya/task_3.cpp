#include <cstring>
#include <iostream>  //для ввода/вывода

using namespace std;

// int end()//функция не дающая закрыться консоли
// {
//     cout << endl << "END" << endl;
//     _getch();
//     return 0;
// }

const string russianVowels = "аяуюоеёэиы";  //Массив с русскими глассными
const int countVowels = (russianVowels.size() / 2);

int cmpVowels(string strInput) {
  int sum = 0;
  int lengthStrInput = strInput.size();
  for (int i = 0; i < lengthStrInput; i++) {
    for (int j = 0; j < countVowels; j++) {
      // cout << strInput[i] << " " << russianVowels[j];
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
  sum = cmpVowels(strInput);
  cout << sum;
  return 0;
}