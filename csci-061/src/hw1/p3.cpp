#include <iostream>
#include <queue>
#include <string>
#include <unistd.h>

using std::queue;
using std::string;

/// You are tasked with simulating a professor's office hours using C++
/// programming. In this simulation, you will create a queue of sample
/// questions that students have for the professor, and you will simulate
/// the professor answering these questions with a randomized delay.
int main(int argc, char *argv[]) {
  // seed random generation with current time.
  srand(time(nullptr));

  queue<string> questionQueue = queue<string>(
      {"What is the meaining of life?", "What is fun about english class?",
       "How do I get employed?", "Is there a better way to dance?",
       "Is this a good question?"});

  while (questionQueue.size() > 0) {
    // Print the question from the front of the queue.
    std::cout << questionQueue.front() << "\n";
    questionQueue.pop();

    // random wait between 1 and 3
    float wait = rand() / (RAND_MAX / 2.0) + 1.0;
    sleep(wait);

    std::cout << "Professor: That's a great question!\n";
  }

  std::cout << "All questions answered!" << std::endl;
  return 0;
}
