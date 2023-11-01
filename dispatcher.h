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

#define REPLACE 1
const int SECONDS = 1800;
extern std::vector<std::pair<Branch*, Branch*>> branches_list;
extern std::vector<Branch*> branches;
extern std::vector<std::pair<int, int>> car_courier_list;
extern std::vector<std::pair<int, int>> default_courier_list;

class Dispatcher {
   public:
    Dispatcher() = default;
    Dispatcher(const Dispatcher&) = delete;
    Dispatcher(Dispatcher&&) = delete;

    void set_dispatcher();
    int get_simulated_time() const;
    void tick();
    bool probability(int input_time);

    Courier* get_courier(int, Request&);
    Request create_new_request(std::pair<int, int> deviation);
    void assign_new_request();
    void print_time(sf::RenderWindow& window);

    void drawCouriers(sf::RenderWindow& window, int time_);
    std::vector<Courier*> get_couriers() { return couriers_; }
    void add_request(Request request);

   private:
    std::vector<Courier*> couriers_;
    std::vector<std::vector<std::pair<int, int>>>
        branches_;  // must be filled with adjacency list
    // std::vector < Branch * >  branches_;
    std::priority_queue<Request> requests_;
    int simulated_time_;
    std::mt19937 generator;
};

void Dispatcher::set_dispatcher() {
    simulated_time_ = 0;
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
    branches_.resize(branches.size());
    for (int i = 0; i < branches_list.size(); ++i) {
        int a = branches_list[i].first->getNum() - 1;
        int b = branches_list[i].second->getNum() - 1;
        double x1 = branches_list[i].first->getX(),
               y1 = branches_list[i].first->getY(),
               x2 = branches_list[i].second->getX(),
               y2 = branches_list[i].second->getY();
        int len =
            (int)ceil(sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))) / 10;
        branches_[a].push_back({b, len});
        branches_[b].push_back({a, len});
    }
}

int Dispatcher::get_simulated_time() const { return simulated_time_; }

void Dispatcher::tick() {
    simulated_time_ += 1;

    for (auto courier : couriers_) {
        if (courier->is_busy()) {
            if (courier->get_current_request().end_time <=
                get_simulated_time()) {
                courier->give_away_current_request();
            }
        }
        // animation
    }
}

Courier* Dispatcher::get_courier(int start_loc, Request& request) {
    std::vector<int> distance(branches_.size(), INT32_MAX);
    std::priority_queue<std::pair<int, int>> q;

    distance[start_loc] = 0;
    q.push({0, start_loc});
    while (!q.empty()) {
        auto v = q.top().second;
        q.pop();

        for (auto u : branches_[v]) {
            // for (int i = 1; i < branches_[v].size(); ++i) {
            //     auto u = branches_[v][i];
            if (distance[u.first] > distance[v] + u.second) {
                distance[u.first] = distance[v] + u.second;
                q.push({-distance[u.first], u.first});
            }
        }
    }

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

    int preferable_distance = INT_MAX;
    Courier* preferable_courier = nullptr;

    for (auto* courier : couriers_) {
        if (distance[courier->get_location()] < preferable_distance) {
            preferable_distance = distance[courier->get_location()];
            preferable_courier = courier;
        }
    }
    preferable_distance += distance[request.destination];
    preferable_courier->add_wasted_time(preferable_distance);
    request.end_time += preferable_distance;
    return preferable_courier;
}

Request Dispatcher::create_new_request(std::pair<int, int> deviation) {
    generator = std::move(std::mt19937(time(nullptr)));
    return Request(Dispatcher::get_simulated_time(),
                   Dispatcher::get_simulated_time() +
                       (deviation.first +
                        generator() % (deviation.second - deviation.first + 1)),
                   generator() % branches_.size(),
                   generator() % branches_.size(), generator() % 3);

    // A + rand() % (B - A + 1);
}

void Dispatcher::assign_new_request() {
    if (!requests_.empty()) {
        Request request = requests_.top();
        Courier* courier = get_courier(request.source, request);
        if (courier != nullptr) {
            requests_.pop();
            courier->set_request(request);
            courier->add_consumed_time(courier->get_delivery_duration());
        }
    }
}

void Dispatcher::drawCouriers(sf::RenderWindow& window, int time_) {
    for (int i = 0; i < couriers_.size(); ++i) {
        couriers_[i]->draw(window, time_);
    }
}

bool Dispatcher::probability(int input_time) {
    generator = std::move(std::mt19937(time(nullptr)));
    double probability;

    if (input_time < 240) {
        probability = 0.1;  // Morning (before 12:00 PM)
    } else if (input_time < 360) {
        probability = 0.5;  // Afternoon (from 12:00 to 14:00)
    } else {
        probability = 0.2;  // Evening (after 4:00 PM)
    }
    std::bernoulli_distribution dist(probability);
    return dist(generator);
}

void Dispatcher::print_time(sf::RenderWindow& window) {
    int temp = (simulated_time_) % 540 + 540;
    int hours = temp / 60;
    int minutes = temp % 60;
    std::string h_str = std::to_string(hours);
    std::string m_str = std::to_string(minutes);
    if (h_str.length() < 2) h_str = '0' + h_str;
    if (m_str.length() < 2) m_str = '0' + m_str;
    Text t(100, 760, 30, h_str + " : " + m_str);
    t.draw(window);
}

void Dispatcher::add_request(Request request) { requests_.push(request); }