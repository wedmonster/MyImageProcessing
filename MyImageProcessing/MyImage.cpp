
#include "MyImage.h"
#include "stdafx.h"


MyImage::MyImage(void)
{
	image = new CxImage();
}

MyImage::MyImage(CxImage& img)
{
	image = new CxImage();
	image->Copy(img);
}

MyImage::MyImage(MyImage& m_img)
{
	image = new CxImage();
	image->Copy(*m_img.GetCxImage());
}

MyImage::MyImage(int width, int height, int wbpp)
{
	image = new CxImage();
	image->Create(width, height, wbpp);
}

MyImage::~MyImage(void)
{
	delete image;
}

CxImage* MyImage::GetCxImage()
{
	return image;
}

void MyImage::transform(MyImage& newImage, MATRIX3D& mat)
{
	
	MATRIX3D inv = mat.inverse();
	for(int y = 0; y < newImage.GetCxImage()->GetHeight(); y++){
		for(int x = 0; x < newImage.GetCxImage()->GetWidth(); x++){
			newImage.GetCxImage()->SetPixelColor( x, y, bilinearInterpolation(inv.AffineTransform(_POINT(x, y))), false);
		}
	}

}

MyImage MyImage::ScaleImage(double Cx, double Cy)
{
	int width = (int) (GetCxImage()->GetWidth() * Cx);
	int height = (int) (GetCxImage()->GetHeight() * Cy);
	MyImage newImage(width, height, image->GetBpp());
	MATRIX3D mat = ScaleT_Matrix(Cx, Cy);
	transform(newImage, mat);
	return newImage;
}

RGBQUAD MyImage::bilinearInterpolation(_POINT& input)
{
	int l = floor(input.getX());
	int k = floor(input.getY());
	double a = input.getX() - l;
	double b = input.getY() - k;
	if(l < 0 || l >= image->GetWidth() || k < 0 || k >= image->GetHeight() ||
		l+1 < 0 || l + 1 >= image->GetWidth() || k + 1 < 0 || k + 1 >= image->GetHeight())
		return MyRGB(0xff, 0xff, 0xff);
	
	int red = calcBilinear(l, k, a, b, R);
	int green = calcBilinear(l, k, a, b, G);
	int blue = calcBilinear(l, k, a, b, B);
		
	return MyRGB(red, green, blue);
}

int MyImage::calcBilinear(int l, int k, double a, double b, int channel)
{
	return (1-a)*(1-b)*getChannelColor(l, k, channel) + 
				a*(1-b)*getChannelColor(l+1, k, channel) +
					(1-a)*b*getChannelColor(l, k+1, channel) +
						a*b*getChannelColor(l+1, k+1, channel);
}

int MyImage::getChannelColor(int x, int y, int channel)
{
	switch(channel){
	case R:		return image->GetPixelColor(x, y).rgbRed;
	case G:		return image->GetPixelColor(x, y).rgbGreen;
	case B:		return image->GetPixelColor(x, y).rgbBlue;
	}
	return 0;
}

RGBQUAD MyImage::MyRGB(int r, int g, int b)
{
	RGBQUAD rgb;
	rgb.rgbRed = r;
	rgb.rgbGreen = g;
	rgb.rgbBlue = b;
	return rgb;
}

bool MyImage::Load(LPCTSTR lpszPathName)
{
	return image->Load(lpszPathName);
}

MATRIX3D ScaleT_Matrix(double Cx, double Cy)
{
	double m[3][3] = { Cx,  0, 0,
						0, Cy, 0,
						0,  0, 1 };
	MATRIX3D mat(m);
	//if(mat.isInversible())	return mat.inverse();
	//else return mat;
	return mat;
}

MyImage MyImage::GrayScaleImage()
{
	MyImage tmp(*this);
	CxImage* m_pImage = tmp.GetCxImage();
	RGBQUAD color;
	int gray;
	for(int y = 0; y < m_pImage->GetHeight(); y++){
		for(int x = 0; x < m_pImage->GetWidth(); x++){
			color = m_pImage->GetPixelColor(x, y);
			gray = (color.rgbRed + color.rgbGreen + color.rgbBlue) / 3;
			m_pImage->SetPixelColor(x, y, RGB(gray, gray, gray)); 
		}
	}
	return tmp;
}

MyImage MyImage::InverseImage()
{
	MyImage tmp(*this);
	CxImage* m_pImage = tmp.GetCxImage();
	RGBQUAD color;
	int r, g, b;
	for(int y = 0; y < m_pImage->GetHeight(); y++){
		for(int x = 0; x < m_pImage->GetWidth(); x++){
			color = m_pImage->GetPixelColor(x, y);
			r = 0xff ^ color.rgbRed;
			g = 0xff ^ color.rgbGreen;
			b = 0xff ^ color.rgbBlue;

			m_pImage->SetPixelColor(x, y, RGB(r, g, b));
		}
	}
	return tmp;
}

