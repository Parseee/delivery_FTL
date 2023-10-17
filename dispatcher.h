#pragma once
#include <vector>
#include "request.h"

class Dispatcher {
public:
    Dispatcher (Request* request) {
        
    }
    void processRequests();
};