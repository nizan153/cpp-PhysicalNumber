#include "PhysicalNumber.h"
#include <iostream>
#include <iomanip>
using namespace ariel;

PhysicalNumber::PhysicalNumber(double x, Unit u) : data(x), unit(u) {}

PhysicalNumber::PhysicalNumber(const PhysicalNumber& other) : data(other.data), unit(other.unit) {}

double PhysicalNumber::getData() { return data; }

Unit PhysicalNumber::getUnit() { return unit; }

void PhysicalNumber::setData(double d) { data = d; }

void PhysicalNumber::setUnit(Unit u) { unit = u; }

bool PhysicalNumber::checkUnit(PhysicalNumber& pn) {
    if(this->isLength()) {
        return pn.isLength();
    }
    else if(this->isTime()) {
        return pn.isTime();
    }
    else {
        return pn.isMass();
    }
}

bool PhysicalNumber::isLength() {
    return (this->getUnit() == Unit::KM) || (this->getUnit() == Unit::M) || (this->getUnit() == Unit::CM);
}
bool PhysicalNumber::isTime() {
    return (this->unit == Unit::HOUR) || (this->unit == Unit::MIN) || (this->unit == Unit::SEC);
}
bool PhysicalNumber::isMass() {
    return (this->getUnit() == Unit::TON) || (this->getUnit() == Unit::KG) || (this->getUnit() == Unit::G);
}
PhysicalNumber PhysicalNumber::operator+() {
    return *this;
}

PhysicalNumber PhysicalNumber::operator+(const PhysicalNumber& other) {
    PhysicalNumber temp = other;
    double ans;
    if(!checkUnit(temp)){
        throw std::invalid_argument("Not the same units");
    }
    else if(isLength()){
        switch(this->getUnit()) {
            case Unit::KM:
                ans = Convertor::toKM(temp) + this->getData();
                break;
            case Unit::M:
                ans = Convertor::toM(temp) + this->getData(); 
                break;
            case Unit::CM:
                ans = Convertor::toCM(temp) + this->getData();
                break;
            default:
                break;
        }
    }
    else if(isMass()) {
        switch(this->getUnit()) {
            case Unit::TON:
                ans = Convertor::toTon(temp) + this->getData();
                break;
            case Unit::KG:
                ans = Convertor::toKG(temp) + this->getData(); 
                break;
            case Unit::G:
                ans = Convertor::toG(temp) + this->getData();
                break;
            default:
                break;
        }
    }
    else{
        switch(this->getUnit()) {
            case Unit::HOUR:
                ans = Convertor::toHour(temp) + this->getData();
                break;
            case Unit::MIN:
                ans = Convertor::toMin(temp) + this->getData(); 
                break;
            case Unit::SEC:
                ans = Convertor::toSec(temp) + this->getData();
                break;
            default:PhysicalNumber temp = other;
    if(!checkUnit(temp)){
        throw std::invalid_argument("different Units");
    }
                break;
        }
    }
    return PhysicalNumber(ans, this->getUnit());
}

PhysicalNumber& PhysicalNumber::operator++() {
    this->setData(this->getData() + 1);
    return *this;
}

PhysicalNumber PhysicalNumber::operator++(int unused) {
    PhysicalNumber temp = *this;
    ++(*this);
    return temp;
}

PhysicalNumber& PhysicalNumber::operator+=(const PhysicalNumber& other) {
    PhysicalNumber temp = *this + other;
    data = temp.data;
    return temp;
}

PhysicalNumber PhysicalNumber::operator-() {
    return PhysicalNumber(-data, unit);
}

PhysicalNumber& PhysicalNumber::operator--() {
    this->setData(this->getData() - 1);
    return *this;
}

PhysicalNumber PhysicalNumber::operator--(int unused) {
    PhysicalNumber temp = *this;
    --(*this);
    return temp;
}

PhysicalNumber& PhysicalNumber::operator-=(const PhysicalNumber& other) {
    PhysicalNumber temp = *this - other;
    data = temp.data;
    return temp;
}

