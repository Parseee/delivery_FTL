#pragma once
#include <vector>
#include "request.h"

class Dispatcher {
public:
    Dispatcher(Request *request) {
        std::cout << "good\n";
    }
    void processRequest();
 private:
    Request request;
};