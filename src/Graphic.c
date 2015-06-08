////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Graphic.h"


// Deux textures pour le moment
GLuint textures[3];


////////////////////////////////////////////////////////////
///
/// Getion des évènements
///
////////////////////////////////////////////////////////////
void Graphic_Init( SDL_Surface *screen )
{
    // Create the window
    SDL_Init( SDL_INIT_VIDEO );

    screen = SDL_SetVideoMode( LARGEUR_ECRAN, HAUTEUR_ECRAN, PROFONDEUR_ECRAN, SDL_OPENGL );
    SDL_WM_SetCaption( TITRE_PROGRAMME, NULL);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluOrtho2D( 0, LARGEUR_ECRAN, 0, HAUTEUR_ECRAN );
    glEnable(GL_TEXTURE_2D);

    textures[0] = loadTexture("../data/boite.jpg", 1);
    textures[1] = loadTexture("../data/boite_fixe.jpg", 1);
}


////////////////////////////////////////////////////////////
///
/// Getion des évènements
///
////////////////////////////////////////////////////////////
void Graphic_Draw()
{
    int i = 0;
    int j = 0;

    // Efface l'écran et reinitialise la matrix de projection
    glClear( GL_COLOR_BUFFER_BIT );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    // Dessine les éléments
    for ( i = 0; i < nbObjects; i++ )
    {
        // Forme
        glPushMatrix();

            if( objects[i].nbVertices != 4 )
            {
                glColor4ub( 255,   255, 255, 255 );
                glTranslated( objects[i].position.x, objects[i].position.y, 0);
                glBindTexture( GL_TEXTURE_2D, textures[0] );

                if ( objects[i].fixed )     glColor4ub(   255, 128, 128, 255 );
                else                        glColor4ub(   0, 0, 255, 255 );

                glBegin(GL_TRIANGLE_FAN);

                for ( j = 0; j < objects[i].nbVertices; j++ )
                {
                    glTexCoord2f( objects[i].vertices[j].x, objects[i].vertices[j].y );
                    glVertex2f( objects[i].vertices[j].x, objects[i].vertices[j].y );
                }

                glTexCoord2f( objects[i].vertices[0].x, objects[i].vertices[0].y );
                glVertex2f( objects[i].vertices[0].x, objects[i].vertices[0].y );

                   glEnd();
            }
            else
            {
                glColor4ub( 255,   255, 255, 255 );
                glTranslated( objects[i].position.x, objects[i].position.y, 0);

                if( !objects[i].fixed )
                    glBindTexture( GL_TEXTURE_2D, textures[0] );
                else
                    glBindTexture( GL_TEXTURE_2D, textures[1] );

                glBegin(GL_QUADS);

                    glTexCoord2i( 0, 0 );     glVertex2f( objects[i].vertices[0].x, objects[i].vertices[0].y );
                    glTexCoord2i( 1, 0 );     glVertex2f( objects[i].vertices[1].x, objects[i].vertices[1].y );
                    glTexCoord2i( 1, 1 );     glVertex2f( objects[i].vertices[2].x, objects[i].vertices[2].y );
                    glTexCoord2i( 0, 1 );     glVertex2f( objects[i].vertices[3].x, objects[i].vertices[3].y );

                glEnd();
            }

        glPopMatrix();

        if ( objects[i].nbVertices > 5 )
        {
            // Contour
            glPushMatrix();
                glTranslated( objects[i].position.x, objects[i].position.y, 0);
                glBegin(GL_LINE_LOOP);

                if ( objects[i].fixed )     glColor4ub(   255,   0, 0, 255 );
                else                        glColor4ub(     0, 255, 0, 255 );

                for ( j = 0; j < objects[i].nbVertices; j++ )
                    glVertex2f( objects[i].vertices[j].x, objects[i].vertices[j].y );

                glVertex2f( objects[i].vertices[0].x, objects[i].vertices[0].y );

                glEnd();
            glPopMatrix();
        }
    }

    // Dessine le menu en bas a droite
    Graphic_DrawMain();

    // Met à jour l'écran
    glFlush();
    SDL_GL_SwapBuffers();
}



////////////////////////////////////////////////////////////
///
/// Dessine le menu en bas a droite
///
////////////////////////////////////////////////////////////
void Graphic_DrawMain()
{
    if( drawMain )
    {
        // Cadre
        glPushMatrix();
            glEnable(GL_BLEND) ;
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glTranslated( LARGEUR_ECRAN - 125, HAUTEUR_ECRAN - 75, 0);
            glColor4ub( 255, 255, 255, 230 );
            glBegin(GL_TRIANGLE_FAN);

                glVertex2f( -100, -50 );
                glVertex2f(  100, -50 );
                glVertex2f(  100,  50 );
                glVertex2f( -100,  50 );

            glEnd();
            glDisable(GL_BLEND);
        glPopMatrix();

        // Affiche l'objet actuel dans le cadre
        glPushMatrix();
            glTranslated( LARGEUR_ECRAN - 200, HAUTEUR_ECRAN - 50, 0);
            glColor4ub(   0, 102, 0, 255 );
            glBegin(GL_TRIANGLE_FAN);
            switch( itemToAdd )
            {
                case 1:
                    glVertex2f( -15, -15 );
                    glVertex2f(  15, -15 );
                    glVertex2f(  15,  15 );
                    glVertex2f( -15,  15 );
                    break;
                case 2:
                    glVertex2f( 16.454483, 9.500000);
                    glVertex2f( 12.212964, 14.554845);
                    glVertex2f( 6.498381, 17.854160);
                    glVertex2f( -0.000003, 19.000000);
                    glVertex2f( -6.498386, 17.854158);
                    glVertex2f( -12.212969, 14.554841);
                    glVertex2f( -16.454485, 9.499997);
                    glVertex2f( -18.711348, 3.299313);
                    glVertex2f( -18.711348, -3.299316);
                    glVertex2f( -16.454483, -9.500000);
                    glVertex2f( -12.212962, -14.554846);
                    glVertex2f( -6.498381, -17.854160);
                    glVertex2f( 0.000000, -19.000000);
                    glVertex2f( 6.498382, -17.854160);
                    glVertex2f( 12.212963, -14.554846);
                    glVertex2f( 16.454481, -9.500003);
                    glVertex2f( 18.711346, -3.299320);
                    glVertex2f( 18.711348, 3.299309);
                    break;
                default:
                    glVertex2f( -15, -15 );
                    glVertex2f(  15, -15 );
                    glVertex2f(  15,  15 );
                    glVertex2f( -15,  15 );
                    break;
            }

            glEnd();
        glPopMatrix();
    }
}
