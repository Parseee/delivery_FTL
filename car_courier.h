#pragma once
#include "courier.h"

#define COMMON_DEFAULT_TIME_CONSUMPTION 20

class CarCourier: public Courier {
 public:
    CarCourier(int num, int location) : 
        Courier(num, location, COMMON_DEFAULT_TIME_CONSUMPTION) {}

    virtual bool is_car() const override final { return true; }
    virtual int get_delivery_duration() const override final { return COMMON_DEFAULT_TIME_CONSUMPTION; }
};