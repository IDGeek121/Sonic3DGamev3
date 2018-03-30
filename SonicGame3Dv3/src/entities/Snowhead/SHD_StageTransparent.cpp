#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "shdstagetransparent.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../entities/player.h"
#include "../../toolbox/maths.h"
#include "../camera.h"

#include <list>
#include <iostream>
#include <algorithm>

std::list<TexturedModel*> SHD_StageTransparent::models;

SHD_StageTransparent::SHD_StageTransparent()
{
	position.x = 0;
	position.y = 0;
	position.z = 0;
	rotX = 0;
	rotY = 0;
	rotZ = 0;
	scale = 1;
	visible = true;
	updateTransformationMatrix();
}

void SHD_StageTransparent::step()
{

}

std::list<TexturedModel*>* SHD_StageTransparent::getModels()
{
	return &SHD_StageTransparent::models;
}

void SHD_StageTransparent::loadStaticModels()
{
	if (SHD_StageTransparent::models.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading SHD_StageTransparent static models...\n");

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/Snowhead/", "SnowheadTransparent.obj");
	for (auto newModel : (*newModels))
	{
		SHD_StageTransparent::models.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;
}

void SHD_StageTransparent::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting SHD_StageTransparent static models...\n");
	for (auto model : SHD_StageTransparent::models)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}

	SHD_StageTransparent::models.clear();
}