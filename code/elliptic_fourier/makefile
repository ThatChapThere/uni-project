all:
	@g++ -std=c++20\
		$(shell pkg-config --cflags cairomm-1.16 gtkmm-4.0 --libs cairomm-1.16 gtkmm-4.0)\
		-o elliptic_fourier\
		*.cpp
