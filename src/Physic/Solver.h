////////////////////////////////////////////////////////////
//
// PTI : Collision detection
// Copyright (C) 2009 Orhan Donovan ( dorhan@nantes.epsi.fr )
//
// - Author : Orhan Donovan.
// - Create : 10/10/2009.
// - Desc.  : Réponse à une collision
//
////////////////////////////////////////////////////////////

#ifndef SOLVER_H
#define SOLVER_H

    // Library
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include "Math.h"
    #include "../Vector.h"
    #include "../Object.h"

    extern int  nbObjects;
    extern Object *objects;

    ///////////////////////////////
    /// Separe les objets
    ///////////////////////////////
    void Solver_ApplyForces( int idA, int idB, Vector *direction, float *force );

    ///////////////////////////////
    /// Rend les forces aux polygons
    ///////////////////////////////
    void Solver_Separate( int idA, int idB, Vector *direction );

#endif

