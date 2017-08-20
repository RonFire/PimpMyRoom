//
//  Mesh.hpp
//  FinalProject
//
//  Created by Ronald Brenner on 20.08.17.
//  Copyright © 2017 rapidRonald. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <glad/glad.h>

#include <assimp/Importer.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"

#include <math.h>
#include <iostream>

#include <GLFW/glfw3.h>


struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec3 TexCoords;
};

struct Teture {
	unsigned int id;
	string type;
};

class Mesh
{
public:
	// Mesh Data
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	// Functions
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	void Draw(Shader shader);
	
private:
	// Render data
	unsigned int VBO, EBO, VAO;
	// Functions
	void setupMesh();
};

#endif /* Mesh_hpp */
