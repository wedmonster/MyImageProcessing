#include "function.h"
#include "StdAfx.h"

int CRIP(double val)
{
	if(val > 255.0) return 0xff;
	else if(val < 0) return 0;
	return (int) val;
}