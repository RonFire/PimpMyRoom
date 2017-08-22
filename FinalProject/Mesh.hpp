//
//  Mesh.hpp
//  FinalProject
//
//  Created by Ronald Brenner on 20.08.17.
//  Copyright © 2017 rapidRonald. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <assimp/Importer.hpp>

#include "Shader.hpp"
#include <vector>


struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
};

struct Texture {
	unsigned int id;
	std::string type;
	aiString path;
};

class Mesh
{
public:
	// Mesh Data
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	// Functions
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void Draw(Shader shader);
	
private:
	// Render data
	unsigned int VBO, EBO, VAO;
	// Functions
	void setupMesh();
};

#endif /* Mesh_hpp */
