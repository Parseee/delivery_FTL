#pragma once
#include "courier.h"

class CarCourier : public Courier {
  void setIsCar() { is_car_ = true; }
}