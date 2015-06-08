////////////////////////////////////////////////////////////
//
// PTI : Collision detection
// Copyright (C) 2009 Orhan Donovan ( dorhan@nantes.epsi.fr )
//
// - Author : Orhan Donovan.
// - Create : 26/09/2009.
// - Desc.  : Gestion des collisions
//
////////////////////////////////////////////////////////////

#ifndef PHYSIC_H
#define PHYSIC_H

    // Library
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include "Math.h"
    #include "Define.h"
    #include "Vector.h"
    #include "Object.h"
    #include "Physic/Finder.h"
    #include "Physic/Solver.h"

    extern int   nbObjects;
    extern int   etatGravity;
    extern int   currentScene;
    extern float gravity;
    extern int   noCollision;
    extern Object *objects;

    ////////////////////////////
    /// Coeur des collisions
    ////////////////////////////
    void Physic_Run( float framerate );


#endif


