#include "GameMap.h"
#include "GameSimsRenderer.h"
#include "TextureManager.h"
#include "../../Common/Maths.h"
#include "../../Common/Assets.h"
#include "../../Common/TextureLoader.h"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace NCL;
using namespace CSC3222;
using namespace Rendering;

GameMap::GameMap(const std::string& filename, std::vector<SimObject*>& objects, TextureManager& texManager)	{
	tileTexture = texManager.GetTexture("FruitWizard//arcade_platformerV2.png");
	validSpawnPositions = new std::vector<int>;

	std::ifstream mapFile(Assets::DATADIR + filename);

	if (!mapFile) {
		std::cout << "GameMap can't be loaded in!" << std::endl;
		return;
	}

	mapFile >> mapWidth;
	mapFile >> mapHeight;

	mapData		= new char[mapWidth * mapHeight];
	mapCosts	= new int[mapWidth * mapHeight];
	//Node data array to store list of map node structs
	nodeData = new MapNode[mapWidth * mapHeight];

	for (int y = 0; y < mapHeight; ++y) {
		for (int x = 0; x < mapWidth; ++x) {
			int tileIndex = ((mapHeight - 1 - y) * mapWidth) + x;
			mapFile >> mapData[tileIndex];
		}
	}

	for (int y = 0; y < mapHeight; ++y) {
		for (int x = 0; x < mapWidth; ++x) {
			int tileIndex = ((mapHeight - 1 - y) * mapWidth) + x;
			char c;
			mapFile >> c;
			mapCosts[tileIndex] = c;
			//Store x and y values in node data
			nodeData[(y * mapWidth) + x].posX = x;
			nodeData[(y * mapWidth) + x].posY = y;
		}
	}

	openList = new std::vector<MapNode*>;
	closedList = new std::vector<MapNode*>;

	BuildMapMesh();
}

GameMap::~GameMap()	{
	delete[] mapData;
	delete[] mapCosts;
	delete[] mapTexCoords;
	delete[] nodeData;

	delete mapMesh;
}

void GameMap::DrawMap(GameSimsRenderer & r) {
	r.DrawMesh((OGLMesh*)mapMesh, (OGLTexture*)tileTexture);
}

void GameMap::BuildMapMesh() {
	vector<Vector2> texCoords;
	vector<Vector3> positions;

	Vector2 primaryTile;

	AddNewTilePos(0, 0, positions, Vector2(mapWidth *16.0f, mapHeight * 16.0f));
	AddNewTileTex(0, 176, texCoords, Vector2(160, 128));

	for (int y = 0; y < mapHeight; ++y) {
		for (int x = 0; x < mapWidth; ++x) {
			int tileType = mapData[(y * mapWidth) + x];
			//Set potential spawn value to false (potential spawn is if the current tile should check above it)
			//E.g. bottom of ladder should not spawn fruit since above will be a ladder tile
			bool potentialSpawn = false;
			switch (tileType) {
			case '0': {
				continue;
			}break; //Top of ladder
				//the normal tile types first
				case 'T': {
					primaryTile = Vector2(320, 0);
					potentialSpawn = true;
				}break; //Top of ladder
				case 'L':primaryTile = Vector2(320, 16); break; //Ladder
				case 'B':primaryTile = Vector2(320, 32); break; //Bottom of ladder

				case 't': {
					primaryTile = Vector2(336, 0); 
					potentialSpawn = true;
				}break; //Top of ladder
				case 'l':primaryTile = Vector2(336, 16); break; //Ladder
				case 'b':primaryTile = Vector2(336, 32); break; //Bottom of ladder

				case 'G': {
					primaryTile = Vector2(224, 48);
					potentialSpawn = true;
				}break;//Random grass tiles
				case 'F': { //Left End
					primaryTile = Vector2(208, 48);
					potentialSpawn = true;
				}break;//Random grass tiles
				case 'H': { //Right End
					primaryTile = Vector2(240, 48);
					potentialSpawn = true;
				}break;//Random grass tiles

				case 'W': {//wall
					primaryTile = Vector2(256, 112);
				}break;//Random grass tiles
				case 'w': {//wall top
					primaryTile = Vector2(256, 96);
				}break;//Random grass tiles
			}
			//If the current tile is a potential spawn location
			if (potentialSpawn) {
				//If the tile above is empty
				if (mapData[((y + 1) * mapWidth) + x] == '0') {
					//Add the x and y value to the valid spawn list
					validSpawnPositions->emplace_back(x);
					validSpawnPositions->emplace_back(y + 1);
				}
				//Reset potential spawn
				potentialSpawn = false;
			}
			
			AddNewTilePos(x, y, positions);
			AddNewTileTex((int)primaryTile.x, (int)primaryTile.y, texCoords);
		}
	}
	fullValidSpawnPositions = *validSpawnPositions;
	mapMesh = new OGLMesh();
	mapMesh->SetVertexPositions(positions);
	mapMesh->SetVertexTextureCoords(texCoords);
	mapMesh->SetPrimitiveType(NCL::GeometryPrimitive::Triangles);
	mapMesh->UploadToGPU();
}

