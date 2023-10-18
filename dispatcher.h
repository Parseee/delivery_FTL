#pragma once
#include <vector>
#include <iostream>
#include "request.h"

class Dispatcher {
public:
    Dispatcher (Request* request);
    void processRequests();
};
