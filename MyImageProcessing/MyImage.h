/**
* @mainpage	MyImage
*
* @file MyImage.h
* @brief MyImage 클래스 선언
*/

#pragma once
#include "ximage.h"
#include "matrix.h"

class MyImage
{
/**
* @class MyImage
* @author Jung Jinhong
* @date 2012-11-10
* @brief 각종 영상처리 기법 구현
*/
public:
	/**
	* @breif 기본 생성자 CxImage에 동적할당은 하지만 아무 기능 수행 못함
	* @see MyImage(void)
	* @see MyImage(CxImage& img)
	* @see MyImage(MyImage& m_img)
	* @see MyImage(int width, int height, int wbpp)
	*/
	MyImage(void);

	/**
	* @breif CxImage를 받아서 Copy하며 생성
	* @see MyImage(void)
	* @see MyImage(CxImage& img)
	* @see MyImage(MyImage& m_img)
	* @see MyImage(int width, int height, int wbpp)
	* @param img : 원본 CxImage
	*/
	MyImage(CxImage& img);

	/**
	* @breif 복사 생성자
	* @see MyImage(void)
	* @see MyImage(CxImage& img)
	* @see MyImage(MyImage& m_img)
	* @see MyImage(int width, int height, int wbpp)
	* @param m_img : 원본 MyImage
	*/
	MyImage(MyImage& m_img);

	/**
	* @breif 새로운 CxImage(width byheight)를 만든다.
	* @param width : 너비 (pixel)
	* @param height : 높이 (piexl)
	* @param wbbp : bbp
	* @see MyImage(void)
	* @see MyImage(CxImage& img)
	* @see MyImage(MyImage& m_img)
	*/
	MyImage(int width, int height, int wbpp);

	/**
	* A destructor. 동적 할당 했던 CxImage 해제
	*/
	~MyImage(void);
	
	/**
	* @brief CxImage 포인터를 반환한다.
	*/
	CxImage* GetCxImage();
	
	/**
	* @brief lpszPathName의 이미지를 불러와 CxImage에 Load한다.
	* @param lpszPathName : 파일 경로
	*/
	bool Load(LPCTSTR lpszPathName);

	/**
	* @brief 이미지를 가로 w배, 세로 h배 Scale(확대/축소)한다. 
	* @param w : 가로 비율
	* @param h : 세로 비율
	*/
	MyImage ScaleImage(double w, double h);

	/**
	* @brief 이미지를 Gray-Scale하여 반환한다.
	* @return Gray-Scaled image.
	*/
	MyImage GrayScaleImage();

	/**
	* @brief 이미지 색상을 반전시킨다. 
	* @return Inversed image
	*/
	MyImage InverseImage();

	/**
	* @brief threshold 값을 기준으로 이진화한다. 
	* @param threshold : 기준값
	* @return Binarizied image
	*/
	MyImage BinarizeImage(int threshold);

	/**
	* @brief Histogram Equalization을 수행하고 변환 영상을 리턴한다. 
	* @return Histogram Equalized image
	*/
	MyImage HistogramEqualizeImage();

	/**
	* @brief 선명화(Sharpening) 기법 : Laplacian Filter
	* @return Filtered image by Laplacian
	*/	
	MyImage LaplacianFilterImage();

	/**
	* @brief 선명화(Sharpening) 기법 : High-Boost Filter
	* @return Filtered image by High-Boost
	*/
	MyImage HighBoostFilterImage(const double A);
	
	/**
	* @brief 선명화(Sharpening) 기법 : Sobel Filter
	* @return Filtered image by Sobel
	*/
	MyImage SobelFilterImage();

	/**
	* @brief 평활화(Smoothing) 기법 : Linear Filter
	* @return Filtered image by Linear
	*/
	MyImage SmoothingLinearFilterImage();

	/**
	* @brief Order-Statistics 기법 : Max Filter
	* @return Filtered image by Max
	*/
	MyImage MaxFilterImage();

	/**
	* @brief Order-Statistics 기법 : Min Filter
	* @return Filtered image by Min
	*/
	MyImage MinFilterImage();

	/**
	* @brief Order-Statistics 기법 : Median Filter
	* @return Filtered image by Median
	*/
	MyImage MedianFilterImage();

	/**
	* @brief Order-Statistics 기법 : Mean Filter
	* @return Filtered image by Mean
	*/
	MyImage MeanFilterImage();

