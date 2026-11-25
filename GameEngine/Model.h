#ifndef model_h
#define model_h
#include "Mesh.h";

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
private:
	std::vector<Mesh> meshes;
	std::vector<Texture> loadedtextures;

	const char* textureDirectory;

public:
	Model(const char* path);

	Model(const char* modelPath, const char* texturePath);

	void Draw(Shader& shader);

private:
	void loadModel(const char* path);

	void processNode(aiNode* node, const aiScene* scene);

	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType type);
};
#endif