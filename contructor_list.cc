#include <iostream>

double x = 9.5;

class A {
  public:
	const int i{10};
	double& r{x};
};

int main(int argc, char const *argv[])
{
	A a;
	std::cout << a.i << " " << a.r << std::endl;
	return 0;
}