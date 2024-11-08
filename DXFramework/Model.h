/**
* \class Model mesh
*
* \brief Very basic OBJ loading mesh object
*
* Is treated like a standard mesh object, but loads a basic OBJ file based on provided filename.
* Future version will update/replace this model loader with something more complete.
*
* \author Paul Robertson
*/


#ifndef _MODEL_H_
#define _MODEL_H_

#include "BaseMesh.h"
//#include "TokenStream.h"
#include <vector>
#include <fstream>

using namespace DirectX;

class Model
{
	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT3 normal;
		XMFLOAT2 texture;
	};

public:
	/** \brief Initialises the mesh and vertex list, but loading in from a file
	* Provide filename to OBJ object, will be loaded and store like other mesh objects.
	* @param device is the renderer device
	* @param device context is the renderer device context
	* @param filename is a char* for filename.
	*/
	Model(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const char* filename);
	~Model();
	void sendData(ID3D11DeviceContext* deviceContext);
	unsigned int getIndexCount() const;

private:
	void initBuffers(ID3D11Device* device, const std::vector<VertexType>& vertices, const std::vector<unsigned int>& indices);
	void loadModel(ID3D11Device* device, const char* filename);
	

	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11Buffer* m_indexBuffer = nullptr;
	unsigned int m_indexCount = 0;

	ModelType* model;
};

#endif