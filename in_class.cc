#include <iostream>

int func() {
	int i{};
	std::cin >> i; 
	return i;
}

class A {
  public:
  	A(int y_) : y{y_} {}
	static int s;
	int x{func()};
	int y{12};
};

int A::s = func();

int main(int argc, char const *argv[])
{
	A a(99);
	std::cout << A::s << " " << a.x << " " << a.y << std::endl;
	return 0;
}