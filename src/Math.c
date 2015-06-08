////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Math.h"


/////////////////////////////////////////////////////////
/// Calculate Pi
/////////////////////////////////////////////////////////
float Pi()
{
    return atan(1.0f) * 4.0f;
}

////////////////////////////////////////////////////////////
/// Calculate Pi * 2
////////////////////////////////////////////////////////////
float TwoPi()
{
    return 2.0f * Pi();
}

inline float frand( float x )
{
	return (rand() / (float) RAND_MAX ) * x;
}

// taken from
// http://www.physicsforums.com/showthread.php?s=e251fddad79b926d003e2d4154799c14&t=25293&page=2&pp=15
float Math_CalculateMass( const Vector *A, int Anum, float density )
{
    int i = 0;
    int j = 0;

	if (Anum < 2)
		return 5.0f * density;

	float mass = 0.0f;

	for( j = Anum-1, i = 0; i < Anum; j = i, i ++)
	{
		Vector P0 = A[j];
		Vector P1 = A[i];
		mass +=  (float) fabs( ( P0.x * P1.x ) - ( P0.y - P1.y ) );
	}

	if (Anum <= 2)
		mass = 10.0f;

	mass *= density * 0.5f;

	return mass;
}
