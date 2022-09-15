#include <iostream>
#include <tuple>
// sudo apt-get install libboost-all-dev
#include <boost/range/adaptor/indexed.hpp>

namespace Example_lib{
    template <typename T> std::tuple<T, int> Max(T* x){
        std::tuple<T, int> max_x(x[0], 0);
        for (auto const& x_i : x | boost::adaptors::indexed(0)){
            std::cout << x_i.value() << x_i.index() << std::endl;
        }

        return max_x;
    }
}
