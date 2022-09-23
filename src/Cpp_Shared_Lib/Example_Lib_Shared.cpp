#include "Example_Lib.hpp"

// g++ -shared -std=c++17 -fPIC -o DLL/Example_Lib_Shared.dll Example_Lib_Shared.hpp
// g++ -shared -std=c++17 -fPIC -o SO/Example_Lib_Shared.so Example_Lib_Shared.hpp

// probably use only struct for in/out

template <typename T> 
struct FCE_ARRAY_MinMax_INPUT_Str{
    T *Array;
    size_t N;
};

template <typename T> 
struct FCE_ARRAY_MinMax_OUTPUT_Str{
    T Value;
    int Index;
};


extern "C" { 
    __declspec(dllexport) int* Generate_Random_Array(const int MIN, const int MAX, const size_t N)
    {
        std::srand(time(0)); 

        int* Output = new int[N];
        for(auto i = 0; i < N; ++i){
            Output[i] = static_cast<int>(MIN + rand() % (MAX - MIN + 1));
        }

        return Output;
    }

     __declspec(dllexport) void Multiply_Array_By_Number(const int Number, int *Array, const size_t N) 
     { 
        /*
        Multiplying an array by a number
        Multiply each element in a list by a number in
        */
        int x_temp;
        for (auto i = 0; i < N; ++i)
        {
            x_temp = Array[i];
            Array[i] = x_temp * Number;
        }
    }

    __declspec(dllexport) FCE_ARRAY_MinMax_OUTPUT_Str<int> Array_MinMax(FCE_ARRAY_MinMax_INPUT_Str<int>* Input, const bool return_min_val)
    {
        FCE_ARRAY_MinMax_OUTPUT_Str<int> Output;
        Output.Value = Input->Array[0]; Output.Index = 0;
        for(auto i = 1; i < Input->N; ++i){
            if(return_min_val == true){
                if(Output.Value > Input->Array[i]){
                    Output.Value = Input->Array[i];
                    Output.Index = i;
                }
            }else{
                if(Output.Value < Input->Array[i]){
                    Output.Value = Input->Array[i];
                    Output.Index = i;
                }
            }
        }

       return Output;
    }

    /*
    __declspec(dllexport) std::tuple<int, int> Max_Int(const int *x, const size_t N)
    {   
        std::vector<int> x_v(x, x + N);
        return Example_Lib::Max<int>(x_v);
    }

    __declspec(dllexport) int* Max_Int_Py(int *x, const size_t N)
    {   
        static int res[2]{x[0], 0};
        for(int i = 1; i < N; ++i){
            if(res[0] < x[i]){
                res[0] = x[i];
                res[1] = i;
            }
        }
        return res;
    }

    __declspec(dllexport) std::tuple<double, double> Max_Double(const double *x, const size_t N)
    {   
        std::vector<double> x_v(x, x + N);
        return Example_Lib::Max<double>(x_v);
    }
    __declspec(dllexport) Example_Lib::Find_Min_Value_Output_str<int> Min_Int(Example_Lib::Find_Min_Value_Input_str<int> *x){
        return Example_Lib::Min<int>(x);
    }
    __declspec(dllexport) Example_Lib::Find_Min_Value_Output_str<double> Min_Double(Example_Lib::Find_Min_Value_Input_str<double> *x){
        return Example_Lib::Min<double>(x);
    }
    */
}
