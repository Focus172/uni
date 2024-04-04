#include "Bigint.h"
#include <iostream>

using namespace std;

int main() {
  Bigint a;

  cout << Bigint(-123) << endl;
  cout << Bigint(0) << endl;
  cout << Bigint(123) << endl;
  cout << Bigint("-123") << endl;
  cout << Bigint("0") << endl;
  cout << Bigint("123") << endl;
  cout << Bigint() << endl;
  cout << "Please type -12345: ";
  cin >> a;
  cout << "a = " << a << endl;
  cout << endl;
  cout << Bigint("-12345678901234567890") + Bigint("12345678901234567890")
       << endl;
  cout << Bigint("12345678901234567890") + Bigint("-12345678901234567890")
       << endl;
  cout << Bigint("-12345678901234567890") + Bigint("1234567890123456789")
       << endl;
  cout << Bigint("1234567890123456789") + Bigint("-12345678901234567890")
       << endl;
  cout << Bigint("-1234567890123456789") + Bigint("12345678901234567890")
       << endl;
  cout << Bigint("12345678901234567890") + Bigint("-1234567890123456789")
       << endl;
  cout << Bigint("-12345678901234567890") + Bigint("-12345678901234567890")
       << endl;
  cout << Bigint("12345678901234567890") + Bigint("12345678901234567890")
       << endl;

  return 0;

  // std::cout << "a := 2" << std::endl;
  // Biguint a = Biguint(2);
  // std::cout << "a = " << a << std::endl;
  // std::cout << "a += 4" << std::endl;
  // a += Biguint(4);
  // std::cout << "a = " << a << std::endl;
  // std::cout << "a += " << 0xFFFFFFF5 << std::endl;
  // a += 0xFFFFFFF5;
  // std::cout << "a = " << a << std::endl;
  // std::cout << "a += 7" << std::endl;
  // a += 7;
  // std::cout << "a = " << a << std::endl;
  // std::cout << "a += " << 0xF << std::endl;
  // a += 0xF;
  // std::cout << "a = " << a << std::endl;
  // std::cout << "a -= 4" << std::endl;
  // a -= 4;
  // std::cout << "a = " << a << std::endl;
  // std::cout << "a -= 19" << std::endl;
  // a -= 19;
  // std::cout << "a = " << a << std::endl;
  //
  // std::cout << "a := 5" << std::endl;
  // a = Biguint("5");
  // std::cout << "a = " << a << std::endl;
  //
  // std::cout << "a *= " << a << std::endl;
  // a *= a;
  // std::cout << "a = " << a << std::endl;
  //
  // std::cout << "a = a >> 2" << std::endl;
  // a = a >> 2;
  // std::cout << "a = " << a << std::endl;
  //
  // std::cout << "a = a << 1" << std::endl;
  // a = a << 1;
  // std::cout << "a = " << a << std::endl;
  //
  // std::cout << "a = a >> 10" << std::endl;
  // a = a >> 10;
  // std::cout << "a = " << a << std::endl;
  //
  // std::cout << "a = a >> 30" << std::endl;
  // a = a >> 30;
  // std::cout << "a = " << a << std::endl;
  //
  // std::cout << "a = a << 29" << std::endl;
  // a = a << 29;
  // std::cout << "a = " << a << std::endl;
  //
  // std::cout << "a /= 2" << std::endl;
  // a /= 2;
  // std::cout << "a = " << a << std::endl;
  //
  // std::cout << "a /= 10" << std::endl;
  // a /= 10;
  // std::cout << "a = " << a << std::endl;
  //
  // std::cout << "a /= 250" << std::endl;
  // a /= 250;
  // std::cout << "a = " << a << std::endl;
  //
  // std::cout << "a / 4 = " << a / 4 << std::endl;
  //
  // // a *= 0xFFFFFF55;
  // // std::cout << a << std::endl;
  // // a *= a;
  // // std::cout << a << std::endl;
  // // a *= a;
  // // std::cout << a << std::endl;
  //
  // return 0;
}
