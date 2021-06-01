#include <iostream>
#include <math.h>
#include <cscobj.h>
#include <vector>
#include <Windows.h>
#include <iterator>
#include "histogram.h"

using namespace std;

void find_minmax(vector<double> numbers, double& min, double& max)
{
    min = numbers[0];
    max = numbers[0];
    for (double x : numbers)
    {
        if (x < min)
        {
            min = x;
        }
        else if (x > max)
        {
            max = x;
        }
    }
}
