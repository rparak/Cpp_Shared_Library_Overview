//#include "Example_lib.hpp"

#include <iostream>
#include <tuple>
#include <vector>
// g++ -std=c++17 test_lib.cpp -o test_lib -ldl
int main()
{
    std::tuple<int, int> x(1, 8);

    std::cout << std::get<0>(x) << " " << std::get<1>(x) << std::endl;

    std::get<0>(x) = 8; std::get<1>(x) = 1;
    std::cout << std::get<0>(x) << " " << std::get<1>(x) << std::endl;

    int arr[5] = {16, 2, 77, 40, 120};

    std::vector<int> arr_v {16, 2, 77, 40, 120};

    // int n = sizeof(arr) / sizeof(arr[0]);
    // vector<int> vect(n, 10);
    /*
    for(const auto& x : arr_v){
        std::cout << x << std::endl;
    }*/

    for(auto it = arr_v.begin(); it != arr_v.end(); ++it){
        std::cout << *it << std::endl;
    }

    return 0;
}