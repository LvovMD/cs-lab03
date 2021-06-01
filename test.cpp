#include <iostream>
#include <math.h>
#include <cscobj.h>
#include <vector>
#include <Windows.h>
#include <iterator>
#include "histogram.h"

#include <cassert>

void test_positive()
{
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}

void test_negative()
{
    double min = 0;
    double max = 0;
    find_minmax({-1, -2, -3}, min, max);
    assert(min == -3);
    assert(max == -1);
}
void test_equal()
{
    double min = 0;
    double max = 0;
    find_minmax({1, 1, 1}, min, max);
    assert(min == 1);
    assert(max == 1);
}

void test_one()
{
    double min = 0;
    double max = 0;
    find_minmax({1}, min, max);
    assert(min == 1);
    assert(max == 1);
}

void test_null()
{
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min == 0);
    assert(max == 0);
}

void svg_test_positive()
{
    double dash = 10;
    double dasharray = 20;
    string line = "";
    line = svg_line(0.0,0.0,10.0,10.0,"black",1.0,dash,dasharray);
    size_t pos = line.find("stroke-dasharray =)"+to_string(dash)+" "+to_string(dasharray));
    assert(pos>0);
}

void svg_test_negative()
{
    double dash = 10;
    double dasharray = 20;
    string line = "";
    line = svg_line(0.0,0.0,10.0,10.0,"black",1.0,dash,dasharray);
    size_t pos = line.find("stroke-dasharray =)"+to_string(dasharray)+" "+to_string(dash));
    assert(pos=string::npos);
}

int main()
{
    test_positive();
    test_negative();
    test_equal();
    test_one();
    svg_test_positive();
    svg_test_negative();
}
