#include <iostream>
#include <math.h>
#include <cscobj.h>
#include <vector>
#include <Windows.h>
#include <iterator>
#include "histogram.h"

using namespace std;

void svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end()
{
    cout << "</svg>\n";
}

void svg_text(double left, double baseline, string text)
{
    cout << "<text x='"<<left<<"' y='"<<baseline<<"'>"<<text<<"</text>";
}
void svg_rect(double x, double y, double width, double height, string stroke, string fill)
{
    cout << "<rect x='"<<x<<"' y='"<<y<<"' width='"<<width<<"' height='"<<height<<"' stroke='"<<stroke<<"' fill='"<<fill<<"' />";
}

string svg_line(double x1, float y1, double x2, float y2, string stroke, float stroke_width, double stroke_dash, double stroke_dasharray)
{
    return "<line x1='"+to_string(x1)+"' y1='"+to_string(y1)+"' x2='"+to_string(x2)+"' y2='"+to_string(y2)+
    "' stroke='"+stroke+"' stroke-width='"+to_string(stroke_width)
    +"' stroke-dasharray = '"+to_string(stroke_dash)+" "+to_string(stroke_dasharray)+"'/>";
}

string make_info_text()
{
    stringstream buffer;
    // TODO: получить версию системы, записать в буфер.
    // TODO: получить имя компьютера, записать в буфер.
    return buffer.str();
}

void show_histogram_svg(vector<size_t> bins, size_t bin_count, vector<vector<char>> bin_naming_list,double dash, double dasharray)
{

    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto LINE_HEIGHT = 5.0;
    double BLOCK_WIDTH = 10;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    vector<char[80]> bin_namings(bin_count);
    size_t iter = 0;
    for (size_t iter = 0; iter < bin_count; iter++)
    {
        for (char l : bin_naming_list[iter])
        {
            bin_namings[iter][strlen(bin_namings[iter])] = l;
        }
    }
    double max_len = strlen(bin_namings[0]);
    for (size_t i = 0; i < bin_count; i++)
    {
        if (strlen(bin_namings[i]) > max_len)
        {
            max_len = strlen(bin_namings[i]);
        }
    }
    double max_count = bins[0];
    for (double x : bins)
    {
        if (x > max_count)
        {
            max_count = x;
        }
    }
    if (max_count*BLOCK_WIDTH > IMAGE_WIDTH)
    {
        BLOCK_WIDTH = static_cast<double>(IMAGE_WIDTH) / static_cast<double>(max_count);
    }
    for (size_t i = 0; i < bin_count; i++)
    {
        svg_text(TEXT_LEFT, i*(BIN_HEIGHT+LINE_HEIGHT) + TEXT_BASELINE, bin_namings[i]);
        for (size_t j = 0; j < (bins[i]); j++)
        {
            svg_rect(TEXT_LEFT+TEXT_WIDTH*strlen(bin_namings[i])+(BLOCK_WIDTH*(j-1)), i*(BIN_HEIGHT+LINE_HEIGHT), BLOCK_WIDTH, BIN_HEIGHT,"red","white");
        }
        if (i>0)
        {
            cout << svg_line(0,i*(BIN_HEIGHT)+(i-1)*LINE_HEIGHT+LINE_HEIGHT/2,IMAGE_WIDTH,i*(BIN_HEIGHT)+(i-1)*LINE_HEIGHT+LINE_HEIGHT/2,"black",LINE_HEIGHT,dash,dasharray);
        }
        cout << endl;
    }
    svg_end();
}
