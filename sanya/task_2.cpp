#include <iostream>

using namespace std;
//����� ����������� � ������ � ������� ������ ������� �����, � �� ������ �������
//���-�� ����?!  ������ �� ������ ������� 8 ���� �� ������ x64
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
