#include <math.h>
#include <list>

#include "triangle3d.h"
#include "../toolbox/vector.h"
#include "collisionmodel.h"
#include "../engineTester/main.h"


CollisionModel::CollisionModel()
{
	playerIsOn = false;
}

void CollisionModel::generateMinMaxValues()
{
	if (triangles.size() == 0)
	{
		return;
	}

	minX = triangles.front()->minX;
	maxX = triangles.front()->maxX;
	minY = triangles.front()->minY;
	maxY = triangles.front()->maxY;
	minZ = triangles.front()->minZ;
	maxZ = triangles.front()->maxZ;

	for (Triangle3D* tri : triangles)
	{
		minX = fmin(minX, tri->minX);
		maxX = fmax(maxX, tri->maxX);
		minY = fmin(minY, tri->minY);
		maxY = fmax(maxY, tri->maxY);
		minZ = fmin(minZ, tri->minZ);
		maxZ = fmax(maxZ, tri->maxZ);
	}
}

void CollisionModel::offsetModel(Vector3f* offset)
{
	float x = offset->x;
	float y = offset->y;
	float z = offset->z;

	for (Triangle3D* tri : triangles)
	{
		tri->p1X += x;
		tri->p2X += x;
		tri->p3X += x;
		tri->p1Y += y;
		tri->p2Y += y;
		tri->p3Y += y;
		tri->p1Z += z;
		tri->p2Z += z;
		tri->p3Z += z;

		tri->generateValues();
	}

	generateMinMaxValues();
}

void CollisionModel::rotateModelY(float yRot, Vector3f* center)
{

}

//makes a collision model be the transformed version of this collision model
void CollisionModel::transformModel(CollisionModel* targetModel, Vector3f* translate, float yRot, float zRot)
{

}

//makes a collision model be the transformed version of this collision model
void CollisionModel::transformModel(CollisionModel* targetModel, Vector3f* translate, float yRot)
{

}

//makes a collision model be the transformed version of this collision model
void CollisionModel::transformModel(CollisionModel* targetModel, Vector3f* translate)
{

}

void CollisionModel::deleteAllTriangles()
{
	for (Triangle3D* tri : triangles)
	{
		delete tri;
		Global::countDelete++;
	}

	triangles.clear();
}