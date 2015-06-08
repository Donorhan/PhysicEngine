////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Finder.h"


////////////////////////////////////////////////////////////
///
/// Recherche d'un contact entre les objets
///
////////////////////////////////////////////////////////////
int Finder_Find( int idObjetA, int idObjetB, Vector *pDirection, float *pForce )
{
    /// Verification ( Si les deux objets sont de type fixe inutile de tester la collision )
    if ( objects[idObjetA].fixed && objects[idObjetB].fixed )
        return 0;

    /// Variables
    int nbVerticesA     = objects[idObjetA].nbVertices;
    int nbVerticesB     = objects[idObjetB].nbVertices;
    Vector diffPosition;
    diffPosition.x      = objects[idObjetA].position.x - objects[idObjetB].position.x;
    diffPosition.y      = objects[idObjetA].position.y - objects[idObjetB].position.y;
    Vector diffVelocity;
    diffVelocity.x      = objects[idObjetA].velocity.x - objects[idObjetB].velocity.x;
    diffVelocity.y      = objects[idObjetA].velocity.y - objects[idObjetB].velocity.y;

    /// Variables utiles
    Vector axis[64];
    float  forces[64];
    float tempVelocity;
    Vector vertice0;
    Vector vertice1;
    Vector verticeF;  // Différence entre les deux sommets.
    int    nbAxis = 0;
    int    i      = 0;
    int    j      = 0;

    // Si les deux objets sont en mouvement on recherche tout de suite une éventuelle collision en les projetant sur un axe
    axis[nbAxis].x = -diffVelocity.y;
    axis[nbAxis].y =  diffVelocity.x;
    tempVelocity   = Vector_Multiply( &diffVelocity, &diffVelocity );
	if ( tempVelocity > 0.00001f )
	{
        if ( !Finder_LookInterval( idObjetA, idObjetB, &axis[nbAxis], &forces[nbAxis], &diffPosition, &diffVelocity, pForce ) )
            return 0;

		nbAxis++;
	}

    /// Recherche des axes du polygone A.
	for( j = nbVerticesA - 1, i = 0; i < nbVerticesA; j = i, i++ )
	{
	    // Récupération des coordonnées
		vertice0.x  = objects[idObjetA].vertices[j].x;
		vertice0.y  = objects[idObjetA].vertices[j].y;
		vertice1.x  = objects[idObjetA].vertices[i].x;
		vertice1.y  = objects[idObjetA].vertices[i].y;
		verticeF.x  = vertice1.x - vertice0.x;
		verticeF.y  = vertice1.y - vertice0.y;

		// Création de l'axe séparateur
		axis[nbAxis].x = -verticeF.y;
		axis[nbAxis].y =  verticeF.x;

		if ( !Finder_LookInterval( idObjetA, idObjetB, &axis[nbAxis], &forces[nbAxis], &diffPosition, &diffVelocity, pForce ) )
            return 0;

		nbAxis++;
	}

    /// Recherche des axes du polygone B.
	for( j = nbVerticesB - 1, i = 0; i < nbVerticesB; j = i, i++ )
	{
	    // Récupération des coordonnées
		vertice0.x  = objects[idObjetB].vertices[j].x;
		vertice0.y  = objects[idObjetB].vertices[j].y;
		vertice1.x  = objects[idObjetB].vertices[i].x;
		vertice1.y  = objects[idObjetB].vertices[i].y;
		verticeF.x  = vertice1.x - vertice0.x;
		verticeF.y  = vertice1.y - vertice0.y;

		// Création de l'axe séparateur
		axis[nbAxis].x = -verticeF.y;
		axis[nbAxis].y =  verticeF.x;

		if ( !Finder_LookInterval( idObjetB, idObjetA, &axis[nbAxis], &forces[nbAxis], &diffPosition, &diffVelocity, pForce ) )
            return 0;

		nbAxis++;
	}

	/// Recherche de la direction de la projection et sa force
	if ( !FindMTD( axis, forces, nbAxis, pDirection, pForce ) )
        return 0;

    /// Verifie que les deux polygones sont bien séparés
    if ( Vector_Multiply( pDirection, &diffPosition ) < 0.0f )
    {
        pDirection->x = -pDirection->x;
        pDirection->y = -pDirection->y;
    }

    return 1;
}


