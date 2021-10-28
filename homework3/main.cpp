#include <iostream>
#include <iterator>

template <unsigned int... valsT> struct iseq {};

template <unsigned int... valsT> void print(iseq<valsT...>) {
  static constexpr unsigned int vals[] = {valsT...};
  std::copy(std::begin(vals), std::end(vals),
            std::ostream_iterator<int>(std::cout, " "));
  std::endl(std::cout);
}

// reverse
template<typename Res, typename Rem> struct Reverse;

// template<int T, int Remain> struct Reverse<iseq<>, iseq<T, TRemain...>>;


// add
template<typename x1, typename x2, typename x3> struct Add;

template<unsigned int x1, unsigned int x2, unsigned int sign>
struct Add<iseq<x1>, iseq<x2>,iseq<sign>> {
    constexpr static unsigned int res = x1 + x2 + sign;
};

int main() {

    constexpr auto x = Add<iseq<2>,iseq<4>,iseq<0>>::res;
    std::cout << x << std::endl;
  // std::cout << M<3>::val << std::endl;
}