MyImage MyImage::BinarizeImage(int threshold)
{
	int gray;
	MyImage tmp(*this);
	CxImage* m_pImage = tmp.GetCxImage();
	for(int y = 0; y < m_pImage->GetHeight(); y++){
		for(int x = 0; x < m_pImage->GetWidth(); x++){
			gray = m_pImage->GetPixelGray(x, y);
			if(gray > threshold) gray = 255;
			else gray = 0;

			m_pImage->SetPixelColor(x, y, RGB(gray, gray, gray));
		}
	}
	return tmp;
}

MyImage MyImage::HistogramEqualizeImage()
{
	
	int cdf[256][3] = {0, };
	int n[256][3] = {0,};
	int s[256][3] = {0, };	
	
	for(int y = 0; y < image->GetHeight(); y++){
		for(int x = 0; x < image->GetWidth(); x++){
			n[ image->GetPixelColor(x, y).rgbRed ][R]++;		
			n[ image->GetPixelColor(x, y).rgbGreen ][G]++;
			n[ image->GetPixelColor(x, y).rgbBlue ][B]++;
		}
	}
	cdf[0][R] = n[0][R];
	cdf[0][G] = n[0][G];
	cdf[0][B] = n[0][B];

	for(int i = 1; i < 256; i++){
		cdf[i][R] = cdf[i-1][R] + n[i][R];
		cdf[i][G] = cdf[i-1][G] + n[i][G];
		cdf[i][B] = cdf[i-1][B] + n[i][B];
	}

	double MN = image->GetWidth() * image->GetHeight();
	int L = 256;

	for(int i = 0; i < 256; i++){
		s[i][R] = ROUND((double)(L - 1)/MN*cdf[i][R]);
		s[i][G] = ROUND((double)(L - 1)/MN*cdf[i][G]);
		s[i][B] = ROUND((double)(L - 1)/MN*cdf[i][B]);
	}

	MyImage tmp(*this);
	CxImage* m_pImage = tmp.GetCxImage();
	for(int y = 0; y < m_pImage->GetHeight(); y++){
		for(int x = 0; x < m_pImage->GetWidth(); x++){
			int red = m_pImage->GetPixelColor(x, y).rgbRed;
			int green = m_pImage->GetPixelColor(x, y).rgbGreen;
			int blue = m_pImage->GetPixelColor(x, y).rgbBlue;
			m_pImage->SetPixelColor(x, y, RGB(s[red][R], s[green][G], s[blue][B]));
		}
	}
	
	return tmp;
}

RGBQUAD MyImage::calculateMask(const double mask[][3], _POINT& input)
{
	double r_sum = 0.0;
	double g_sum = 0.0;
	double b_sum = 0.0;
	int x = input.getX(); 
	int y = input.getY();

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			r_sum += (mask[i][j] * image->GetPixelColor(x-1+i, y-1+j).rgbRed);
			g_sum += (mask[i][j] * image->GetPixelColor(x-1+i, y-1+j).rgbGreen);
			b_sum += (mask[i][j] * image->GetPixelColor(x-1+i, y-1+j).rgbBlue);
		}
	}
	r_sum = CRIP(r_sum);
	g_sum = CRIP(g_sum);
	b_sum = CRIP(b_sum);

	return MyRGB((int)r_sum, (int)g_sum, (int)b_sum);
}

MyImage MyImage::LaplacianFilterImage()
{
	///Laplacian Mask
	double mask[3][3] = {-1, -1, -1,
						 -1,  9, -1,
						 -1, -1, -1};
	MyImage tmp(*this);
	CxImage* m_pImage = tmp.GetCxImage();
	for(int y = 1; y < m_pImage->GetHeight()-1; y++){
		for(int x = 1; x < m_pImage->GetWidth()-1; x++){
			m_pImage->SetPixelColor(x, y, calculateMask(mask, _POINT(x, y)));
		}
	}
	return tmp;
}

MyImage MyImage::HighBoostFilterImage(const double A)
{
	///HighBoost Mask
	double mask[3][3] = {-1,  -1, -1,
						-1,  8+A, -1,
						-1,   -1, -1};
	MyImage tmp(*this);
	CxImage* m_pImage = tmp.GetCxImage();
	for(int y = 1; y < m_pImage->GetHeight()-1; y++){
		for(int x = 1; x < m_pImage->GetWidth()-1; x++){
			m_pImage->SetPixelColor(x, y, calculateMask(mask, _POINT(x, y)));
		}
	}
	return tmp;
}

