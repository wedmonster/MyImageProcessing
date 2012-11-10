/**
*	@file function.h
*/
#pragma once

///반올림 매크로
#define ROUND(x) ((int) ((x) + 0.5))

///R채널 정의
#define R 0

///G채널 정의
#define G 1

///B채널 정의
#define B 2

///부동 소수점 계산을 위한 Epsilon
#define EPS 1e-6

///파이 상수 정의
#define M_PI 3.141592653589793

///0~255의 값으로 설정 함수
int CRIP(double val);



//#ifndef FUNCTION_H
//#define FUNCTION_H



//#endif


/*
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
	double v = input.getX()*T.get(0, 0) + input.getY()*T.get(1, 0) + 1*T.get(2, 0);
	double w = input.getX()*T.get(0, 1) + input.getY()*T.get(1, 1) + 1*T.get(2, 1);
	return _POINT(v, w);
}

_POINT ScaleT(_POINT& input, MATRIX3D inv){
	return AffineTransform(input, inv);	
}



RGBQUAD NoInterpolation(_POINT& input, CxImage& img)
{
	int v = (int) input.getX();
	int w = (int) input.getY();
	return img.GetPixelColor(v, w);
}

RGBQUAD NearestNeihborInterpolation(_POINT& input, CxImage& img)
{
	int v = ROUND(input.getX());
	int w = ROUND(input.getY());
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
	return ROUND((1-a)*(1-b)*GetChannelColor(l, k, img, channel) + 
					a*(1-b)*GetChannelColor(l+1, k, img, channel) +
						(1-a)*b*GetChannelColor(l, k+1, img, channel) +
							a*b*GetChannelColor(l+1, k+1, img, channel));
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
	int l = floor(input.getX());
	int k = floor(input.getY());
	double a = input.getX() - l;
	double b = input.getY() - k;
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

*/