#include <iostream>
#include <math.h>
#include <cscobj.h>
#include <vector>
#include <Windows.h>
#include <iterator>
#include <sstream>
#include <string>
#include "histogram.h"
#include <curl/curl.h>

using namespace std;

vector<double> input_numbers(istream& in, size_t count,bool prompt)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        if (prompt) cerr << "Enter number " << i + 1 << ": ";
        in >> result[i];
    }
    return result;
}

Input read_input(istream& in, bool prompt)
{
    Input data;
    if (prompt) cerr << "Enter number count: ";
    in >> data.number_count;
    data.numbers = input_numbers(in, data.number_count,prompt);
    if (prompt) cerr << "Enter bin count: ";
    in >> data.bin_count;
    string str;
    in.get();
    in.get();
    for (size_t i = 0; i < data.bin_count; i++)
    {
        if (prompt) cerr << "Enter bin " << i + 1 << " naming: ";
        getline(in,str);
        data.bin_namings.push_back(str);
    }
    if (prompt) cerr << "Enter separator dash: ";
    in >> data.dash;
    if (prompt) cerr << "Enter separator dasharray: ";
    in >> data.dasharray;
    return data;
}

size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx)
{
    size_t data_size = item_size * item_count;
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    char* item_list = reinterpret_cast<char*>(items);
    buffer->write(item_list, data_size);
    return data_size;
}

Input download(const string& address)
{
    stringstream buffer;
    CURL *curl = curl_easy_init();
        if(curl)
        {
            CURLcode res;
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
            curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
            res = curl_easy_perform(curl);
            if (res != 0)cout<<curl_easy_strerror(res);
            curl_easy_cleanup(curl);
        }
    return read_input(buffer, false);
}

vector<size_t> make_histogram(Input data)
{
    vector<size_t> bins(data.bin_count);
    double min = data.numbers[0];
    double max = data.numbers[0];
    find_minmax(data.numbers, min, max);
    double bin_size = (max - min) / data.bin_count;
    for (size_t i = 0; i < data.number_count; i++)
    {
        bool found = false;
        for (size_t j = 0; (j < data.bin_count - 1) && !found; j++)
        {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;
            if ((lo <= data.numbers[i]) && (data.numbers[i] < hi))
            {
                bins[j]++;
                found = true;
            }
        }
        if (!found)
        {
            bins[data.bin_count - 1]++;
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



int main(int argc, char* argv[])
{
    curl_global_init(CURL_GLOBAL_ALL);
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Input data;
    if (argc>1)
    {
    data = download(argv[1]);
    }
    else
    {
    data = read_input(cin,true);
    }
    const auto bins = make_histogram(data);
    show_histogram_svg(bins, data.bin_count, data.bin_namings,data.dash,data.dasharray);
    return 0;
}
