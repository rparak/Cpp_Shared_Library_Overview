#include "Example_Lib.hpp"

// g++ -shared -std=c++17 -fPIC -o DLL/Example_Lib_Shared.dll Example_Lib_Shared.hpp
// g++ -shared -std=c++17 -fPIC -o SO/Example_Lib_Shared.so Example_Lib_Shared.hpp

// probably use only struct for in/out

template <typename T> 
struct Find_Min_Value_Output_str{
    T value;
    int idx;
};

template <typename T> 
struct Find_Min_Value_Input_str{
    T *x;
    size_t N;
};

extern "C" { 
    __declspec(dllexport) Find_Min_Value_Output_str<int> Min_Int(Find_Min_Value_Input_str<int>* x)
    {
        Find_Min_Value_Output_str<int> output;
        output.value = x->x[0]; output.idx = 0;
        for(auto i = 1; i < x->N; ++i){
            if(output.value > x->x[i]){
                output.value = x->x[i];
                output.idx   = i;
            }
        }

       return output;
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
