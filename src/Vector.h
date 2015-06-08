////////////////////////////////////////////////////////////
//
// PTI : Collision detection
// Copyright (C) 2009 Orhan Donovan ( dorhan@nantes.epsi.fr )
//
// - Author : Orhan Donovan.
// - Create : 27/09/2009.
// - Desc.  : Vector.
//
////////////////////////////////////////////////////////////

#ifndef VECTOR_H
#define VECTOR_H

    // Library
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>

    // Structures
    typedef struct
    {
        float x;
        float y;
    } Vector;


    // Normalise le vecteur ( Lui donne une taille de 0 à 1 )
    float Vector_Normalise( Vector *vector );

    // Calcul la taille du vecteur
    float Vector_Length( Vector *vector );

    // Multiplie deux vecteurs
    float Vector_Multiply( Vector *vector1, Vector *vector2 );

#endif
