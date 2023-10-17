#include <iostream>
#include <vector>
#include <random>
#include "request.h"
#include "courier.h"
#include "dispatcher.h"
#include "branch.h"

int main() {
    // some code for gui

    while (true) {
        // add random time for waiting
        Request *request = new Request();
        Dispatcher dispatcher(request);
    }
}
