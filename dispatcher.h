#pragma once

#include "request.h"
#include "default_courier.h"
#include "car_courier.h"
#include "branch.h"
#include <vector>
#include <random>

#define DEFAULT_TIME_MULTIPLIER 720

class Dispatcher {
 public: 
    Dispatcher(unsigned int default_courier_amount, 
    unsigned int car_courier_amount) : 
                                    time_multiplier_(DEFAULT_TIME_MULTIPLIER), 
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
    Dispatcher(const Dispatcher&) = delete;
    Dispatcher(Dispatcher&&) = delete;

    void set_time_multiplier(int mult) {
        time_multiplier_ = mult;
    }

    time_t get_current_time() const {
        return (time(nullptr) - time0) * time_multiplier_;
    }

    Request* create_new_request () {
        return new Request(get_current_time(), 1, 2, 2);
    }

    int assign_new_request(Request *request) {
        Courier *courier = couriers_.top();
        courier->add_new_request(request);
        courier->add_consumed_time(1); // where to get consumed time????
        // anything else?
    }

 private: 
    std::priority_queue < Courier *,
     std::vector < Courier * >,
     std::greater < Courier ** > > 
     couriers_;
    std::vector < Branch * >  branches_;
    int time_multiplier_;
    time_t time0;
    std::mt19937 generator;
};