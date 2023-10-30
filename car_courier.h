#pragma once
#include "courier.h"

class CarCourier : public Courier {
   public:
    CarCourier(int num, int location) : Courier(num, location) {}

    virtual bool is_car() const override final { return true; }
};