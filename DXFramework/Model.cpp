// Model mesh and load
// Loads a .obj and creates a mesh object from the data
#include "model.h"
#include "../DXFramework/DXF.h"


// load model datat, initialise buffers (with model data) and load texture.
Model::Model(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const char* filename)
{
	loadModel(device, filename);
}

// Release resources.
Model::~Model()
{

	if (model)
	{
		delete[] model;
		model = 0;
	}
}


// Initialise buffers with model data.
void Model::initBuffers(ID3D11Device* device, const std::vector<VertexType>& vertices, const std::vector<unsigned int>& indices)
{
	// Vertex buffer
	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * vertices.size();
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA vertexData = {};
	vertexData.pSysMem = vertices.data();
	device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);

	// Index buffer
	D3D11_BUFFER_DESC indexBufferDesc = {};
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned int) * indices.size();
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA indexData = {};
	indexData.pSysMem = indices.data();
	device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);

	m_indexCount = indices.size();
}

// Modified from a mulit-threaded version by Mark Ropper (CGT).
void Model::loadModel(ID3D11Device* device, const char* filename)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);

	if (!scene || !scene->HasMeshes()) {
		// Handle error
		return;
	}

	std::vector<VertexType> vertices;
	std::vector<unsigned int> indices;

	// Process each mesh in the scene
	for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[i];

		for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
			VertexType vertex;
			vertex.position = XMFLOAT3(mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z);
			vertex.normal = XMFLOAT3(mesh->mNormals[j].x, mesh->mNormals[j].y, mesh->mNormals[j].z);
			if (mesh->mTextureCoords[0]) {
				vertex.texture = XMFLOAT2(mesh->mTextureCoords[0][j].x, mesh->mTextureCoords[0][j].y);
			}
			else {
				vertex.texture = XMFLOAT2(0.0f, 0.0f); // Default if no UVs
			}
			vertices.push_back(vertex);
		}

		for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
			aiFace face = mesh->mFaces[j];
			for (unsigned int k = 0; k < face.mNumIndices; k++) {
				indices.push_back(face.mIndices[k]);
			}
		}
	}

	// Create Direct3D buffers
	initBuffers(device, vertices, indices);
}

void Model::sendData(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride = sizeof(VertexType);
	unsigned int offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

unsigned int Model::getIndexCount() const
{
	return m_indexCount;
}
