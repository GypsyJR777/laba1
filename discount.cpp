#include "discount.h"

Discount::Discount() : Purchase() {}

Discount::Discount(const int& minute_, const int& hour_, const int& day_,
                   const int& month_, const int& year_,
                   const int& sum_buys_, const std::string& card_number_,
                   const std::string& phone_number_, const bool& activate_) :
    Purchase(minute_, hour_, day_, month_, year_, sum_buys_, card_number_, phone_number_, activate_){}

Discount::Discount(const Discount& other) : Purchase(other) {}
