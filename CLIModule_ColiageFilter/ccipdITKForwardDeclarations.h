#ifndef __ccipdITKForwardDeclarations_h
#define __ccipdITKForwardDeclarations_h

#include "ccipdCore.h"

//////////////////////////////////////////////////////////////////////////////////////////
// forward declarations for faster compiling
namespace itk
{

template<
  typename TValueType,
  unsigned int VLength
> class FixedArray;

template<
  class        TPixel,
  unsigned int VImageDimension
> class        Image;

template<typename TComponent> class    RGBPixel;
template<typename TComponent> class    RGBAPixel;

template<
  class        TScalarType,
  unsigned int NInputDimensions,
  unsigned int NOutputDimensions
> class        Transform;

template<
  class        TScalarType,
  unsigned int NInputDimensions,
  unsigned int NOutputDimensions
> class MatrixOffsetTransformBase;

template<
  class        TScalarType,
  unsigned int NDimensions
> class        AffineTransform;

template<
  class        TScalarType, 
  unsigned int NDimensions,
  unsigned int TBSplineOrder
> class        BSplineBaseTransform;

template<
  class        TScalarType, 
  unsigned int NDimensions,
  unsigned int TBSplineOrder
> class        BSplineTransform;

template<
  unsigned int TDimension
> class        ImageMaskSpatialObject;

template<
  unsigned int VImageDimension
> class        ImageRegion;

template<
  unsigned int VImageDimension
> class Size;

template<
  class TObjectType
> class SmartPointer;

template<
  typename T,
  unsigned int TDimension
> class Vector;
  
template<
  typename T,
  unsigned int TDimension
> class CovariantVector;

template<
  class TCoordRep,
  unsigned int NPointDimension
> class Point;

template<
  unsigned int VIndexDimension
> class Index;

template<
  class TInputImage,
  class TOutputImage,
  class TDisplacementField
> class WarpImageFilter;

template<
  unsigned int VImageDimension
> class ImageBase;

template<
  class TFixedImage,
  class TMovingImage
> class ImageToImageMetric;

class SingleValuedCostFunction;

template<
  class TInputImage,
  class TCoordRep
> class InterpolateImageFunction;

template<
  class        TPixel,
  unsigned int VImageDimension
> class VectorImage;

template<
  class TInputImage,
  class TCoordRep
> class VectorInterpolateImageFunction;

template<
  class TElementIdentifier,
  class TElement
> class VectorContainer;

template<
  typename     TPixelType,
  unsigned int VDimension,
  typename     TMeshTraits
> class Mesh;

template<
  typename TPixelType,
  unsigned int VDimension,
  typename TMeshTraits
> class PointSet;

template<
  typename     TPixelType,
  unsigned int VPointDimension,
  unsigned int VMaxTopologicalDimension,
  typename     TCoordRep,
  typename     TInterpolationWeight,
  typename     TCellPixelType
> class DefaultStaticMeshTraits;

class SingleValuedNonLinearOptimizer;

template<
  typename TValueType
> class OptimizerParameters;

class Command;

template<
  typename TFixedImage,
  typename TMovingImage
> class ImageRegistrationMethod;

template<
  class TFixedImage,
  class TMovingImage,
  class TDisplacementField
> class PDEDeformableRegistrationFunction;

namespace fem
{

/// Finite Element Model (FEM)
template<
  unsigned int VDimension
> class FEMObject;

/// FEM Solver
template<
  unsigned int TDimension
> class SolverCrankNicolson;

/// FEM Solver
template<
  unsigned int TDimension
> class Solver;

/// FEM Registration
template<
  class TMovingImage,
  class TFixedImage,
  class TFemObjectType
> class FEMRegistrationFilterBase;

/// Multi-threaded FEM Registration
template<
  class TMovingImage,
  class TFixedImage,
  class TFemObjectType
> class FEMRegistrationFilterMultiThreaded;

class Solution;            ///< FEM Solution
class LinearSystemWrapper; ///< FEM Linear system

/// Image loads
template<
  class TMoving,
  class TFixed
> class FiniteDifferenceFunctionLoad;

class Material;
class MaterialLinearElasticity;
class Element;
class Element3DC0LinearHexahedronMembrane;
class Element3DC0LinearTetrahedron;
class Load;
class LoadLandmark;

} // namespace fem

} // namespace itk
//////////////////////////////////////////////////////////////////////////////////////////



#endif // __ccipdITKForwardDeclarations_h
