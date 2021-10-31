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

// add_item
template <typename x1, typename x2, typename x3> struct Add_item;

template <unsigned int x1, unsigned int x2, unsigned int sign>
struct Add_item<iseq<x1>, iseq<x2>, iseq<sign>> {
  static constexpr unsigned int add_value = x1 + x2 + sign;
  static constexpr unsigned int value = (add_value) % 10;
  static constexpr unsigned int sign_flag = add_value / 10;
  using new_sign = iseq<sign_flag>;
};

// add func
template <typename res, typename x1, typename x2, typename sign> struct Add;

// 第一种情况：刚开始计算，结果为空， x1和x2有数值，符号位为0
template <unsigned int T1, unsigned int... TRmain1, unsigned int T2,
          unsigned int... TRmain2>
struct Add<iseq<>, iseq<T1, TRmain1...>, iseq<T2, TRmain2...>, iseq<0>()> {
  using tmp = Add_item<iseq<T1>, iseq<T2>, iseq<0>>;
  using res = typename Add<tmp, iseq<TRmain1...>, iseq<TRmain2...>,
                           typename tmp::new_sign>::res;
};

// 第二种情况：结果不为空，x1为空
template <unsigned int... TRes, unsigned int T2, unsigned int... TRmain2,
          unsigned int sign>
struct Add<iseq<TRes...>, iseq<>, iseq<T2, TRmain2...>, iseq<sign>> {
  using tmp = Add_item<iseq<T2>, iseq<0>, iseq<sign>>;
  using res = typename std::conditional<
      (tmp::sign_flag == 1),
      typename Add<iseq<TRes..., tmp::value>, iseq<>, iseq<TRmain2...>,
                   typename tmp::new_sign>::res,
      iseq<TRes..., tmp::value, TRmain2...>>::type;
};

// 第三种情况：结果不为空，x2为空
template <unsigned int... TRes, unsigned int T1, unsigned int... TRmain1,
          unsigned int sign>
struct Add<iseq<TRes...>, iseq<T1, TRmain1...>, iseq<>, iseq<sign>> {
  using tmp = Add_item<iseq<T1>, iseq<0>, iseq<sign>>;
  using res = typename std::conditional<
      (tmp::sign_flag == 1),
      typename Add<iseq<TRes..., tmp::value>, iseq<>, iseq<TRmain1...>,
                   typename tmp::new_sign>::res,
      iseq<TRes..., tmp::value, TRmain1...>>::type;
};

// 第四种情况:结果不为空，x1,x2为空,//需要根据符号位是否为0来判断
template <unsigned int... TRes, unsigned int sign>
struct Add<iseq<TRes...>, iseq<>, iseq<>, iseq<sign>> {
  using res = typename std::conditional<(sign == 1), iseq<TRes..., sign>,
                                        iseq<TRes...>>::type;
};

// 第五种情况：结果不为空，x1,x2也不为空
template <unsigned int... TRes, unsigned int T1, unsigned int... TRmain1,
          unsigned int T2, unsigned int... TRmain2, unsigned int sign>
struct Add<iseq<TRes...>, iseq<T1, TRmain1...>, iseq<T2, TRmain2...>,
           iseq<sign>> {
  using tmp = Add_item<iseq<T1>, iseq<T2>, iseq<sign>>;
  using res = typename Add<iseq<TRes..., tmp::value>, iseq<TRmain1...>,
                           iseq<TRmain2...>, typename tmp::new_sign>::res;
};

// convert N to 10
template <typename Res, typename Rem, typename N> struct ConvertNToTen;

//第一种情况:结果为空，输入不为空
template <unsigned int T, unsigned int... TRmain, unsigned int N>
struct ConvertNToTen<iseq<>, iseq<T, TRmain...>, iseq<N>> {
  static constexpr unsigned int value = T;
  using iseq_value = iseq<value>;
  using res = typename ConvertNToTen<iseq_value, iseq<TRmain...>, iseq<N>>::res;
};

//第二种情况：结果不为空，输入不为空
template <unsigned int TRes, unsigned int T, unsigned int... TRmain,
          unsigned int N>
struct ConvertNToTen<iseq<TRes>, iseq<T, TRmain...>, iseq<N>> {
  static constexpr unsigned int value = TRes * N + T;
  using iseq_value = iseq<value>;
  using res = typename ConvertNToTen<iseq_value, iseq<TRmain...>, iseq<N>>::res;
};

// 终止条件：结果不为空，输入为空
template <unsigned int TRes, unsigned int N>
struct ConvertNToTen<iseq<TRes>, iseq<>, iseq<N>> {
  using res = iseq<TRes>;
};

// convert 10 to M
template<typename Res, typename Rem, typename M> struct ConvertTenToM;

//第一种情况：结果为空，输入不为空
template <unsigned int T, unsigned int M>
struct ConvertTenToM<iseq<>, iseq<T>, iseq<M>> {
  static constexpr unsigned int quotient = T / M;
  static constexpr unsigned int remainder = T % M;
  using res = typename ConvertTenToM<iseq<remainder>, iseq<quotient>, iseq<M>>::res;
};

//第二种情况：结果不为空，输入不为空
template <unsigned int... TProcessed, unsigned int T, unsigned int M>
struct ConvertTenToM<iseq<TProcessed...>, iseq<T>, iseq<M>> {
  static constexpr unsigned int quotient = T / M;
  static constexpr unsigned int remainder = T % M;
  // using iseq_value = iseq<quotient>;
  using res = typename ConvertTenToM<iseq<remainder, TProcessed...>, iseq<quotient>, iseq<M>>::res;
};

//第三种情况：终止条件
template <unsigned int... TProcessed, unsigned int M>
struct ConvertTenToM<iseq<TProcessed...>, iseq<0>, iseq<M>> {
  using res = iseq<TProcessed...>;
};

int main() {

  // constexpr auto x = Add<iseq<2>, iseq<4>, iseq<0>>::res;
  // using D1 = Add_item<iseq<9>, iseq<2>, iseq<1>>;
  // print(D1());
  // print(D1::new_sign());

  // using D2 = Add_item<iseq<9>, iseq<0>, iseq<1>>;
  // print(D2());
  // print(D2::new_sign());
  // print(D2::new_sign());
  // // std::cout << x << std::endl;
  // using D = iseq<1, 5, 8, 2, 9>;
  // print(D());
  // using res = Reverse<iseq<>, D>::old_seq;
  // print(res());

  // using D2 = iseq<1,9, 3 ,9,8>;
  // using D1 = iseq<5>;

  // using reverse_D1 = Reverse<iseq<>, D1>::old_seq;
  // using reverse_D2 = Reverse<iseq<>, D2>::old_seq;

  // using res = Add<iseq<>, reverse_D1, reverse_D2, iseq<0>>::res;

  // using final_res = Reverse<iseq<>, res>::old_seq;
  // print(final_res());

  // using D1 = iseq<0, 1, 1, 1, 1, 0, 1, 0>;
  // using D1_10 = ConvertNToTen<iseq<>, D1, iseq<2>>::res;
  // print(D1_10());

  using D1 = iseq<122>;
  using D1_10 = ConvertTenToM<iseq<>, D1, iseq<2>>::res;
  print(D1_10());
}
