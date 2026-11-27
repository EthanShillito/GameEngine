#ifndef mesh_h
#define mesh_h

#include "Shader.h"
#include <vector>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoord;
};

enum TextureType
{
	Diffuse,
	Specular,
	Normal
};

struct Texture
{
	unsigned int id;
	std::string path;
	TextureType type;
};

class Mesh
{
private:
	//Mesh data
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indicies;
	std::vector<Texture> textures;

	//Buffer obejcts
	unsigned int VAO, VBO, EBO;

public:
	Mesh(std::vector<Vertex> verticies, std::vector<unsigned int> indicies, std::vector<Texture> textures);

	void Draw(Shader& shader);

private:
	void SetupMesh();
};
#endif