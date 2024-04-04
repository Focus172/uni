#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

/// Define a FoodOrder struct with the following attributes:
/// - name (a string): Represents the name of the food item.
/// - priority (an integer): Represents the priority of the order, with higher
/// values indicating more urgent orders.
struct FoodOrder {
  std::string name;
  uint32_t priority;
};

// You are tasked with creating a C++ program for a restaurant to manage food
// orders using a priority queue. Your program should follow these
// specifications:
// - Implement a custom comparison operator for  FoodOrder objects to ensure
// that higher-priority orders are processed first in the priority queue.
//
// - Create a  priority_queue of  FoodOrder objects called  orderQueue to manage
// food orders.
//
// - Implement a function called  processOrder that simulates the processing
// of food orders. For this simulation, assume that it takes 2 seconds to
// prepare each food item.
//
// - Add at least five example food orders with different priorities to the
// orderQueue.
//
// - Simulate the processing of food orders by dequeuing orders from the
// priority queue one by one, calling the processOrder  function for each
// order, and displaying a message indicating that the order is ready. */
//
// - Test your program with the provided example food orders and provide the
// expected output.
/* Input:  */
/**/
/* Food Name       Priority */
/* -------------------------- */
/* Pizza           3 */
/* Burger          2 */
/* Salad           1 */
/* Pasta           3 */
/* Ice Cream       2 */

/// Output:
/// Restaurant Orders:
/// Preparing Pizza (Priority: 3)
/// Order for Pizza (Priority: 3) is ready.
/// Preparing Pasta (Priority: 3)
/// Order for Pasta (Priority: 3) is ready.
/// Preparing Burger (Priority: 2)
/// Order for Burger (Priority: 2) is ready.
/// Preparing Ice Cream (Priority: 2)
/// Order for Ice Cream (Priority: 2) is ready.
/// Preparing Salad (Priority: 1)
/// Order for Salad (Priority: 1) is ready.
int main(int argc, char *argv[]) {
  std::vector<FoodOrder> orders{
      {"Pizza", 3}, {"Burger", 2}, {"Salad", 1}, {"Pasta", 3}, {"Ice Cream", 2},
  };

  constexpr auto comp = [](FoodOrder &lhs, FoodOrder &rhs) {
    return lhs.priority < rhs.priority;
  };

  std::make_heap(orders.begin(), orders.end(), comp);

  while (orders.size() > 0) {
    FoodOrder top = orders.front();
    std::cout << "Preparing " << top.name << " (Priority: " << top.priority
              << ")\n";

    // pop the top then remove it from out buffer
    std::pop_heap(orders.begin(), orders.end(), comp);
    orders.pop_back();

    std::cout << "Order for " << top.name << " (Priority: " << top.priority
              << ") is ready.\n";
  }

  std::cout << std::endl;

  return 0;
}
