
#include "ximage.h"
#include <cmath>
#include <iostream>
#include <memory.h>
#include <algorithm>
using namespace std;

#define ROUND(x) ((int) ((x) + 0.5))
#define R 0
#define G 1
#define B 2
#define EPS 1e-6



typedef struct _POINT{
	double x;
	double y;
	_POINT(double x, double y){
		setPoint(x, y);
	}
	void setPoint(double x, double y){
		this->x = x;
		this->y = y;
	}
}_POINT;

class MATRIX2D{
public:
	MATRIX2D(){

	}
	MATRIX2D(MATRIX2D& mat){
		memcpy(this->a, mat.a, sizeof(a));
	}
	MATRIX2D(double a[][2]){
		memcpy(this->a, a, sizeof(this->a));
	}
	MATRIX2D(double t[], int n){
		if(n == 4){
			double na[2][2] = { t[0], t[1], t[2], t[3] };
			memcpy(this->a, na, sizeof(this->a));
		}
	}
	
	double getDet(){
		return a[1][1]*a[2][2] - a[1][2]*a[2][1];
	}
	bool isInversible(){
		if(fabs(getDet()) <= EPS) return false;
		else return true;
	}
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
	double a[2][2];
};

class MATRIX3D
{
public:
	MATRIX3D():det(0.0), det_flag(false), isSet(false){

	}

	MATRIX3D(MATRIX3D& mat){
		memcpy(this->A, mat.A, sizeof(A));
		det_flag = false;
		isSet = true;
		det = calcDet();
	}
	MATRIX3D(double a[][3]){
		memcpy(this->A, a, sizeof(this->A));
		isSet = true;
		det = calcDet();
	}
	
	bool isInversible(){
		if(isSet){
			if(fabs(getDet()) <= EPS) return false;
			else return true;
		}else return false;
	}
	double getDet(){
		if(det_flag) return det;
		else calcDet();
	}
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
	double get(int i, int j){
		return A[i][j];
	}
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
private:
	bool det_flag;
	bool isSet;
	double A[3][3];
	double det;
	double calcDet(){
		if(isSet){
			det_flag = true;
			return A[0][0]*A[1][1]*A[2][2] + A[0][1]*A[1][2]*A[2][0] + A[0][2]*A[1][0]*A[2][1] 
				- A[0][0]*A[1][2]*A[2][1] - A[0][1]*A[1][0]*A[2][2] - A[0][2]*A[1][1]*A[2][0];
		}else return 0.0;
	}
};
RGBQUAD WHITE()
{
	RGBQUAD white;
	white.rgbBlue = 255;
	white.rgbGreen = 255;
	white.rgbRed = 255;
	return white;
}

_POINT AffineTransform(_POINT& input, MATRIX3D& T){
	//T must be inversed.
	double v = input.x*T.get(0, 0) + input.y*T.get(1, 0) + 1*T.get(2, 0);
	double w = input.x*T.get(0, 1) + input.y*T.get(1, 1) + 1*T.get(2, 1);
	return _POINT(v, w);
}

_POINT ScaleT(_POINT& input, MATRIX3D inv){
	return AffineTransform(input, inv);	
}

MATRIX3D ScaleT_Matrix(int Cx, int Cy){
	double m[3][3] = { Cx,  0, 0,
						0, Cy, 0,
						0,  0, 1 };
	MATRIX3D mat(m);
	if(mat.isInversible())	return mat.inverse();
	else return mat;
}

RGBQUAD NoInterpolation(_POINT& input, CxImage& img)
{
	int v = (int) input.x;
	int w = (int) input.y;
	return img.GetPixelColor(v, w);
}

RGBQUAD NearestNeihborInterpolation(_POINT& input, CxImage& img)
{
	int v = ROUND(input.x);
	int w = ROUND(input.y);
	if(v < 0 || v >= img.GetWidth() || w < 0 || w >= img.GetHeight())
		return WHITE();
	else return img.GetPixelColor(v, w);
}

int GetChannelColor(int x, int y, CxImage& img, int channel)
{
	switch(channel){
	case R:
		return img.GetPixelColor(x, y).rgbRed;
	case G:
		return img.GetPixelColor(x, y).rgbGreen;
	case B:
		return img.GetPixelColor(x, y).rgbBlue;
	}
}

int CalcBilinear(int l, int k, double a, double b, CxImage& img, int channel)
{
	return (1-a)*(1-b)*GetChannelColor(l, k, img, channel) + 
				a*(1-b)*GetChannelColor(l+1, k, img, channel) +
					(1-a)*b*GetChannelColor(l, k+1, img, channel) +
						a*b*GetChannelColor(l+1, k+1, img, channel);
}

