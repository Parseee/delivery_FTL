#pragma once
#include <vector>
#include "request.h"

class Dispatcher {
public:
    std::vector<Request> requests;
    
    void processRequests();
};