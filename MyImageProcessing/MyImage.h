/**
* @mainpage	MyImage
*
* @file MyImage.h
* @brief MyImage Ŭ���� ����
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
* @brief ���� ����ó�� ��� ����
*/
public:
	/**
	* @breif �⺻ ������ CxImage�� �����Ҵ��� ������ �ƹ� ��� ���� ����
	* @see MyImage(void)
	* @see MyImage(CxImage& img)
	* @see MyImage(MyImage& m_img)
	* @see MyImage(int width, int height, int wbpp)
	*/
	MyImage(void);

	/**
	* @breif CxImage�� �޾Ƽ� Copy�ϸ� ����
	* @see MyImage(void)
	* @see MyImage(CxImage& img)
	* @see MyImage(MyImage& m_img)
	* @see MyImage(int width, int height, int wbpp)
	* @param img : ���� CxImage
	*/
	MyImage(CxImage& img);

	/**
	* @breif ���� ������
	* @see MyImage(void)
	* @see MyImage(CxImage& img)
	* @see MyImage(MyImage& m_img)
	* @see MyImage(int width, int height, int wbpp)
	* @param m_img : ���� MyImage
	*/
	MyImage(MyImage& m_img);

	/**
	* @breif ���ο� CxImage(width byheight)�� �����.
	* @param width : �ʺ� (pixel)
	* @param height : ���� (piexl)
	* @param wbbp : bbp
	* @see MyImage(void)
	* @see MyImage(CxImage& img)
	* @see MyImage(MyImage& m_img)
	*/
	MyImage(int width, int height, int wbpp);

	/**
	* A destructor. ���� �Ҵ� �ߴ� CxImage ����
	*/
	~MyImage(void);
	
	/**
	* @brief CxImage �����͸� ��ȯ�Ѵ�.
	*/
	CxImage* GetCxImage();
	
	/**
	* @brief lpszPathName�� �̹����� �ҷ��� CxImage�� Load�Ѵ�.
	* @param lpszPathName : ���� ���
	*/
	bool Load(LPCTSTR lpszPathName);

	/**
	* @brief �̹����� ���� w��, ���� h�� Scale(Ȯ��/���)�Ѵ�. 
	* @param w : ���� ����
	* @param h : ���� ����
	*/
	MyImage ScaleImage(double w, double h);

	/**
	* @brief �̹����� Gray-Scale�Ͽ� ��ȯ�Ѵ�.
	* @return Gray-Scaled image.
	*/
	MyImage GrayScaleImage();

	/**
	* @brief �̹��� ������ ������Ų��. 
	* @return Inversed image
	*/
	MyImage InverseImage();

	/**
	* @brief threshold ���� �������� ����ȭ�Ѵ�. 
	* @param threshold : ���ذ�
	* @return Binarizied image
	*/
	MyImage BinarizeImage(int threshold);

	/**
	* @brief Histogram Equalization�� �����ϰ� ��ȯ ������ �����Ѵ�. 
	* @return Histogram Equalized image
	*/
	MyImage HistogramEqualizeImage();

	/**
	* @brief ����ȭ(Sharpening) ��� : Laplacian Filter
	* @return Filtered image by Laplacian
	*/	
	MyImage LaplacianFilterImage();

	/**
	* @brief ����ȭ(Sharpening) ��� : High-Boost Filter
	* @return Filtered image by High-Boost
	*/
	MyImage HighBoostFilterImage(const double A);
	
	/**
	* @brief ����ȭ(Sharpening) ��� : Sobel Filter
	* @return Filtered image by Sobel
	*/
	MyImage SobelFilterImage();

	/**
	* @brief ��Ȱȭ(Smoothing) ��� : Linear Filter
	* @return Filtered image by Linear
	*/
	MyImage SmoothingLinearFilterImage();

	/**
	* @brief Order-Statistics ��� : Max Filter
	* @return Filtered image by Max
	*/
	MyImage MaxFilterImage();

	/**
	* @brief Order-Statistics ��� : Min Filter
	* @return Filtered image by Min
	*/
	MyImage MinFilterImage();

	/**
	* @brief Order-Statistics ��� : Median Filter
	* @return Filtered image by Median
	*/
	MyImage MedianFilterImage();

	/**
	* @brief Order-Statistics ��� : Mean Filter
	* @return Filtered image by Mean
	*/
	MyImage MeanFilterImage();

	/**
	* @brief ������ ������ �߽����� ����ǥ��(r, theta)�� ��ȯ�� �̹����� ��ȯ�Ѵ�.
	* ���簢�� �̹����� ���´ٰ� �����Ѵ�.
	* @return image in Polar-coordination
	*/
	MyImage TransformIntoPolar();

	/**
	* @brief �� ũ�� r/root(2) by r/root(2)�̰� (r/root(2), r/root(2))�� �߽��� ������ǥ��� ��ȯ�� �̹����� ��ȯ�Ѵ�. r�� �̹����� height�̴�. 
	* @return image in Cartecian-coordination
	*/
	MyImage TransformIntoCartecian();

	/**
	* @brief ������ t�� power-law�� �����Ѵ�.
	* @return Power-Lawed image
	*/
	MyImage PowerLawImage(double t);

