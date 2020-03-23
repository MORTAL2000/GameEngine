#pragma once

#include "Renderer.hpp"
#include "TerrainEntity.hpp"
#include "ObjmodelEntity.hpp"
#include "CubemapEntity.hpp"

class EntityManager
{
private:
	Renderer _renderer;
	unsigned int _nextTextureSlot = 0;
	
	std::vector<Basemodel*> _models;
	std::vector<TerrainEntity*> _terrains;	
	std::vector<ObjmodelEntity*> _objs;
	CubemapEntity* _cubemap;
	
public:
	EntityManager()
	{
		
	}

	~EntityManager()
	{
		for (auto t : _objs)
			delete t;

		for (auto obj : _terrains)
			delete obj;

		delete _cubemap;
	}

	TerrainEntity* addTerrainEntity(const unsigned int& size, const unsigned int& tileSize, const char* heightmap, const char* terrainTexture, const char* pathwayTexture, const char* blendmap, const char* vsShader, const char* fsShader)
	{
		TerrainEntity* terrain = new TerrainEntity(size, tileSize, heightmap, terrainTexture, pathwayTexture, blendmap, vsShader, fsShader, &_nextTextureSlot);
		_terrains.push_back(terrain);
		_models.push_back((Basemodel*)terrain->getModel());
		return terrain;
	}
	
	ObjmodelEntity* addOBJEntity(const char* objFile, const char* texture, const char* vsShader, const char* fsShader)
	{
		ObjmodelEntity* obj = new ObjmodelEntity(objFile, texture, vsShader, fsShader, &_nextTextureSlot);
		_objs.push_back(obj);
		_models.push_back((Basemodel*)obj->getModel());
		return obj;
	}

	void addCubemapEntity()
	{
		_cubemap = new CubemapEntity(&_nextTextureSlot);
		_models.push_back((Basemodel*)_cubemap->getModel());
	}
	
	void render()
	{
		_renderer.prepare();
		_renderer.render(_models);
	}
};