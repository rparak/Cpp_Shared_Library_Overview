#include <iostream>
// sudo apt-get install libboost-all-dev
#include <boost/range/adaptor/indexed.hpp>

namespace Example_lib{
    template <typename T> std::tuple<T, int> Max(T* x){
        std::tuple<T, int> max_x(x[0], 0);
        for (auto const& in_byte_arr_i : in_byte_arr | boost::adaptors::indexed(0)){

        }
    }
}