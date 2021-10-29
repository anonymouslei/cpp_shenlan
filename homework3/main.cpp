#include <iostream>
#include <iterator>

template <unsigned int... valsT> struct iseq {};

template <unsigned int... valsT> void print(iseq<valsT...>) {
  static constexpr unsigned int vals[] = {valsT...};
  std::copy(std::begin(vals), std::end(vals),
            std::ostream_iterator<int>(std::cout, " "));
  std::endl(std::cout);
}

// reverse, //写的不对
template <typename Res, typename Rem> struct Reverse;

// 第一种情况：前面的数组为0，后面的数组有值。将后面的数字的第一位放到前面的数组
template <unsigned int T, unsigned int... TRmain>
struct Reverse<iseq<>, iseq<T, TRmain...>> {
  using new_seq = iseq<T>;
  using old_seq = typename Reverse<new_seq, iseq<TRmain...>>::old_seq;
};

// 第二种情况: 前后的数组都不为空
template <unsigned int... TProcessed, unsigned int T, unsigned int... TRmain>
struct Reverse<iseq<TProcessed...>, iseq<T, TRmain...>> {
  using new_seq = iseq<T, TProcessed...>;
  using old_seq = typename Reverse<new_seq, iseq<TRmain...>>::old_seq;
};

// 第三种情况：前面的数组已满，后面的数组为空
template <unsigned int... TRmain> struct Reverse<iseq<TRmain...>, iseq<>> {
  using old_seq = iseq<TRmain...>;
};

// add
template <typename x1, typename x2, typename x3> struct Add;
// TODO: 如果满10，则进一

template <unsigned int x1, unsigned int x2, unsigned int sign>
struct Add<iseq<x1>, iseq<x2>, iseq<sign>> {
  constexpr static unsigned int res = x1 + x2 + sign;
};

int main() {

  constexpr auto x = Add<iseq<2>, iseq<4>, iseq<0>>::res;
  // std::cout << x << std::endl;
  using D = iseq<1, 5, 8, 2, 9>;
  print(D());
  using res = Reverse<iseq<>, D>::old_seq;
  print(res());
}
