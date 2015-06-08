////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Vector.h"


// Normalise le vecteur
float Vector_Normalise( Vector *vector )
{
    float length = Vector_Length( vector );

    // Evite division par 0.
    if( length == 0.0f )
        return 0.0f;

    vector->x *= ( 1.0f / length );
    vector->y *= ( 1.0f / length );

    return length;
}

// Calcul la taille du vecteur
float Vector_Length( Vector *vector )
{
    return sqrt( vector->x * vector->x + vector->y * vector->y );
}


// Multiplication de deux vector
float Vector_Multiply( Vector *vector1, Vector *vector2 )
{
    return ( vector1->x * vector2->x ) + ( vector1->y * vector2->y );
}
