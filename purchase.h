#pragma once
#include <iostream>
#include <string>

struct Time{
    int minute;
    int hour;
};

struct Date{
    int day;
    int month;
    int year;
};


class Purchase{
public:
    Purchase();
    Purchase(const int& minute_, const int& hour_, const int& day_, const int& month_, const int& year_,
             const int& sum_buys_, const std::string& card_number_, const std::string& phone_number_, const bool& activate_);
    Purchase(const Purchase& other);
    std::string Get_time_and_date();
    int Get_sum();
    Time Get_time_admin();
    Date Get_date_admin();
    std::string Get_card_number();
    std::string Get_phone_number();
    std::string Get_card_info();
    bool Get_activator();
private:
    Time time;
    Date date;
    int sum_buys;
    std::string phone_number;
    std::string card_number;
    bool activate;
};

bool Equality(Purchase& left, Purchase& right);
