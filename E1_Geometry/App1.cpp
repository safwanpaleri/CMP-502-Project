// Lab1.cpp
// Lab 1 example, simple coloured triangle mesh
#include "App1.h"

App1::App1()
{
	//mesh = nullptr;
	colourShader = nullptr;
}

void App1::init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in, bool VSYNC, bool FULL_SCREEN)
{
	// Call super/parent init function (required!)
	BaseApplication::init(hinstance, hwnd, screenWidth, screenHeight, in, VSYNC, FULL_SCREEN);

	// Create Mesh object
	//mesh = new ColourTriangle(renderer->getDevice(), renderer->getDeviceContext());

	colourShader = new ColourShader(renderer->getDevice(), hwnd);

	backgroundQuad = new TexturedQuad(renderer->getDevice(), renderer->getDeviceContext());
	textureShader = new TextureShader(renderer->getDevice(), hwnd);
	textureMgr->loadTexture(L"BackgroundTexture", L"res/Textures/bg.jpg");
	textureMgr->loadTexture(L"TreeTexture", L"res/Textures/br_sakura_bark.jpg");

	//sakuraTree = new SakuraTree(renderer->getDevice(), renderer->getDeviceContext());
	mymodel = new Model(renderer->getDevice(), renderer->getDeviceContext(), "res/trees/uploads_files_855516_Tree.obj");

	*sx, * sy, * sz = 0.05f;
}


App1::~App1()
{
	// Run base application deconstructor
	BaseApplication::~BaseApplication();

	if (colourShader)
	{
		delete colourShader;
		colourShader = 0;
	}
}


bool App1::frame()
{
	bool result;

	result = BaseApplication::frame();
	if (!result)
	{
		return false;
	}
	
	// Render the graphics.
	result = render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool App1::render()
{
	// Clear the scene. (default blue colour)
	renderer->beginScene(0.39f, 0.58f, 0.92f, 1.0f);

	// Generate the view matrix based on the camera's position.
	camera->update();

	// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	
	XMMATRIX worldMatrix = renderer->getWorldMatrix();
	XMMATRIX viewMatrix = camera->getViewMatrix();
	XMMATRIX projectionMatrix = renderer->getProjectionMatrix();

	XMMATRIX scaleMatrix = XMMatrixScaling(1.545f,0.83f,1.0f);
	XMMATRIX scaledWorldMatrix = XMMatrixMultiply(scaleMatrix, worldMatrix);

	backgroundQuad->sendData(renderer->getDeviceContext());
	textureShader->setShaderParameters(renderer->getDeviceContext(), scaledWorldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture(L"BackgroundTexture"));
	textureShader->render(renderer->getDeviceContext(), backgroundQuad->getIndexCount());
	// Define a scaling factor

	worldMatrix = renderer->getWorldMatrix();
	viewMatrix = camera->getViewMatrix();
	projectionMatrix = renderer->getProjectionMatrix();
	float scaleFactor = 0.05f;
	scaledWorldMatrix = XMMatrixScaling(0.417f, 0.417f, 0.0f) * worldMatrix;
	XMMATRIX translationMatrix = XMMatrixTranslation(4.167f, -2.222f, -0.370f);
	XMMATRIX scaledTranslatedWorldMatrix = XMMatrixMultiply(scaledWorldMatrix, translationMatrix);
	mymodel->sendData(renderer->getDeviceContext());
	textureShader->setShaderParameters(renderer->getDeviceContext(), scaledTranslatedWorldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture(L"TreeTexture"));
	textureShader->render(renderer->getDeviceContext(), mymodel->getIndexCount());

	// Render GUI
	gui();

	// Present the rendered scene to the screen.
	renderer->endScene();

	return true;
}

void App1::gui()
{
	// Force turn off unnecessary shader stages.
	renderer->getDeviceContext()->GSSetShader(NULL, NULL, 0);
	renderer->getDeviceContext()->HSSetShader(NULL, NULL, 0);
	renderer->getDeviceContext()->DSSetShader(NULL, NULL, 0);

	// Build UI
	/*ImGui::Text("FPS: %.2f", timer->getFPS());
	ImGui::Checkbox("Wireframe mode", &wireframeToggle);
	*/
	/*ImGui::Text(("tree position"));
	ImGui::SliderFloat("tx", tx, -10.0f, 10.0f);
	ImGui::SliderFloat("ty", ty, -10.0f, 10.0f);
	ImGui::SliderFloat("tz", tz, -10.0f, 10.0f);
	
	ImGui::Text(("tree size"));
	ImGui::SliderFloat("sx", sx, 0.0f, 0.1f);
	ImGui::SliderFloat("sy", sy, 0.0f,0.1f);
	ImGui::SliderFloat("sz", sz, 0.0f, 0.1f);*/

	/*XMMATRIX worldMatrix = renderer->getWorldMatrix();
	XMMATRIX viewMatrix = camera->getViewMatrix();
	XMMATRIX projectionMatrix = renderer->getProjectionMatrix();
	float scaleFactor = 0.05f;
	XMMATRIX scaledWorldMatrix = XMMatrixScaling(*sx, *sy, *sz) * worldMatrix;
	XMMATRIX translationMatrix = XMMatrixTranslation(*tx, *ty, *tz);
	XMMATRIX scaledTranslatedWorldMatrix = XMMatrixMultiply(scaledWorldMatrix, translationMatrix);
	mymodel->sendData(renderer->getDeviceContext());
	textureShader->setShaderParameters(renderer->getDeviceContext(), scaledTranslatedWorldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture(L"TreeTexture"));
	textureShader->render(renderer->getDeviceContext(), mymodel->getIndexCount());*/
	
	// Render UI
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

