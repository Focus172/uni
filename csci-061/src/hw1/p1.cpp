#include <iostream>
#include <stack>
#include <string>

using std::stack;
using std::string;

// returns a magic value repersentative of the presendence of the operator.
// Usefull only for comparing given the output on two different characters.
// returns -1 if is not in list of known operators.
int token_presedence(char t) {
  switch (t) {

  case '(':
    return 1000;
  case ')':
    return 1000;
  case '+':
    return 4;
  case '-':
    return 4;
  case '*':
    return 2;
  case '/':
    return 2;
  case '^':
    return 1;
  default:
    return -1;
  }
}

/// Write a C++ program that can take in a mathematical expression
/// in "infix" notation and converts it to 'postfix' notation.
string infix_to_postfix(string infix) {
  string postfix;
  stack<char> operators;

  for (char c : infix) {

    if (c == ' ') {
      continue;
    }
    // if its an operand or number
    if (token_presedence(c) == -1) {
      // append it to expression
      postfix.push_back(c);

      // if is opening paren
    } else if (c == '(') {
      // push it to stack
      operators.push(c);

      // if is close paren
    } else if (c == ')') {
      while (operators.top() != '(') {
        // move top to ret string
        postfix.push_back(' ');
        postfix.push_back(operators.top());
        operators.pop();

        // PERF: there is no to ever check in an ideal beacuse every open has
        // a clse but we live in the real world.
        if (operators.empty()) {
          std::cerr << std::endl
                    << "ERROR: expr is missing an open parenthesis."
                    << std::endl;
          return "";
        }
      }
      operators.pop(); // remove the open paren

      // its a operator
    } else {
      while (!operators.empty() &&
             token_presedence(c) >= token_presedence(operators.top())) {

        // pop operator and append it to expr
        postfix.push_back(' ');
        postfix.push_back(operators.top());
        operators.pop();
      }

      operators.push(c);
      postfix.push_back(' ');
    }
  }

  while (!operators.empty()) {
    if (operators.top() == '(') {
      std::cerr << std::endl
                << "ERROR: expr is missing a closing parenthesis." << std::endl;
      return "";
    }
    postfix.push_back(' ');
    postfix.push_back(operators.top());
    operators.pop();
  }

  return postfix;
}

int main(int argc, char *argv[]) {
  std::cout << "Testing the code!\n";

  /* std::cout << infix_to_postfix("4*4-2") << "\n"; */
  /* std::cout << infix_to_postfix("(((A + B) * C) - ((D - E) * (F + G)))") */
  /*           << "\n"; */

  std::cout << "I: a+b*(c^d-e)^(f+g*h)-i\n";
  std::cout << "O: " << infix_to_postfix("a+b*(c^d-e)^(f+g*h)-i") << "\n";
  std::cout << "A: a b c d ^ e - f g h * + ^ * + i -\n";

  std::cout << "\n";

  std::cout << "I: A*(B+C)/D\n";
  std::cout << "O: " << infix_to_postfix("A*(B+C)/D") << "\n";
  std::cout << "A: A B C + * D /\n";

  /* std::cout << infix_to_postfix("13+2 / 12") << std::endl; */

  /* std::cout << infix_to_postfix("(2 + 2*4 / 12") << std::endl; */
  /* std::cout << infix_to_postfix("21/4 - 2 + 12) / 2") << std::endl; */

  return 0;
}
