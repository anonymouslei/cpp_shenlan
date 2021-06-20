#include <iostream>
#include <vector>

int main(void) {
	constexpr size_t buffer_count = 10000;
	std::vector<size_t> buffer(buffer_count);
	for (size_t i = 0; i < buffer_count; ++i) {
		buffer[i] = i;
	}

	size_t max_value = buffer[0];
	for (size_t i = 0; i < buffer_count; ++i) {
		max_value = (max_value > buffer[i]) ? max_value : buffer[i]; // 获取max_value和buffer中的最大值
	}
	// max_value is the max value of the buffer
	// 程序逻辑上没有问题，但是有可以提高的地方。
	// 比较的速度比较快，但是我们要花费比较多的时间在for循环上
	// 花费更多的时间在 for(size_t i = 0; i < buffer_count; ++i)
	// 我们希望花更多的时间在处理逻辑上，而不是花时间在for循环上

	// new version
	for (size_t i = 0; i < buffer_count; i += 8) {
		max_value = (max_value > buffer[i]) ? max_value : buffer[i]; 
		max_value = (max_value > buffer[i+1]) ? max_value : buffer[i+1]; 
		max_value = (max_value > buffer[i+2]) ? max_value : buffer[i+2];
		max_value = (max_value > buffer[i+3]) ? max_value : buffer[i+3];
		max_value = (max_value > buffer[i+4]) ? max_value : buffer[i+4];
		max_value = (max_value > buffer[i+5]) ? max_value : buffer[i+5];
		max_value = (max_value > buffer[i+6]) ? max_value : buffer[i+6];
		max_value = (max_value > buffer[i+7]) ? max_value : buffer[i+7];
	}

	// if buffer_count is 10001,那么输出结果变成了乱码。
	// 处理顺序：
	// 0-7, 8-15, ... 9992-9999, 后面的会发生内存访问越界

	// 解决办法： version 2 
	for (size_t i = 0; i + 8 < buffer_count; i += 8) {
		max_value = (max_value > buffer[i]) ? max_value : buffer[i]; 
		max_value = (max_value > buffer[i+1]) ? max_value : buffer[i+1]; 
		max_value = (max_value > buffer[i+2]) ? max_value : buffer[i+2];
		max_value = (max_value > buffer[i+3]) ? max_value : buffer[i+3];
		max_value = (max_value > buffer[i+4]) ? max_value : buffer[i+4];
		max_value = (max_value > buffer[i+5]) ? max_value : buffer[i+5];
		max_value = (max_value > buffer[i+6]) ? max_value : buffer[i+6];
		max_value = (max_value > buffer[i+7]) ? max_value : buffer[i+7];
	}
	for (size_t i = buffer_count / 8 * 8; i < buffer_count; ++i) {
		max_value = (max_value > buffer[i]) ? max_value : buffer[i]; 
	}
	// 缺点，同一个逻辑的代码，可是我们不得不写两遍。我们写了两个for循环

	// version 3
	auto ptr = buffer.begin();
	for (size_t i = 0; i + 8 < buffer_count; i += 8) {
		max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
		max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
		max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
		max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
		max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
		max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
		max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
		max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
	}

	switch (buffer_count % 8) {
	case 7: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]]
	case 6: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]]
	case 5: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]]
	case 4: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]]
	case 3: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]]
	case 2: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]]
	case 1: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
	};

	// version 4
	// 先处理一部分代码，让剩余代码是8的倍数
	// 前提：数组不为空
	switch (buffer_count % 8) {
	case 0: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]]
	case 7: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]]
	case 6: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]]
	case 5: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]]
	case 4: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]]
	case 3: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]]
	case 2: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]]
	case 1: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
	};
	for (size_t i = 0; i < (buffer_count - 1)/8; i += 8) {
		max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
		max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
		max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
		max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
		max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
		max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
		max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
		max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
	}

	// version 5
	// switch 内部套循环 => 达夫设备
	size_t i = 0;
	switch (buffer_count % 8) {
		for (; i < (buffer_count + 7)/8; ++i) { [[fallthrough]]
		case 0: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]]
		case 7: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]]
		case 6: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]]
		case 5: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]]
		case 4: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]]
		case 3: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]]
		case 2: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr; [[fallthrough]]
		case 1: max_value = (max_value > *ptr) ? max_value : *ptr; ++ptr;
	}
	};
	// 首先根据buffer_count跳到某一个case，在顺序执行完case之后，会继续执行for循环
	// 本质上就是先执行switch，再执行for循环
	// for循环的判断条件需要修改，因为他会先执行switch，然后执行++i,然后回来的时候出发判断条件
	
	// 再编译的时候打开 -Wimplicit-fallthrough 会提示fallthrough
}