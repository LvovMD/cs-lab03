#include <iostream>
#include <math.h>
#include <cscobj.h>
#include <vector>
#include <Windows.h>

using namespace std;


int main()
{

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
    vector<double> numbers(number_count);
    for (size_t i = 0; i < number_count; i++)
    {
        cerr << "Enter number " << i + 1 << ": ";
        cin >> numbers[i];
    }
    size_t bin_count;
    cerr << "Enter bin count: ";
    cin >> bin_count;
    vector<size_t> bins(bin_count);
    vector<char[80]> bin_namings(bin_count);
    cin.get();
    for (size_t i = 0; i < bin_count; i++)
    {
        cerr << "Enter bin " << i + 1 << " naming: ";
        cin.getline(bin_namings[i], 80);
    }
    double max_len = strlen(bin_namings[0]);
    for (size_t i = 0; i < bin_count; i++)
    {
        if (strlen(bin_namings[i]) > max_len)
        {
            max_len = strlen(bin_namings[i]);
        }
    }
    double min = numbers[0];
    double max = numbers[0];
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
    const size_t SCREEN_WIDTH = 80;
    size_t MAX_ASTERISK = SCREEN_WIDTH - max_len - 1;
    double max_count = bins[0];
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
        height = static_cast<double>(MAX_ASTERISK) /static_cast<double>(max_count);
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
    return 0;
}
