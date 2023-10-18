#pragma once
#include <queue>
#include <vector>

#include "request.h"

class Courier {
 public:
  void setRequest(Request request);
  void startRequest(Request Request);
  void Update();
  virtual void setIsCar() = 0;

  int get_source() const { return request_.source; }
  int get_destination() const { return request_.destination; }
  int get_urgency() const { return request_.urgency; }
  int get_location() const { return current_location_; }
  Request get_current_request();
  bool is_car() { return is_car_; }

 protected:
  int number_;
  bool is_car_;
  int average_time_;

  std::queue<Request> pending_request_;
  std::vector<Request> completed_request_;
  Request current_request;
  int current_location_;
  bool is_free_;
  int actual_time_;
};