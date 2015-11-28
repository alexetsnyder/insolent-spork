#include <iostream>
#include <cstdlib>
#include "Angle.h"
#include "mymatrix.h"



int main()
{
	mat4 I = identity();
	mat4 inverse;
	double m[16];

	convert_mat4_to_array(I, m);

	convert_array_to_mat4(m, inverse);
}

