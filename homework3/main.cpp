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
    // : std::conditional<((x1 + x2 + sign) < 10), iseq<x1 + x2 + sign>,
                      //  iseq<x1 + x2 + sign - 10>>::type {
  static constexpr unsigned add_value = x1+x2+sign;
  static constexpr unsigned int value = (add_value) % 10;
  static constexpr unsigned sign_flag = add_value / 10;
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
  using res = typename std::conditional<(tmp::sign_flag == 1), 
                                         typename Add<iseq<TRes..., tmp::value>, iseq<tmp::sign_flag>, iseq<TRmain2...>, iseq<0>>::res, 
                                         iseq<TRes..., tmp::value, TRmain2...>>::type; 
                                        //  iseq<TRes..., >>::type;
// typename Add<tmp, iseq<TRmain1...>, iseq<>, typename tmp::new_sign>::res, 
                                // iseq<TRes..., tmp::value, TRmain1...>
  // using res = iseq<TRes..., T2 + sign, TRmain2...>;
};

// 第三种情况：结果不为空，x2为空
template <unsigned int... TRes, unsigned int T1, unsigned int... TRmain1,
          unsigned int sign>
struct Add<iseq<TRes...>, iseq<T1, TRmain1...>, iseq<>, iseq<sign>> {
  using tmp = Add_item<iseq<T1>, iseq<0>, iseq<sign>>;
  using res = typename std::conditional<(tmp::sign_flag == 1), 
                                         typename Add<iseq<TRes..., tmp::value>, iseq<tmp::sign_flag>, iseq<TRmain1...>, iseq<0>>::res, 
                                         iseq<TRes..., tmp::value, TRmain1...>>::type; 
};

// 第四种情况:结果不为空，x1,x2为空,//需要根据符号位是否为0来判断
template <unsigned int... TRes, 
          unsigned int sign>
struct Add<iseq<TRes...>, iseq<>, iseq<>, iseq<sign>>{
  using res = typename std::conditional<(sign == 1), iseq<TRes..., sign>, iseq<TRes...>>::type;
};

// 第五种情况：结果不为空，x1,x2也不为空
template <unsigned int... TRes, unsigned int T1, unsigned int... TRmain1, unsigned int T2,
          unsigned int... TRmain2, unsigned int sign>
struct Add<iseq<TRes...>, iseq<T1, TRmain1...>, iseq<T2, TRmain2...>, iseq<sign>> {
  using tmp = Add_item<iseq<T1>, iseq<T2>, iseq<sign>>;
  using res = typename Add<iseq<TRes..., tmp::value>, iseq<TRmain1...>, iseq<TRmain2...>,
                           typename tmp::new_sign>::res;
};

int main() {

  // constexpr auto x = Add<iseq<2>, iseq<4>, iseq<0>>::res;
  // using D1 = Add_item<iseq<9>, iseq<2>, iseq<1>>;
  // print(D1());
  // print(D1::new_sign());

  // using D2 = Add_item<iseq<0>, iseq<0>, iseq<0>>;
  // print(D2());
  // print(D2::new_sign());
  // // std::cout << x << std::endl;
  // using D = iseq<1, 5, 8, 2, 9>;
  // print(D());
  // using res = Reverse<iseq<>, D>::old_seq;
  // print(res());

  using D2 = iseq<1,5,9,9>;
  using D1 = iseq<0>;

  using reverse_D1 = Reverse<iseq<>, D1>::old_seq;
  using reverse_D2 = Reverse<iseq<>, D2>::old_seq;

  using res = Add<iseq<>, reverse_D1, reverse_D2, iseq<0>>::res;

  using final_res = Reverse<iseq<>, res>::old_seq;
  print(final_res());


}

