#ifndef __ccipdSliceTypes_h
#define __ccipdSliceTypes_h

////////////////////////////////////////////////////////////////////////////////////////////////////
#include "ccipdCore.h"
#include "ccipdITKForwardDeclarations.h"
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

namespace ccipd
{
	/**
	 * \addtogroup Common
	 * @{
	 */

	////////////////////////////////////////////////////////////////////////////////////////////////////

	/// For 2D images
	const unsigned int SliceDimension = 2;

	////////////////////////////////////////////////////////////////////////////////////////////////////

	/// 2D image type
	typedef itk::Image< InternalPixelType, SliceDimension > SliceImageType;
	typedef itk::Image<double, SliceDimension> SliceImageDoubleType;

	/// 2D transform image type
	typedef itk::Image<
		TransformValueType,
		SliceDimension
	> TransformImageType;

	/// A smart pointer to a 2D image
	typedef itk::SmartPointer< SliceImageType > SliceImagePointer;
	typedef itk::SmartPointer< SliceImageDoubleType > SliceImageDoubleTypePointer;

	/// A smart pointer to a const 2D image
	typedef itk::SmartPointer<  const SliceImageType > SliceImageConstPointer;

	typedef std::vector<SliceImagePointer     >      SliceImagesContainer;
	typedef std::vector<SliceImageConstPointer>      SliceConstImagesContainer;

	/// 2D image base
	typedef itk::ImageBase<
		SliceDimension
	> SliceImageBase;

	/// 2D image region
	typedef itk::ImageRegion<
		SliceDimension
	> SliceRegionType;

	////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////////////

	/// 2D mask type
	typedef itk::Image<MaskPixelType, SliceDimension> SliceMaskImageType;

	/// A smart pointer to a 2D mask
	typedef itk::SmartPointer<SliceMaskImageType> SliceMaskImagePointer;

	/// A smart pointer to a const 2D mask
	typedef itk::SmartPointer<const SliceMaskImageType> SliceMaskImageConstPointer;

	/// 2D mask spatial object
	typedef itk::ImageMaskSpatialObject<SliceDimension> SliceMaskSpatialType;

	////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////////////

	/// Define a 2D transformation
	typedef itk::Transform<
		TransformValueType,
		SliceDimension,
		SliceDimension
	> SliceTransformType;

	/// Smart pointer to 2D transformation
	typedef itk::SmartPointer<
		SliceTransformType
	> SliceTransformPointer;

	/// Smart pointer to const 2D transformation
	typedef itk::SmartPointer<
		const SliceTransformType
	> SliceTransformConstPointer;

	////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////////////

	/// 2D warp field vector
	typedef itk::Vector<
		WarpValueType,
		SliceDimension
	> SliceWarpPixelType;

	/// 2D warp field
	typedef itk::Image<
		SliceWarpPixelType,
		SliceDimension
	> SliceWarpFieldType;

	/// 2D warp field smart pointer
	typedef itk::SmartPointer<
		SliceWarpFieldType
	> SliceWarpFieldPointer;

	/// 2D warp field smart pointer
	typedef itk::SmartPointer<
		const SliceWarpFieldType
	> SliceWarpFieldConstPointer;

	////////////////////////////////////////////////////////////////////////////////////////////////////

	/// RGB image pixel type

	typedef itk::RGBPixel <InternalPixelType>   RGBPixelType;
	typedef itk::RGBAPixel<InternalPixelType>   RGBAPixelType; // Alpha controls transparency of the pixel

	//typedef itk::RGBPixel <float>   RGBPixelFType;
	//typedef itk::RGBAPixel<float>   RGBAPixelFType; // Alpha controls transparency of the pixel

	/// 2D RGB image slice

	typedef itk::Image<RGBPixelType, SliceDimension> RGBSliceType;
	typedef itk::Image<RGBAPixelType, SliceDimension> RGBASliceType;
	//
	//typedef itk::Image<RGBPixelType, SliceDimension> RGBSliceType;
	//typedef itk::Image<RGBAPixelType, SliceDimension> RGBASliceType;

	/// Smart pointer to 2D RGB slice
	typedef itk::SmartPointer<RGBSliceType> RGBSlicePointer;
	typedef itk::SmartPointer<RGBASliceType> RGBASlicePointer;

	/// Smart pointer to const 2D RGB slice
	typedef itk::SmartPointer<const RGBSliceType> RGBSliceConstPointer;
	typedef itk::SmartPointer<const RGBASliceType> RGBASliceConstPointer;

	typedef std::vector<RGBSlicePointer >			RGBSliceImagesContainer;
	typedef std::vector<RGBASlicePointer>			RGBASliceImagesContainer;

	typedef std::vector<RGBSliceConstPointer >      RGBSliceConstImagesContainer;
	typedef std::vector<RGBASliceConstPointer>      RGBASliceConstImagesContainer;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////

	/// 2D RGB warp field vector
	typedef itk::Vector<WarpValueType, SliceDimension> RGBWarpPixelType;

	/// 2D RGB warp field
	typedef itk::Image<SliceWarpPixelType, SliceDimension> RGBWarpFieldType;

	/// 2D RGB warp field smart pointer
	typedef itk::SmartPointer<SliceWarpFieldType> RGBWarpFieldPointer;

	/// 2D RGB warp field smart pointer
	typedef itk::SmartPointer<const SliceWarpFieldType> RGBWarpFieldConstPointer;
	////////////////////////////////////////////////////////////////////////////////////////////////////

	/** @} */
} // namespace ccipd
#endif // __ccipdRGBSliceTypes_h
