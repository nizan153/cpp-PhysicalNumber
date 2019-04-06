/**
 * Examples of automatic tests for the exercise on physical numbers.
 *
 * @author Erel Segal-Halevi
 * @since 2019-02
 */

#include <iostream>
#include <sstream>
using std::cout, std::endl, std::istringstream;
#include "PhysicalNumber.h"
using ariel::PhysicalNumber, ariel::Unit;
#include "badkan.hpp"

int main() {
  badkan::TestCase testcase;
  int grade=0;
  int signal = setjmp(badkan::longjmp_buffer);
  if (signal == 0) {

    // BASIC TESTS - DO NOT CHANGE
    PhysicalNumber a(2, Unit::KM);
    PhysicalNumber b(300, Unit::M);
    PhysicalNumber c(2, Unit::HOUR);
    PhysicalNumber d(30, Unit::MIN);


    PhysicalNumber l1(1, Unit::KM);
    PhysicalNumber l2(1, Unit::M);
    PhysicalNumber l3(100, Unit::CM);

    PhysicalNumber t1(1, Unit::HOUR);
    PhysicalNumber t2(1, Unit::MIN);
    PhysicalNumber t3(60, Unit::SEC);

    PhysicalNumber m1(1, Unit::TON);
    PhysicalNumber m2(1, Unit::KG);
    PhysicalNumber m3(1000, Unit::G);

    testcase
    .setname("Basic output")
    .CHECK_OUTPUT(a, "2[km]")
    .CHECK_OUTPUT(b, "300[m]")

    .setname("Compatible dimensions")
    .CHECK_OUTPUT(b+a, "2300[m]")
    .CHECK_OUTPUT((a+=b), "2.3[km]")
    .CHECK_OUTPUT(a, "2.3[km]")
    .CHECK_OUTPUT(a+a, "4.6[km]")
    .CHECK_OUTPUT(b-b, "0[m]")
    .CHECK_OUTPUT(c, "2[hour]")
    .CHECK_OUTPUT(d, "30[min]")
    .CHECK_OUTPUT(d+c, "150[min]")

    .setname("Incompatible dimensions")
    .CHECK_THROWS(a+c)
    .CHECK_THROWS(a+d)
    .CHECK_THROWS(b+c)
    .CHECK_THROWS(b+d)

    .setname("Basic input")
    .CHECK_OK(istringstream("700[kg]") >> a)
    .CHECK_OUTPUT((a += PhysicalNumber(1, Unit::TON)), "1700[kg]")

    // YOUR TESTS - INSERT AS MANY AS YOU WANT

    .setname("Basic output")
    .CHECK_OUTPUT(m1, "1[ton]")
    .CHECK_OUTPUT(m2, "1[kg]")
    .CHECK_OUTPUT(m3, "1000[g]")



    .setname("Compatible dimensions")
    .CHECK_EQUAL(l2 == l3, true)
    .CHECK_EQUAL(m2 == m3, true)
    .CHECK_EQUAL(t2 == t3, true)
    .CHECK_EQUAL(t1 > t2, true)
    .CHECK_EQUAL(m3 < m1, true)
    .CHECK_EQUAL(t2 >= t3, true)
    .CHECK_EQUAL(l1 != l2, true)
    .CHECK_EQUAL(l2 == l1, false)
    .CHECK_EQUAL(l3 > l2, false)
    .CHECK_EQUAL(m1 == m2, false)
    .CHECK_EQUAL(t1 == t2, false)
    .CHECK_EQUAL(t1 < t2, false)
    .CHECK_EQUAL(l2 > l3, false)
    .CHECK_EQUAL(m2 < m3, false)
    .CHECK_OUTPUT(-l1, "-1[km]")
    .CHECK_OUTPUT(-l2, "-1[m]")
    .CHECK_OUTPUT(-l3, "-1000[cm]")
    .CHECK_OUTPUT(+l1, "1[km]")
    .CHECK_OUTPUT(+l2, "1[m]")
    .CHECK_OUTPUT(+l3, "1000[cm]")
    .CHECK_OUTPUT(-t1, "-1[hour]")
    .CHECK_OUTPUT(-t2, "-1[min]")
    .CHECK_OUTPUT(-t3, "-60[sec]")
    .CHECK_OUTPUT(+t1, "1[hour]")
    .CHECK_OUTPUT(+t2, "1[min]")
    .CHECK_OUTPUT(+t3, "1[sec]")
    .CHECK_OUTPUT(-m1, "-1[ton]")
    .CHECK_OUTPUT(-m2, "-1[kg]")
    .CHECK_OUTPUT(-m3, "-1000[g]")
    .CHECK_OUTPUT(+m1, "1[ton]")
    .CHECK_OUTPUT(+m3, "1000[g]")
    .CHECK_OUTPUT(l2+l3, "2[kg]")
    .CHECK_OUTPUT(l2-l3, "0[kg]")
    .CHECK_OUTPUT(t3+t2, "120[sec]")
    .CHECK_OUTPUT(t2-t3, "0[min]")
    .CHECK_OUTPUT(m3-m2, "0[g]")
    .CHECK_OUTPUT(m2+m3, "2[kg]")
    .CHECK_OUTPUT(t3-t2, "0[sec]")
    .CHECK_OUTPUT(t2+t3, "2[min]")
    .CHECK_OK(t1+=t2)
    .CHECK_OK(t2++)
    .CHECK_OK(m1+=m3)
    .CHECK_OK(m2--)
    .CHECK_OK(--m1)
    .CHECK_OK(l2-l3)
    .CHECK_OK(t1=t2+t2)
    .CHECK_OK(m1+=m1)
    .CHECK_OK(t3+t3)
    .CHECK_OK(--t1)
    .CHECK_OK(++l2)
    .CHECK_OK(l3++)
    .CHECK_OK(t1--)
    .CHECK_OK(-m2)
    .CHECK_OK(-l2)
    .CHECK_OK(-t1)
    .CHECK_OK(+m3)
    .CHECK_OK(+t3)
    .CHECK_OK(t1+=t1)
    .CHECK_OK(t1+t1)


    .setname("Incompatible dimensions")
    .CHECK_THROWS(t1 + m1)
    .CHECK_THROWS(t2 - m1)
    .CHECK_THROWS(l3 + t1)
    .CHECK_THROWS(l1 - m3)
    .CHECK_THROWS(t1 += m2)
    .CHECK_THROWS(t2 -= m1)
    .CHECK_THROWS(m3 += t2)
    .CHECK_THROWS(m1 -= l3)
    .CHECK_THROWS(l1 = l2 + m2)
    .CHECK_THROWS(t3 = l1 + m2)
    .CHECK_THROWS(m3 = t2 - m1)
    .CHECK_THROWS(m1 > l2)
    .CHECK_THROWS(m2 == t1)
    .CHECK_THROWS(m3 >= l3)
    .CHECK_THROWS(t1 != m2)
    .CHECK_THROWS(t2 < l1)
    .CHECK_THROWS(t2 == m2)
    .CHECK_THROWS(t2 == l2)
    .CHECK_THROWS(t1 != m3)
    .CHECK_THROWS(l2 != t2)
    .CHECK_THROWS(l3 == m1)
    .CHECK_THROWS(l1 > m1)
    .CHECK_THROWS(l3 >= m3)
    .CHECK_THROWS(m1 <= t2)
    .CHECK_THROWS(t1 >= m1)
    .CHECK_THROWS(t3 <= m2)


    .setname("Basic input")
    .CHECK_OK(istringstream("1500[m]") >> l2)
    .CHECK_OUTPUT((l2 += PhysicalNumber(1, Unit::KM)), "2500[m]")
    .CHECK_OK(istringstream("30[sec]") >> t3)
    .CHECK_OUTPUT((t3 += PhysicalNumber(1, Unit::MIN)), "90[sec]")
    .CHECK_OK(istringstream("500[g]") >> m1)
    .CHECK_OUTPUT((m1 += PhysicalNumber(1, Unit::KG)), "1500[g]")

      .print(cout, /*show_grade=*/false);
      grade = testcase.grade();
    } else {
      testcase.print_signal(signal);
      grade = 0;
    }
    cout <<  "*** Grade: " << grade << " ***" << endl;
    return grade;
}
