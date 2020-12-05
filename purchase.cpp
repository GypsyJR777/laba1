#include "purchase.h"


Purchase::Purchase(){
    date.day = 0;
    date.month = 0;
    date.year = 0;
    time.hour = 0;
    time.minute = 0;
    sum_buys = 0;
    card_number = " ";
    phone_number = " ";
    activate = false;
}

Purchase::Purchase(const int& minute_, const int& hour_, const int& day_, const int& month_, const int& year_,
                   const int& sum_buys_, const std::string& card_number_, const std::string& phone_number_, const bool& activate_){
    if(minute_ < 60 && hour_ < 24 && day_ < 31 && minute_ >= 0 && hour_ >= 0 && day_ > 0 && month_ >= 1 && month_ <= 12 && year_ <= 2020){
        if (sum_buys_ >= 0){
            date.day = day_;
            date.month = month_;
            date.year = year_;
            time.hour = hour_;
            time.minute = minute_;
            sum_buys = sum_buys_;
        } else {
           std::cout << "Enter a positive purchase amount\n";
           if(sum_buys_ > 0){
                sum_buys = sum_buys_;
            } else{
                sum_buys = 0;
                date.day = day_;
                date.month = month_;
                date.year = year_;
                time.hour = hour_;
                time.minute = minute_;
            }
        }
    } else {
        std::cout << "Enter a right period of the time\n";
    }
    card_number = card_number_;
    phone_number = phone_number_;
    activate = activate_;
}

Purchase::Purchase(const Purchase& other){
    std::string str;
    time = other.time;
    date = other.date;
    sum_buys = other.sum_buys;
    card_number = other.card_number;
    phone_number = other.phone_number;
    activate = other.activate;
}

std::string Purchase::Get_time_and_date(){
    return "Date: " + std::to_string(date.day) + " . " + std::to_string(date.month) + " . " + std::to_string(date.year) + " Time: " + std::to_string(time.hour) + " : " + std::to_string(time.minute);
}

Time Purchase::Get_time_admin(){
    return time;
}

Date Purchase::Get_date_admin(){
    return date;
}

int Purchase::Get_sum(){
    return sum_buys;
}

bool Purchase::Get_activator(){
    return activate;
}

std::string Purchase::Get_card_number(){
    return card_number;
}

std::string Purchase::Get_phone_number(){
    return phone_number;
}

std::string Purchase::Get_card_info(){
    if(activate == true){
        return "Number: " + card_number + " ;Phone: " + phone_number + " ; Activate";
    } else {
        return "Number: " + card_number + " ;Phone: " + phone_number + " ; Non activate";
    }
}

bool Equality(Purchase& left, Purchase& right){
    return (left.Get_sum() == right.Get_sum()) && (left.Get_time_and_date() == right.Get_time_and_date());
}
