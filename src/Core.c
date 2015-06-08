////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Core.h"

////////////////////////////////////////////////////////////
/// Variables globales
////////////////////////////////////////////////////////////
float   gravity      = 0.05f; // Gravité de la scene
float   objectSize   = 45.0f;
int     etatGravity  = 1;
int     noCollision  = 0;     // Active où non les collisions
int     itemToAdd    = 1;     // BOITE
int     drawMain     = 0;
int     nbObjects    = 0;
int     currentScene = 5;
Object *objects      = NULL;



////////////////////////////////////////////////////////////
///
/// Boucle principale
///
////////////////////////////////////////////////////////////
void Core_Run()
{
    int play            = 1;      ///< Stop ou lance l'application.
    float framerate     = 0.0f;   ///< Temps entre deux tours de boucle.
    SDL_Surface *screen = NULL;   ///< La fenêtre
    SDL_Event    event;           ///< Récupération des évènements utilisateur.


    ///< Initialisation de la scène
    Graphic_Init( screen );
    Core_CreateScene( 5 );

    ///< Boucle principale
    while ( play )
    {
        // Gestion du temps
        framerate = Core_SetTime();

        // Recherche des évènements
        Event_Get( &event, &play );

        // Gestion des collisions
        Physic_Run( framerate );

        // Affichage de l'interface
        Graphic_Draw();
    }

    Core_CleanScene();
    SDL_FreeSurface( screen );
    SDL_Quit();
}


