////////////////////////////////////////////////////////////
//
// PTI : Collision detection
// Copyright (C) 2009 Orhan Donovan ( dorhan@nantes.epsi.fr )
//
// - Author : Orhan Donovan.
// - Create : 10/09/2009.
// - Desc.  : Gestion de l'affichage
//
////////////////////////////////////////////////////////////

#ifndef GRAPHIC_H
#define GRAPHIC_H

    // Library
    #include <stdio.h>
    #include <stdlib.h>
    #include <SDL/SDL.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include "Define.h"
    #include "Object.h"
    #include "Others/sdlglutils.h"

    extern int itemToAdd;
    extern int  nbObjects;
    extern int drawMain;
    extern Object *objects;

    //////////////////////////////////
    /// Récupère les évènements du joueur
    //////////////////////////////////
    void Graphic_Init( SDL_Surface *screen );

    //////////////////////////////////
    /// Dessine la scene
    //////////////////////////////////
    void Graphic_Draw();

    //////////////////////////////////
    /// Dessine le menu avec les différents éléments
    //////////////////////////////////
    void Graphic_DrawMain();

#endif


