#include "mesh.h"

Mesh::Mesh(vector<Vertex>vertices, vector<unsigned int>indices, vector<Texture>textures):
	vertices(vertices),
	indices(indices),
	textures(textures) {
	
	Mesh::setupMesh();
}