/// ----------------------- BEGIN HEADER FILE ----------------------------- //

#include <cerrno>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <optional>
#include <ostream>
#include <string>
#include <thread>
#include <climits> // tells what the word size is for the current arch with MAX_INT

int main(int argc, char **argv);

int callback(std::string *);
int fib(int);

/// ------------------------- END HEADER FILE ----------------------------- //

// using namespace std; // for when you are dumb

int main(const int argc, char **argv) {
  std::cout << "Welcome to CSCI60!" << std::endl;

  char *name = argv[0];

  // printf("Function name is: %s\n", name);

  int index = 0;
  char *arg = argv[index];
  while (arg != NULL) {
        printf("Arg[%d] is %s\n", index, arg);
    index++;
    arg = argv[index];
  }

  srand(time(0));
    // retruns between 0 and RAND_MAX
  std::cout << "Random value: " << rand() << std::endl;
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
  implicit_string[3] = 'q';

  // char *c_string = "waho";
  // c_string[3] = 'a';

  // \a == bell
  // \r == dos line return
  printf("Enter a number: ");

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

  std::sqrt(-1);
  if (errno != 0) {
    printf("no sqrt on negatives\n");
  }

  std::cout << (3.0 / 4.0) << std::endl;

  // char str[80];
  // char staaa[80] = "Value of pi";
  // str[0] = 'a';
  // str[1] = '\0';
  // sprintf(str, "Value of Pi = %f", M_PI);
  // puts(str);

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

  t.join();

  return EXIT_SUCCESS;
  // return EXIT_FAILURE;
}

/// Thread that is made to be an example of race condition
int callback(std::string *s) {
  // for (int i = 0; i < 10; i++) {
  // s->push_back('a');
  // std::cout << *s << std::endl;
  // }
  // s->pop_back();
  puts("hi from thread 2");
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
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
