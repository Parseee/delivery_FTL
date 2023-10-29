#pragma once

#include <SFML/Graphics.hpp>
#include <climits>
#include <random>

#ifdef DEBUG
#include <iostream>
#endif

#include "car_courier.h"
#include "default_courier.h"
#include "gui.h"
#include "request.h"

#define DEFAULT_TIME_MULTIPLIER 720

#define REPLACE 1
const int SECONDS = 1800;
extern std::vector<std::pair<Branch*, Branch*>> branches_list;
extern std::vector<Branch*> branches;
extern std::vector<std::pair<int, int>> car_courier_list;
extern std::vector<std::pair<int, int>> default_courier_list;

#define DEPRECATED

class Dispatcher {
   public:
    Dispatcher() = default;
    Dispatcher(const Dispatcher&) = delete;
    Dispatcher(Dispatcher&&) = delete;

    void set_dispatcher();
    void set_time_multiplier(int);
    time_t get_current_time() const;
    int get_simulated_time() const;
    int get_days() const;
    void tick();
    void update_days();

    Courier* get_courier(int);
    Request create_new_request();
    void assign_new_request(Request);

    void drawCouriers(sf::RenderWindow& window);

    // debug method
#ifdef DEPRECATED
    Courier* get_last_courier_and_kill() {
        Courier* courier = couriers_.back();
        couriers_.pop_back();
        return courier;
    }
#endif

   private:
    std::vector<Courier*> couriers_;
    std::vector<std::vector<std::pair<int, int>>>
        branches_;  // must be filled with adjacency list
    // std::vector < Branch * >  branches_;
    time_t time0;
    int days_;
    int simulated_time_;
    int time_multiplier_;
    std::mt19937 generator;
};

void Dispatcher::set_dispatcher() {
    time_multiplier_ = DEFAULT_TIME_MULTIPLIER;

    generator.seed(time(nullptr));
    simulated_time_ = 0;
    days_ = 0;
    int courier_number = 0;
    for (int i = 0; i < couriers_.size(); ++i) {
        delete couriers_[i];
    }
    couriers_.clear();
    for (int i = 0; i < default_courier_list.size(); ++i) {
        couriers_.push_back(new DefaultCourier(default_courier_list[i].first,
                                               default_courier_list[i].second));
    }
    for (size_t i = 0; i < car_courier_list.size(); ++i) {
        couriers_.push_back(
            new CarCourier(car_courier_list[i].first,
                           car_courier_list[i].second));  // make good numbers
    }

    branches_.clear();
    branches_.resize(branches.size() + 1);
    for (int i = 0; i < branches_list.size(); ++i) {
        int a = branches_list[i].first->getNum();
        int b = branches_list[i].second->getNum();
        double x1 = branches_list[i].first->getX(),
               y1 = branches_list[i].first->getY(),
               x2 = branches_list[i].second->getX(),
               y2 = branches_list[i].second->getY();
        int len =
            (int)ceil(sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))) / 10;
        branches_[a].push_back({b, len});
        branches_[b].push_back({a, len});
    }
    time0 = time(nullptr);
}

void Dispatcher::set_time_multiplier(int mult) { time_multiplier_ = mult; }

time_t Dispatcher::get_current_time() const {
    return (time(nullptr)) * time_multiplier_;
}

int Dispatcher::get_simulated_time() const { return simulated_time_; }

int Dispatcher::get_days() const { return days_; }

void Dispatcher::tick() {
    simulated_time_ += 1;

    for (auto courier : couriers_) {
        if (courier->get_curent_request().end_time <= get_simulated_time()) {
            courier->give_away_current_request();
            // anything else?
        }
    }
}

void Dispatcher::update_days() {
    simulated_time_ = 0;
    ++days_;
}

Courier* Dispatcher::get_courier(int start_loc) {
    std::vector<int> distance(branches_.size(), INT32_MAX);
    std::priority_queue<std::pair<int, int>> q;

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
    Courier* preferable_courier = nullptr;

    for (auto* courier : couriers_) {
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
    Courier* courier = get_courier(request.source);
    if (courier == nullptr) {
        throw std::logic_error("No courier here!");
    }
    courier->add_new_request(request);
    courier->add_consumed_time(courier->get_delivery_duration());
}

void Dispatcher::drawCouriers(sf::RenderWindow& window) {
    for (int i = 0; i < couriers_.size(); ++i) {
        couriers_[i]->draw(window);
    }
}