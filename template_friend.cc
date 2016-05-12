template <typename T> class Pal;

template <typename T> class C {
	friend class Pal<T>; // need
	template <typename X> friend class Pal2;
	friend class Pal3;
};

int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}