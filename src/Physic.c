////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Physic.h"


////////////////////////////////////////////////////////////
///
/// Coeur des collisions
///
////////////////////////////////////////////////////////////
void Physic_Run( float framerate )
{
    int    i         = 0;
    int    j         = 0;
    int    collision = 0;
    float  force     = 0.0f;
    Vector direction;


    // Gravité
    if( etatGravity )
        for ( i = 0; i < nbObjects; i++ )
            objects[i].velocity.y -= gravity;

    // Parcours les objets de la scène
    for ( i = 0; i < nbObjects; i++ )
    {
        for ( j = i + 1; j < nbObjects; j++ )
        {
            // Initialisation des variables
            collision   = 0;
            direction.x = 0.0f;
            direction.y = 0.0f;
            force       = 1.0f;

            // Recherche si les deux polygones sont en contacts
            collision = Finder_Find( i, j, &direction, &force );

            // Si il y a une collision on sépare les objets
            if ( collision )
            {
                if( noCollision )
                    if( currentScene == 5 && ( i > 3 && j > 3 ) )
                        continue;

                if ( force < 0.0f )
                {
                    direction.x *= -force;
                    direction.y *= -force;
                    Solver_Separate( i, j, &direction );
                }
                else
                    Solver_ApplyForces( i, j, &direction, &force );

                continue;
            }
        }
    }

     // Mise à jour des objets
    for ( i = 0; i < nbObjects; i++ )
    {
        if ( objects[i].fixed )
        {
            objects[i].velocity.x = 0.0f;
            objects[i].velocity.y = 0.0f;
            continue;
        }

        objects[i].position.x += objects[i].velocity.x;
        objects[i].position.y += objects[i].velocity.y;
	}
}
