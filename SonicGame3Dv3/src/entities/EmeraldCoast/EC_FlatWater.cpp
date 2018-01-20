#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ecflatwater.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../entities/player.h"
#include "../../toolbox/maths.h"
#include "../camera.h"

#include <list>
#include <iostream>
#include <algorithm>

std::list<TexturedModel*> EC_FlatWater::models;

EC_FlatWater::EC_FlatWater()
{
	this->position.x = 0;
	this->position.y = 0;
	this->position.z = 0;
	this->rotX = 0;
	this->rotY = 0;
	this->rotZ = 0;
	this->scale = 1;
	this->visible = false;
	updateTransformationMatrix();
}


void EC_FlatWater::step()
{
	if (Global::gameCamera->getPosition()->z > 2000)
	{
		visible = true;

		if (Global::gamePlayer->getX() > -721.26f && Global::gamePlayer->getX() < 378.71f &&
			Global::gamePlayer->getZ() > 4567.68f && Global::gamePlayer->getZ() < 5667.667f &&
			Global::gamePlayer->getY() < 576)
		{
			Global::gamePlayer->setInWater(581);
		}
		else if (Global::gamePlayer->getX() > 420.37f && Global::gamePlayer->getX() < 1212.35f &&
				 Global::gamePlayer->getZ() > 5713.0f && Global::gamePlayer->getZ() < 6505.0f &&
			     Global::gamePlayer->getY() < 586)
		{
			Global::gamePlayer->setInWater(590);
		}
	}
	else
	{
		visible = false;
	}
}

std::list<TexturedModel*>* EC_FlatWater::getModels()
{
	return &EC_FlatWater::models;
}

void EC_FlatWater::loadStaticModels()
{
	if (EC_FlatWater::models.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading EC_FlatWater static models...\n");

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/EmeraldCoast/", "FlatWater.obj");
	for (auto newModel : (*newModels))
	{
		EC_FlatWater::models.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;
}

void EC_FlatWater::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting EC_FlatWater static models...\n");
	for (auto model : EC_FlatWater::models)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}

	EC_FlatWater::models.clear();
}

std::string EC_FlatWater::getName()
{
	return "EC_FlatWater";
}