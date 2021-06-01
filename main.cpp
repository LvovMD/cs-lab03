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



int main()
{
    auto info = GetVersion();
    DWORD mask = 0x0000ffff;
    DWORD version = info & mask;
    printf("%u %x \n",version,version);
    DWORD platform = info >> 16;
    DWORD min_mask = 0x0000ff00;
    DWORD minor = info & min_mask;
    printf("%u %x \n",minor,minor);
    DWORD maj_mask = 0x000000ff;
    DWORD major = info & maj_mask;
    printf("%u %x \n",major,major);
    if ((info & 0x8000000) == 0)
    {
        DWORD build = platform;
        printf("%u %x \n",platform,platform);
    }
    return 0;
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
    cerr << "Enter separator dash: ";
    double dash;
    cin >>  dash;
    cerr << "Enter separator dasharray: ";
    double dasharray;
    cin >> dasharray;
    const auto bins = make_histogram(numbers, number_count, bin_count);
    show_histogram_svg(bins, bin_count, bin_namings,dash,dasharray);
    return 0;
}
