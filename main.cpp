#include <iostream>
#include <math.h>
#include <cscobj.h>
#include <vector>
#include <Windows.h>
#include <iterator>
#include "histogram.h"

using namespace std;

vector<double> input_numbers(size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cerr << "Enter number " << i + 1 << ": ";
        cin >> result[i];
    }
    return result;
}

vector<size_t> make_histogram(vector<double> numbers, size_t number_count, size_t bin_count)
{
    vector<size_t> bins(bin_count);
    double min = numbers[0];
    double max = numbers[0];
    find_minmax(numbers, min, max);
    double bin_size = (max - min) / bin_count;
    for (size_t i = 0; i < number_count; i++)
    {
        bool found = false;
        for (size_t j = 0; (j < bin_count - 1) && !found; j++)
        {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;
            if ((lo <= numbers[i]) && (numbers[i] < hi))
            {
                bins[j]++;
                found = true;
            }
        }
        if (!found)
        {
            bins[bin_count - 1]++;
        }
    }
    return bins;
}

void show_histogramm_text(vector<size_t> bins, size_t bin_count, vector<vector<char>> bin_naming_list)
{
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
    const size_t SCREEN_WIDTH = 80;
    size_t MAX_ASTERISK = SCREEN_WIDTH - max_len - 1;
    for (double x : bins)
    {
        if (x > max_count)
        {
            max_count = x;
        }
    }
    double height = 1;
    if (max_count > MAX_ASTERISK)
    {
        height = static_cast<double>(MAX_ASTERISK) / static_cast<double>(max_count);
    }
    for (size_t i = 0; i < bin_count; i++)
    {
        size_t tab = max_len - strlen(bin_namings[i]);
        for (size_t j = 0; j < tab; j++)
        {
            cout << " ";
        }
        cout << bin_namings[i] << "|";
        for (size_t j = 0; j < (height * bins[i]); j++)
        {
            cout << "*";
        }
        cout << endl;
    }
}

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
void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black")
{
    cout << "<rect x='"<<x<<"' y='"<<y<<"' width='"<<width<<"' height='"<<height<<"' stroke='"<<stroke<<"' fill='"<<fill<<"' />";
}

void svg_line(double x1, float y1, double x2, float y2, string stroke, float stroke_width, double stroke_dash, double stroke_dasharray)
{
    cout << "<line x1='"<<x1<<"' y1='"<<y1<<"' x2='"<<x2<<"' y2='"<<y2<<"' stroke='"<<stroke<<"' stroke-width='"<<stroke_width<<"' stroke-dasharray = '"<<stroke_dash<<" "<<stroke_dasharray<<"'/>";
}

void show_histogram_svg(vector<size_t> bins, size_t bin_count, vector<vector<char>> bin_naming_list)
{

    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
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
        svg_text(TEXT_LEFT, i*(BIN_HEIGHT) + TEXT_BASELINE, bin_namings[i]);
        for (size_t j = 0; j < (bins[i]); j++)
        {
            svg_rect(TEXT_LEFT+TEXT_WIDTH*strlen(bin_namings[i])+(BLOCK_WIDTH*(j-1)), i*(BIN_HEIGHT), BLOCK_WIDTH, BIN_HEIGHT,"red","white");
        }
        cout << endl;
    }
    svg_end();
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
    const auto numbers = input_numbers(number_count);
    size_t bin_count;
    cerr << "Enter bin count: ";
    cin >> bin_count;
    cin.get();
    vector<char>naming(80);
    vector<vector<char>> bin_namings(bin_count,naming);
    vector<char[80]> bin_naming_list(bin_count);
    for (size_t i = 0; i < bin_count; i++)
    {
        cerr << "Enter bin " << i + 1 << " naming: ";
        cin.getline(bin_naming_list[i], 80);
    }
    for (size_t iter = 0; iter < bin_count; iter++)
    {
        for (size_t i = 0; i <= strlen(bin_naming_list[iter]); i++)
        {
            char* name = bin_naming_list[iter];
            bin_namings[iter].push_back(name[i]);
        }
    }
    const auto bins = make_histogram(numbers, number_count, bin_count);
    show_histogram_svg(bins, bin_count, bin_namings);
    return 0;
}
