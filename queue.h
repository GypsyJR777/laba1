#pragma once

#include <iostream>
#include "discount.h"
#include <sstream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <fstream>
#include <vector>
#include <cctype>
using namespace std;

class Queue {
  public :
    Queue();
    Queue(const Queue& Q);
    int push (Discount& p);
    int size();
    int pop(int index);
    int clean_();
    Discount back();
    int toFile();
    int intoFile();
    void setIteratorIndex(int index);
    void setIteratorValue(Discount i);
    int getIteratorIndex();
    Discount getIteratorValue();
    bool check_discount(const string& card_num_, const int& day_, const int& month_);
    string allSum(Time& t1,Time& t2, Date& d1, Date& d2);
private:
    pair<int,Discount> iterator;
    Discount *queue_;
    int size_;
} ;

std::ostream& operator << (std::ostream &os, const Queue &q);

bool operator > (const Time& left, const Time& right);

vector<int> Parse(string& str);

vector<string> ParseCard(string& str);

bool operator == (Queue& left, Queue& right);

bool Equal(Queue& left, Queue& right);