PhysicalNumber PhysicalNumber::operator-(const PhysicalNumber& other) {
    PhysicalNumber temp = other;
    temp = *this + (-temp);
    return PhysicalNumber(temp.getData(), this->getUnit());
}

bool PhysicalNumber::operator==(const PhysicalNumber& other) {
    PhysicalNumber temp = other;
    double left, right;

    if(!checkUnit(temp)){
        throw std::invalid_argument("different Units");
    }
    else if(isLength()){
        left = Convertor::toCM(*this);
        right = Convertor::toCM(temp);
    }
    else if(isMass()) {
        left = Convertor::toG(*this);
        right = Convertor::toG(temp);
    }
    else {
        left = Convertor::toSec(*this);
        right = Convertor::toSec(temp);
    }
    return left == right;
}

bool PhysicalNumber::operator!=(const PhysicalNumber& other) {
    PhysicalNumber temp = other;
    if(!checkUnit(temp)){
        throw std::invalid_argument("different Units");
    }
    return !(*this==other);
}

bool PhysicalNumber::operator>(const PhysicalNumber& other) {
    PhysicalNumber temp = other;
    double left, right;
    if(!checkUnit(temp)){
        throw std::invalid_argument("different Units");
    }
    else if(isLength()){
        left = Convertor::toCM(*this);
        right = Convertor::toCM(temp);
    }
    else if(isMass()) {
        left = Convertor::toG(*this);
        right = Convertor::toG(temp);
    }
    else {
        left = Convertor::toSec(*this);
        right = Convertor::toSec(temp);        
    }
    return left > right;
} 

bool PhysicalNumber::operator<(const PhysicalNumber& other) {
    PhysicalNumber temp = other;
    double left, right;
    if(!checkUnit(temp)){
        throw std::invalid_argument("different Units");
    }
    else if(isLength()){
        left = Convertor::toCM(*this);
        right = Convertor::toCM(temp);
    }
    else if(isMass()) {
        left = Convertor::toG(*this);
        right = Convertor::toG(temp);
    }
    else {
        left = Convertor::toSec(*this);
        right = Convertor::toSec(temp);        
    }
    return left < right;
}

bool PhysicalNumber::operator<=(const PhysicalNumber& other) {
    PhysicalNumber temp = other;
    if(!checkUnit(temp)){
        throw std::invalid_argument("different Units");
    }
    return (this->operator==(other)) || (this->operator<(other));
}

bool PhysicalNumber::operator>=(const PhysicalNumber& other) {
    PhysicalNumber temp = other;
    if(!checkUnit(temp)){
        throw std::invalid_argument("different Units");
    }
    return (this->operator==(other)) || (this->operator>(other));
}

std::ostream& ariel::operator<<(ostream& os, const PhysicalNumber& pn) {
    PhysicalNumber temp(pn);
    string str;
    switch (temp.getUnit()) {
        case Unit::KM :
            str = "km";
            break;
        case Unit::M :
            str = "m";
            break;
        case Unit::CM :
            str = "cm";
            break;
        case Unit::HOUR :
            str = "hour";
            break;
        case Unit::MIN :
            str = "min";
            break;
        case Unit::SEC :
            str = "sec";
            break;
        case Unit::TON :
            str = "ton";
            break;
        case Unit::KG :
            str = "kg";
            break;
        case Unit::G :
            str = "g";
            break;
    }
    return os << temp.getData() << "[" << str << "]";
}

std::istream& ariel::operator>>(istream& is, PhysicalNumber& pn) {
    string str;
    long double d;
    ios::pos_type sp = is.tellg();
    if(!(is >> d) || !(checkInputUnit(is, pn))) {
        auto es = is.rdstate();
        is.clear();
        is.seekg(sp);
        is.clear(es);
    }
    else {
        pn.setData(d);
    }
    
    return is;
}

