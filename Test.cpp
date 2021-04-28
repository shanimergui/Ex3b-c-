
#include "doctest.h"
#include "NumberWithUnits.hpp"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;
using namespace ariel;
ifstream units_file{"units.txt"};

TEST_CASE("operators: + , - , += , -= , (+) ,(-)"){
    NumberWithUnits::read_units(units_file);

    NumberWithUnits a{2, "ton"};
    NumberWithUnits b{300, "kg"};
    CHECK((a+b) == NumberWithUnits{2.3, "ton"});
    CHECK((b+a) == NumberWithUnits{2300, "kg"});
    CHECK((a-b) == NumberWithUnits{1.7, "ton"});
    CHECK((b-a) == NumberWithUnits{-1700, "kg"});

    CHECK((a+=b) == NumberWithUnits{2.3, "ton"});
    CHECK(a == NumberWithUnits{2.3, "ton"});
    CHECK((b+=a) == NumberWithUnits{2600, "kg"});
    CHECK(b == NumberWithUnits{2600, "kg"});
    CHECK((a-=b) == NumberWithUnits{-0.3, "ton"});
    CHECK(a == NumberWithUnits{-0.3, "ton"});
    CHECK((b-=a) == NumberWithUnits{2900, "kg"});
    CHECK(b == NumberWithUnits{2900, "kg"});

}

TEST_CASE("Adding one to enother-check throws"){
    NumberWithUnits::read_units(units_file);

    NumberWithUnits c{2, "ton"};
    NumberWithUnits d{300, "m"};
    CHECK_THROWS(c+d);
    CHECK_THROWS(d+c);

}


TEST_CASE("prefix ++ --  postfix ++ ---"){
    NumberWithUnits::read_units(units_file);

    NumberWithUnits e{2, "km"};
    CHECK(e++ == NumberWithUnits{2, "km"});
    CHECK(e == NumberWithUnits{3, "km"});
    CHECK(++e == NumberWithUnits{4, "km"});
    CHECK(e == NumberWithUnits{4, "km"});
    CHECK(e-- == NumberWithUnits{4, "km"});
    CHECK(e == NumberWithUnits{3, "km"});
    CHECK(--e == NumberWithUnits{2, "km"});
    CHECK(e == NumberWithUnits{2, "km"});
}


TEST_CASE("Multiplication operators: {float*x, x*float, x*=float, float*=x}"){
    NumberWithUnits::read_units(units_file);
    NumberWithUnits f{2, "ton"};
    NumberWithUnits g{300, "kg"};

    CHECK((2.7*f) == NumberWithUnits{5.4, "ton"});
    CHECK((f*3.5) == NumberWithUnits{7, "ton"});
    CHECK((2.7*g) == NumberWithUnits{810, "kg"});
    CHECK((g*3.5) == NumberWithUnits{1050, "kg"});

}



TEST_CASE("Comparison operators: {>, >=, <, <=, ==, !=}"){
    NumberWithUnits::read_units(units_file);

    CHECK_LT(NumberWithUnits{1, "km"}  , NumberWithUnits{2000, "m"});
    CHECK_GT(NumberWithUnits{5000, "m"}, NumberWithUnits{3, "km"});
    CHECK_NE(NumberWithUnits{5, "km"}  , NumberWithUnits{3000, "m"});
    CHECK_EQ(NumberWithUnits{300, "cm"}, NumberWithUnits{3, "m"});

    CHECK_LT(NumberWithUnits{50, "cm"}  , NumberWithUnits{5, "m"});
    CHECK_GT(NumberWithUnits{5000, "m"}, NumberWithUnits{50, "cm"});
    CHECK_NE(NumberWithUnits{5, "cm"}  , NumberWithUnits{5000, "m"});
    CHECK_EQ(NumberWithUnits{500, "cm"}, NumberWithUnits{5, "m"});


}
TEST_CASE("Comparison operators: {<< >>}"){
    //<<
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a{2, "km"};
    NumberWithUnits b{300, "m"};

    stringstream inside;
    inside << (a+b) ;
    CHECK(inside.str() == "2.3[km]");

    stringstream inside1;
    inside1 << (a-b) ;
    CHECK(inside1.str() == "1.7[km]");

    stringstream inside2;
    inside2 << (b+a) ;
    CHECK(inside2.str() == "2300[m]");


// >>
NumberWithUnits c{2, "ton"};
istringstream sample_input{"700 [ m ]"};
sample_input >> c;

stringstream inside3;
inside3 << c ;
CHECK(inside3.str() == "700[m]");


NumberWithUnits d{15, "m"};
istringstream sample_input1{"5 [ cm ]"};
sample_input1 >> d;

stringstream inside4;
inside4 << d ;
CHECK(inside4.str() == "5[cm]");


}



TEST_CASE("operators: + , - , += , -= , (+) ,(-) units1"){
    ifstream units_file{"units1.txt"};
    NumberWithUnits::read_units(units_file);

    NumberWithUnits a{2, "ILS"};
    NumberWithUnits b{4.92, "TRY"};
    NumberWithUnits c{3, "L" };
    NumberWithUnits d{3000, "mL" };
    NumberWithUnits e{4, "kN" };
    NumberWithUnits f{4000, "N" };
    NumberWithUnits g{2, "km" };
    NumberWithUnits h{2000, "cm" };



    CHECK((a+b) == NumberWithUnits{4, "ILS"});
    CHECK((b+a) == NumberWithUnits{9.84, "TRY"});
    CHECK((a-b) == NumberWithUnits{0, "ILS"});
    CHECK((b-a) == NumberWithUnits{0, "TRY"});

    CHECK((c+d) == NumberWithUnits{6, "L"});
    CHECK((d+c) == NumberWithUnits{6000, "mL"});
    CHECK((c-d) == NumberWithUnits{0, "L"});
    CHECK((d-c) == NumberWithUnits{0, "mL"});

    CHECK((e+f) == NumberWithUnits{8, "kN"});
    CHECK((f+e) == NumberWithUnits{8000, "N"});
    CHECK((e-f) == NumberWithUnits{0, "kN"});
    CHECK((f-e) == NumberWithUnits{0, "N"});

    CHECK((g+h) == NumberWithUnits{2.02, "km"});
    CHECK((h+g) == NumberWithUnits{202000, "cm"});
    CHECK((g-h) == NumberWithUnits{1.98, "km"});
    CHECK((h-g) == NumberWithUnits{-198000, "cm"});
}
