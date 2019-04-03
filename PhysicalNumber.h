#ifndef PhysicalNumber_H
#define PhysicalNumber_H

#include <iostream>
#include <string>
#include "Unit.h"
using namespace std;

namespace ariel {

    static string type[] = { "km", "m", "cm", "hour", "min", "sec", "ton", "kg", "g" };
    
    class PhysicalNumber{
        private:
        //     Unit unit;
        //     double data;

        public:
            Unit unit;
            double data;

            PhysicalNumber(double, Unit);
            
            const PhysicalNumber operator+();
            const PhysicalNumber& operator++();       //prefix
            const PhysicalNumber& operator++(int);    //postfix
            const PhysicalNumber operator+=(const PhysicalNumber&);
            friend const PhysicalNumber operator+(PhysicalNumber&, const PhysicalNumber&);
            const PhysicalNumber operator-();
            const PhysicalNumber& operator--();        //prefix
            const PhysicalNumber& operator--(int);     //postfix
            const PhysicalNumber operator-=(const PhysicalNumber&);
            friend const PhysicalNumber operator-(const PhysicalNumber&, const PhysicalNumber&);

            bool operator==(const PhysicalNumber&);
            bool operator!=(const PhysicalNumber&);
            bool operator>(const PhysicalNumber&);
            bool operator<(const PhysicalNumber&);
            bool operator<=(const PhysicalNumber&);
            bool operator>=(const PhysicalNumber&);
        
            friend ostream& operator<<(ostream&, const PhysicalNumber&);
            friend istream& operator>>(istream&, PhysicalNumber&);    
    };
}

#endif