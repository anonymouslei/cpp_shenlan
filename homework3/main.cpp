#include <iostream>
#include <iterator>

template <int... valsT> struct iseq {};

template <int... valsT> void print(iseq<valsT...>) {
  static constexpr int vals[] = {valsT...};
  std::copy(std::begin(vals), std::end(vals),
            std::ostream_iterator<int>(std::cout, " "));
  std::endl(std::cout);
}

// reverse
// template<typename Res, typename Rem> struct Reverse;

// template<int U1> struct Reverse<>;


// add
template<typename x1, typename x2, typename x3> struct Add;

template<int x1, int x2, int sign>
struct Add<iseq<x1>, iseq<x2>,iseq<sign>> {
    constexpr static int res = x1 + x2 + sign;
};

int main() {

    constexpr auto x = Add<iseq<2>,iseq<4>,iseq<0>>::res;
    std::cout << x << std::endl;
  // std::cout << M<3>::val << std::endl;
}