MyImage MyImage::SobelFilterImage()
{
	double mask_x[3][3] = {-1, -2, -1,
							0,  0,  0,
						    1,  2,  1};
	double mask_y[3][3] = {-1,  0, 1,
						   -2,  0, 2,
						   -1,  0, 1};

	MyImage tmp(*this);
	CxImage* m_pImage = tmp.GetCxImage();
	for(int y = 1; y < m_pImage->GetHeight()-1; y++){
		for(int x = 1; x < m_pImage->GetWidth()-1; x++){
			RGBQUAD X_RGB = calculateMask(mask_x, _POINT(x, y));
			RGBQUAD Y_RGB = calculateMask(mask_y, _POINT(x, y));

			RGBQUAD S_RGB  = MyRGB(abs(X_RGB.rgbRed) + abs(Y_RGB.rgbRed),
									abs(X_RGB.rgbGreen) + abs(Y_RGB.rgbGreen),
										abs(X_RGB.rgbBlue) + abs(Y_RGB.rgbBlue));
			
			m_pImage->SetPixelColor(x, y, S_RGB);
		}
	}
	return tmp;
}

MyImage MyImage::SmoothingLinearFilterImage(){
	double mask[3][3] = {1.0/16, 2.0/16, 1.0/16,
						2.0/16, 4.0/16, 2.0/16,
						1.0/16, 2.0/16, 1.0/16};
	MyImage tmp(*this);
	CxImage* m_pImage = tmp.GetCxImage();
	for(int y = 1; y < m_pImage->GetHeight()-1; y++){
		for(int x = 1; x < m_pImage->GetWidth()-1; x++){
			m_pImage->SetPixelColor(x, y, calculateMask(mask, _POINT(x, y)));
		}
	}
	return tmp;
}

RGBQUAD MyImage::getMaxRGB(_POINT& input)
{
	int x = input.getX();
	int y = input.getY();

	int r_max = 0;
	int g_max = 0;
	int b_max = 0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			r_max = max(r_max, image->GetPixelColor(x + i - 1, y + i - 1).rgbRed);
			g_max = max(g_max, image->GetPixelColor(x + i - 1, y + i - 1).rgbGreen);
			b_max = max(b_max, image->GetPixelColor(x + i - 1, y + i - 1).rgbBlue);
		}
	}
	return MyRGB(r_max, g_max, b_max);
}


RGBQUAD MyImage::getMinRGB(_POINT& input)
{
	int x = input.getX();
	int y = input.getY();

	int r_min = 0xff;
	int g_min = 0xff;
	int b_min = 0xff;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			r_min = min(r_min, image->GetPixelColor(x + i - 1, y + i - 1).rgbRed);
			g_min = min(g_min, image->GetPixelColor(x + i - 1, y + i - 1).rgbGreen);
			b_min = min(b_min, image->GetPixelColor(x + i - 1, y + i - 1).rgbBlue);
		}
	}
	return MyRGB(r_min, g_min, b_min);
}

RGBQUAD MyImage::getMeanRGB(_POINT& input)
{
	int x = input.getX();
	int y = input.getY();

	int r_sum = 0;
	int g_sum = 0;
	int b_sum = 0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			r_sum += image->GetPixelColor(x + i - 1, y + i - 1).rgbRed;
			g_sum += image->GetPixelColor(x + i - 1, y + i - 1).rgbGreen;
			b_sum += image->GetPixelColor(x + i - 1, y + i - 1).rgbBlue;
		}
	}
	r_sum /= 9;
	g_sum /= 9;
	b_sum /= 9;
	return MyRGB(r_sum, g_sum, b_sum);
}

RGBQUAD MyImage::getMedianRGB(_POINT& input)
{
	int x = input.getX();
	int y = input.getY();

	int r_arr[9], g_arr[9], b_arr[9];
	int r_idx = 0, g_idx = 0, b_idx =0;

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			r_arr[r_idx++] = image->GetPixelColor(x + i - 1, y + i - 1).rgbRed;
			g_arr[g_idx++] = image->GetPixelColor(x + i - 1, y + i - 1).rgbGreen;
			b_arr[b_idx++] = image->GetPixelColor(x + i - 1, y + i - 1).rgbBlue;
		}
	}
	sort(r_arr, r_arr+9);
	sort(g_arr, g_arr+9);
	sort(b_arr, b_arr+9);
	return MyRGB(r_arr[4], g_arr[4], b_arr[4]);
}

MyImage MyImage::MaxFilterImage()
{
	MyImage tmp(*this);
	CxImage* m_pImage = tmp.GetCxImage();
	for(int y = 1; y < m_pImage->GetHeight()-1; y++){
		for(int x = 1; x < m_pImage->GetWidth()-1; x++){
			m_pImage->SetPixelColor(x, y, getMaxRGB(_POINT(x, y)));
		}
	}
	return tmp;
}

