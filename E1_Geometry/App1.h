// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "../DXFramework/DXF.h"
#include "ColourShader.h"
#include "ColourTriangle.h"
#include "Model.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "TexturedQuad.h"
#include "TextureShader.h"

class App1 : public BaseApplication
{
public:

	App1();
	~App1();
	void init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input* in, bool VSYNC, bool FULL_SCREEN);

	bool frame();

protected:
	bool render();
	void gui();

private:
	ColourShader* colourShader;

	TexturedQuad* backgroundQuad;
	TextureShader* textureShader;
	Model* mymodel;

	float* tx = new float();
	float* ty = new float();
	float* tz = new float();
	
	float* sx = new float();
	float* sy = new float();
	float* sz = new float();
};

#endif