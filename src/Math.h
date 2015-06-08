////////////////////////////////////////////////////////////
//
// PTI : Collision detection
// Copyright (C) 2009 Orhan Donovan ( dorhan@nantes.epsi.fr )
//
// - Author : Orhan Donovan.
// - Create : 10/09/2009.
// - Desc.  : Fonctions mathématiques
//
////////////////////////////////////////////////////////////

#ifndef MATH_H
#define MATH_H

    // Library
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include "Vector.h"

    /////////////////////////////////////////////////////////
    /// Calculate Pi
    /////////////////////////////////////////////////////////
    float Pi();


    ////////////////////////////////////////////////////////////
    /// Calculate Pi * 2
    ////////////////////////////////////////////////////////////
    float TwoPi();

    float frand( float x );

    float Math_CalculateMass( const Vector *A, int Anum, float density );


#endif
