#include "queue.h"

bool operator == (Queue& left, Queue& right){
    if(left.size() == right.size()){
        for (int i = 0; i < left.size(); i++){
            left.setIteratorIndex(i);
            right.setIteratorIndex(i);
            if(!(left.getIteratorValue().Get_time_and_date() == right.getIteratorValue().Get_time_and_date() && left.getIteratorValue().Get_sum() == right.getIteratorValue().Get_sum())){
                return false;
            }
        }
        return true;
    }else {
        return false;
    }
}

bool operator >= (const Time& left, const Time& right){
    if(left.hour > right.hour){
        return true;
    } else if(left.minute >= right.minute && left.hour == right.hour){
        return true;
    } else{
        return false;
    }
}

bool operator > (const Time& left, const Time& right){
    if(left.hour > right.hour){
        return true;
    } else if(left.minute > right.minute && left.hour == right.hour){
        return true;
    } else{
        return false;
    }
}

bool operator >= (const Date& left, const Date& right){
    if (left.year > right.year){
        return true;
    } else if(left.month > right.month && left.year == right.year){
        return true;
    } else if(left.day >= right.day && left.month == right.month && left.year == right.year){
        return true;
    } else{
        return false;
    }
}

bool operator > (const Date& left, const Date& right){
    if (left.year > right.year){
        return true;
    } else if(left.month > right.month && left.year == right.year){
        return true;
    } else if(left.day > right.day && left.month == right.month && left.year == right.year){
        return true;
    } else{
        return false;
    }
}

vector<int> Parse(string& str){
    stringstream s(str);
    int b;
    int j = 0;
    vector<int> date = {0, 0, 0, 0, 0};
    do{
        if(s >> b){
            date[j] = b;
            j++;
        } else {
            s.clear();
            s.ignore(1, ' ');
        }
    }while(!s.eof());
    return date;
}

vector<string> ParseCard(string& str){
    stringstream s(str);
    vector<string> card = {"0", "0"};
    int j = 0;
    char b;
    do{
        s >> b;
        if (isdigit(b)){
            card[j] += b;
        } else{
            s.clear();
            s.ignore(1, ' ');
            j++;
        }
    }while(!s.eof());
    return card;
}

Queue::Queue() {
    this->queue_ = new Discount[1]();
    this->size_ = 0;
    this->iterator.first = 0;
    this->iterator.second = this->queue_[0];
    std::cout << "Default constructor\n";
}

Queue::Queue(const Queue& Q){
    this->queue_ = Q.queue_;
    this->size_ = Q.size_;
    this->iterator = Q.iterator;
    cout << "Copy constructor working\n";
}

int Queue::clean_(){
    delete [] this->queue_;
    this->queue_ = new Discount[0];
    this->size_ = 0;
    return 0;
}

int Queue::push(Discount& p){
    if(this->size() == 0 || (p.Get_time_admin() >= this->back().Get_time_admin() && p.Get_date_admin() >= this->back().Get_date_admin())){
        this->size_++;
        Discount *new_array = new Discount[this->size_];
        for (int i = 0; i < this->size_ - 1; i++){
            new_array[i] = this->queue_[i];
        }
        new_array[this->size_ - 1] = p;
        delete [] this->queue_;
        this->queue_ = new Discount[this->size_];
        this->queue_= new_array;
        this->iterator.second = this->queue_[this->iterator.first];
        return 0;
    }else{
        cout << "Enter corect date\n";
        return 1;
    }
}

int Queue::pop(int index){
    if (index < this->size_){
        this->size_--;
        Discount* new_array = new Discount[size_];
        for (int i = 0; i < index; i++)
            new_array[i] = this->queue_[i];
        for (int i = index; i < size_; i++)
            new_array[i] = this->queue_[i + 1];
        delete [] this->queue_;
        this->queue_ = new Discount[size_];
        this->queue_ = new_array;
        if (this->iterator.first >= this->size_)
            this->iterator.first = this->size_ - 1;
        this->iterator.second = this->queue_[this->iterator.first];
        return 0;
    }
    return 1;
}

int Queue::size() {
  return size_;
}

Discount Queue::back() {
return queue_[size_-1]; }

