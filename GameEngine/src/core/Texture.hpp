#pragma once

#include "stb_image/stb_image.h"
#include "OpenGLErrorManager.hpp"
#include <iostream>

class Texture
{ 
private:
	unsigned int _RendererID;
	std::string _Filepath;
	unsigned char* _LocalBuffer;
	int _Width, _Height, _BPP, _Slot;
	
public:
	Texture(const std::string& path)
		: _RendererID(0), _Filepath(path), _LocalBuffer(nullptr), _Width(0), _Height(0), _BPP(0)
	{
		GLCall(glGenTextures(1, &_RendererID));
		//GLCall(glActiveTexture(GL_TEXTURE0 + slot));
		GLCall(glBindTexture(GL_TEXTURE_2D, _RendererID));
		
		stbi_set_flip_vertically_on_load(0);
		_LocalBuffer = stbi_load(path.c_str(), &_Width, &_Height, &_BPP, 0);

		if (_LocalBuffer)
		{
			GLenum format;
			if (_BPP == 1)
				format = GL_RED;
			else if (_BPP == 3)
				format = GL_RGB;
			else if (_BPP == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, _RendererID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, _Width, _Height, 0, format, GL_UNSIGNED_BYTE, _LocalBuffer);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(_LocalBuffer);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
			stbi_image_free(_LocalBuffer);
		}
	}

	~Texture()
	{
		GLCall(glDeleteTextures(1, &_RendererID));
	}

	void bind() const
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, _RendererID));
	}

	void unbind() const
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}
};