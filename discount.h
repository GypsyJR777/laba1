#pragma once

#include "purchase.h"

#include <set>
#include <vector>

using namespace std;

class Discount : public Purchase{
public:
    Discount();
    Discount(const int& minute_, const int& hour_, const int& day_, const int& month_, const int& year_,
             const int& sum_buys_, const string& card_number_, const string& phone_number_,
             const bool& activate_);
    Discount(const Discount& other);
};

