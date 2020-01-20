#pragma once

#include "Model.hpp"

class Renderer
{
public:
	void prepare()
	{
		GLCall(glClearColor(0.368f, 0.721f, 0.811f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

	void render(const std::vector<Model*>& Models)
	{
		for(Model* m : Models)
		{
			m->draw();
			GLCall(glDrawElements(GL_TRIANGLES, m->getNumberOfVertices(), GL_UNSIGNED_INT, nullptr));
			m->undraw();
		}
	}
};