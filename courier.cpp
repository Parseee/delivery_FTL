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

Request Courier::get_current_request() { return current_request_; }

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
    // if (!is_busy_) {
    Branch* br = branches_map[current_location_];
    if (br != nullptr) {
        x_ = br->getX() + 75 / 2.0 - 20;
        y_ = br->getY() - 15;
        Field courier(x_, y_, 40, 60);
        if (this->is_car())
            courier.setImage("images/car.png");
        else
            courier.setImage("images/default.png");
        courier.setText(std::to_string(number_), 18);
        courier.draw(window);
    }
    // } else {
    //     int from = current_request_.source;
    //     int to = current_request_.destination;
    //     double x1 = branches_map[from]->getX(), y1 =
    //     branches_map[from]->getY(),
    //            x2 = branches_map[to]->getX(), y2 = branches_map[to]->getY();
    //     double alpha, beta;
    //     beta = atan2(fabs(x1 - x2), fabs(y1 - y2));
    //     alpha = atan2(fabs(y1 - y2), fabs(x1 - x2));
    //     double length = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    //     double len = (current_request_.end_time -
    //     current_request_.start_time) /
    //                  (time_ - current_request_.end_time) *
    //                  (double)(ceil(length) / 10);
    //     if (x1 <= x2 && y1 <= y2) {
    //         y_ += sin(alpha) * len;
    //         x_ += cos(alpha) * len;
    //     } else if (x1 >= x2 && y1 <= y2) {
    //         y_ += sin(alpha) * len;
    //         x_ -= cos(alpha) * len;
    //     } else if (x1 <= x2 && y1 >= y2) {
    //         y_ -= sin(alpha) * len;
    //         x_ += cos(alpha) * len;
    //     } else if (x1 >= x2 && y1 >= y2) {
    //         y_ -= sin(alpha) * len;
    //         x_ -= cos(alpha) * len;
    //     }
    //}
}

int Courier::get_delivery_duration() {
    return get_current_request().end_time - get_current_request().start_time;
}

void Courier::add_wasted_time(int time_to_add) { wasted_time_ += time_to_add; }

bool Courier::is_clicked(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            double mouse_x = event.mouseButton.x;
            double mouse_y = event.mouseButton.y;
            if (mouse_x >= x_ && mouse_x <= x_ + 40 && mouse_y >= y_ &&
                mouse_y <= y_ + 60) {
                return true;
            }
        }
    }
    return false;
}

void Courier::draw_info(sf::RenderWindow& window) {
    Field req(1370, 30, 200, 200);
    req.setColor(sf::Color(211, 211, 211));
    Text req_text(1380, 40, 25, "COURIER " + std::to_string(number_),
                  sf::Color::Red);
    req.draw(window);
    req_text.draw(window);
    Text requests(1380, 75, 20,
                  "Completed: " + std::to_string(completed_requests_.size()));
    requests.draw(window);
    if (!is_busy_) {
        Text busy(1380, 110, 20, "Status: free");
        busy.draw(window);
    } else {
        Text busy(1380, 110, 20, "Status: working");
        Text from(1380, 145, 20,
                  "From: " + std::to_string(current_request_.source + 1));
        Text to(1380, 180, 18,
                "To: " + std::to_string(current_request_.destination + 1));
        busy.draw(window);
        from.draw(window);
        to.draw(window);
    }
}