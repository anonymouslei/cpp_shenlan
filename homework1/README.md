# project 1
## 使用方法
./a.out num.txt 8 3
## 编程思路
- 将参数读入程序
- 将string数据类型转换为vector形式（StringToVector）
  - 存入符号位。
  - 将第一个不为0的数存入数组
  - 循环存入其他的数
  - 如果数字都是零，那么在数组中写入一个0
- 两个数相加（Addition）
    - 符号位都是正相加（same_sign_add）
      - 对相同size的部分进行相加。如果超出范围，则进位(OutBounds)
      - 将相同size外的部分加上进位符（ten_flag）写入结果
    - 符号位都是负相加(same_sign_add)
      - 同“符号位都是正”
    - 符号位不同相加
      - 比较大小，得到绝对值较大的数（isgreater）
        - 比较size，size大的数则大
        - 在size相同的情况下，从高位到低位比较每一位的大小，高位大就直接输出
      - 用大的数减去小的数（subtraction）
        - 先减去相同size的部分
        - 再将不同size的部分加上进位直接写入结果
- 将M进制转化为N进制（ConvertMToN）
  - reference: https://blog.csdn.net/Jaster_wisdom/article/details/52107785
  - 参考了该博客的思路，但是代码都是自己独立完成
- vector转化为String(VectorToString)
- 将结果输出到屏幕上