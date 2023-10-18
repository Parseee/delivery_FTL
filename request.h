#pragma once
#include <string>

struct Request {
  int start_time;
  int end_time;
  int source;
  int destination;
  int urgency;
};