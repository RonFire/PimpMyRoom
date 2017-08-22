//
//  Model.hpp
//  FinalProject
//
//  Created by Ronald Brenner on 22.08.17.
//  Copyright © 2017 rapidRonald. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include <stdio.h>
#include "Shader.hpp"
#include "Mesh.hpp"
#include "stb_image.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
	// Functions
	Model(char *path);
	void Draw(Shader shader);
	
private:
	// Model data
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> textures_loaded;
	// Functions
	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
	unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma=false);
};
#endif /* Model_hpp */
