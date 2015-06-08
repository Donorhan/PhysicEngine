////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Event.h"


////////////////////////////////////////////////////////////
///
/// Getion des évènements
///
////////////////////////////////////////////////////////////
void Event_Get( SDL_Event *event, int *play )
{
    static int down = 0;
    static int type = 0;  ///< Indique si l'objet à ajouter est de type fixe.
    int object      = 0;
    static int downX = 0;
    static int downY = 0;

    while ( SDL_PollEvent( event ) )
    {
        switch( event->type )
        {
            case SDL_QUIT:
                *play = 0;
                break;
            case SDL_MOUSEBUTTONUP:
                // Drag and drop
                if( downX != event->motion.x || downY != HAUTEUR_ECRAN - event->motion.y )
                {
                    nbObjects++;
                    objects = realloc( objects, sizeof( Object ) * nbObjects );

                    Object_Create( &objects[nbObjects - 1], CERCLE );
                    objects[nbObjects - 1].position.x = event->motion.x;
                    objects[nbObjects - 1].position.y = HAUTEUR_ECRAN - event->motion.y;
                    objects[nbObjects - 1].velocity.x      = (event->motion.x - downX ) / 30.0f;
                    objects[nbObjects - 1].velocity.y      = (event->motion.y - downY ) / 40.0f;
                }
                // Ajout
                else
                {
                    if ( event->button.button == SDL_BUTTON_RIGHT )
                    {
                        type = 1;
                        down = 0;
                    }
                    else if ( event->button.button == SDL_BUTTON_LEFT)
                    {
                        down = 1;
                        type = 0;
                    }
                    else if ( event->button.button == SDL_BUTTON_WHEELUP )
                    {
                        itemToAdd--;

                        if( itemToAdd <= 0 )
                            itemToAdd = 3;
                    }
                    else if ( event->button.button == SDL_BUTTON_WHEELDOWN )
                    {
                        itemToAdd++;

                        if( itemToAdd >= 3 )
                            itemToAdd = 1;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if ( event->button.button == SDL_BUTTON_RIGHT )
                    {
                        type = 1;
                        down = 1;
                    }

                    downX = event->motion.x;
                    downY = HAUTEUR_ECRAN - event->motion.y;
                    break;
                }

            case SDL_KEYDOWN:
                switch ( event->key.keysym.sym )
                {
                    case SDLK_ESCAPE:
                        drawMain = !drawMain;
                        break;
                    case SDLK_q:
                        Core_CreateScene( 1 );
                        break;
                    case SDLK_w:
                        Core_CreateScene( 2 );
                        break;
                    case SDLK_e:
                        Core_CreateScene( 3 );
                        break;
                    case SDLK_r:
                        Core_CreateScene( 4 );
                        break;
                    case SDLK_t:
                        Core_CreateScene( 5 );
                        break;
                    case SDLK_c:
                        noCollision = (noCollision == 1 ) ? 0 : 1;
                        break;
                    case SDLK_g:
                        etatGravity = !etatGravity;
                        break;
                    case SDLK_x:
                        itemToAdd = 2;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }

    // Ajout d'un objet dans la scène
    if ( down )
    {
        switch( itemToAdd )
        {
            case 1:
                object = BOITE;
                break;
            case 2:
                object = CERCLE;
                break;
            default:
                object = BOITE;
                break;
        }

        nbObjects++;
        objects = realloc( objects, sizeof( Object ) * nbObjects );

        Object_Create( &objects[nbObjects - 1], object );
        objects[nbObjects - 1].position.x = event->motion.x;
        objects[nbObjects - 1].position.y = HAUTEUR_ECRAN - event->motion.y;
        objects[nbObjects - 1].fixed      = type;

        down = 0;
    }
}

