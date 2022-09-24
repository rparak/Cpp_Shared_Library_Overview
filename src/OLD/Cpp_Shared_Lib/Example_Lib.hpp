#include <iostream>
#include <tuple>
#include <ctime>
#include <vector>
// test -> craete new
// please finish the project -> tomorrow||||
namespace Example_Lib{
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

    template<typename T> T* Generate_Random_Array(const T MIN, const T MAX, const int N){
        std::srand(time(0)); 

        T* output = new T[N];
        for(auto i = 0; i < N; ++i){
            output[i] = static_cast<T>(MIN + rand() % (MAX - MIN + 1));
        }

        return output;
    }

    template<typename T> std::tuple<T, int> Max(std::vector<T> x){
        T max_val; int max_val_idx = 0; int i = 0;
        for(const auto& x_i : x){
            if(max_val < x_i){
                max_val     = x_i;
                max_val_idx = i;
            }
            ++i;
        }
        
        return {max_val, max_val_idx};
    }

    template <typename T> Find_Min_Value_Output_str<T> Min(Find_Min_Value_Input_str<T> *x){
        Find_Min_Value_Output_str<T> output;
        output.value = x->x[0]; output.idx = 0;
        for(auto i = 1; i < x->N; ++i){
            if(output.value > x->x[i]){
                output.value = x->x[i];
                output.idx   = i;
            }
        }

       return output;
    }

    template <typename T>
    class Simple_Calculator {
        public:
            // Initialization of input parameters
            explicit Simple_Calculator(const T param_1, const T param_2) 
                : __param_1(param_1), __param_2(param_2)
            {}
            ~Simple_Calculator()
            {}

            std::string Get_Parameters(){
                return std::string("Parameter 1: ") + std::to_string(this->__param_1) + "\nParameter 2: " + std::to_string(this->__param_2);
            }

            T Addition(){ 
                return this->__param_1 + this->__param_2; 
            }

            T Substraction() { 
                return this->__param_1 - this->__param_2;
            }

        private:
            T __param_1{0};
            T __param_2{0};
    };
}
