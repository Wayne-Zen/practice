#include <iostream>
#include <memory>

class B {
  public:
	virtual void say() {
		std::cout << "B" << std::endl;
	}
};

class D : public B {
  public:
	/* virtual */ void say() override { // implicitly virtual, better to claim virtual
		std::cout << "D" << std::endl;
	}
};

class DD : public D {
  public:
  	void say() override;
};

void DD::say() /*X override X*/ {
	std::cout << "DD" << std::endl;
}


int main(int argc, char const *argv[])
{
	std::shared_ptr<B> p1{std::make_shared<B>()};
	p1->say(); // B

	std::shared_ptr<D> p2{std::make_shared<D>()};
	p2->say(); // D

	std::shared_ptr<B> p3{std::make_shared<D>()};
	p3->say(); // D

	std::shared_ptr<B> p4{new D{}};
	p4->say(); // D

	B* p5 = new D{};
	p5->say(); // D

	B* p6 = new DD{};
	p6->say(); // DD

	return 0;
}