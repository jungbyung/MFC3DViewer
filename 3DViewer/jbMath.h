#pragma once
#include <vector>

#define EPSILON 0.00001f
#define PI 3.141592f
#define PI2 PI*2.f


namespace jbMath
{
	class Matrix;
	class Vector3
	{
	public:
		float x, y, z;
		Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
		Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
		~Vector3() {}

		bool operator ==(Vector3& vec);
		bool operator !=(Vector3& vec);
		Vector3 operator +(Vector3& vec);
		Vector3 operator -(Vector3& vec);
		Vector3 operator * (float f);
		Vector3 operator *(Vector3& vec);
		bool operator > (Vector3& vec);
		bool operator < (Vector3& vec);
		bool operator <= (Vector3& vec);
		bool operator >= (Vector3& vec);

		Vector3 operator-();

		void SetVector3(float _x, float _y, float _z);
		void SetX(float _x);
		void SetY(float _y);
		void SetZ(float _z);

		//제곱근된 길이(크기)
		float Length();
		//제곱근이 안된 길이(크기)
		float sqrtLength();
		Vector3 Normalize();

		Vector3 TransformCoord(Matrix* pMat);
		Vector3 TransformNormal(Matrix* pMat);

		bool ZeroVector();

		static float Dot(Vector3 v1, Vector3 v2);
		static Vector3 cross(Vector3 v1, Vector3 v2);
		static Vector3 vecMin(Vector3 v1, Vector3 v2);
		static Vector3 vecMax(Vector3 v1, Vector3 v2);
	};
	Vector3 operator*(float f, Vector3 vec);


	class Matrix
	{
	public:
		float m[4][4];

		Matrix() {}
		~Matrix() {}

		bool operator == (Matrix mat);
		bool operator != (Matrix mat);
		Matrix operator + (Matrix mat);
		Matrix operator - (Matrix mat);
		Matrix operator * (float x);
		Matrix operator * (Matrix mat);

		Matrix operator-();

		static Matrix Identity();
		Matrix Transpose();
		Matrix Inverse(float& fDet);
	private:

		float	Determinent(int n);
		Matrix  Adjoint();
		float	Cofactor(int nRow, int nCol, int size);
		float	Minor(int nRow, int nCol, int size);

	};
	Matrix operator * (float f, Matrix mat);

	Matrix View(Vector3* pEye, Vector3* pUp, Vector3* pLookAt);
	Matrix Proj(float fFovY, float fAspect, float fNearZ, float fFarZ);
	Matrix Proj();
	Matrix Viewport(float fX, float fY, float fW, float fH, float fMinZ, float fMaxZ);

	Matrix Translation(float x, float y, float z);
	Matrix Translation(Vector3* pVec);
	Matrix RotateX(float fAngle);
	Matrix RotateY(float fAngle);
	Matrix RotateZ(float fAngle);
	Matrix RotateXYZ(Vector3 vec);
	Matrix Scale(float x, float y, float z);
	Matrix Scale(Vector3 vec);

	float Clamp(float f, float max, float min);
}