////////////////////////////////////////////////////////////
///
/// Verifie qu'il n'y a pas de collision entre les deux polygones
///
////////////////////////////////////////////////////////////
int Finder_LookInterval( int idObjectA, int idObjectB, Vector *axeSeparateur, float *force, Vector *diffPosition, Vector *diffVelocity, float *pForce )
{
    /// Variables
    float h         = 0.0f;
	float minA      = 0.0f;
	float maxA      = 0.0f;
	float minB      = 0.0f;
	float maxB      = 0.0f;
	float distance0 = 0.0f;
	float distance1 = 0.0f;
	float velocity  = 0.0f;
	float time0     = 0.0f;
	float time1     = 0.0f;
	float temp      = 0.0f;

    // Projection des sommets sur l'axe
	Finder_GetProjection( idObjectA, axeSeparateur, &minA, &maxA );
	Finder_GetProjection( idObjectB, axeSeparateur, &minB, &maxB );

    // Calcul de la difference entre les deux polygones sur l'axe
	h = ( diffPosition->x * axeSeparateur->x ) + ( diffPosition->y * axeSeparateur->y );

	minA += h;
	maxA += h;

	distance0 = minA - maxB;
	distance1 = minB - maxA;

	if ( distance0 > 0.0f || distance1 > 0.0f )
	{
	    // Recherche par rapport a la vitesse de l'objet la futur distance du polygone.
		velocity = Vector_Multiply( diffVelocity, axeSeparateur );

		// Vitesse faible ? Inutile de continuer
		if ( fabs( velocity ) < 0.0000001f )
			return 0;

        // Calcul du moment de l'impact
		time0 = -distance0 / velocity;
		time1 =  distance1 / velocity;

		if ( time0 > time1 )
		{
		    temp  = time0;
		    time0 = time1;
		    time1 = temp;
        }

		*force  = ( time0 > 0.0f ) ? time0 : time1;

		if ( *force < 0.0f || *force > *pForce )
			return 0;

		return 1;
	}
	else
	{
	    // Récupère la force la plus importante
		*force = ( distance0 > distance1 )? distance0 : distance1;

		return 1;
	}
}



////////////////////////////////////////////////////////////
///
/// Projection des sommets sur l'axe
///
////////////////////////////////////////////////////////////
void Finder_GetProjection( int idObject, Vector *axeSeparateur, float *min, float *max )
{
    /// Variables
    int   i = 0;
    float d = 0.0f;

    /// Calculs
	*min = ( objects[idObject].vertices[0].x * axeSeparateur->x ) + ( objects[idObject].vertices[0].y * axeSeparateur->y );
	*max = *min;

	/// Projection
	for ( i = 1; i < objects[idObject].nbVertices; i++ )
	{
		d = ( objects[idObject].vertices[i].x * axeSeparateur->x ) + ( objects[idObject].vertices[i].y * axeSeparateur->y );

		if (d < *min)         *min = d;
        else if (d > *max)    *max = d;
	}
}


////////////////////////////////////////////////////////////
///
/// Calculs de la direction et de la force de projection
///
////////////////////////////////////////////////////////////
int FindMTD( Vector axes[], float forces[], int nbAxes, Vector *direction, float *force )
{
	int mini = -1;
	int i    = 0;
	float n  = 0.0f;

	*force       = 0.0f;
	direction->x = 0.0f;
	direction->y = 0.0f;


    // Recherche d'une collision
	for( i = 0; i < nbAxes; i++ )
	{
		if ( forces[i] > 0 )
		{
			if ( forces[i] > *force )
			{
				mini         = i;
				*force       = forces[i];
                direction->x = axes[i].x;
                direction->y = axes[i].y;
                Vector_Normalise( direction );
			}
		}
	}

	// Trouvé ?
	if ( mini != -1 )
		return 1;

	// Recherche d'un "chevauchement" entre les polygones
	for ( i = 0; i < nbAxes; i++ )
	{
		n          = Vector_Normalise( &axes[i] );
		forces[i] /= n;

		if ( forces[i] > *force || mini == -1 )
		{
			mini         = i;
			*force       = forces[i];
			direction->x = axes[i].x;
			direction->y = axes[i].y;
		}
	}

	if ( mini == -1 )
		printf("Error\n");

	return ( mini != -1 );
}
