#include <iostream>
#include <random>
#include <vector>

#include "include/courier.h"
#include "include/request.h"

// please use mt as randomizer!!!

// i think its need to use vector with current active couriers to update status (and location) 
// for each courier

int main() {
  // some code for gui
  Request *request = new Request();
  //in cycle we will update status for each courier because they can deliver requests in parallel
}