istream& ariel::checkInputUnit(istream& is, PhysicalNumber& pn) {
    string s;
    int i, j;
    is >> s;
    i = s.find('[');
    j = s.find(']');
    if(!is) { return is; }
    if((i == -1) || (j == -1)) { 
        is.setstate(ios::failbit);
        return is; 
    }
    s = s.substr(i+1, j-1);
    if(s.compare("km") == 0) { pn.setUnit(Unit::KM); }
    else if(s.compare("m") == 0) { pn.setUnit(Unit::M); }
    else if(s.compare("cm") == 0) { pn.setUnit(Unit::M); }
    else if(s.compare("ton") == 0) { pn.setUnit(Unit::TON); }
    else if(s.compare("kg") == 0) { pn.setUnit(Unit::KG); }
    else if(s.compare("g") == 0) { pn.setUnit(Unit::G); }
    else if(s.compare("hour") == 0) { pn.setUnit(Unit::HOUR); }
    else if(s.compare("min") == 0) { pn.setUnit(Unit::MIN); }
    else if(s.compare("sec") == 0) { pn.setUnit(Unit::SEC); }
    else{ is.setstate(ios:: failbit); }

    return is;
}



// Convertor

double Convertor::toKM(PhysicalNumber& pn) {
    double ans;
    switch(pn.getUnit()) {
        case Unit::M :
            ans = pn.getData() / 1000;
            break;
        case Unit::CM :
            ans = pn.getData() / 1000 / 100;
            break;
        default:
            ans = pn.getData();
            break;
    }
    return ans;
}

double Convertor::toM(PhysicalNumber& pn) {
    double ans;
    switch(pn.getUnit()) {
        case Unit::KM :
            ans = pn.getData() * 1000;
            break;
        case Unit::CM :
            ans = pn.getData() / 100;
            break;
        default:
            ans = pn.getData();
            break;
    }
    return ans;
}

double Convertor::toCM(PhysicalNumber& pn) {
    double ans;
    switch(pn.getUnit()) {
        case Unit::KM :
            ans = pn.getData() * 1000 * 100;
            break;
        case Unit::M :
            ans = pn.getData() * 100;
            break;
        default:
            ans = pn.getData();
            break;
    }
    return ans;
}

double Convertor::toHour(PhysicalNumber& pn) {
    double ans;
    switch(pn.getUnit()) {
        case Unit::MIN :
            ans = pn.getData() / 60;
            break;
        case Unit::SEC :
            ans = pn.getData() / 60 / 60;
            break;
        default:
            ans = pn.getData();
            break;
    }
    return ans;
}

double Convertor::toMin(PhysicalNumber& pn) {
    double ans;
    switch(pn.getUnit()) {
        case Unit::HOUR :
            ans = pn.getData() * 60;
            break;
        case Unit::SEC :
            ans = pn.getData() / 60;
            break;
        default:
            ans = pn.getData();
            break;
    }
    return ans;
}

double Convertor::toSec(PhysicalNumber& pn) {
    double ans;
    switch(pn.getUnit()) {
        case Unit::HOUR :
            ans = pn.getData() * 60 * 60;
            break;
        case Unit::MIN :
            ans = pn.getData() * 60;
            break;
        default:
            ans = pn.getData();
            break;
    }
    return ans;
}

double Convertor::toTon(PhysicalNumber& pn) {
    double ans;
    switch(pn.getUnit()) {
        case Unit::KG :
            ans = pn.getData() / 1000;
            break;
        case Unit::G :
            ans = pn.getData() / 1000;
            break;
        default:
            ans = pn.getData();
            break;
    }
    return ans;
}

double Convertor::toKG(PhysicalNumber& pn) {
    double ans;
    switch(pn.getUnit()) {
        case Unit::TON :
            ans = pn.getData() * 1000;
            break;
        case Unit::G :
            ans = pn.getData() / 1000;
            break;
        default:
            ans = pn.getData();
            break;
    }
    return ans;
}

double Convertor::toG(PhysicalNumber& pn) {
    double ans;
    switch(pn.getUnit()) {
        case Unit::TON :
            ans = pn.getData() * 1000 * 1000;
            break;
        case Unit::KG :
            ans = pn.getData() * 1000;
            break;
        default:
            ans = pn.getData();
            break;
    }
    return ans;
}