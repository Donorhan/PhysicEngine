////////////////////////////////////////////////////////////
//
// PTI : Collision detection
// Copyright (C) 2009 Orhan Donovan ( dorhan@nantes.epsi.fr )
//
// - Author : Orhan Donovan.
// - Create : 10/10/2009.
// - Desc.  : Recherche de collisions
//
////////////////////////////////////////////////////////////

#ifndef FINDER_H
#define FINDER_H

    // Library
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include "Math.h"
    #include "../Vector.h"
    #include "../Object.h"

    extern int  nbObjects;
    extern Object *objects;

    ////////////////////////////
    /// Coeur des collisions
    ////////////////////////////
    int Finder_Find( int idObjetA, int idObjetB, Vector *pDirection, float *pForce );

    ////////////////////////////
    /// Regarde l'interval
    ////////////////////////////
    int Finder_LookInterval( int idObjectA, int idObjectB, Vector *axeSeparateur, float *force, Vector *diffPosition, Vector *diffVelocity, float *pForce );

    ////////////////////////////
    /// Projection des sommets sur l'axe
    ////////////////////////////
    void Finder_GetProjection( int idObject, Vector *axeSeparateur, float *min, float *max );

    ////////////////////////////
    /// Recherche de la direction dans laquelle pousser le polygon
    ////////////////////////////
    int FindMTD( Vector axes[], float forces[], int nbAxes, Vector *direction, float *force );

#endif


