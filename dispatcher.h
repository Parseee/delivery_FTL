#pragma once

#include "request.h"
#include "default_courier.h"
#include "car_courier.h"
#include "branch.h"
#include <vector>
#include <random>

#define DEFAULT_TIME_MULTIPLIER 720

#define REPLACE 1
const int SECONDS = 1800;

class Dispatcher {
 public: 
    Dispatcher(int, int); 
    Dispatcher(const Dispatcher&) = delete;
    Dispatcher(Dispatcher&&) = delete;

    void set_time_multiplier(int mult);
    time_t get_current_time() const;

    Request create_new_request ();
    void assign_new_request(Request request);

    // debug method
    Courier* get_last_courier_and_kill() {
        Courier* courier = couriers_.top();
        couriers_.pop();
        return courier;
    }

 private: 
    std::priority_queue < Courier * > couriers_;
    std::vector < Branch * >  branches_;
    int time_multiplier_;
    time_t time0;
    std::mt19937 generator;
};


Dispatcher::Dispatcher(int default_courier_amount, 
        int car_courier_amount) : time_multiplier_(DEFAULT_TIME_MULTIPLIER), 
                                  generator(std::random_device()()) { // snatched from the depths of the internet
    if (default_courier_amount + car_courier_amount > 7) {
        throw std::logic_error("Too much couriers");
    }
    int courier_number = 0;
    for (size_t i = 0; i < default_courier_amount; ++i) {
        couriers_.push(new DefaultCourier(courier_number++, i));
    }
    for (size_t i = 0; i < car_courier_amount; ++i) {
        couriers_.push(new CarCourier(courier_number++, i)); // make good numbers
    }
    time0 = time(nullptr);
}

void Dispatcher::set_time_multiplier(int mult) {
    time_multiplier_ = mult;
}

time_t Dispatcher::get_current_time() const {
    return (time(nullptr)) * time_multiplier_;
}

// edit end_time
Request Dispatcher::create_new_request () {
    return Request(Dispatcher::get_current_time(), 
                   Dispatcher::get_current_time() + SECONDS, REPLACE, REPLACE, REPLACE);
}

void Dispatcher::assign_new_request(Request request) {
    Courier *courier = couriers_.top();
    courier->add_new_request(request);
    courier->add_consumed_time(courier->get_delivery_duration());
    // anything else?
}