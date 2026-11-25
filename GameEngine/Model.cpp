#include "Model.h"

//constructor
Model::Model(const char* path) {
	//if not specified assume in same folder as model
	std::string strPath = std::string(path);
	textureDirectory = strPath.substr(0, strPath.find_last_of('/')).c_str();

	loadModel(path);
}

//constructor with speicifed location for textures
Model::Model(const char* modelPath, const char* texturePath) {
	textureDirectory = texturePath;

	loadModel(modelPath);
}



//Render the model to the screen
void Model::Draw(Shader& shader) {
	for (int i = 0; i < meshes.size(); i++) {
		meshes[i].Draw(shader);
	}
}

//load the model from file
void Model::loadModel(const char* path) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cerr << "ERROR::ASSIMP::Failed_To_Import_Model: " << importer.GetErrorString() << std::endl;
		return;
	}

	processNode(scene->mRootNode, scene);
}

//process single node in imported model hierarcy
void Model::processNode(aiNode* node, const aiScene* scene) {
	//Process any meshes in node
	for (int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	//Recusive call to children
	for (int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

//process mesh in imported model hierarcy
Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indicies;
	std::vector<Texture> textures;

	//Verticies
	for (int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;

		vertex.Position.x = mesh->mVertices[i].x;
		vertex.Position.y = mesh->mVertices[i].y;
		vertex.Position.z = mesh->mVertices[i].z;

		vertex.Normal.x = mesh->mNormals[i].x;
		vertex.Normal.y = mesh->mNormals[i].y;
		vertex.Normal.z = mesh->mNormals[i].z;

		glm::vec2 texCoord;
		if (mesh->mTextureCoords[0]) {
			texCoord.x = mesh->mTextureCoords[0][i].x;
			texCoord.y = mesh->mTextureCoords[0][i].y;
		}
		else {
			texCoord = glm::vec2(0, 0);
		}
		vertex.TexCoord = texCoord;

		vertices.push_back(vertex);
	}

	//Indicies
	for (int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; j++) {
			indicies.push_back(face.mIndices[j]);
		}
	}

	//Textures
	if (mesh->mMaterialIndex > 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_NORMALS);
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	}

	return Mesh(vertices, indicies, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* material, aiTextureType type) {
	std::vector<Texture> textures;
	for (int i = 0; i < material->GetTextureCount(type); i++) {
		aiString path;
		material->GetTexture(type, i, &path);

		//check if already loaded into memory
		bool loaded = false;
		for (int j = 0; j < loadedtextures.size(); i++) {
			if (std::strcmp(loadedtextures[j].path.data(), path.C_Str()) == 0) {
				textures.push_back(loadedtextures[j]);
				loaded = true;
				break;
			}
		}

		if (!loaded) {
			Texture texture;
			texture.id = loadTexture(textureDirectory + '/' + *path.C_Str());
			switch (type) {
				case aiTextureType_DIFFUSE:
					texture.type = TextureType::Diffuse;
					break;
				case aiTextureType_SPECULAR:
					texture.type = TextureType::Specular;
					break;
				case aiTextureType_NORMALS:
					texture.type = TextureType::Normal;
					break;
				default:
					texture.type = TextureType::Diffuse;
					break;
			}
			texture.path = path.C_Str();
			textures.push_back(texture);
			loadedtextures.push_back(texture);
		}
	}

	return textures;
}