RGBQUAD SetRGB(int r, int g, int b)
{
	RGBQUAD rgb;
	rgb.rgbRed = r;
	rgb.rgbGreen = g;
	rgb.rgbBlue = b;
	return rgb;
}

RGBQUAD BilinearInterpolation(_POINT& input, CxImage& img)
{
	int l = floor(input.x);
	int k = floor(input.y);
	double a = input.x - l;
	double b = input.y - k;
	if(l < 0 || l >= img.GetWidth() || k < 0 || k >= img.GetHeight() ||
		l+1 < 0 || l + 1 >= img.GetWidth() || k + 1 < 0 || k + 1 >= img.GetHeight())
		return WHITE();
	
	int red = CalcBilinear(l, k, a, b, img, R);
	int green = CalcBilinear(l, k, a, b, img, G);
	int blue = CalcBilinear(l, k, a, b, img, B);
		
	return SetRGB(red, green, blue);
}

int getMax(int x, int y, int k, CxImage* img)
{
	int _max = 0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(k == R) 
				_max = max(_max, img->GetPixelColor(x + i - 1, y + i - 1).rgbRed);
			else if(k == G)
				_max = max(_max, img->GetPixelColor(x + i - 1, y + i - 1).rgbGreen);
			else if(k == B)
				_max = max(_max, img->GetPixelColor(x + i - 1, y + i - 1).rgbBlue);
		}
	}
	return _max;
}
int getMin(int x, int y, int k, CxImage* img)
{
	int _min = 0xff;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(k == R) 
				_min = min(_min, img->GetPixelColor(x + i - 1, y + i - 1).rgbRed);
			else if(k == G)
				_min = min(_min, img->GetPixelColor(x + i - 1, y + i - 1).rgbGreen);
			else if(k == B)
				_min = min(_min, img->GetPixelColor(x + i - 1, y + i - 1).rgbBlue);
		}
	}
	return _min;
}
int partition(int* A, int p, int r){
	int x = A[r];
	int i = p - 1;
	for(int j = p; j<=r-1; j++)
		if(A[j] <= x) 
			swap(A[++i], A[j]);
	swap(A[i+1], A[r]);

	return i + 1;	
}

int select(int* A, int p, int r, int i){
	if(p == r) return A[p];
	int q = partition(A, p, r);

	int k = q - p + 1;

	if(i < k) return select(A, p, q - 1, i);
	else if(i == k) return A[q];
	else return select(A, q + 1, r, i - k);
}

int getMedian(int x, int y, int k, CxImage* img)
{
	int _min = 0xff;
	int arr[9];
	int idx = 0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(k == R) 
				arr[idx++] = img->GetPixelColor(x + i - 1, y + i - 1).rgbRed;
			else if(k == G)
				arr[idx++] = img->GetPixelColor(x + i - 1, y + i - 1).rgbGreen;
			else if(k == B)
				arr[idx++] = img->GetPixelColor(x + i - 1, y + i - 1).rgbBlue;
		}
	}
	//sort(arr, arr+9);
	return select(arr, 0, 8, 4);
	//return arr[4];
}

CxImage MaxFilter(CxImage* img)
{
	CxImage tmp;
	tmp.Copy(*img);
	for(int y = 1; y < img->GetHeight()-1; y++){
		for(int x = 1; x < img->GetWidth()-1; x++){
			int red = getMax(x, y, R, img);
			int green = getMax(x, y, G, img);
			int blue = getMax(x, y, B, img);		

			tmp.SetPixelColor(x, y, RGB(red, green, blue));
		}
	}
	return tmp;
}

CxImage MinFilter(CxImage* img)
{
	CxImage tmp;
	tmp.Copy(*img);
	for(int y = 1; y < img->GetHeight()-1; y++){
		for(int x = 1; x < img->GetWidth()-1; x++){
			int red = getMin(x, y, R, img);
			int green = getMin(x, y, G, img);
			int blue = getMin(x, y, B, img);		

			tmp.SetPixelColor(x, y, RGB(red, green, blue));
		}
	}
	return tmp;
}

CxImage MedianFilter(CxImage* img)
{
	CxImage tmp;
	tmp.Copy(*img);
	for(int y = 1; y < img->GetHeight()-1; y++){
		for(int x = 1; x < img->GetWidth()-1; x++){
			int red = getMedian(x, y, R, img);
			int green = getMedian(x, y, G, img);
			int blue = getMedian(x, y, B, img);		

			tmp.SetPixelColor(x, y, RGB(red, green, blue));
		}
	}
	return tmp;
}