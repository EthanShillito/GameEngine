#ifndef model_h
#define model_h
#include "Mesh.h"
#include "utils.h"

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
private:
	std::vector<Mesh> meshes;
	std::vector<Texture> loadedtextures;

	std::string textureDirectory;

public:
	Model(std::string path);

	Model(std::string modelPath, std::string texturePath);

	void Draw(Shader& shader);

private:
	void loadModel(std::string path);

	void processNode(aiNode* node, const aiScene* scene);

	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType type);
};
#endif