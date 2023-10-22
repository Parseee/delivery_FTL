#pragma once
#include <string>

struct Request {
    time_t start_time;
    time_t end_time;
    unsigned int source;
    unsigned int destination;
    unsigned int urgency;
    
    Request (time_t start_time,
             time_t end_time,
             unsigned int source,
             unsigned int destination,
             unsigned int urgency) : 
                                    start_time(start_time),
                                    end_time(end_time),
                                    source(source),
                                    destination(destination),
                                    urgency(urgency) {}

    bool operator<(const Request req) const {
        return this->urgency > req.urgency;
    } 
};