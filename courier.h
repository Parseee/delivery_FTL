#pragma once
#include <vector>
#include "request.h"

class Courier {
 public:
    std::vector < Request > assignedRequests;

    void takeRequest(Request request);

    void executeRequest();

    int get_source() const { return request_.source; }

    int get_destination() const { return request_.destination; }

    int get_urgency() const { return request_.urgency; }

    int get_location() const { return current_location_; }

 private:

    Request request_;
    int current_location_;
};