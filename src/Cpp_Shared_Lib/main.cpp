#include "Example_Lib.hpp"

// g++ -std=c++17 main.cpp -o main -ldl
int main()
{
    const size_t SIZE = 5;

    auto *arr_1 = Example_Lib::Generate_Random_Array<int>(1, 100, SIZE);

    int arr_n[SIZE];
    std::copy(arr_1, arr_1 + SIZE, arr_n);

    for(auto i = 0; i < SIZE; ++i){
        std::cout << arr_n[i] << std::endl;
    }

    auto [max_value, max_index] = Example_Lib::Max<int>(arr_n);
    std::cout << max_value << std::endl;
    std::cout << max_index << std::endl;

    Example_Lib::Find_Min_Value_Input_str<int> input_str;
    input_str.x = arr_n;
    input_str.N = std::size(arr_n);

    Example_Lib::Find_Min_Value_Output_str<int> output_str = Example_Lib::Min(&input_str);
    std::cout << output_str.value << std::endl;
    std::cout << output_str.idx << std::endl;

    Example_Lib::Simple_Calculator<int> Calculator{output_str.value, max_value};
    std::cout << Calculator.Get_Parameters() << std::endl;
    std::cout << Calculator.Addition() << std::endl;
    std::cout << Calculator.Substraction() << std::endl;

    return 0;
}
