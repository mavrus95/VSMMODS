#pragma once /// this will pragma all classes using one set of functions libs composite
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>
#pragma once 
#include "Vsm.hpp"

#define PRO_KEY  0x80000000
/////////////////////////
// DLL EXPORT FUNCTION //
/////////////////////////
#define EXPORT __declspec(dllexport)   // needed to export functions to the proteus simulations & licence engines you can import .lib's etc here
// null case tie's
#define VOID	void
/////////////////////////////
// NULL CASE TYPE DEFINE'S //
/////////////////////////////
typedef float	FLOAT;
typedef double	DOUBLE;
typedef char	CHAR;
typedef short	SHORT;
typedef int		INT;
typedef int		BOOL;
typedef long	LONG;

class MAREADOUT : public IACTIVEMODEL
{
	public: // Implementation of IACTIVEMODEL
		MAREADOUT (VOID);
		virtual ~MAREADOUT(VOID);
		virtual VOID initialize (ICOMPONENT *cpt);
		virtual ISPICEMODEL *getspicemodel (CHAR *device);
		virtual IDSIMMODEL *getdsimmodel (CHAR *device);
		virtual VOID plot (ACTIVESTATE state);
		virtual VOID animate (INT element, ACTIVEDATA *newstate);
		virtual BOOL actuate (WORD key, INT x, INT y, DWORD flags);
	private:
		ICOMPONENT *component;
		POINT textorg;
		HTEXTSTYLE textstyle;
		CHAR rout[19];
};
