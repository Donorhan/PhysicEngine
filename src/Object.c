////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Object.h"


////////////////////////////////////////////////////////////
///
/// Création d'un objet
///
////////////////////////////////////////////////////////////
void Object_Create( Object *object, int type )
{
    // Initialisation
    object->position.x = LARGEUR_ECRAN / 2;
    object->position.y = HAUTEUR_ECRAN / 2;
    object->velocity.x = 0;
    object->velocity.y = 0;
    object->nbVertices = type;
    object->fixed      = 0;
    object->mass       = 0.0f;
    object->invMass    = 0.0f;

    // Création
    object->vertices = malloc( sizeof( Vector ) * object->nbVertices );

    // Création de la forme
    Object_CreateShape( object, objectSize );

    // Calculs du poids et autres
    Object_CalculateWeight( object );

    object->invMass = ( object->mass > 0.0000001f)? 1.0f / object->mass : 0.0f;
}


////////////////////////////////////////////////////////////
///
/// Création de la forme
///
////////////////////////////////////////////////////////////
void Object_CreateShape( Object *object, float angle )
{
    int   i = 0;
	float a  = Pi()    / object->nbVertices;
	float da = TwoPi() / object->nbVertices;

	for( i = 0; i < object->nbVertices; i ++)
	{
		a += da;

        object->vertices[i].x = cos(a) * angle;
		object->vertices[i].y = sin(a) * angle;
	}
}


////////////////////////////////////////////////////////////
///
/// Création d'une boite ( et rectangle )
///
////////////////////////////////////////////////////////////
void Object_CreateBox( Object *object, int width, int height )
{
    object->nbVertices = 4;

    object->vertices[0].x = -width  / 2;
    object->vertices[0].y = -height / 2;

    object->vertices[1].x = width   / 2;
    object->vertices[1].y = -height / 2;

    object->vertices[2].x = width  / 2;
    object->vertices[2].y = height / 2;

    object->vertices[3].x = -width / 2;
    object->vertices[3].y = height / 2;
}


////////////////////////////////////////////////////////////
///
/// Calcul le poids et autre variables de l'objet
///
////////////////////////////////////////////////////////////
void Object_CalculateWeight( Object *object )
{
	float  fDensity = (frand(1.0f) < 0.3f)? 0.0f : 1.0f;

    object->mass    = Math_CalculateMass( object->vertices, object->nbVertices, fDensity );
    object->invMass = (object->mass > 0.0f)? 1.0f / object->mass : 0.0f;
}

////////////////////////////////////////////////////////////
///
/// Surrpimr d'un objet
///
////////////////////////////////////////////////////////////
void Object_Delete( Object *object )
{
    free( object->vertices );
}
