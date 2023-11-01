#include "courier.h"

#include <SFML/Graphics.hpp>
#include <map>
#include <queue>
#include <vector>

#include "gui.h"
#include "request.h"

extern std::map<int, Branch*> branches_map;

Courier::Courier(int number, int location)
    : number_(number), current_location_(location), consumed_time_(0) {}

Courier::Courier(Courier&& courier)
    : number_(courier.number_),
      current_request_(courier.current_request_),
      completed_requests_(std::move(courier.completed_requests_)),
      current_location_(courier.current_location_),
      consumed_time_(courier.consumed_time_) {
    courier.number_ = 0;
    courier.current_location_ = 0;
    courier.consumed_time_ = 0;
}

Request Courier::get_current_request() {
    if (is_busy_)
        return current_request_;
    else
        throw std::logic_error("There are no requests!");
}

void Courier::add_consumed_time(int time_to_add) {
    consumed_time_ += time_to_add;
}

void Courier::set_request(Request request) {
    current_request_ = request;
    is_busy_ = true;
}

Request Courier::give_away_current_request() {
    Request request = get_current_request();
    is_busy_ = false;
    completed_requests_.push_back(request);
    current_location_ = request.destination;
    return request;
}

void Courier::draw(sf::RenderWindow& window, int time_) {
    if (!is_busy_) {
        Branch* br = branches_map[current_location_];
        if (br != nullptr) {
            x_ = br->getX() + 75 / 2.0 - 20;
            y_ = br->getY() - 15;
        }
    } else {
        int from = current_request_.source;
        int to = current_request_.destination;
        double x1 = branches_map[from]->getX(), y1 = branches_map[from]->getY(),
               x2 = branches_map[to]->getX(), y2 = branches_map[to]->getY();
        double alpha, beta;
        beta = atan2(fabs(x1 - x2), fabs(y1 - y2));
        alpha = atan2(fabs(y1 - y2), fabs(x1 - x2));
        double len = (current_request_.end_time - current_request_.start_time) /
                     (time_ - current_request_.end_time);
        if (x1 <= x2 && y1 <= y2) {
            y_ += sin(alpha) * len;
            x_ += cos(alpha) * len;
        } else if (x1 >= x2 && y1 <= y2) {
            y_ += sin(alpha) * len;
            x_ -= cos(alpha) * len;
        } else if (x1 <= x2 && y1 >= y2) {
            y_ -= sin(alpha) * len;
            x_ += cos(alpha) * len;
        } else if (x1 >= x2 && y1 >= y2) {
            y_ -= sin(alpha) * len;
            x_ -= cos(alpha) * len;
        }
    }
    Field courier(x_, y_, 40, 60);
    if (this->is_car())
        courier.setImage("images/car.png");
    else
        courier.setImage("images/default.png");
    courier.setText(std::to_string(number_), 18);
    courier.draw(window);
}

int Courier::get_delivery_duration() {
    return get_current_request().end_time - get_current_request().start_time;
}

void Courier::add_wasted_time(int time_to_add) { wasted_time_ += time_to_add; }