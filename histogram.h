#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED
#include <iostream>
#include <math.h>
#include <cscobj.h>
#include <vector>
#include <Windows.h>
#include <iterator>

using namespace std;

struct Input
{
    size_t number_count;
    vector<double> numbers;
    size_t bin_count;
};

void find_minmax(vector<double> numbers, double& min, double& max);
void svg_begin(double width, double height);
void svg_end();
void svg_text(double left, double baseline, string text);
void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black");
string svg_line(double x1, float y1, double x2, float y2, string stroke, float stroke_width, double stroke_dash, double stroke_dasharray);
void show_histogram_svg(vector<size_t> bins, size_t bin_count, vector<vector<char>> bin_naming_list,double dash, double dasharray);

#endif // HISTOGRAM_H_INCLUDED
