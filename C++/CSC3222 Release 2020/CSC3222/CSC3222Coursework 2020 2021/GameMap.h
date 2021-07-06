#pragma once
#include <string>
#include <vector>

#include "../../Common/Vector2.h"
#include "../../Common/Vector3.h"
#include "../../Common/Vector4.h"
#include "../../Common/MeshGeometry.h"

namespace NCL {
	namespace Rendering {
		class TextureBase;
	}
	using namespace Maths;
	namespace CSC3222 {
		class GameSimsRenderer;
		class SimObject;
		class TextureManager;

		class GameMap	{
		public:
			GameMap(const std::string& filename, std::vector<SimObject*>& objects, TextureManager& texManager);
			~GameMap();

			void DrawMap(GameSimsRenderer & r);

			//Functions to get map width and height
			int GetMapWidth() const {
				return mapWidth;
			}
			int GetMapHeight() const {
				return mapHeight;
			}

			//Getter for valid spawn locations
			std::vector<int>* getValidSpawnPositions() const {
				return validSpawnPositions;
			}

			//Function to convert between world positions and tile positions
			Vector2 WorldPosToTilePos(const Vector2& worldPos) const;
			Vector2 TilePosToWorldPos(const Vector2& tilePos) const;

			//Function to convert from tile position to index
			int TilePosToIndex(const Vector2 pos) const;

			//Function to get if a given tile is empty
			bool IsTilePosEmpty(Vector2 tilePos);

			//Function to generate the path
			bool GeneratePath(const Vector2& worldFrom, const Vector2& worldTo, std::vector<Vector2>* path) const;

			//Function to reset the valid spawn positions
			void ResetValidSpawnPositions();


			//Struct to store data for nodes
			struct MapNode {
			public:
				//Equality operator to check the positions
				bool operator==(const MapNode& other) {
					return posX == other.posX &&
						posY == other.posY;
				}
				//The best parents
				MapNode* bestParent;
				//X and Y positions
				int posX;
				int posY;
				//Values for the calculations
				float g;
				float h;
				float f;
				//Whether the node is closed
				bool closed = false;
			};

		protected:
			void BuildMapMesh();
			void AddNewTilePos(int x, int y, std::vector<Vector3>& pos, Vector2 tileSize = Vector2(16, 16));
			void AddNewTileTex(int x, int y, std::vector<Vector2>& tex, Vector2 texSize = Vector2(16,16));

			int mapWidth;
			int mapHeight;
			int structureCount;

			Rendering::TextureBase*	tileTexture;
			char*	mapData;
			int*			mapCosts;
			Vector2*		mapTexCoords;

			MeshGeometry* mapMesh;

			//List for current valid spawn locations and all valid spawn positions
			std::vector<int>* validSpawnPositions;
			std::vector<int> fullValidSpawnPositions;
			
			
			

			//Function to get the heuristic (Manhattan distance
			float GetHeuristic(MapNode* a, MapNode* b) const;
			//Function to get the best node in the open list
			MapNode* GetBestNode() const;
			
			//Lists of map nodes for the open and closed lists
			std::vector<MapNode*>* openList;
			std::vector<MapNode*>* closedList;
			
			//List of map nodes for the node data
			MapNode* nodeData;
			
		};
	}
}

