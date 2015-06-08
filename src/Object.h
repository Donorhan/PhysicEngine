////////////////////////////////////////////////////////////
//
// PTI : Collision detection
// Copyright (C) 2009 Orhan Donovan ( dorhan@nantes.epsi.fr )
//
// - Author : Orhan Donovan.
// - Create : 26/09/2009.
// - Desc.  : Objets du jeu
//
////////////////////////////////////////////////////////////

#ifndef OBJECTS_H
#define OBJECTS_H

    // Library
    #include <stdio.h>
    #include <stdlib.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <math.h>
    #include "Math.h"
    #include "Define.h"
    #include "Vector.h"

    extern float objectSize;

    typedef struct
    {
        Vector position;
        Vector velocity;

        int nbVertices;
        Vector *vertices;

        int   fixed;
        float mass;
        float invMass;

    } Object;


    ////////////////////////////
    /// Création d'un objet
    ////////////////////////////
    void Object_Create( Object *object, int type );

    ////////////////////////////
    /// Création de la forme
    ////////////////////////////
    void Object_CreateShape( Object *object, float angle );

    ////////////////////////////
    /// Création d'une boite
    ////////////////////////////
    void Object_CreateBox( Object *object, int width, int height );

    ////////////////////////////
    /// Calcul le poids & co
    ///////////////////////////
    void Object_CalculateWeight( Object *object );

    ////////////////////////////
    /// Suppression d'un objet
    ////////////////////////////
    void Object_Delete( Object *object );

#endif

