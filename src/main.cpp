/// ----------------------- BEGIN HEADER FILE ----------------------------- //

#include <cmath>
#include <cstdio>
#include <iostream>
#include <optional>
#include <ostream>
#include <string>
#include <thread>

int main(int argc, char **argv);

int callback(std::string *);
int fib(int);

/// ------------------------- END HEADER FILE ----------------------------- //

// using namespace std; // for when you are dumb

int main(const int argc, char **argv) {
  std::cout << "Welcome to CSCI60!" << std::endl;

  // for (int i = 0; i < 5; i++) {
  // code in a loop
  // }
  int d = -4;
  // double pi(3.14);
  // bool good;
  // char c;
  // short h;
  // long e;

  // The same thing
  std::string explicit_string = "teast";
  char implicit_string[] = "waho";
  // \a == bell
  // \r == dos line return
  printf("%s\n", "Enter a number, double, bool, and char.");

  // can be serperated by newline or space
  // std::cin >> d >> pi >> good >> c;
  std::cin >> d;

  if (d == '\0') {
    printf("Enter a diget please\n");
  } else {
    printf("You entered: %d\n", d);
  }

  // free(argv);

  // printf("recived %d args\n", argc);

  // void *array = malloc(10);
  // array[0] = 'h';
  // array[1] = 'e';
  // array[2] = 'l';
  // array[3] = 'p';
  // array[4] = '\0';
  // printf("%s\n", array);
  // free(array);

  // std::pow(2, 4);
  // std::cos(2);

  std::cout << (3.0 / 4.0) << std::endl;

  // std::operator<<(std::cout, "test\n");

  std::string sss = "wha";
  std::string *s = &sss;

  std::thread::id id = std::this_thread::get_id();
  std::cout << "Thread id: " << id << std::endl;

  std::thread t = std::thread(&callback, s);

  for (int i = 0; i < 10; i++) {
    s->push_back('b');
    std::cout << *s << std::endl;
  }

  // std::cout << "hi from thread 1" << std::endl;
  // ss->pop_back();
  // std::cout << *ss << std::endl;

  // printf("Thread 1 says fib 41 is: %d\n", fib(41));

  // char str[80];
  // char staaa[80] = "Value of pi";
  // str[0] = 'a';
  // str[1] = '\0';
  // sprintf(str, "Value of Pi = %f", M_PI);
  // puts(str);

  t.join();
  return EXIT_SUCCESS;
}

/// Thread that is made to be an example of race condition
int callback(std::string *s) {
  // for (int i = 0; i < 10; i++) {
  // s->push_back('a');
  // std::cout << *s << std::endl;
  // }
  // s->pop_back();
  puts("hi from thread 2");
  std::this_thread::sleep_for(std::chrono::seconds(1));
  // printf("Thread 2 says fib 42 is: %d\n", fib(42));
  return 0;
}

int fib(int x) {
  switch (x) {
  case 0:
    return 0;
  case 1:
    return 1;
  default:
    return fib(x - 1) + fib(x - 2);
  }
}

struct Node {
  int data;
  struct Node *next;
};
