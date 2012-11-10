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
	* @brief 2D Cartesian Coordinate x, y를 표현
	*/
public:
	///x좌표
	double x;
	///y좌표
	double y;
public:
	/**
	* @brief 좌표 (x, y)를 설정
	* @param x : x 좌표
	* @param y : y 좌표
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
	* @brief 2차원 행렬 표현
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
	* @breif double형 2차원 배열을 행렬화
	* @param a : 2차원 배열 (2 * 2)
	*/
	MATRIX2D(double a[][2]){
		memcpy(this->a, a, sizeof(this->a)); //this->a이기 때문에 괜찮음
	}

	/**
	* @brief double형 1차원 배열을 2차원 행렬화
	* @param t : 1차원 배열 (1 * 4)
	* @param n : 크기(must be 4)
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
	* @brief Inverse 가능 여부, Det가 0이면 false
	*/
	bool isInversible(){
		if(fabs(getDet()) <= EPS) return false;
		return true;
	}

	/**
	* @brief this의 역행렬을 구해 반환
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
	///행렬 원소 (2*2)
	double a[2][2];
};

class MATRIX3D
{
	/**
	* @brief 3차원 행렬 표현
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
	* @breif double형 3차원 배열을 행렬화
	* @param a : 3차원 배열 (3 * 3)
	*/
	MATRIX3D(double a[][3]){
		memcpy(this->A, a, sizeof(this->A));
		isSet = true;
		det = calcDet();
	}

	/**
	* @brief Inverse 가능 여부, Det가 0이면 false
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
	* @breif 역행렬을 구해 리턴
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
	* @breif 입력으로 들어오는 좌표에 대해서 AffineTransform을 수행하여 변환된 좌표를 리턴한다.
	* @param input : 변형되기 원하는 좌표 
	*/
	_POINT AffineTransform(_POINT& input){
		double v = input.getX()*get(0, 0) + input.getY()*get(1, 0) + 1*get(2, 0);
		double w = input.getX()*get(0, 1) + input.getY()*get(1, 1) + 1*get(2, 1);
		return _POINT(v, w);
	}
private:

	///Determinant 계산 여부, 미리 계산하기 위함
	bool det_flag;

	///행렬의 값이 설정되었는지 여부
	bool isSet;

	///실제 행렬 값
	double A[3][3];

	///Determinant
	double det;

	///판별식을 계산하기 위한 함수
	double calcDet(){
		if(isSet){
			det_flag = true;
			return A[0][0]*A[1][1]*A[2][2] + A[0][1]*A[1][2]*A[2][0] + A[0][2]*A[1][0]*A[2][1] 
				- A[0][0]*A[1][2]*A[2][1] - A[0][1]*A[1][0]*A[2][2] - A[0][2]*A[1][1]*A[2][0];
		}else return 0.0;
	}
};