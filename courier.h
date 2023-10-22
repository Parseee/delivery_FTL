#pragma once
#include <vector>
#include <queue>
#include "request.h"


class Courier {
 public: 
    Courier (int number, int location, int avg_time);
    Courier (const Courier&) = delete; // we don't need clones!
    Courier (Courier&& courier);
    virtual ~Courier() = default;
    virtual bool is_car() const = 0;
    virtual int get_delivery_duration() const = 0;
    int get_location() const { return current_location_; }
    void add_consumed_time(int time_to_add);

    Request get_curent_request();
    void add_new_request(Request request);
    Request give_away_current_request();

    bool operator<(Courier& courier);

 protected:

    unsigned int number_;
    unsigned int delivery_duration;
    // here we have an array and a priority_queue of requests assigned to every courier. \
       current request is pending_request_.top()
    std::priority_queue < Request > pending_request_;
    std::vector < Request > completed_requests_;
    unsigned int current_location_;
    unsigned int consumed_time_;
};

Courier::Courier(int number,
                 int location,
                 int avg_time) : number_(number),
                                 current_location_(location),
                                 delivery_duration(avg_time), 
                                 consumed_time_(0) {}

Courier::Courier(Courier&& courier) : number_(courier.number_),
                                      delivery_duration(courier.delivery_duration),
                                      pending_request_(std::move(courier.pending_request_)),
                                      completed_requests_(std::move(courier.completed_requests_)),
                                      current_location_(courier.current_location_),
                                      consumed_time_(courier.consumed_time_) {
    courier.number_ = 0;
    courier.delivery_duration = 0;
    courier.current_location_ = 0;
    courier.consumed_time_ = 0;
}

bool Courier::operator<(Courier& courier) {
    return this->get_curent_request().end_time > courier.get_curent_request().end_time;
}

Request Courier::get_curent_request() {
    if (pending_request_.empty()) {
        throw std::logic_error("There are no requests!");
    } else return pending_request_.top();
}

void Courier::add_consumed_time(int time_to_add) {
    consumed_time_ += time_to_add;
}

void Courier::add_new_request(Request request) {
    pending_request_.push(request);
}

Request Courier::give_away_current_request() {
    Request request = get_curent_request();
    pending_request_.pop();
    completed_requests_.push_back(request);
    return request;
}