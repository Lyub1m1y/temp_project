#include <iostream>

using namespace std;
//зачем выёживаться и писать в условии задачи двойное слово, а не просто указать
//кол-во байт?!  Выберу по своему желанию 8 байт на основе x64
int main() {
  int n = 0, result = 0;
  cin >> n;
  while (n != 0) {
    result += n % 10;
    n /= 10;
  }
  cout << result;
  return 0;
}
