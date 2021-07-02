
void fun() {

}

namespace MyNS {

	int fun = 3; // 如果这么写会产生编译错误。因为第一步的
				 // 查找是叫名称查找。
	void fun() {
		std::cout << "MyNS\n";
	}

	void g() {
		fun(); // unqualified lookup,
		       // 进行主机查找，首先查找MyNS, 如果能找到fun，
		       // 就不再继续查找了
	}
}

int main() {
	fun(); // unqualified lookup
	::fun(); // qualified lookup
	MyNS::fun(); // qualified lookup
}

// Argument Dependent Lookup: ADL
// version 1
struct Str {};

void fun(Str x) {

}

int main() {
	Str val;
	fun(val);
}
// 上面的程序是可以正常工作的

// version 2
namespace MyNS {

	struct Str {};

	void fun(Str x) {

	}
}

int main() {
	MyNS::Str val;
	fun(val); // 非依赖名称，
	//c++中会根据实参进行依赖查找
}