void GameMap::AddNewTilePos(int x, int y, std::vector<Vector3>& pos, Vector2 tileSize) {
	Vector3 topLeft		= Vector3((x + 0) * tileSize.x, (y + 0) * tileSize.y, 0);
	Vector3 topRight	= Vector3((x + 1) * tileSize.x, (y + 0) * tileSize.y, 0);
	Vector3 bottomLeft	= Vector3((x + 0) * tileSize.x, (y + 1) * tileSize.y, 0);
	Vector3 bottomRight = Vector3((x + 1) * tileSize.x, (y + 1) * tileSize.y, 0);

	pos.emplace_back(topLeft);
	pos.emplace_back(bottomLeft);
	pos.emplace_back(topRight);

	pos.emplace_back(topRight);
	pos.emplace_back(bottomLeft);
	pos.emplace_back(bottomRight);
}

void GameMap::AddNewTileTex(int x, int y, std::vector<Vector2>& tex, Vector2 texSize) {
	Vector2 topLeft		= Vector2((x + 0.0f) , (y + texSize.y));
	Vector2 topRight	= Vector2((x + texSize.x), (y + texSize.y));
	Vector2 bottomLeft	= Vector2((x + 0.0f) , (y + 0.0f));
	Vector2 bottomRight = Vector2((x + texSize.x), (y + 0.0f));

	tex.emplace_back(topLeft);
	tex.emplace_back(bottomLeft); 
	tex.emplace_back(topRight);

	tex.emplace_back(topRight);
	tex.emplace_back(bottomLeft);
	tex.emplace_back(bottomRight);
}


//Function to convert a world position to a tile position
Vector2 GameMap::WorldPosToTilePos(const Vector2& worldPos) const {
	//Find the x and y by dividing the world position by the tile size (16) and clamp between the valid range
	int x = std::clamp((int)worldPos.x / 16, 0, mapWidth - 1);
	int y = std::clamp((int)worldPos.y / 16, 0, mapHeight - 1);
	//Return a vector with the x and y
	return Vector2(x, y);
}

//Function to convert a tile position to a world position
Vector2 GameMap::TilePosToWorldPos(const Vector2& tilePos) const {
	//Return a vector with the tile positions multiplied by the tile size (16)
	return Vector2(tilePos.x * 16, tilePos.y * 16);
}

//Function to convert tile position to an array index
int GameMap::TilePosToIndex(const Vector2 pos) const {
	//Return the y position multiplied by the map width plus the x position 
	return (pos.y * mapWidth) + pos.x;
}

//Function to find if a given tile position is empty
bool GameMap::IsTilePosEmpty(Vector2 tilePos) {
	//Get the value in the map data list using the tile position to index function
	char c = mapData[TilePosToIndex(tilePos)];
	//Return true if the character is 0 (0 is an empty position)
	return (c == '0');
}

//Function to reset valid spawn locations
void GameMap::ResetValidSpawnPositions() {
	//Sets the valid spawn locations to a backup of every location from the start of the game
	*validSpawnPositions = fullValidSpawnPositions;
}


