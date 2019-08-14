#pragma once

class cMesh;
class cLoader
{
public:
	cLoader();
	~cLoader();


	static cMesh* OBJLoader(char* fileName);
};

