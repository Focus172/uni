#include <cerrno>
#include <chrono>
#include <climits> // tells what the word size is for the current arch with MAX_INT
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <istream>
#include <optional>
#include <ostream>
#include <thread>

// using namespace std; // for when you are dumb

int main(const int argc, char **argv) {
  // std::cout << "Welcome to CSCI60!" << std::endl;
  // char *name = argv[0];

  // printf("Function name is: %s\n", name);

  // int index = 0;
  // char *arg = argv[index];
  // while (arg != NULL) {
  //   printf("Arg[%d] is %s\n", index, arg);
  //   index++;
  //   arg = argv[index];
  // }

  // seed rng
  srand(time(0));
  // retruns between 0 and RAND_MAX
  // double d = rand();

  // \a == bell
  // \r == dos line return
  // printf("Enter a number: ");

  // std::sqrt(-1);
  // if (errno != 0) {
  //   printf("no sqrt on negatives\n");
  // }

  // std::thread::id id = std::this_thread::get_id();
  // std::cout << "Thread id: " << id << std::endl;
  //
  // std::thread t = std::thread(&callback, s);
  //
  // for (int i = 0; i < 10; i++) {
  //   s->push_back('b');
  //   std::cout << *s << std::endl;
  // }

  // t.join();

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
