#include <iostream>
#include <tuple>
#include <ctime>

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

template <typename T>
class Simple_Calculator {
    public:
        /*
        // Initialization of input parameters
        explicit Simple_Calculator(const T param_1, const T param_2) 
            : __param_1(param_1), __param_2(param_2)
        {}
        ~Simple_Calculator()
        {}
        */

        Simple_Calculator(T param_1, T param_2){
            this->param_1 = param_1;
            this->param_2 = param_2;
        }

        std::string Get_Parameters(){
            return std::string("Parameter 1: ") + std::to_string(this->param_1) + "\nParameter 2: " + std::to_string(this->param_2);
        }

        T Addition(){ 
            return this->param_1 + this->param_2; 
        }

        T Substraction() { 
            return this->param_1 - this->param_2;
        }

    private:
        T param_1{0};
        T param_2{0};
};


template <typename T>
class Test{
     private:
        T p1{0};
        T p2{0};
     public:
        // Initialization of input parameters
        explicit Test(T pp1, T pp2) 
            : p1(pp1), p2(pp2)
        {}
        ~Test()
        {}
        void setInt(T k){
            this->p1 = k;
        }
        int getInt(){
            return this->p1;
        }

        int Addition(){ 
            return this->p1 + this->p2; 
        }
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

    // class
    __declspec(dllexport) Simple_Calculator<int>* SC_Class_Create(const int Param_1, const int Param_2)
	{
		return new Simple_Calculator<int>(Param_1, Param_2);
	}

    __declspec(dllexport) void SC_Class_Delete(Simple_Calculator<int>* SC_Cls)
	{
        if(SC_Cls){
		    delete SC_Cls;
            SC_Cls = nullptr;
        }
	}

    __declspec(dllexport) std::string SC_Class_Get_Parameters(Simple_Calculator<int>* SC_Cls)
	{
        return SC_Cls->Get_Parameters();
	}

    __declspec(dllexport) int SC_Class_Addition_Parameters(Simple_Calculator<int>* SC_Cls, int result)
	{
        return SC_Cls->Addition();
	}

    __declspec(dllexport) int SC_Class_Substraction_Parameters(Simple_Calculator<int>* SC_Cls)
	{
        return SC_Cls->Substraction();
	}



    __declspec(dllexport) Test<int>* init(int k1, int k2) 
    {
        return new Test<int>(k1, k2);
    }

    __declspec(dllexport) void setInt(Test<int>* self, int k) 
    {
        self->setInt(k);
    }
    __declspec(dllexport) int getInt(Test<int>* self) 
    {
        return self->getInt();
    }

    __declspec(dllexport) int Addition(Test<int>* self) 
    {
        return self->Addition();
    }
}
