#include "stdafx.h"
#include "jbMath.h"

namespace jbMath
{
	bool Vector3::operator==(Vector3 & vec)
	{
		return (fabs(x - vec.x) < EPSILON && fabs(y - vec.y) < EPSILON && fabs(z - vec.z) < EPSILON);
	}
	bool Vector3::operator!=(Vector3 & vec)
	{
		return !(*this == vec);
	}
	Vector3 Vector3::operator+(Vector3 & vec)
	{
		return Vector3(x + vec.x, y + vec.y, z + vec.z);
	}
	Vector3 Vector3::operator-(Vector3 & vec)
	{
		return Vector3(x - vec.x, y - vec.y, z - vec.z);
	}
	Vector3 Vector3::operator*(float f)
	{
		return Vector3(x * f, y * f, z * f);
	}
	Vector3 Vector3::operator*(Vector3 & vec)
	{
		return Vector3(x * vec.x, y * vec.y, z * vec.z);
	}
	bool Vector3::operator>(Vector3 & vec)
	{
		return this->sqrtLength() > vec.sqrtLength();
	}
	bool Vector3::operator<(Vector3 & vec)
	{
		return this->sqrtLength() < vec.sqrtLength();
	}
	bool Vector3::operator<=(Vector3 & vec)
	{
		return (this->sqrtLength() < vec.sqrtLength() || fabs(this->sqrtLength() - vec.sqrtLength()) < EPSILON);
	}
	bool Vector3::operator>=(Vector3 & vec)
	{
		return (this->sqrtLength() > vec.sqrtLength() || fabs(this->sqrtLength() - vec.sqrtLength()) < EPSILON);
	}
	Vector3 Vector3::operator-()
	{
		return Vector3(-x, -y, -z);
	}
	void Vector3::SetVector3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
	void Vector3::SetX(float _x)
	{
		x = _x;
	}
	void Vector3::SetY(float _y)
	{
		y = _y;
	}
	void Vector3::SetZ(float _z)
	{
		z = _z;
	}
	float Vector3::Length()
	{
		return static_cast<float>(sqrt(x*x + y*y + z*z));
	}
	float Vector3::sqrtLength()
	{
		return static_cast<float>(x*x + y*y + z*z);
	}
	Vector3 Vector3::Normalize()
	{
		float l = this->Length();
		return Vector3(x / l, y / l, z / l);
	}
	Vector3 Vector3::TransformCoord(Matrix * pMat)
	{
		Matrix mat = *pMat;
		Vector3 v;
		float w = 1.0f;
		v.x = x * mat.m[0][0] + y * mat.m[1][0] + z * mat.m[2][0] + w * mat.m[3][0];
		v.y = x * mat.m[0][1] + y * mat.m[1][1] + z * mat.m[2][1] + w * mat.m[3][1];
		v.z = x * mat.m[0][2] + y * mat.m[1][2] + z * mat.m[2][2] + w * mat.m[3][2];
		w = x * mat.m[0][3] + y * mat.m[1][3] + z * mat.m[2][3] + w * mat.m[3][3];
		if (fabs(w) > EPSILON)
		{
			v.x /= w;
			v.y /= w;
			v.z /= w;
		}
		return v;
	}
	Vector3 Vector3::TransformNormal(Matrix * pMat)
	{
		Matrix mat = *pMat;
		Vector3 v;
		v.x = x * mat.m[0][0] + y * mat.m[1][0] + z * mat.m[2][0];
		v.y = x * mat.m[0][1] + y * mat.m[1][1] + z * mat.m[2][1];
		v.z = x * mat.m[0][2] + y * mat.m[1][2] + z * mat.m[2][2];
		return v;
	}
	bool Vector3::ZeroVector()
	{
		return this->sqrtLength() < EPSILON;
	}
	float Vector3::Dot(Vector3 v1, Vector3 v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}
	Vector3 Vector3::cross(Vector3 v1, Vector3 v2)
	{
		return Vector3(v1.y * v2.z - v1.z * v2.y,
						v1.z * v2.x - v1.x * v2.z,
						v1.x * v2.y - v1.y * v2.x);
	}
	Vector3 Vector3::vecMin(Vector3 v1, Vector3 v2)
	{
		Vector3 vec;
		vec.x = (v1.x > v2.x) ? v2.x : v1.x;
		vec.y = (v1.y > v2.y) ? v2.y : v1.y;
		vec.z = (v1.z > v2.z) ? v2.z : v1.z;
		return vec;
	}
	Vector3 Vector3::vecMax(Vector3 v1, Vector3 v2)
	{
		Vector3 vec;
		vec.x = (v1.x < v2.x) ? v2.x : v1.x;
		vec.y = (v1.y < v2.y) ? v2.y : v1.y;
		vec.z = (v1.z < v2.z) ? v2.z : v1.z;
		return vec;
	}
	Vector3 operator*(float f, Vector3 vec)
	{
		return vec * f;
	}
	Matrix operator*(float f, Matrix mat)
	{
		Matrix newMat;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				newMat.m[i][j] = mat.m[i][j] * f;
			}
		}
		return newMat;
	}
	bool Matrix::operator==(Matrix mat)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (fabs((*this).m[i][j] - mat.m[i][j]) > EPSILON) return false;
			}
		}
		return true;
	}
	bool Matrix::operator!=(Matrix mat)
	{
		return !((*this) == mat);
	}
	Matrix Matrix::operator+(Matrix mat)
	{
		Matrix newMat;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				newMat.m[i][j] = (*this).m[i][j] + mat.m[i][j];
			}
		}
		return newMat;
	}
	Matrix Matrix::operator-(Matrix mat)
	{
		Matrix newMat;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				newMat.m[i][j] = (*this).m[i][j] - mat.m[i][j];
			}
		}
		return newMat;
	}
	Matrix Matrix::operator*(float f)
	{
		Matrix newMat;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				newMat.m[i][j] = (*this).m[i][j] * f;
			}
		}
		return newMat;
	}
	Matrix Matrix::operator*(Matrix mat)
	{
		Matrix newMat;
		
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				newMat.m[i][j] = 0.f;
				for (int k = 0; k < 4; k++)
				{
					newMat.m[i][j] += ((*this).m[i][k] * mat.m[k][j]);
				}
			}
		}
		return newMat;
	}
	Matrix Matrix::operator-()
	{
		Matrix mat;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				mat.m[i][j] = m[i][j] * -1;
			}
		}
		return mat;
	}
	Matrix Matrix::Identity()
	{
		Matrix newMat;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				newMat.m[i][j] = ((i == j) ? 1.f : 0.f);
			}
		}
		return newMat;
	}
	Matrix Matrix::Transpose()
	{
		Matrix newMat;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				newMat.m[i][j] = (*this).m[j][i];
			}
		}
		return newMat;
	}
	Matrix Matrix::Inverse(float& fDet)
	{
		fDet = Determinent(4);
		if (fabs(fDet) < EPSILON)
		{
			fDet = 0.0f;
			return Matrix::Identity();
		}
		return (1.f / fDet) * Adjoint();
	}

	float Matrix::Determinent(int n)
	{
		if (n == 2)
		{
			return (*this).m[0][0] * (*this).m[1][1] - (*this).m[0][1] * (*this).m[1][0];
		}

		float fDet = 0.0f;
		for (int i = 0; i < n; ++i)
		{
			fDet += ((*this).m[0][i] * Cofactor(0, i, n));
		}
		return fDet;
	}

	Matrix Matrix::Adjoint()
	{
		Matrix mat;

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				mat.m[i][j] = Cofactor(j, i, 4);
			}
		}

		return mat;
	}

	float Matrix::Cofactor(int nRow, int nCol, int size)
	{
		float fConst = 1.0f;
		if ((nRow + nCol) % 2 == 1)
			fConst = -1.0f;

		return fConst * Minor(nRow, nCol, size);
	}

	float Matrix::Minor(int nRow, int nCol, int size)
	{
		Matrix mat = Matrix::Identity();
		int nMinorRow = 0;
		int nMinorCol = 0;

		for (int i = 0; i < 4; ++i)
		{
			if (i == nRow)
				continue;

			nMinorCol = 0;
			for (int j = 0; j < 4; ++j)
			{
				if (j == nCol)
					continue;
				mat.m[nMinorRow][nMinorCol] = (*this).m[i][j];
				++nMinorCol;
			}

			++nMinorRow;
		}

		return mat.Determinent(size-1);
	}


	Matrix View(Vector3 * pEye, Vector3* pUp, Vector3* pLookAt)
	{
		Vector3 l = (*pLookAt - *pEye).Normalize();
		Vector3 r = Vector3::cross(*pUp, l).Normalize();
		Vector3 u = Vector3::cross(l, r).Normalize();

		Matrix viewMat = Matrix::Identity();

		viewMat.m[0][0] = r.x; viewMat.m[0][1] = u.x; viewMat.m[0][2] = l.x;
		viewMat.m[1][0] = r.y; viewMat.m[1][1] = u.y; viewMat.m[1][2] = l.y;
		viewMat.m[2][0] = r.z; viewMat.m[2][1] = u.z; viewMat.m[2][2] = l.z;
		viewMat.m[3][0] = -Vector3::Dot(r, *pEye);
		viewMat.m[3][1] = -Vector3::Dot(u, *pEye);
		viewMat.m[3][2] = -Vector3::Dot(l, *pEye);
		return viewMat;
	}
	Matrix Proj(float fFovY, float fAspect, float fNearZ, float fFarZ)
	{
		Matrix projMat = Matrix::Identity();

		float fScaleY = 1.0f / tanf(fFovY / 2.0f);
		float fScaleX = fScaleY / fAspect;

		projMat.m[0][0] = fScaleX;
		projMat.m[1][1] = fScaleY;
		projMat.m[2][2] = fFarZ / (fFarZ - fNearZ);
		projMat.m[2][3] = 1.0f;
		projMat.m[3][2] = -(fFarZ * fNearZ) / (fFarZ - fNearZ);
		projMat.m[3][3] = 0.0f;

		return projMat;
	}
	Matrix Proj()
	{
		Matrix projMat = Matrix::Identity();
		projMat.m[2][2] = 0.f;
		return projMat;
	}
	Matrix Viewport(float fX, float fY, float fW, float fH, float fMinZ, float fMaxZ)
	{
		Matrix vpMat = Matrix::Identity();

		vpMat.m[0][0] = fW / 2.0f;
		vpMat.m[1][1] = -fH / 2.0f;
		vpMat.m[2][2] = fMaxZ - fMinZ;
		vpMat.m[3][0] = fX + fW / 2.0f;
		vpMat.m[3][1] = fY + fH / 2.0f;
		vpMat.m[3][2] = fMinZ;

		return vpMat;
	}
	Matrix Translation(float x, float y, float z)
	{
		return Translation(&Vector3(x, y, z));
	}
	Matrix Translation(Vector3 * pVec)
	{
		Matrix tMat = Matrix::Identity();
		tMat.m[3][0] = pVec->x;
		tMat.m[3][1] = pVec->y;
		tMat.m[3][2] = pVec->z;
		return tMat;
	}
	Matrix RotateX(float fAngle)
	{
		Matrix rxMat = Matrix::Identity();
		rxMat.m[1][1] = cosf(fAngle);
		rxMat.m[1][2] = sinf(fAngle);
		rxMat.m[2][1] = -sinf(fAngle);
		rxMat.m[2][2] = cosf(fAngle);
		return rxMat;
	}
	Matrix RotateY(float fAngle)
	{
		Matrix ryMat = Matrix::Identity();
		ryMat.m[0][0] = cosf(fAngle);
		ryMat.m[0][2] = -sinf(fAngle);
		ryMat.m[2][0] = sinf(fAngle);
		ryMat.m[2][2] = cosf(fAngle);
		return ryMat;
	}
	Matrix RotateZ(float fAngle)
	{
		Matrix rzMat = Matrix::Identity();
		rzMat.m[0][0] = cosf(fAngle);
		rzMat.m[0][1] = sinf(fAngle);
		rzMat.m[1][0] = -sinf(fAngle);
		rzMat.m[1][1] = cosf(fAngle);
		return rzMat;
	}
	Matrix RotateXYZ(Vector3 vec)
	{
		Matrix rotMat = Matrix::Identity();
		rotMat = RotateX(vec.x) * RotateY(vec.y) * RotateZ(vec.z);
		return rotMat;
	}
	Matrix Scale(float x, float y, float z)
	{
		Matrix sMat = Matrix::Identity();
		sMat.m[0][0] = x;
		sMat.m[1][1] = y;
		sMat.m[2][2] = z;
		return sMat;
	}
	Matrix Scale(Vector3 vec)
	{
		return Scale(vec.x, vec.y, vec.z);
	}
	float Clamp(float f, float max, float min)
	{
		if (f > max)
			f = max;
		else if (f < min)
			f = min;

		return f;
	}
}
