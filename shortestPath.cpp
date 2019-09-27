

#include <iostream>
#include <cmath> // required for sqrt()


// x ,y, z coordinate data type
template <class T>
class coord
{
public:
	coord() : x(0), y(0), z(0) { };
	coord(T set_x) : x(set_x), y(0), z(0) { };
	coord(T set_x, T set_y) : x(set_x), y(set_y), z(0) { };
	coord(T set_x, T set_y, T set_z) : x(set_x), y(set_y), z(set_z) { };

	// copy constructor
	coord(const coord& rhs) : x(rhs.get_x()), y(rhs.get_y()), z(rhs.get_z()) { };

	inline T get_x() const { return x };
	inline T get_y() const { return y };
	inline T get_z() const { return z };

	~coord() { };

protected:
	T x;
	T y;
	T z;
};

int main()
{

	const double pi = 3.14;

	const double omega_max = 2; // maximum angular velocity in radians per second
	const double velocity = 5; // straight-line velocity in metres per second

	const double radius_min = velocity / omega_max; // Radius of smallest achievable turning circle in metres

	const double circumference = (velocity * 2 * pi) / omega_max;
	const double freq = (2 * pi) * omega_max; // time taken to complete a full circle measured in seconds

	coord<float> c1(50.0f, 24.0f), c2(103.0f, 124.0f), c3(300.0f,162.0f); // c1: start coord, c2: intermediate coord, c3: destination coord
	coord<float> midpoint(((c1.get_x() + c3.get_x()) / 2), ((c1.get_y() + c3.get_y()) / 2), ((c1.get_z() + c3.get_z()) /2) ); // 3d coord through which bisector will project from coord c2
	// coord<float> pivot(c1.get_x ... TODO

}