	/**
	* @brief 영상의 중점을 중심으로 극좌표계(r, theta)로 변환한 이미지를 반환한다.
	* 정사각형 이미지만 들어온다고 가정한다.
	* @return image in Polar-coordination
	*/
	MyImage TransformIntoPolar();

	/**
	* @brief 총 크기 r/root(2) by r/root(2)이고 (r/root(2), r/root(2))이 중심인 직각좌표계로 변환한 이미지를 반환한다. r은 이미지의 height이다. 
	* @return image in Cartecian-coordination
	*/
	MyImage TransformIntoCartecian();

	/**
	* @brief 지수승 t로 power-law를 적용한다.
	* @return Power-Lawed image
	*/
	MyImage PowerLawImage(double t);

private:
	///이미지를 저장하기 위한 CxImage
	CxImage* image;
	
	/**
	* @brief 현재 이미지를 Trasform계수(3차원 행렬)에 의해 변형하여 newImage에 저장한다. 내부적으로 AffineTransform를 수행한다.
	* @param newImage : 변형된 이미지를 저장
	* @param mat : Transform계수, Forward Mapping으로 넘겨준다. - 주로 쓰이는 것은 따로 정의해야함
	*/
	void transform(MyImage& newImage, MATRIX3D& mat);
	
	/**
	* @brief input에 대한 Inverse Mapping시 Bilinear Interpolation 방식으로 픽셀 값을 가져온다. 
	* @param input : Coordinate in destination image
	*/
	RGBQUAD bilinearInterpolation(_POINT& input);

	/**
	* @brief Bilinear Interpolation을 위한 보조 계산 함수
	*/
	int calcBilinear(int l, int k, double a, double b, int channel);

	/**
	* @brief RGB중 하나의 채널에서 (x, y)의 픽셀 값을 리턴한다. 
	* @param x : x 좌표
	* @param y : y 좌표
	* @param channel : R(0), G(1), B(2) in function.h
	* @return 픽셀값(int, 0x00~0xff)
	*/
	int getChannelColor(int x, int y, int channel);

	/**
	* @brief 각 채널의 픽셀값을 받아서 RGBQUAD로 반환
	* @param r : R채널의 값(int, 0x00~0xff)
	* @param g : G채널의 값(int, 0x00~0xff)
	* @param b : B채널의 값(int, 0x00~0xff)
	*/
	RGBQUAD MyRGB(int r, int g, int b);

	/**
	* @brief 3 by 3 mask를 받아서 적용하고 계산 결과를 리턴
	* @param mask : 마스크 in x.h
	* @param input : 기준 좌표
	*/
	RGBQUAD calculateMask(const double mask[][3], _POINT& input);

	/**
	* @brief 기준 좌표를 중심으로 3 by 3내의 값중 가장 큰 것의 RGB값을 리턴
	* 현재는 각 채널 별로 값을 뽑아서 조합하여 리턴하는 것으로 하고 있음.	          
	* @param input : 기준 좌표
	*/
	RGBQUAD getMaxRGB(_POINT& input);

	/**
	* @brief 기준 좌표를 중심으로 3 by 3내의 값중 가장 작은 것의 RGB값을 리턴
	* 현재는 각 채널 별로 값을 뽑아서 조합하여 리턴하는 것으로 하고 있음.	          
	* @param input : 기준 좌표
	*/
	RGBQUAD getMinRGB(_POINT& input);

	/**
	* @brief 기준 좌표를 중심으로 3 by 3내의 값중 중간 RGB값을 리턴
	* 현재는 각 채널 별로 값을 뽑아서 조합하여 리턴하는 것으로 하고 있음.	          
	* @param input : 기준 좌표
	*/
	RGBQUAD getMedianRGB(_POINT& input);

	/**
	* @brief 기준 좌표를 중심으로 3 by 3내의 값중 평균 RGB값을 리턴
	* 현재는 각 채널 별로 값을 뽑아서 조합하여 리턴하는 것으로 하고 있음.	          
	* @param input : 기준 좌표
	*/
	RGBQUAD getMeanRGB(_POINT& input);
	
	/**
	* @brief 기준점 c와 점 p가 이루는 각을 동경(1, 0)을 기준으로 계산
	* @return 0~360
	* @param c : 기준점 좌표
	* @param p : 점 좌표
	*/
	double getDegree(_POINT& c, _POINT& p);
};

MATRIX3D ScaleT_Matrix(double Cx, double Cy);
