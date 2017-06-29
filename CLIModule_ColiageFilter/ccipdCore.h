#ifndef __ccipdCore_h
#define __ccipdCore_h

#include "ccipdCodeOptions.h"
#include "ccipdMacros.h"

#define LabShortName "CCIPD"
#define LabDomain    "http://ccipd.case.edu"

//////////////////////////////////////////////////////////////////////////////////////////
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#ifndef _SCL_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#endif
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//#ifndef VCL_CAN_STATIC_CONST_INIT_INT
//#define VCL_CAN_STATIC_CONST_INIT_INT   0
//#endif
//#ifndef VCL_CAN_STATIC_CONST_INIT_FLOAT
//#define VCL_CAN_STATIC_CONST_INIT_FLOAT 0
//#endif
//////////////////////////////////////////////////////////////////////////////////////////

#define FLOATING_POINT_TOLERANCE 0.005

namespace ccipd
{
	//////////////////////////////////////////////////////////////////////////////////////////
	// core types
	typedef double             InternalPixelType;
	typedef float              WarpValueType;
	typedef float              LandmarkType;
	typedef LandmarkType       MedialAxisType;
	typedef LandmarkType       MeshPixelType;
	typedef double             TransformValueType;
	typedef unsigned char      MaskPixelType;
	typedef bool               BinaryPixelType;
	typedef double             EvaluationValueType;
	typedef std::size_t        HashValueType;
	//////////////////////////////////////////////////////////////////////////////////////////
	typedef unsigned int       mxUint64;

	//////////////////////////////////////////////////////////////////////////////////////////
	// default parameters

	/**
	 * \brief By default, ignore image orientation when loading images?
	 * \ingroup Common
	 */
	const bool defaultIgnoreOrientation = false;
	//////////////////////////////////////////////////////////////////////////////////////////
} // namespace ccipd
#endif
