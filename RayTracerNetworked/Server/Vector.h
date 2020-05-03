#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#include <iostream>
#include <string>
#include "math.h"

class Vector {

public:

	Vector() {
		m_x = 0;
		m_y = 0;
		m_z = 0;
	}

	Vector(const float &x, const float &y, const float &z) {
		m_x = x;
		m_y = y;
		m_z = z;
	}

	Vector(const Vector &v) {
		m_x = v.m_x;
		m_y = v.m_y;
		m_z = v.m_z;
	}

	float DotProduct(const Vector &v) const {
		return (m_x * v.m_x) + (m_y * v.m_y) + (m_z * v.m_z);
	}

	Vector Scale(const float &f) {
		return *this * f;
	}

	float Scaler(const Vector &v) const {
		return DotProduct(v);
	}

	Vector CrossProduct(const Vector &v) const {
		float x = (m_y * v.m_z) - (m_z * v.m_y);
		float y = (m_z * v.m_x) - (m_x * v.m_z);
		float z = (m_x * v.m_y) - (m_y * v.m_x);
		return Vector(x, y, z);
	}

	float Magnitude() const {

		return sqrtf(m_x * m_x + m_y * m_y + m_z * m_z);
	}

	void PrintVector()
	{
		//Don't have to do the too string here i just it cause i can.
		std::cout << "X:" + std::to_string(m_x) + " Y:" + std::to_string(m_y) + " Z:" + std::to_string(m_z) + "\n";
	}

	Vector Normalize() const {
		Vector Test(*this);
		float inverse = 1 / Magnitude();
		if (Magnitude() == 0)
		{
			inverse = 1 / 1;
		}

		Test.m_x *= inverse;
		Test.m_y *= inverse;
		Test.m_z *= inverse;

		return Test;
	}

	Vector Lerp(const Vector &v, const float &t) const {
		float x = (1 - t) * m_x + t * v.m_x;
		float y = (1 - t) * m_y + t * v.m_y;
		float z = (1 - t) * m_z + t * v.m_z;

		return Vector(x, y, z);
	}

	Vector Negitve() const {
		return Vector(-m_x, -m_y, -m_z);
	}

	//Operator overloads
	//ADD
	Vector operator+(const Vector &v) {
		Vector rtn(m_x + v.m_x, m_y + v.m_y, m_z + v.m_z);
		return rtn;
	}

	Vector& operator+=(const Vector &v) {
		//Vector rtn(m_x + v.m_x, m_y + v.m_y, m_z + v.m_z);
		this->m_x += v.m_x;
		this->m_y += v.m_y;
		this->m_z += v.m_z;
		return *this;
	}

	Vector operator+(const float &s) {
		Vector rtn(m_x + s, m_y + s, m_z + s);
		return rtn;
	}

	Vector& operator+=(const float &s) {
		this->m_x += s;
		this->m_y += s;
		this->m_z += s;
		return *this;
	}
	//SUB
	Vector operator-(const Vector &v) {
		Vector rtn(m_x - v.m_x, m_y - v.m_y, m_z - v.m_z);
		return rtn;
	}

	Vector& operator-=(const Vector &v) {
		this->m_x -= v.m_x;
		this->m_y -= v.m_y;
		this->m_z -= v.m_z;
		return *this;
	}

	Vector& operator-(const float &s) {
		Vector rtn(m_x - s, m_y - s, m_z - s);
		return rtn;
	}

	Vector& operator-=(const float &s) {
		this->m_x -= s;
		this->m_y -= s;
		this->m_z -= s;
		return *this;
	}
	//MULTI
	Vector operator*(const Vector &v) {
		Vector rtn(m_x * v.m_x, m_y * v.m_y, m_z * v.m_z);
		return rtn;
	}

	Vector& operator*=(const Vector &v) {
		this->m_x *= v.m_x;
		this->m_y *= v.m_y;
		this->m_z *= v.m_z;
		return *this;
	}

	Vector operator*(const float &f) {
		Vector rtn(m_x * f, m_y * f, m_z * f);
		return rtn;
	}

	Vector& operator*=(const float &f) {
		this->m_x *= f;
		this->m_y *= f;
		this->m_z *= f;
		return *this;
	}
	//DIV
	Vector operator/(const Vector &v) {
		Vector rtn(m_x / v.m_x, m_y / v.m_y, m_z / v.m_z);
		return rtn;
	}

	Vector& operator/=(const Vector &v) {
		this->m_x /= v.m_x;
		this->m_y /= v.m_y;
		this->m_z /= v.m_z;
		return *this;
	}

	Vector operator/(const float &f) {
		Vector rtn(m_x / f, m_y / f, m_z / f);
		return rtn;
	}

	Vector& operator/=(const float &f) {
		this->m_x /= f;
		this->m_y /= f;
		this->m_z /= f;
		return *this;
	}

	//Compare
	bool operator!=(const Vector &v) {
		if (m_x != v.m_x && m_y != v.m_y && m_z != v.m_z)
		{
			return true;
		}
		return false;
	}

	bool operator==(const Vector &v) {
		if (*this != v) {
			return false;
		}
		return true;
	}

	float m_x;
	float m_y;
	float m_z;
};

#endif //VECTOR_H_INCLUDED
