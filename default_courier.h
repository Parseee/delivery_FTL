#pragma once

#include "courier.h"

class DefaultCourier : public Courier {
   public:
    DefaultCourier(int number, int location) : Courier(number, location) {}

    virtual bool is_car() const override final { return false; }

   private:
};