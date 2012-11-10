/**
* @file matrix.h
* @brief Matrix Class 
*/

#pragma once
#include <memory.h>
#include <cmath>
#include <iostream>
#include <algorithm>
#include "function.h"
using namespace std;


class _POINT{
	/**
	* @brief 2D Cartesian Coordinate x, y�� ǥ��
	*/
public:
	///x��ǥ
	double x;
	///y��ǥ
	double y;
public:
	/**
	* @brief ��ǥ (x, y)�� ����
	* @param x : x ��ǥ
	* @param y : y ��ǥ
	*/
	_POINT(double x, double y){
		setPoint(x, y);
	}

	_POINT(_POINT& p){
		this->x = p.getX();
		this->y = p.getY();
	}
	/**
	* @brief setter for (x, y)
	*/
	void setPoint(double x, double y){
		this->x = x;
		this->y = y;
	}
	/**
	* @brief getter for x
	*/
	double getX(){return x;}
	/**
	* @brief getter for y
	*/
	double getY(){return y;}
};

class MATRIX2D{
	/**
	* @brief 2���� ��� ǥ��
	*/
public:
	MATRIX2D(){

	}
	/**
	* @brief copy constructor
	*/
	MATRIX2D(MATRIX2D& mat){
		memcpy(this->a, mat.a, sizeof(a));
	}
	/**
	* @breif double�� 2���� �迭�� ���ȭ
	* @param a : 2���� �迭 (2 * 2)
	*/
	MATRIX2D(double a[][2]){
		memcpy(this->a, a, sizeof(this->a)); //this->a�̱� ������ ������
	}

	/**
	* @brief double�� 1���� �迭�� 2���� ���ȭ
	* @param t : 1���� �迭 (1 * 4)
	* @param n : ũ��(must be 4)
	*/
	MATRIX2D(double t[], int n){
		if(n == 4){
			double na[2][2] = { t[0], t[1], t[2], t[3] };
			memcpy(this->a, na, sizeof(this->a));
		}
	}
	
	/**
	* @breif get Determinant
	*/
	double getDet(){
		return a[1][1]*a[2][2] - a[1][2]*a[2][1];
	}

	/**
	* @brief Inverse ���� ����, Det�� 0�̸� false
	*/
	bool isInversible(){
		if(fabs(getDet()) <= EPS) return false;
		return true;
	}

	/**
	* @brief this�� ������� ���� ��ȯ
	*/
	MATRIX2D inverse(){
		double k = 1.0 / getDet();
		MATRIX2D tmp = *this;
		swap(tmp.a[1][1], tmp.a[2][2]);
		swap(tmp.a[1][2], tmp.a[2][1]);
		tmp.a[1][1] = tmp.a[1][1]*k;
		tmp.a[1][2] = -tmp.a[1][2]*k; 
		tmp.a[2][1] = -tmp.a[2][1]*k;
		tmp.a[2][2] = tmp.a[2][2]*k;
		return tmp;
	}
private:
	///��� ���� (2*2)
	double a[2][2];
};

class MATRIX3D
{
	/**
	* @brief 3���� ��� ǥ��
	*/
public:
	MATRIX3D():det(0.0), det_flag(false), isSet(false){

	}
	/**
	* @brief copy constructor, calculate determinant in advance.
	*/
	MATRIX3D(MATRIX3D& mat){
		memcpy(this->A, mat.A, sizeof(A));
		det_flag = false;
		isSet = true;
		det = calcDet();
	}

	/**
	* @breif double�� 3���� �迭�� ���ȭ
	* @param a : 3���� �迭 (3 * 3)
	*/
	MATRIX3D(double a[][3]){
		memcpy(this->A, a, sizeof(this->A));
		isSet = true;
		det = calcDet();
	}

	/**
	* @brief Inverse ���� ����, Det�� 0�̸� false
	*/
	bool isInversible(){
		if(isSet){
			if(fabs(getDet()) <= EPS) return false;
			else return true;
		}
		return false;
	}

	/**
	* @breif get Determinant
	*/
	double getDet(){
		if(det_flag) return det;
		return calcDet();
	}

	/**
	* @breif get cofactor of (_i, _j)
	*/
	double getCofactor(int _i, int _j){
		double v[4];
		int k = 0;
		for(int i = 0; i < 3; i++){
			if(_i == i) continue;
			for(int j = 0; j < 3; j++){
				if(_j == j) continue;
				v[k++] = A[i][j];
			}
		}
		MATRIX2D met(v, 4);
		return met.getDet() * pow(-1, (double)(_i + _j));
	}


	void set(int i, int j, double v){
		A[i][j] = v;
	}

	/**
	* @breif get an element of (i , j) in this Matrix
	*/
	double get(int i, int j){
		return A[i][j];
	}

	/**
	* @breif ������� ���� ����
	*/
	MATRIX3D inverse(){
		double a = A[0][0];	double b = A[0][1];	double c = A[0][2];
		double d = A[1][0]; double e = A[1][1]; double f = A[1][2];
		double g = A[2][0]; double h = A[2][1]; double i = A[2][2];
		
		double m[3][3] = { e*i-f*h, c*h-b*i, b*f-c*e,
						   f*g-d*i, a*i-c*g, c*d-a*f,
						   d*h-e*g, b*g-a*h, a*e-b*d };

		MATRIX3D INV(m);
		
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++)
				INV.set(i, j, INV.get(i, j) / det);
		return INV;
	}

	/**
	* @breif �Է����� ������ ��ǥ�� ���ؼ� AffineTransform�� �����Ͽ� ��ȯ�� ��ǥ�� �����Ѵ�.
	* @param input : �����Ǳ� ���ϴ� ��ǥ 
	*/
	_POINT AffineTransform(_POINT& input){
		double v = input.getX()*get(0, 0) + input.getY()*get(1, 0) + 1*get(2, 0);
		double w = input.getX()*get(0, 1) + input.getY()*get(1, 1) + 1*get(2, 1);
		return _POINT(v, w);
	}
private:

	///Determinant ��� ����, �̸� ����ϱ� ����
	bool det_flag;

	///����� ���� �����Ǿ����� ����
	bool isSet;

	///���� ��� ��
	double A[3][3];

	///Determinant
	double det;

	///�Ǻ����� ����ϱ� ���� �Լ�
	double calcDet(){
		if(isSet){
			det_flag = true;
			return A[0][0]*A[1][1]*A[2][2] + A[0][1]*A[1][2]*A[2][0] + A[0][2]*A[1][0]*A[2][1] 
				- A[0][0]*A[1][2]*A[2][1] - A[0][1]*A[1][0]*A[2][2] - A[0][2]*A[1][1]*A[2][0];
		}else return 0.0;
	}
};