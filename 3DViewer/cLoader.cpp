#include "stdafx.h"
#include "cLoader.h"
#include <stdio.h>
#include "cMesh.h"

cLoader::cLoader()
{
}


cLoader::~cLoader()
{
}
cMesh* cLoader::OBJLoader(char * fileName)
{
	FILE* fp;
	fopen_s(&fp, fileName, "r");

	std::vector<jbMath::Vector3> pos;
	std::vector<jbMath::Vector3> normals;

	jbMath::Matrix matR = jbMath::RotateX(-PI / 2.f) * jbMath::RotateY(PI);
	//jbMath::Matrix matS = jbMath::Scale(0.1f, 0.1f, 0.1f);

	//jbMath::Matrix mat = matS * matR;
	jbMath::Matrix mat = matR;

	cMesh* pMesh = new cMesh;
	float x, y, z;
	int cnt = 0;
	while (!feof(fp))
	{
		char szBuf[1024];
		fgets(szBuf, 1024, fp);

		if (szBuf[0] == 'v')
		{
			if (szBuf[1] == 'n')
			{
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				normals.push_back(jbMath::Vector3(x, y, z));
			}
			else
			{
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				pos.push_back(jbMath::Vector3(x, y, z));
			}
		}
		if (szBuf[0] == 'f')
		{
			int p0, p1, p2;
			int n0, n1, n2;
			sscanf_s(szBuf, "%*s %d/%*d/%d %d/%*d/%d %d/%*d/%d", &p0, &n0, &p1, &n1, &p2, &n2);

			jbUtill::pcn v0(pos[p0-1].TransformCoord(&mat), jbMath::Vector3(0.5f, 0.5f, 0.5f), normals[n0-1].TransformNormal(&mat).Normalize());
			jbUtill::pcn v1(pos[p1-1].TransformCoord(&mat), jbMath::Vector3(0.5f, 0.5f, 0.5f), normals[n1-1].TransformNormal(&mat).Normalize());
			jbUtill::pcn v2(pos[p2-1].TransformCoord(&mat), jbMath::Vector3(0.5f, 0.5f, 0.5f), normals[n2-1].TransformNormal(&mat).Normalize());
			
			pMesh->pushVertex(v0);
			pMesh->pushVertex(v2);
			pMesh->pushVertex(v1);

			pMesh->pushIndex(cnt++);
			pMesh->pushIndex(cnt++);
			pMesh->pushIndex(cnt++);
		}
	}


	return pMesh;
}
