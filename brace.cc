#include <vector>
#include <string>
#include <memory>
#include <iostream>

int a{1};
double b{2.0};
int arr[]{1, 2, 3};
std::string s{"hi"};
std::vector<int> v{1, 2, 3};
int *pia{new int[10]{1, 2, 3}};

class A {
  public:
  	A(int i1, int i2) 
  	: i1_{i1}, i2_{i2} {}

  	// a call to a delegating constructor shall be the only member-initializer
  	A(int i1, int i2, std::string s) 
  	: A{i1, i2} {
  		s_ = s; 
  		// s_{s};
  	} 

  private:
	int i1_{1};
	int i2_{2};
	std::string s_{};
};

int main(int argc, char const *argv[])
{
	const int ci{}; // 0
	int *pi{new int{42}};
	delete pi;
	auto p{std::make_shared<int>(42)};
	auto q{p};
	return 0;
}