//Function to generate a path using the A* pathfinding algorithm
bool GameMap::GeneratePath(const Vector2& worldFrom, const Vector2& worldTo, std::vector<Vector2>* path) const {
	//Set the success variable to false to start
	bool success = false;

	//Set two map node variables to the corresponding map nodes from node data
	MapNode* a = &nodeData[TilePosToIndex(WorldPosToTilePos(worldFrom))];
	MapNode* b = &nodeData[TilePosToIndex(WorldPosToTilePos(worldTo))];
	//Set the other values to default
	a->g = 0;
	a->h = GetHeuristic(a, b);
	a->f = a->g + a->h;
	//Add the first node to the open list
	openList->emplace_back(a);

	//While there are more nodes to be checked
	while (!openList->empty()) {
		//Get the best node in the open list
		MapNode* p = GetBestNode();
		//If the best node is the node we are trying to get to (path has been found)
		if (p->posX == b->posX && p->posY == b->posY) {
			//Set a map node to the position to get to
			MapNode* r = b;
			//While that node is not the starting node
			while (!(r->posX == a->posX && r->posY == a->posY)) {
				//Add the node to the path (* 16 for world position, + 8 for middle of tile)
				path->emplace_back(Vector2((r->posX * 16) + 8, (r->posY * 16) + 8));
				//Set the map node to the parent (next node to complete the path)
				r = r->bestParent;
				
			}
			//Once the list has been completed, clear the open and closed list
			openList->clear();
			closedList->clear();
			//Set the success variable to true since a path was found
			success = true;
		}
		//If the best node is not the destination
		else {
			//Set n to 4 which is the number of possible directions to check, up down left and right
			int n = 4;
			//Set the default cost to 0
			float cost = 0;
			//For each of the directions to check
			for (int i = 0; i < n; i++) {
				//Create a new map node
				MapNode* q;
				//Set the default index to -1
				int index = -1;

				//Switch the direction
				switch (i) {
				//Up
				case 0: 
					//Check to make sure the check will stay within the map bounds (not check for a tile that doesnt exist)
					if (p->posY < 19) {
						//Set the index using the tile position to index function and get the tile above
						index = TilePosToIndex(Vector2(p->posX, p->posY + 1));
					}
					//If the tile above is out of bounds, continue on to the next one
					else {
						continue;
					}
					break;
				//Right
				case 1:
					//Check to make sure the check will stay within the map bounds (not check for a tile that doesnt exist)
					if (p->posX < 29) {
						//Set the index using the tile position to index function and get the tile to the right
						index = TilePosToIndex(Vector2(p->posX + 1, p->posY));
					}
					//If the tile above is out of bounds, continue on to the next one
					else {
						continue;
					}
					break;
				//Down
				case 2:
					//Check to make sure the check will stay within the map bounds (not check for a tile that doesnt exist)
					if (p->posY > 0) {
						//Set the index using the tile position to index function and get the tile below
						index = TilePosToIndex(Vector2(p->posX, p->posY - 1));
					}
					//If the tile above is out of bounds, continue on to the next one
					else {
						continue;
					}
					break;
				//Left
				case 3:
					//Check to make sure the check will stay within the map bounds (not check for a tile that doesnt exist)
					if (p->posX > 0) {
						//Set the index using the tile position to index function and get the tile to the left
						index = TilePosToIndex(Vector2(p->posX - 1, p->posY));
					}
					//If the tile above is out of bounds, continue on to the next one
					else {
						continue;
					}
					break;
				//Default case which shouldnt happen
				default:
					index = -1;
					break;
				}
				//If the index is not -1 meaning a valid index was given
				if (index != -1) {
					//Check if the map costs at that index isnt 0 (0 means not a valid position to move to)
					if (mapCosts[index] != '0') {
						//Set the q to the node data
						q = &nodeData[index];
						//Set the cost to the corresponding cost
						cost = mapCosts[index];
					}
					//If the map cost is 0 (not a valid move), skip
					else {
						continue;
					}
				}
				//If a valid position was not found, skip
				else {
					continue;
				}
				
				//Set new g, h, and f values using the new data
				float g = p->g + cost;
				float h = GetHeuristic(q, b);
				float f = g + h;
				
				//If the new node is already in the closed list, skip
				if (std::find(closedList->begin(), closedList->end(), q) != closedList->end()) {
					continue;
				}
				//If the new node is in the open list and the new f is greater (the new path is longer), skip 
				if (std::find(openList->begin(), openList->end(), q) != openList->end() && f > q->f) {
					continue;
				}
				//Otherwise
				else {
					//Set the nodes values to the new values
					q->g = g;
					q->h = h;
					q->f = f;
					//Set the new parent
					q->bestParent = p;
					//If the node is not already in the open list, add it to the open list
					if (std::find(openList->begin(), openList->end(), q) == openList->end()) {
						openList->emplace_back(q);
					}
				}
			}
			//Erase the node from the open list and add it to the closed list
			openList->erase(std::find(openList->begin(), openList->end(), p));
			closedList->emplace_back(p);
			//Set the closed trigger to true
			p->closed = true;
		}
	}

	//Clear the open and closed list to prevent huge lists and faults
	openList->clear();
	closedList->clear();
	//If a path was made, true will be returned
	//If the best node was never the destination node, the default value (false) will be returned
	return success;
}

//Function to get the best node in the open list
GameMap::MapNode* GameMap::GetBestNode() const {
	//Set the current best f value to the first f value
	float bestF = openList->at(0)->f;
	//Set the current best node to the first node
	MapNode* bestNode = openList->at(0);
	//For each of the nodes in the list
	for (int i = 0; i < openList->size(); i++) {
		//Set the ith element
		float iF = openList->at(i)->f;
		//If the ith f is better than the current best
		if (iF < bestF) {
			//Set the new best f
			bestF = iF;
			//Set the new best node
			bestNode = openList->at(i);
		}
	}
	//Return the node with the best f
	return bestNode;
}

//Function to get the heuristic (how far a node is)
float GameMap::GetHeuristic(MapNode* a, MapNode* b) const {
	//Returns the distance along the x plus the distance along the y (Manhattan distance)
	return abs(a->posX - b->posX) + abs(a->posY - b->posY);
}