#ifndef PhysicalNumber_H
#define PhysicalNumber_H

#include <iostream>
#include <string>
#include "Unit.h"
using namespace std;

namespace ariel {

    class PhysicalNumber{
        private:
            Unit unit;
            double data;

        public:
            PhysicalNumber(double, Unit);
            PhysicalNumber(const PhysicalNumber&);

            double getData();
            Unit getUnit();
            void setData(double);
            void setUnit(Unit);
            bool checkUnit(PhysicalNumber&);
            bool isLength();
            bool isTime();
            bool isMass();
            

            PhysicalNumber operator+();
            PhysicalNumber& operator++();       //prefix
            PhysicalNumber& operator++(int);    //postfix
            PhysicalNumber& operator+=(const PhysicalNumber&);
            PhysicalNumber operator+(const PhysicalNumber&);
            PhysicalNumber operator-();
            PhysicalNumber& operator--();        //prefix
            PhysicalNumber& operator--(int);     //postfix
            PhysicalNumber& operator-=(const PhysicalNumber&);
            PhysicalNumber operator-(const PhysicalNumber&);

            bool operator==(const PhysicalNumber&);
            bool operator!=(const PhysicalNumber&);
            bool operator>(const PhysicalNumber&);
            bool operator<(const PhysicalNumber&);
            bool operator<=(const PhysicalNumber&);
            bool operator>=(const PhysicalNumber&);
        
            friend ostream& operator<<(ostream&, const PhysicalNumber&);
            friend istream& operator>>(istream&, PhysicalNumber&);    
            friend istream& checkInputUnit(istream&, PhysicalNumber&);
    };
    class Convertor {
        public:
            static double toKM(PhysicalNumber&);
            static double toM(PhysicalNumber&);
            static double toCM(PhysicalNumber&);
            static double toHour(PhysicalNumber&);
            static double toMin(PhysicalNumber&);
            static double toSec(PhysicalNumber&);
            static double toTon(PhysicalNumber&);
            static double toKG(PhysicalNumber&);
            static double toG(PhysicalNumber&);

            // static double convertLength(PhysicalNumber&, Unit);
            // static double convertTime(PhysicalNumber&, Unit);
            // static double convertMasa(PhysicalNumber&, Unit);
    };
}

#endif