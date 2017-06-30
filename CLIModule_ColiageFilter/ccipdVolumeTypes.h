#ifndef __ccipdVolumeTypes_h
#define __ccipdVolumeTypes_h



//////////////////////////////////////////////////////////////////////////////////////////
#include "ccipdCore.h"
#include "ccipdSliceTypes.h"


// std includes
ccipdDisableAllWarnings
#include <vector>
#include <itkImage.h>
ccipdEnableAllWarnings

//////////////////////////////////////////////////////////////////////////////////////////



namespace ccipd
{



/**
 * \addtogroup Common
 * @{
 */



//////////////////////////////////////////////////////////////////////////////////////////
// image types
const unsigned int VolumeDimension       = 3;
const unsigned int VolumeVectorDimension = 4;

/// Note that "double" is from itkImageBase.h
typedef itk::Point< double, VolumeDimension > VolumePointType;

typedef itk::ImageBase< VolumeDimension > VolumeImageBase;

typedef itk::SmartPointer< VolumeImageBase > VolumeImageBasePointer;

typedef itk::SmartPointer< const VolumeImageBase > VolumeImageBaseConstPointer;

typedef itk::Image< InternalPixelType, VolumeDimension > VolumeImageType;

typedef itk::SmartPointer< VolumeImageType > VolumeImagePointer;

typedef itk::SmartPointer< const VolumeImageType > VolumeImageConstPointer;

typedef itk::ImageRegion< VolumeDimension > VolumeRegionType;

typedef std::vector< VolumeRegionType > VolumeRegionsContainer;

typedef std::vector<VolumeImagePointer>      VolumeImagesContainer     ;
typedef std::vector<VolumeImageConstPointer> VolumeConstImagesContainer;

//////////////////////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////////////////////
// mask types

typedef itk::Image< MaskPixelType, VolumeDimension > VolumeMaskImageType;

typedef itk::SmartPointer< VolumeMaskImageType > VolumeMaskImagePointer;

typedef itk::SmartPointer< const VolumeMaskImageType > VolumeMaskImageConstPointer;

typedef std::vector< VolumeMaskImagePointer> VolumeMaskImagesContainer;

typedef std::vector< VolumeMaskImageConstPointer > VolumeConstMaskImagesContainer;

typedef itk::ImageMaskSpatialObject< VolumeDimension > VolumeMaskSpatialType;


typedef itk::VectorImage < MaskPixelType, VolumeDimension > MaskVectorType   ;
typedef itk::SmartPointer< MaskVectorType                 > MaskVectorPointer;
typedef itk::SmartPointer< const MaskVectorType           > MaskVectorConstPointer;


//////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////
// boolean types

typedef itk::Image< BinaryPixelType, VolumeDimension > VolumeBinaryImageType;

typedef itk::SmartPointer< VolumeBinaryImageType > VolumeBinaryImagePointer;

typedef itk::SmartPointer< const VolumeMaskImageType > VolumeBinaryImageConstPointer;
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
// volume metric types
typedef itk::ImageToImageMetric< VolumeImageType, VolumeImageType > VolumeMetricType;

//////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
// volume feature types

typedef itk::VectorImage< InternalPixelType, VolumeDimension > VolumeVectorType;

typedef itk::SmartPointer< VolumeVectorType > VolumeVectorPointer;

typedef itk::SmartPointer< const VolumeVectorType > VolumeVectorConstPointer;

typedef VolumeVectorType    VolumeFeaturesType ;

typedef VolumeVectorPointer VolumeFeaturesPointer;

typedef VolumeVectorConstPointer  VolumeFeaturesConstPointer ;


typedef std::vector< VolumeFeaturesPointer      > VolumeFeaturesImagesContainer;
typedef std::vector< VolumeFeaturesConstPointer > VolumeFeaturesConstImagesContainer;

typedef std::vector< VolumeVectorPointer      > VolumeVectorImagesContainer;
typedef std::vector< VolumeVectorConstPointer > VolumeVectorConstImagesContainer;

//////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////
// transformation types

typedef itk::Transform< TransformValueType, VolumeDimension, VolumeDimension > VolumeTransformType;

typedef itk::SmartPointer< VolumeTransformType > VolumeTransformPointer;

typedef itk::SmartPointer< const VolumeTransformType > VolumeTransformConstPointer;

typedef itk::MatrixOffsetTransformBase< TransformValueType, VolumeDimension, VolumeDimension > VolumeLinearTransformType;

typedef itk::SmartPointer< VolumeLinearTransformType > VolumeLinearTransformPointer;

typedef itk::SmartPointer< const VolumeLinearTransformType > VolumeLinearTransformConstPointer;

typedef itk::SmartPointer< VolumeTransformType > VolumeTransformPointer;

typedef itk::SmartPointer< const VolumeTransformType > VolumeTransformConstPointer;

typedef itk::AffineTransform< TransformValueType, VolumeDimension > VolumeAffineTransformType;

typedef itk::SmartPointer< VolumeAffineTransformType > VolumeAffineTransformPointer;

typedef itk::SmartPointer< const VolumeAffineTransformType > VolumeAffineTransformConstPointer;

typedef std::vector< VolumeTransformPointer > VolumeTransformsContainer;

typedef std::vector< VolumeTransformConstPointer > VolumeConstTransformsContainer;

//////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////
// transformation types

const unsigned int splineOrder=3;

typedef itk::BSplineTransform< TransformValueType, VolumeDimension, splineOrder > VolumeBSplineTransformType;

typedef itk::SmartPointer< VolumeBSplineTransformType > VolumeBSplineTransformPointer;

typedef itk::SmartPointer< const VolumeBSplineTransformType > VolumeBSplineTransformConstPointer;

typedef std::vector< VolumeBSplineTransformPointer > VolumeBSplineTransformsContainer;

typedef std::vector< VolumeBSplineTransformConstPointer > VolumeConstBSplineTransformsContainer;

//////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////
// warp field types

typedef itk::Vector< WarpValueType, VolumeDimension > VolumeWarpPixelType;

typedef itk::Image< VolumeWarpPixelType, VolumeDimension > VolumeWarpFieldType;

typedef itk::SmartPointer< VolumeWarpFieldType > VolumeWarpFieldPointer;

typedef itk::SmartPointer< const VolumeWarpFieldType > VolumeWarpFieldConstPointer;

//////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////
typedef itk::ImageToImageMetric< VolumeImageType, VolumeImageType > VolumeMetricType;
//////////////////////////////////////////////////////////////////////////////////////////

/// RGB image pixel type

//typedef itk::RGBPixel <unsigned char>   RGBPixelType ;
//typedef itk::RGBAPixel<unsigned char>   RGBAPixelType; // Alpha controls transparency of the pixel


/// 3D RGB images
typedef itk::Image<RGBPixelType, VolumeDimension> RGBVolumeType;
typedef itk::Image<RGBAPixelType, VolumeDimension> RGBAVolumeType;

typedef itk::ImageBase<VolumeDimension> VolumeImageBaseType;

/// Smart pointer to 2D RGB slice
typedef itk::SmartPointer< RGBVolumeType > RGBVolumePointer   ;
typedef std::vector<RGBVolumePointer>      RGBVolumeContainer ;

typedef itk::SmartPointer< RGBAVolumeType> RGBAVolumePointer  ;
typedef std::vector<RGBAVolumePointer>     RGBAVolumeContainer;

/// Smart pointer to const 2D RGB slice
typedef itk::SmartPointer<const RGBVolumeType>  RGBVolumeConstPointer  ;
typedef std::vector<RGBVolumeConstPointer>      RGBConstVolumeContainer;

typedef itk::SmartPointer<const RGBAVolumeType> RGBAVolumeConstPointer;
typedef std::vector<RGBAVolumeConstPointer>     RGBAConstVolumeContainer;





/** @} */
} // namespace ccipd
#endif // __ccipdVolumeTypes_h
