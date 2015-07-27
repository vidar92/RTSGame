#pragma once
#include <vector>
struct sMapEnityPos
{
	float x,y,z;
};

struct sTextureCoord
{
	float s,t;
};

class Terrain
{
public:
	Terrain(int w,int h);
	~Terrain(void);
	void Draw(int w,int h);
	void LoadTExture();
	
private:
	//sMapEnityPos** pMapVertices;
	std::vector<unsigned int> indices;
	std::vector<sMapEnityPos> pMapVertices;
	std::vector<sTextureCoord> pMapTextureCoord;
	int textureID;
};

