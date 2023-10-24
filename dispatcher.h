#pragma once

#include <random>
#include <vector>
#include <climits>

#ifdef DEBUG
#include <iostream>
#endif

#include "branch.h"
#include "car_courier.h"
#include "default_courier.h"
#include "request.h"

#define DEFAULT_TIME_MULTIPLIER 720

#define REPLACE 1
const int SECONDS = 1800;

#define DEPRECATED

class Dispatcher {
   public:
    Dispatcher(int, int);
    Dispatcher(const Dispatcher&) = delete;
    Dispatcher(Dispatcher&&) = delete;

    void set_time_multiplier(int);
    time_t get_current_time() const;
    int get_simulated_time() const;
    int get_days() const;
    void tick();
    void update_days();

    Courier* get_courier(int);
    Request create_new_request();
    void assign_new_request(Request);

    // debug method
#ifdef DEPRECATED
    Courier* get_last_courier_and_kill() {
        Courier* courier = couriers_.back();
        couriers_.pop_back();
        return courier;
    }
#endif

   private:
    std::vector <Courier*> couriers_;
    std::vector < std::vector < std::pair < int, int > > > branches_; // must be filled with adjacency list
    // std::vector < Branch * >  branches_;
    time_t time0;
    int days_;
    int simulated_time_;
    int time_multiplier_;
    std::mt19937 generator;
};

Dispatcher::Dispatcher(int default_courier_amount, int car_courier_amount)
    : time_multiplier_(DEFAULT_TIME_MULTIPLIER),
      generator(std::random_device()()),
      simulated_time_(0),
      days_(0) {
    if (default_courier_amount + car_courier_amount > 7) {
        throw std::logic_error("Too much couriers");
    }
    int courier_number = 0;
    for (size_t i = 0; i < default_courier_amount; ++i) {
        couriers_.push_back(new DefaultCourier(courier_number++, i));
    }
    for (size_t i = 0; i < car_courier_amount; ++i) {
        couriers_.push_back(
            new CarCourier(courier_number++, i));  // make good numbers
    }

    branches_ = std::vector < std::vector < std::pair < int, int > > > {{{1, 1}, {2, 2}}, {{0, 1}, {2, 1}}, {{0, 2}, {1, 1}}};
    time0 = time(nullptr);
}

void Dispatcher::set_time_multiplier(int mult) { time_multiplier_ = mult; }

time_t Dispatcher::get_current_time() const {
    return (time(nullptr)) * time_multiplier_;
}

int Dispatcher::get_simulated_time() const { return simulated_time_; }

int Dispatcher::get_days() const { return days_; }

void Dispatcher::tick() { simulated_time_ += 1; }

void Dispatcher::update_days() {
    simulated_time_ = 0;
    ++days_;
}

Courier* Dispatcher::get_courier(int start_loc) {
    std::vector < int > distance(branches_.size(), INT32_MAX);
    std::priority_queue < std::pair < int, int > > q;

    distance[start_loc] = 0;
    q.push({0, start_loc});
    while (!q.empty()) {
        auto v = q.top().second;
        q.pop();

        for (auto u : branches_[v]) {
            if (distance[u.first] > distance[v] + u.second) {
                distance[u.first] = distance[v] + u.second;
                q.push({-distance[u.first], u.second});
            }
        }
    }

#ifdef DEBUG
    std::cout << "\n-------------\n";
    std::cout << "Distances are: ";
    for (auto elem : distance) {
        std::cout << elem << " ";
    }
    std::cout << "\n-------------\n";
    std::cout << "Couriers' locations are: ";
    for (auto elem : couriers_) {
        std::cout << elem->get_location() << " ";
    }
    std::cout << "\n-------------\n";
#endif

    int preferable_distance = INT_MAX;
    Courier *preferable_courier = nullptr;

    for (auto *courier : couriers_) {
        if (distance[courier->get_location()] < preferable_distance) {
            preferable_distance = distance[courier->get_location()];
            preferable_courier = courier;
        }
    }
    return preferable_courier;
}

// edit end_time
Request Dispatcher::create_new_request() {
    return Request(Dispatcher::get_current_time(),
                   Dispatcher::get_current_time() + SECONDS, REPLACE, REPLACE,
                   REPLACE);
}

void Dispatcher::assign_new_request(Request request) {
    Courier *courier = get_courier(request.source);
    if (courier == nullptr) {
        throw std::logic_error("No courier here!");
    }
    courier->add_new_request(request);
    courier->add_consumed_time(courier->get_delivery_duration());
}