MyImage MyImage::MinFilterImage()
{
	MyImage tmp(*this);
	CxImage* m_pImage = tmp.GetCxImage();
	for(int y = 1; y < m_pImage->GetHeight()-1; y++){
		for(int x = 1; x < m_pImage->GetWidth()-1; x++){
			m_pImage->SetPixelColor(x, y, getMinRGB(_POINT(x, y)));
		}
	}
	return tmp;
}

MyImage MyImage::MeanFilterImage()
{
	MyImage tmp(*this);
	CxImage* m_pImage = tmp.GetCxImage();
	for(int y = 1; y < m_pImage->GetHeight()-1; y++){
		for(int x = 1; x < m_pImage->GetWidth()-1; x++){
			m_pImage->SetPixelColor(x, y, getMeanRGB(_POINT(x, y)));
		}
	}
	return tmp;
}


MyImage MyImage::MedianFilterImage()
{
	MyImage tmp(*this);
	CxImage* m_pImage = tmp.GetCxImage();
	for(int y = 1; y < m_pImage->GetHeight()-1; y++){
		for(int x = 1; x < m_pImage->GetWidth()-1; x++){
			m_pImage->SetPixelColor(x, y, getMedianRGB(_POINT(x, y)));
		}
	}
	return tmp;
}

MyImage MyImage::TransformIntoPolar()
{	
	int c_x = image->GetWidth() / 2;
	int c_y = image->GetHeight() / 2;

	MyImage tmp(360,sqrt( pow( c_x, 2.0) + pow(c_y, 2.0) ), image->GetBpp()); 
	CxImage* m_pImage = tmp.GetCxImage();

	for(int r = 0; r < m_pImage->GetHeight(); r++){
		for(int d = 0; d < m_pImage->GetWidth(); d++){
			double theta = d*M_PI/180;
			double x = r*cos(theta)+c_x;
			double y = r*sin(theta)+c_y;
			m_pImage->SetPixelColor(d, r, bilinearInterpolation(_POINT(x, y)));
		}
	}
	return tmp;
}

MyImage MyImage::TransformIntoCartecian()
{	
	//int r = (int)sqrt((double)image->GetHeight());
	int r = (int)(image->GetHeight() / sqrt( 2.0));
	MyImage tmp(r*2, r*2, image->GetBpp());
	CxImage* m_pImage = tmp.GetCxImage();

	int c_x = r; int c_y = r;

	for(int y = 0; y < m_pImage->GetHeight(); y++){
		for(int x = 0; x < m_pImage->GetWidth(); x++){
			double r = sqrt( pow( c_x - x , 2.0) + pow(c_y - y, 2.0) );
			/*double theta = 0.0;
			if(c_x - x != 0){				
				if(c_y - y == 0.0){
					if(c_y < y) theta = 270.0;
					else theta = 90.0;
				}else{
					double m = (double)(y - c_y) /(double)(x - c_x);
					theta = atan(m)*180/M_PI;
					if(x - c_x < 0) theta += 180;
					else if(y - c_y < 0) theta += 360;
				}
			}else{
				if(c_x <= x) theta = 0.0;
				else theta = 180.0;
			}*/

			double theta = getDegree(_POINT(c_x, c_y), _POINT(x, y));

			m_pImage->SetPixelColor(x, y, bilinearInterpolation(_POINT(theta, r)));
		}
	}
	return tmp;
}

double MyImage::getDegree(_POINT& c, _POINT& p)
{
	double theta = 0.0;
	int c_x = (int)c.getX(); int c_y = (int)c.getY();
	int x = (int)p.getX(); int y = (int)p.getY();

	if(c_x - x != 0){				
		if(c_y - y == 0){
			if(c_y < y) theta = 270.0;
			else theta = 90.0;
		}else{
			double m = (double)(y - c_y) /(double)(x - c_x);
			theta = atan(m)*180/M_PI;
			if(x - c_x < 0) theta += 180;
			else if(y - c_y < 0) theta += 360;
		}
	}else{
		if(c_x <= x) theta = 0.0;
		else theta = 180.0;
	} 
	return theta;
}

MyImage MyImage::PowerLawImage(double t)
{
	int table[256];
	for(int i = 0; i <= 0xff; i++){
		table[i] = CRIP(pow(i, t));
	}
	MyImage tmp(*this);
	CxImage* m_pImage = tmp.GetCxImage();

	for(int y = 0; y < image->GetHeight(); y++){
		for(int x = 0; x < image->GetWidth(); x++){
			int r = table[image->GetPixelColor(x, y).rgbRed];
			int g = table[image->GetPixelColor(x, y).rgbGreen];
			int b = table[image->GetPixelColor(x, y).rgbBlue];
			m_pImage->SetPixelColor(x, y, MyRGB(r, g, b));
		}
	}

	return tmp;

}