int Queue::toFile(){
    QJsonArray array;
    for (int i = 0; i < this->size_; i++){
        QString time = QString::fromUtf8(this->queue_[i].Get_time_and_date().c_str());
        QJsonObject obj {
            {"Sum", this->queue_[i].Get_sum()},
            {"time", time},
            {"Card num", this->queue_[i].Get_card_number().c_str()},
            {"Phone num", this->queue_[i].Get_phone_number().c_str()},
            {"Active", this->queue_[i].Get_activator()}
        };
        array.append(obj);
    }
    QJsonDocument stack_doc(array);
    ofstream out("/home/gypsyjr/laba3/queue_.txt");
    if (out.is_open()){
        out << stack_doc.toJson().toStdString() << endl;
    }
    out.close();
    return 0;
}

int Queue::intoFile(){
    string line, stack = "";
    ifstream in("/home/gypsyjr/laba3/queue_.txt");
    if (in.is_open()){
        while (getline(in, line))
        {
            stack += line;
        }
    }
    in.close();
    QJsonDocument doc = QJsonDocument::fromJson(QString::fromUtf8(stack.c_str()).toLocal8Bit());
    QJsonArray array = doc.array();
    Discount *new_array = new Discount[array.size()];
    for (int i = 0; i < array.size(); i++){
        string str, info;
        str = array.at(i)["time"].toString().toStdString();
        vector<int> date = Parse(str);
        Discount inn(date[4], date[3], date[0], date[1], date[2], array.at(i)["Sum"].toInt(), array.at(i)["Card num"].toString().toStdString(),
                array.at(i)["Phone num"].toString().toStdString(), array.at(i)["Active"].toBool());
        new_array[i] = inn;
    }
    this->queue_ = new_array;
    this->size_ = array.size();
    return 0;
}

void Queue::setIteratorIndex(int index){
    if (this->iterator.first != index && index < this->size_ && index >= 0){
        this->iterator.first = index;
        this->iterator.second = this->queue_[this->iterator.first];
    }
}

bool Queue::check_discount(const string& card_num_, const int& day_, const int& month_){
    int n = 0;
    set<int> day_30 = {4, 6, 9, 11};
    int sum = 0;
    for(int i = 0; i < size_; ++i){
        setIteratorIndex(i);
        if (getIteratorValue().Get_card_number() == card_num_ && getIteratorValue().Get_date_admin().month == month_-1){
            if(day_30.count(getIteratorValue().Get_date_admin().month) > 0 && 30 - getIteratorValue().Get_date_admin().day + day_ <= 30){
                n++;
                sum += getIteratorValue().Get_sum();
            }else if (day_30.count(getIteratorValue().Get_date_admin().month) == 0 && getIteratorValue().Get_date_admin().month != 2
                      && 31 - getIteratorValue().Get_date_admin().day + day_ <= 30){
                n++;
                sum += getIteratorValue().Get_sum();
            }else if(getIteratorValue().Get_date_admin().month == 2 && 28 - getIteratorValue().Get_date_admin().day + day_ <= 30){
                n++;
                sum += getIteratorValue().Get_sum();
            }
        }else if(getIteratorValue().Get_card_number() == card_num_ && getIteratorValue().Get_date_admin().month == month_){
            n++;
            sum += getIteratorValue().Get_sum();
        }
    }
    if(n == 5 && sum >= 500){
        return true;
    }
    return false;
}

int Queue::getIteratorIndex(){
    return this->iterator.first;
}

Discount Queue::getIteratorValue(){
    return this->iterator.second;
}
string Queue::allSum(Time& t1,Time& t2, Date& d1, Date& d2){
    int allsum = 0;
    for(int i = 0; i < size_; ++i){
        setIteratorIndex(i);
        if(getIteratorValue().Get_date_admin() > d1 && d2 > getIteratorValue().Get_date_admin()){
            allsum += getIteratorValue().Get_sum();
        }else if (getIteratorValue().Get_time_admin() >= t1 && t2 >= getIteratorValue().Get_time_admin() && getIteratorValue().Get_date_admin() >= d1 && d2 >= getIteratorValue().Get_date_admin()){
            allsum += getIteratorValue().Get_sum();
        }
    }
    if (allsum == 0){
        return "";
    }
    return to_string(allsum);
}

bool Equal(Queue& left, Queue& right){
    return (left == right);
}
