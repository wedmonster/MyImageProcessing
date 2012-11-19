
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

	//0~360, 
	MyImage tmp(361, sqrt( pow( c_x, 2.0) + pow(c_y, 2.0) ), image->GetBpp()); 
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
	int r = (int)(image->GetHeight() / sqrt( 2.0));
	MyImage tmp(r*2, r*2, image->GetBpp());
	CxImage* m_pImage = tmp.GetCxImage();

	int c_x = r; int c_y = r;

	for(int y = 0; y < m_pImage->GetHeight(); y++){
		for(int x = 0; x < m_pImage->GetWidth(); x++){
			double _r = sqrt( pow( c_x - x , 2.0) + pow(c_y - y, 2.0) );			
			double theta = getDegree(_POINT(c_x, c_y), _POINT(x, y));

			m_pImage->SetPixelColor(x, y, bilinearInterpolation(_POINT(theta, _r)));
		}
	}
	return tmp;
}

double MyImage::getDegree(_POINT& c, _POINT& p)
{
	double theta = 0.0;
	double c_x = c.getX(); double c_y = c.getY();
	double x = p.getX(); double y = p.getY();

	if(fabs(c_x - x) < EPS){
		//c_x = x
		if(fabs(c_y - y) < EPS)	theta = 0.0; 
		else if(c_y > y)		theta = 270.0;
		else if(c_y < y)		theta = 90.0;
	}else {
		if(fabs(c_y - y) < EPS){
			//c_y = y
			if(c_x > x) theta = 180;
			else if(c_x < x) {
				if(c_y <= y) theta = 0.0;
				else if(c_y > y) theta = 360.0;
			}
		}else{
			double m = (double)(y - c_y) /(double)(x - c_x);
			theta = atan(m)*180.0/M_PI;
			if(x - c_x < 0) theta += 180.0;
			else if(y - c_y < 0) theta += 360.0;
		}
	}

	if(theta > 360.0) theta = 360.0;
	else if(theta < 0) theta = 0.0;
	
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

bool MyImage:: IsPowerOf2(int x){
	int ref = 1;
	while(ref < x) ref <<= 1;
	return ref == x;
}

bool MyImage::DFT(int dir, long m, double *x1, double *y1, double *x2, double *y2)
{
	long i, k;
	double arg;
	double cosarg, sinarg;

	for(i = 0; i < m; i++){
		x2[i] = 0;
		y2[i] = 0;
		arg = -dir * 2.0 * PI * i / (double)m;
		for(k = 0; k < m; k++){
			cosarg = cos(k * arg);
			sinarg = sin(k * arg);
			x2[i] += (x1[k] * cosarg - y1[k] * sinarg);
			y2[i] += (x1[k] * sinarg - y1[k] * cosarg);
		}
	}

	if(dir == 1){
		for(i = 0; i < m; i++){
			x1[i] = x2[i] / m;
			y1[i] = y2[i] / m;
		}
	}else{
		for(i = 0; i < m; i++){
			x1[i] = x2[i];
			y1[i] = y2[i];
		}
	}

	return true;
}

void MyImage::DFT(MyImage& imgM, MyImage& imgP)
{
	CxImage m_tempM;
	CxImage m_tempP;
	m_tempM.Copy(*image);
	m_tempP.Copy(m_tempM);
	long FW, FH, FWP, FHP;
	long width, height;
	width = m_tempM.GetWidth();
	height = m_tempM.GetHeight();

	FW = width;
	FH = height;

	FWP = log10((double)FW)/log10(2.0);
	FHP = log10((double)FH)/log10(2.0);

	int H, W, m_FDW, m_FDH;
	W = width = m_tempM.GetWidth();
	H = height = m_tempM.GetHeight();

	double *x11 = new double[W];
	double *y11 = new double[W];
	double *x21 = new double[W];
	double *y21 = new double[W];

	double *x12 = new double[H];
	double *y12 = new double[H];
	double *x22 = new double[H];
	double *y22 = new double[H];

	int x, y;
	double **iReal;
	double **iImg;
	double **sourceArray;
	double **iPReal;
	double **iPImag;

	iReal = new double*[H];
	iImg = new double*[H];
	iPReal = new double*[H];
	iPImag = new double*[H];
	sourceArray = new double*[H];

	for(x = 0; x < H; x++){
		iReal[x] = new double[W];
		iImg[x] = new double[W];
		iPReal[x] = new double[W];
		iPImag[x] = new double[W];
		sourceArray[x] = new double[W];
	}

	for(y = 0; y < H; y++){
		for(x = 0; x < W; x++){
			sourceArray[y][x] = pow(-1.0, x+y)*double(m_tempM.GetPixelGray(x, y));
		}
	}

	for(y = 0; y < H; y++){
		for(x = 0; x < W; x++){
			x11[x] = sourceArray[y][x];
			y11[x] = 0.0;
		}
		DFT(1, W, x11, y11, x21, y21);

		for(x = 0; x < W; x++){
			iReal[y][x] = x11[x];
			iImg[y][x] = y11[x];
		}
	}

	for(x = 0; x < W; x++){
		for(y = 0; y < H; y++){
			x12[y] = iReal[y][x];
			y12[y] = iImg[y][x];
		}
		DFT(1, H, x12, y12, x22, y22);

		for(y = 0; y < H; y++){
			iReal[y][x] = iPReal[y][x] = x12[y];
			iImg[y][x] = iPImag[y][x] = y12[y];
		}
	}

	double MAXMVAL = -10000.0;
	double MINMVAL = 10000.0;
	double MAXPVAL = -10000.0;
	double MINPVAL = 10000.0;

	for(y = 0; y < H; y++){
		for(x = 0; x < W; x++){
			iReal[y][x] = 0.5*(1.0 + log10(pow((iReal[y][x]*iReal[y][x] + iImg[y][x]*iImg[y][x]), 0.5)));
			iImg[y][x] = atan(iImg[y][x]/iReal[y][x]);
			if(iReal[y][x] > MAXMVAL) MAXMVAL = iReal[y][x];
			if(iReal[y][x] < MINMVAL) MINMVAL = iReal[y][x];
			if(iImg[y][x] > MAXPVAL) MAXPVAL = iImg[y][x];
			if(iImg[y][x] < MINPVAL) MINPVAL = iImg[y][x];
		}
	}

	for(y = 0; y < H; y++){
		for(x = 0; x < W; x++){
			iReal[y][x] = (255.0 / (MAXMVAL-MINMVAL))*(iReal[y][x] - MINMVAL);
			iImg[y][x] = (255.0 / (MAXPVAL - MINPVAL))*(iImg[y][x] - MINPVAL);
			m_tempM.SetPixelColor(x, y, RGB(iReal[y][x], iReal[y][x], iReal[y][x]));
			m_tempP.SetPixelColor(x, y, RGB(iImg[y][x], iImg[y][x], iImg[y][x]));
		}
	}
	

	for(x = 0; x < H; x++){
		delete iReal[x];
		delete iImg[x];
		delete iPReal[x];
		delete iPImag[x];
		delete sourceArray[x];
	}

	delete []x11;
	delete []x12;
	delete []x21;
	delete []x22;
	delete []y11;
	delete []y12;
	delete []y21;
	delete []y22;

	imgM.GetCxImage()->Copy(m_tempM);
	imgP.GetCxImage()->Copy(m_tempP);
}

bool MyImage::FFT(int dir, int m, double *x, double* y){
	long nn,i,i1,j,k,i2,l,l1,l2;
	double c1,c2,tx,ty,t1,t2,u1,u2,z;
	
	nn = 1 << m;

	i2 = nn >> 1;
	j = 0;

	for(i = 0 ; i < nn - 1 ; i++ )
	{
		if( i < j ) 
		{
			tx = x[i];
			ty = y[i];
			x[i] = x[j];
			y[i] = y[j];
			x[j] = tx;
			y[j] = ty;

		} // if

		k = 12;
		while( k <= j )
		{
			j -= k;
			k >>= 1;
		}//while

		j += k;
	}// for

	c1 = -1.0;
	c2 = 0.0;
	l2 = 1;

	for(l=0; l < m ; l++) {

		l1 = l2;
		l2 <<= 1;
		u1 = 1.0;
		u2 = 0.0;

		for( j = 0 ; j < l1 ; j++ ) {
			for( i = j ; i < nn ; i += l2 ) {

				i1 = i + l1;
				t1 = u1 * x[i1] - u2 * y[i1];
				t2 = u1 * y[i1] + u2 * x[i1];

				x[i1] = x[i] - t1;
				y[i1] = y[i] - t2;
				x[i] += t1;
				y[i] += t2;
			} // for
			
			z = u1 * c1 - u2 * c2;
			u2 = u1 * c2 + u2 * c1;
			u1 = z;
		} // for

		c2 = sqrt( ( 1.0  - c1) / 2.0 );
		if( dir == 1 )
			c2 = -c2;
		c1 = sqrt( ( 1.0 + c1 ) / 2.0 );
	}// for

	if( dir == 1 ) {
		for ( i = 0 ; i < nn ; i++ ) {
			x[i] /= (double)nn;
			y[i] /= (double)nn;
		}//for
	} // if

	return true;
}

void MyImage::FFT(MyImage& imgM, MyImage& imgP){
	
	//----start------
	CxImage m_tempM;
	CxImage m_tempP;
	CxImage m_iFImage;

	m_tempM.Copy(*this->image);
	m_tempP.Copy(m_tempM);
	long FW, FH, FWP, FHP;
	long width, height;

	width = m_tempM.GetWidth();
	height = m_tempM.GetHeight();

	bool bXpow2 = IsPowerOf2(width);
	bool bYpow2 = IsPowerOf2(height);

	FW = width;
	FH = height;

	FWP = log10((double)FW)/log10(2.0);
	FHP = log10((double)FH)/log10(2.0);

	if(!(bXpow2 && bYpow2))
	{
		long i=0;
		while((1<<i) < width) i++;
		FW = 1<<i;
		i = 0;
		while((1<<i) < height) i++;
		FH = 1<<i;

		FWP = log10((double)FW)/log10(2.0);
		FHP = log10((double)FH)/log10(2.0);
	}
	m_tempM.Resample(FW, FH, 0);
	m_tempP.Resample(FW, FH, 0);
	m_iFImage.Copy(m_tempM);

	int H, W, m_FDW, m_FDH;
	W = m_FDW = m_tempM.GetWidth();
	H = m_FDH = m_tempM.GetHeight();

	double *x11 = new double[W];
	double *y11 = new double[W];
	double *x21 = new double[W];
	double *y21 = new double[W];

	double *x12 = new double[H];
	double *y12 = new double[H];
	double *x22 = new double[H];
	double *y22 = new double[H];

	double **iReal, **iPReal;
	double **iImg, **iPImg;
	double **sourceArray;

	iReal = new double*[H];
	iImg = new double*[H];
	iPReal = new double*[H];
	iPImg = new double*[H];
	sourceArray = new double*[H];

	for(int x = 0; x < H; x++){
		iReal[x] = new double[W];
		iImg[x] = new double[W];
		iPReal[x] = new double[W];
		iPImg[x] = new double[W];
		sourceArray[x] = new double[W];
	}

	for(int y = 0; y < H; y++){
		for(int x = 0; x< W; x++){
			sourceArray[y][x] = pow(-1.0, x + y) * (double) (m_tempM.GetPixelGray(x, y));
		}
	}

	for(int y = 0; y < H; y++){
		for(int x = 0; x < W; x++){
			x11[x] = sourceArray[y][x];
			y11[x] = 0.0;
		}

		FFT(1, FWP, x11, y11);

		for(int x = 0; x < W; x++){
			iReal[y][x] = x11[x];
			iImg[y][x] = y11[x];
		}
	}

	for(int x = 0; x < W; x++){
		for(int y = 0; y < H; y++){
			x12[y] = iReal[y][x];
			y12[y] = iImg[y][x];
		}

		FFT(1, FHP, x12, y12);

		for(int y = 0; y < H; y++){
			iReal[y][x] = iPReal[y][x] = x12[y];
			iImg[y][x] = iPImg[y][x] = y12[y];
		}
	}
	
	double MAXMVAL = -10000.0;
	double MINMVAL = 10000.0;
	double MAXPVAL = -10000.0;
	double MINPVAL = 10000.0;

	for(int y = 0; y < H; y++){
		for(int x = 0; x < W; x++){
			iReal[y][x] = 0.5*(1.0 + log10(pow((iReal[y][x]*iReal[y][x] + iImg[y][x]*iImg[y][x]), 0.5)));
			iImg[y][x] = atan(iImg[y][x] / iReal[y][x]);
			if(iReal[y][x] > MAXMVAL) MAXMVAL = iReal[y][x];
			if(iReal[y][x] < MINMVAL) MINMVAL = iReal[y][x];
			if(iImg[y][x] > MAXPVAL) MAXPVAL = iImg[y][x];
			if(iImg[y][x] < MINPVAL) MINPVAL = iImg[y][x];
		}
	}

	for(int y = 0; y < H; y++){
		for(int x = 0; x < W; x++){
			iReal[y][x] = (255.0 / (MAXMVAL - MINMVAL))*(iReal[y][x] - MINMVAL);
			iImg[y][x] = (255.0 / (MAXPVAL - MINPVAL)) * (iImg[y][x] - MINPVAL);
			m_tempM.SetPixelColor(x, y, RGB(iReal[y][x], iReal[y][x], iReal[y][x]));
			m_tempP.SetPixelColor(x, y, RGB(iImg[y][x], iImg[y][x], iImg[y][x]));
		}
	}

	for(int x = 0; x < H; x++){
		delete sourceArray[x];
		delete iReal[x];
		delete iImg[x];
		delete iPImg[x];
		delete iPReal[x];
	}

	delete[] sourceArray;
	delete[] iReal;
	delete[] iImg;
	delete[] iPImg;
	delete[] iPReal;

	delete []x11;
	delete []y11;
	delete []x21;
	delete []y21;

	delete []x12;
	delete []y12;
	delete []x22;
	delete []y22;
	
	//----end------

	imgM.GetCxImage()->Copy(m_tempM);
	imgP.GetCxImage()->Copy(m_tempP);
}