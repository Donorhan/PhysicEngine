////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Solver.h"


////////////////////////////////////////////////////////////
///
/// Separe les objets
///
////////////////////////////////////////////////////////////
void Solver_ApplyForces( int idA, int idB, Vector *direction, float *force )
{
    // Différence de vitesse
    Vector difference;
    difference.x = objects[idA].velocity.x - objects[idB].velocity.x;
    difference.x = objects[idA].velocity.y - objects[idB].velocity.y;

    // Calcul sous forme de force n
	float n  = Vector_Multiply( &difference, direction);

	Vector Dn;
	Dn.x = direction->x * n;
	Dn.y = direction->y * n;

	Vector Dt;
	Dt.x = direction->x - Dn.x;
	Dt.y = direction->y - Dn.y;

	if ( n > 0.0f )
	{
	    Dn.x = 0.0f;
        Dn.y = 0.0f;
	}

	float dt  = Vector_Multiply( &Dt, &Dt );
	float CoF = FRICTION;

	if ( dt < GLUE * GLUE )
        CoF = 1.01f;

	difference.x = -(1.0f + RESTITUTION) * Dn.x - (CoF) * Dt.x;
	difference.y = -(1.0f + RESTITUTION) * Dn.y - (CoF) * Dt.y;

	float m0 = 0.5f;//0.00034f;
	float m1 = 0.5f;//0.00034f;
	float m  = m0 + m1;
	float r0 = m0 / m;
	float r1 = m1 / m;

    objects[idA].velocity.x += direction->x * r0;
    objects[idA].velocity.y += direction->y * r0;

    objects[idB].velocity.x -= direction->x * r1;
    objects[idB].velocity.y -= direction->y * r1;
}


////////////////////////////////////////////////////////////
///
/// Rend les forces aux polygons
///
////////////////////////////////////////////////////////////
void Solver_Separate( int idA, int idB, Vector *direction )
{
    float force = 0.0f;

    if ( objects[idA].fixed )
	{
		objects[idB].position.x -= direction->x * 2;
		objects[idB].position.y -= direction->y * 2;
	}
	else if ( objects[idB].fixed )
	{
		objects[idA].position.x += direction->x * 2;
		objects[idA].position.y += direction->y * 2;
	}
	else
	{
		objects[idA].position.x += direction->x * 0.5f;
		objects[idA].position.y += direction->y * 0.5f;

		objects[idB].position.x -= direction->x * 0.5f;
		objects[idB].position.y -= direction->y * 0.5f;
	}

	Vector_Normalise( direction );
	Solver_ApplyForces( idA, idB, direction, &force );
}
