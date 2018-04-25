#include "emeraldmanager.h"
#include "entities.h"
#include "emeraldpiece.h"
#include "../engineTester/main.h"
#include "../guis/guimanager.h"
#include "../toolbox/maths.h"

#include <vector>
#include <list>

EmeraldPiece* EmeraldManager::piece1 = nullptr;
EmeraldPiece* EmeraldManager::piece2 = nullptr;
EmeraldPiece* EmeraldManager::piece3 = nullptr;
int EmeraldManager::piecesRemaining = 3;

EmeraldManager::EmeraldManager()
{
	
}

EmeraldManager::EmeraldManager(int hardMode)
{
	std::vector<EmeraldPiece*> piece1List;
	std::vector<EmeraldPiece*> piece2List;
	std::vector<EmeraldPiece*> piece3List;

	int totalPieces = 0;
	EmeraldManager::piece1 = nullptr;
	EmeraldManager::piece2 = nullptr;
	EmeraldManager::piece3 = nullptr;

	visible = false;

	extern std::list<Entity*> gameEntitiesToAdd;

	for (auto e : gameEntitiesToAdd)
	{
		if (e->isEmeraldPiece()) 
		{
			EmeraldPiece* piece = (EmeraldPiece*)e;
			totalPieces++;
			switch(piece->getPieceNumber())
			{
			case 1:
				piece1List.push_back(piece);
				break;

			case 2:
				piece2List.push_back(piece);
				break;

			default:
				piece3List.push_back(piece);
				break;
			}
		}
	}

	if (hardMode != 0)
	{
		EmeraldManager::piecesRemaining = totalPieces;
	}
	else
	{
		//Pick a random p1
		EmeraldManager::piece1 = piece1List[(int)(Maths::random()*piece1List.size())];
		Vector3f p1Loc(EmeraldManager::piece1->getPosition());

		//Calculate distances from p1 to p2
		std::vector<float> distTo2;
		for (EmeraldPiece* piece : piece2List)
		{
			Vector3f p2Loc(piece->getPosition());
			Vector3f diff = p1Loc - p2Loc;
			float dist = diff.lengthSquared();

			distTo2.push_back(dist);
		}

		//Get the minimum distance needed to be a valid p2
		std::sort(distTo2.begin(), distTo2.end());
		float minDist = distTo2[distTo2.size()/2];

		//Generate valid p2's
		std::vector<EmeraldPiece*> validP2s;
		for (EmeraldPiece* piece : piece2List)
		{
			Vector3f p2Loc(piece->getPosition());
			Vector3f diff = p1Loc - p2Loc;
			float dist = diff.lengthSquared();

			if (dist >= minDist)
			{
				validP2s.push_back(piece);
			}
		}

		//Pick a random p2
		EmeraldManager::piece2 = validP2s[(int)(Maths::random()*validP2s.size())];
		Vector3f p2Loc(EmeraldManager::piece2->getPosition());
		Vector3f diff = p1Loc - p2Loc;

		//Calculate cross products to p3's
		std::vector<float> crossProducts;
		for (EmeraldPiece* piece : piece3List)
		{
			float cp = (diff.cross(piece->getPosition())).lengthSquared();

			crossProducts.push_back(cp);
		}

		//Get the minimum area needed to be a valid p3
		std::sort(crossProducts.begin(), crossProducts.end());
		float minCP = crossProducts[crossProducts.size()/2];

		//Generate valid p3's
		std::vector<EmeraldPiece*> validP3s;
		for (EmeraldPiece* piece : piece3List)
		{
			float cp = (diff.cross(piece->getPosition())).lengthSquared();

			if (cp >= minCP)
			{
				validP3s.push_back(piece);
			}
		}

		//Pick a random p3
		EmeraldManager::piece3 = validP3s[(int)(Maths::random()*validP3s.size())];

		EmeraldManager::piecesRemaining = 3;

		//Delete all the other pieces
		for (EmeraldPiece* piece : piece1List)
		{
			if (piece != EmeraldManager::piece1)
			{
				Main_deleteEntity(piece);
			}
		}
		for (EmeraldPiece* piece : piece2List)
		{
			if (piece != EmeraldManager::piece2)
			{
				Main_deleteEntity(piece);
			}
		}
		for (EmeraldPiece* piece : piece3List)
		{
			if (piece != EmeraldManager::piece3)
			{
				Main_deleteEntity(piece);
			}
		}
	}
}

void EmeraldManager::step()
{
	//make ping sounds, update radar
}

void EmeraldManager::collectPiece(EmeraldPiece* collectedPiece)
{
	if (collectedPiece == EmeraldManager::piece1)
	{
		EmeraldManager::piece1 = nullptr;
	}
	else if (collectedPiece == EmeraldManager::piece2)
	{
		EmeraldManager::piece2 = nullptr;
	}
	else if (collectedPiece == EmeraldManager::piece3)
	{
		EmeraldManager::piece3 = nullptr;
	}

	EmeraldManager::piecesRemaining--;

	if (EmeraldManager::piecesRemaining <= 0)
	{
		GuiManager::stopTimer();

		Global::finishStageTimer = 0;
	}
}