#include "courier.h"

#include <SFML/Graphics.hpp>
#include <map>
#include <queue>
#include <vector>

#include "gui.h"
#include "request.h"

extern std::map<int, Branch*> branches_map;

Courier::Courier(int number, int location, int avg_time)
    : number_(number),
      current_location_(location),
      delivery_duration(avg_time),
      consumed_time_(0) {}

Courier::Courier(Courier&& courier)
    : number_(courier.number_),
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

Request Courier::get_curent_request() {
    if (pending_request_.empty()) {
        throw std::logic_error("There are no requests!");
    } else
        return pending_request_.top();
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

void Courier::draw(sf::RenderWindow& window) {
    Branch* br = branches_map[current_location_];
    if (br != nullptr) {
        Field courier(br->getX() + 75 / 2.0 - 15, br->getY() - 15, 30, 60);
        if (this->is_car())
            courier.setImage("images/car.png");
        else
            courier.setImage("images/default.png");
        courier.setText(std::to_string(number_), 18);
        courier.draw(window);
    }
}