////////////////////////////////////////////////////////////
///
/// Création de la scène
///
////////////////////////////////////////////////////////////
void Core_CreateScene( int scene )
{
    int i = 0;
    currentScene = scene;

    Core_CleanScene();
    switch( scene )
    {
         case 1:
            objectSize = 45.0f;
            ///< Scène par defaut
            nbObjects = 4;
            objects = realloc( objects, sizeof( Object ) * nbObjects );

            ///< Création de la forme de l'objet ( bords de la scene )
            for ( i = 0; i < nbObjects; i++ )
            {
                Object_Create( &objects[i], BOITE );

                if( i % 2 )
                    Object_CreateBox( &objects[i], 50, HAUTEUR_ECRAN - 50 );
                else
                    Object_CreateBox( &objects[i], LARGEUR_ECRAN, 50 );

                objects[i].fixed = 1;
            }

            ///< Mise en place des éléments à la bonne position
            // Bord haut
            objects[0].position.x = LARGEUR_ECRAN / 2;
            objects[0].position.y = HAUTEUR_ECRAN;

            // Bord gauche
            objects[1].position.x = 0;
            objects[1].position.y = HAUTEUR_ECRAN / 2;

            // Bord droit
            objects[2].position.x = LARGEUR_ECRAN / 2;
            objects[2].position.y = 0;

            // Bord droit
            objects[3].position.x = LARGEUR_ECRAN;
            objects[3].position.y = HAUTEUR_ECRAN / 2;
            break;
        case 2:
            objectSize = 45.0f;
            ///< Scène par defaut
            nbObjects = 4;
            objects = realloc( objects, sizeof( Object ) * nbObjects );

            ///< Création de la forme de l'objet ( bords de la scene )
            for ( i = 0; i < nbObjects; i++ )
            {
                Object_Create( &objects[i], BOITE );

                if( i % 2 )
                    Object_CreateBox( &objects[i], 50, HAUTEUR_ECRAN - 50 );
                else
                    Object_CreateBox( &objects[i], LARGEUR_ECRAN, 50 );

                objects[i].fixed = 1;
            }

            ///< Mise en place des éléments à la bonne position
            // Bord haut
            objects[0].position.x = LARGEUR_ECRAN / 2;
            objects[0].position.y = HAUTEUR_ECRAN;

            // Bord gauche
            objects[1].position.x = 0;
            objects[1].position.y = HAUTEUR_ECRAN / 2;

            // Bord droit
            objects[2].position.x = LARGEUR_ECRAN / 2;
            objects[2].position.y = 0;

            // Bord droit
            objects[3].position.x = LARGEUR_ECRAN;
            objects[3].position.y = HAUTEUR_ECRAN / 2;
            break;
        case 3:
            objectSize = 65.0f;
            ///< Scène par defaut
            nbObjects = 6;
            objects = realloc( objects, sizeof( Object ) * nbObjects );

            ///< Création de la forme de l'objet ( bords de la scene )
            for ( i = 0; i < nbObjects; i++ )
            {
                Object_Create( &objects[i], BOITE );

                if( i % 2 )
                    Object_CreateBox( &objects[i], 50, HAUTEUR_ECRAN - 50 );
                else
                    Object_CreateBox( &objects[i], LARGEUR_ECRAN, 50 );

                objects[i].fixed = 1;
            }

            ///< Mise en place des éléments à la bonne position
            // Bord haut
            objects[0].position.x = LARGEUR_ECRAN / 2;
            objects[0].position.y = HAUTEUR_ECRAN;

            // Bord gauche
            objects[1].position.x = 0;
            objects[1].position.y = HAUTEUR_ECRAN / 2;

            // Bord droit
            objects[2].position.x = LARGEUR_ECRAN / 2;
            objects[2].position.y = 0;

            // Bord droit
            objects[3].position.x = LARGEUR_ECRAN;
            objects[3].position.y = HAUTEUR_ECRAN / 2;

            // Ballon 1
            Object_Create( &objects[4], CERCLE );
            objects[4].position.x = 50;
            objects[4].position.y = HAUTEUR_ECRAN / 2;
            objects[4].velocity.x = 3.0f;
            objects[4].velocity.y = 0.0f;
            objects[4].fixed      = 0;


            // Ballon 1
            Object_Create( &objects[5], CERCLE );
            objects[5].position.x = LARGEUR_ECRAN - 50;
            objects[5].position.y = HAUTEUR_ECRAN / 2 - 80;
            objects[5].velocity.x = -3.0f;
            objects[5].velocity.y = 0.0f;
            objects[5].fixed      = 0;
            break;
        case 4:
            etatGravity = 0;
            objectSize = 25.0f;
            ///< Scène par defaut
            nbObjects = 15;
            objects = realloc( objects, sizeof( Object ) * nbObjects );

            ///< Création de la forme de l'objet ( bords de la scene )
            for ( i = 0; i < nbObjects; i++ )
            {
                Object_Create( &objects[i], BOITE );

                if( i % 2 )
                    Object_CreateBox( &objects[i], 50, HAUTEUR_ECRAN - 50 );
                else
                    Object_CreateBox( &objects[i], LARGEUR_ECRAN, 50 );

                objects[i].fixed = 1;
            }

            ///< Mise en place des éléments à la bonne position
            // Bord haut
            objects[0].position.x = LARGEUR_ECRAN / 2;
            objects[0].position.y = HAUTEUR_ECRAN;

            // Bord gauche
            objects[1].position.x = 0;
            objects[1].position.y = HAUTEUR_ECRAN / 2;

            // Bord droit
            objects[2].position.x = LARGEUR_ECRAN / 2;
            objects[2].position.y = 0;

            // Bord droit
            objects[3].position.x = LARGEUR_ECRAN;
            objects[3].position.y = HAUTEUR_ECRAN / 2;

            // Ballon 1
            Object_Create( &objects[4], CERCLE );
            objects[4].position.x = 300;
            objects[4].position.y = HAUTEUR_ECRAN / 2;
            objects[4].fixed      = 0;

            // Ballon 2
            Object_Create( &objects[5], CERCLE );
            objects[5].position.x = 250;
            objects[5].position.y = HAUTEUR_ECRAN / 2 - 30;
            objects[5].fixed      = 0;

            Object_Create( &objects[6], CERCLE );
            objects[6].position.x = 250;
            objects[6].position.y = HAUTEUR_ECRAN / 2 + 30;
            objects[6].fixed      = 0;

            Object_Create( &objects[7], CERCLE );
            objects[7].position.x = 200;
            objects[7].position.y = HAUTEUR_ECRAN / 2;
            objects[7].fixed      = 0;

            Object_Create( &objects[8], CERCLE );
            objects[8].position.x = 200;
            objects[8].position.y = HAUTEUR_ECRAN / 2 - 60;
            objects[8].fixed      = 0;

            Object_Create( &objects[9], CERCLE );
            objects[9].position.x = 200;
            objects[9].position.y = HAUTEUR_ECRAN / 2 + 60;
            objects[9].fixed      = 0;

            // Ligne 3
            Object_Create( &objects[10], CERCLE );
            objects[10].position.x = 150;
            objects[10].position.y = HAUTEUR_ECRAN / 2 + 30;
            objects[10].fixed      = 0;

            Object_Create( &objects[11], CERCLE );
            objects[11].position.x = 150;
            objects[11].position.y = HAUTEUR_ECRAN / 2 + 90;
            objects[11].fixed      = 0;

            Object_Create( &objects[12], CERCLE );
            objects[12].position.x = 150;
            objects[12].position.y = HAUTEUR_ECRAN / 2 - 30;
            objects[12].fixed      = 0;

            Object_Create( &objects[13], CERCLE );
            objects[13].position.x = 150;
            objects[13].position.y = HAUTEUR_ECRAN / 2 - 90;
            objects[13].fixed      = 0;

            Object_Create( &objects[14], CERCLE );
            objects[14].position.x = LARGEUR_ECRAN - 50;
            objects[14].position.y = HAUTEUR_ECRAN / 2;
            objects[14].velocity.x = -12.0f;

            break;
        case 5 :
            objectSize = 45.0f;

            ///< Scène par defaut
            nbObjects = 10;
            objects = realloc( objects, sizeof( Object ) * nbObjects );

            ///< Création de la forme de l'objet ( bords de la scene )
            for ( i = 0; i < nbObjects; i++ )
            {
                Object_Create( &objects[i], BOITE );

                if( i % 2 )
                    Object_CreateBox( &objects[i], 50, HAUTEUR_ECRAN - 50 );
                else
                    Object_CreateBox( &objects[i], LARGEUR_ECRAN, 50 );

                objects[i].fixed = 1;
            }

            ///< Mise en place des éléments à la bonne position
            // Bord haut
            objects[0].position.x = LARGEUR_ECRAN / 2;
            objects[0].position.y = HAUTEUR_ECRAN;

            // Bord gauche
            objects[1].position.x = 0;
            objects[1].position.y = HAUTEUR_ECRAN / 2;

            // Bord droit
            objects[2].position.x = LARGEUR_ECRAN / 2;
            objects[2].position.y = 0;

            // Bord droit
            objects[3].position.x = LARGEUR_ECRAN;
            objects[3].position.y = HAUTEUR_ECRAN / 2;

            // Les boites par defaut
            Object_CreateBox( &objects[4], 50, 50 );
            objects[4].position.x = LARGEUR_ECRAN - 100;
            objects[4].position.y = 51;
            objects[4].fixed = 0;

            Object_CreateBox( &objects[5], 50, 50 );
            objects[5].position.x = LARGEUR_ECRAN - 160;
            objects[5].position.y = 51;
            objects[5].fixed = 0;

            Object_CreateBox( &objects[6], 50, 50 );
            objects[6].position.x = LARGEUR_ECRAN - 130;
            objects[6].position.y = 110;
            objects[6].fixed = 0;

            Object_CreateBox( &objects[7], 50, 50 );
            objects[7].position.x = LARGEUR_ECRAN - 220;
            objects[7].position.y = 51;
            objects[7].fixed = 0;

            Object_CreateBox( &objects[8], 50, 50 );
            objects[8].position.x = LARGEUR_ECRAN - 190;
            objects[8].position.y = 110;
            objects[8].fixed = 0;

            Object_CreateBox( &objects[9], 50, 50 );
            objects[9].position.x = LARGEUR_ECRAN - 160;
            objects[9].position.y = 170;
            objects[9].fixed = 0;


            break;
        default:
            break;
    }
}



////////////////////////////////////////////////////////////
///
/// Création de la scène
///
////////////////////////////////////////////////////////////
float Core_SetTime()
{
    static float lastTime  = 0.0f;
    float        framerate = ( SDL_GetTicks() - lastTime );

    if ( framerate > 30 )
        lastTime = SDL_GetTicks();
    else
        SDL_Delay( 30 - framerate );

    return ( framerate / 100.0f );
}


////////////////////////////////////////////////////////////
///
/// Nettoie la scene
///
////////////////////////////////////////////////////////////
void Core_CleanScene()
{
    int i = 0;

    ///< Libération mémoire
    for ( i = 0; i < nbObjects; i++ )
        Object_Delete( &objects[i] );

    free( objects );
    objects   = NULL;

    nbObjects = 0;
}

