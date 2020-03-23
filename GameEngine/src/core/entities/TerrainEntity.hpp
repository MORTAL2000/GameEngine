#pragma once

#include "GroundData.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "Groundmodel.hpp"
#include "Basemodel.hpp"

class TerrainEntity
{	
private:
	GroundData* _groundData;
	Texture* _terrainTex, * _pathwayTex, * _blendmapTex;
	unsigned int _terrainTexCount, _pathwayTexCount, _blendmapTexCount;
	Shader* _shader;
	Groundmodel* _groundModel;	
	
public:	
	TerrainEntity(const unsigned int& size, const unsigned int& tileSize, const char* heightmap, const char* terrainTexture, const char* pathwayTexture, const char* blendmap, const char* vsShader, const char* fsShader, unsigned int* nextTextureSlot)
	{		
		//Create the data
		_groundData = new GroundData(size, tileSize, heightmap);

		//Create 3 textures
		_terrainTexCount = *nextTextureSlot;
		_terrainTex = new Texture(terrainTexture, _terrainTexCount);
		(*nextTextureSlot)++;

		_pathwayTexCount = *nextTextureSlot;
		_pathwayTex = new Texture(pathwayTexture, _pathwayTexCount);
		(*nextTextureSlot)++;

		_blendmapTexCount = *nextTextureSlot;
		_blendmapTex = new Texture(blendmap, _blendmapTexCount);
		(*nextTextureSlot)++;
		
		//Create the shader
		_shader = new Shader(vsShader, fsShader);

		//Combine everything to the model
		_groundModel = new Groundmodel(_groundData, _shader, _terrainTexCount, _pathwayTexCount, _pathwayTexCount, _blendmapTexCount);
	}

	~TerrainEntity()
	{		
		delete _groundData;
		delete _terrainTex;
		delete _pathwayTex;
		delete _blendmapTex;
		delete _shader;
		delete _groundModel;				
	}

	Groundmodel* getModel()
	{
		return _groundModel;
	}
};