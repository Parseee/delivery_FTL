
#include "courier.h"

#include <vector>

#include "request.h"

void Courier::setRequest(Request request) {
  pending_request_.push(request);
  return;
}

void Courier::startRequest(Request request) {
  //current_request = pending.front()
  current_request = request;
  actual_time_ = average_time_ + deviation;
  is_free_ = false;
  current_request.start_time = time;
  return;
}

void Courier::Update() {
  if (current_request.start_time + actual_time_ == time) {
    current_request.end_time = time;
    current_location_ = current_request.destination;
    is_free_ = true;
    completed_request_.push_back(current_request);
    current_request = nullptr;
  }
  return;
}
