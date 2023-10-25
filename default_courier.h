#pragma once

#include "courier.h"
#define COMMON_CAR_TIME_CONSUMPTION 40

class DefaultCourier : public Courier {
   public:
    DefaultCourier(int number, int location)
        : Courier(number, location, COMMON_CAR_TIME_CONSUMPTION) {}

    virtual bool is_car() const override final { return false; }
    virtual int get_delivery_duration() const override final {
        return COMMON_CAR_TIME_CONSUMPTION;
    }
   private:
};