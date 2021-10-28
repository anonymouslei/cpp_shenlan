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
template<int x1, int x2, int sign>
struct Add {
    constexpr static int res = x1 + x2 + sign;
};

int main() {

    constexpr auto x = Add<2,4,0>::res;
    std::cout << x << std::endl;
  // std::cout << M<3>::val << std::endl;
}