private:
	///�̹����� �����ϱ� ���� CxImage
	CxImage* image;
	
	/**
	* @brief ���� �̹����� Trasform���(3���� ���)�� ���� �����Ͽ� newImage�� �����Ѵ�. ���������� AffineTransform�� �����Ѵ�.
	* @param newImage : ������ �̹����� ����
	* @param mat : Transform���, Forward Mapping���� �Ѱ��ش�. - �ַ� ���̴� ���� ���� �����ؾ���
	*/
	void transform(MyImage& newImage, MATRIX3D& mat);
	
	/**
	* @brief input�� ���� Inverse Mapping�� Bilinear Interpolation ������� �ȼ� ���� �����´�. 
	* @param input : Coordinate in destination image
	*/
	RGBQUAD bilinearInterpolation(_POINT& input);

	/**
	* @brief Bilinear Interpolation�� ���� ���� ��� �Լ�
	*/
	int calcBilinear(int l, int k, double a, double b, int channel);

	/**
	* @brief RGB�� �ϳ��� ä�ο��� (x, y)�� �ȼ� ���� �����Ѵ�. 
	* @param x : x ��ǥ
	* @param y : y ��ǥ
	* @param channel : R(0), G(1), B(2) in function.h
	* @return �ȼ���(int, 0x00~0xff)
	*/
	int getChannelColor(int x, int y, int channel);

	/**
	* @brief �� ä���� �ȼ����� �޾Ƽ� RGBQUAD�� ��ȯ
	* @param r : Rä���� ��(int, 0x00~0xff)
	* @param g : Gä���� ��(int, 0x00~0xff)
	* @param b : Bä���� ��(int, 0x00~0xff)
	*/
	RGBQUAD MyRGB(int r, int g, int b);

	/**
	* @brief 3 by 3 mask�� �޾Ƽ� �����ϰ� ��� ����� ����
	* @param mask : ����ũ in x.h
	* @param input : ���� ��ǥ
	*/
	RGBQUAD calculateMask(const double mask[][3], _POINT& input);

	/**
	* @brief ���� ��ǥ�� �߽����� 3 by 3���� ���� ���� ū ���� RGB���� ����
	* ����� �� ä�� ���� ���� �̾Ƽ� �����Ͽ� �����ϴ� ������ �ϰ� ����.	          
	* @param input : ���� ��ǥ
	*/
	RGBQUAD getMaxRGB(_POINT& input);

	/**
	* @brief ���� ��ǥ�� �߽����� 3 by 3���� ���� ���� ���� ���� RGB���� ����
	* ����� �� ä�� ���� ���� �̾Ƽ� �����Ͽ� �����ϴ� ������ �ϰ� ����.	          
	* @param input : ���� ��ǥ
	*/
	RGBQUAD getMinRGB(_POINT& input);

	/**
	* @brief ���� ��ǥ�� �߽����� 3 by 3���� ���� �߰� RGB���� ����
	* ����� �� ä�� ���� ���� �̾Ƽ� �����Ͽ� �����ϴ� ������ �ϰ� ����.	          
	* @param input : ���� ��ǥ
	*/
	RGBQUAD getMedianRGB(_POINT& input);

	/**
	* @brief ���� ��ǥ�� �߽����� 3 by 3���� ���� ��� RGB���� ����
	* ����� �� ä�� ���� ���� �̾Ƽ� �����Ͽ� �����ϴ� ������ �ϰ� ����.	          
	* @param input : ���� ��ǥ
	*/
	RGBQUAD getMeanRGB(_POINT& input);
	
	/**
	* @brief ������ c�� �� p�� �̷�� ���� ����(1, 0)�� �������� ���
	* @return 0~360
	* @param c : ������ ��ǥ
	* @param p : �� ��ǥ
	*/
	double getDegree(_POINT& c, _POINT& p);
};

MATRIX3D ScaleT_Matrix(double Cx, double Cy);
