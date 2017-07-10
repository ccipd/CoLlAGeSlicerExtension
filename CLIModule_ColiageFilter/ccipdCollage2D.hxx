#ifndef __ccipdCollage2D_hxx
#define __ccipdCollage2D_hxx

// THIS IS FOR THE 3D SLICER PLUGIN

////////////////////////////////////////////////////////////////////////////////////////////////////

// ccipd includes
#include "ccipdCastImage.hxx"
#include "ccipdDuplicateITKImage.hxx"
#include "ccipdGetChannelByIndex.hxx"
#include "ccipdGetTFHaralick2.hxx"
#include "ccipdVolumeTypes.h"
#include "ccipdInsertImage.hxx"
#include "ccipdMatrixTypes.h"
#include "ccipdRescaleImage.hxx"
#include "ccipdRoundITKImage.hxx"
#include "ccipdStdVectorUtils.hxx"
#include "ccipdVolumeTypes.h"

// itk includes
#include <itkImageRegion.h>
#include <itkImageRegionIterator.h>
#include <itkImageRegionConstIterator.h>
#include <itkImage.h>
#include <itkImageDuplicator.h>
#include <itkExceptionObject.h>
#include <itkGradientImageFilter.h>
#include <itkExtractImageFilter.h>
#include <itkImageRegionIteratorWithIndex.h>
#include <itkImageMaskSpatialObject.h>

// vnl includes
#include <vnl/vnl_matrix.h>
#include <vnl/algo/vnl_svd.h>

// std includes
#include <cstddef>

namespace ccipd
{
	template <class TInputImageType>
	typename TInputImageType::Pointer
		CreateITKImage(typename TInputImageType::PixelType uniValue, ...)
	{
		typename TInputImageType::Pointer pImage = TInputImageType::New();

		typename TInputImageType::IndexType start;
		start.Fill(0);

		typename TInputImageType::SizeType size;

		//unsigned int TDimension = pImage->ImageDimension;

		va_list arguments;                  // A place to store the list of arguments
		va_start(arguments, pImage->ImageDimension);    // Initializing arguments to store all values after num
#if defined _MSC_VER
		va_arg(arguments, unsigned int);    // First argument is dummy ONLY on MSVC
#endif

		for (unsigned int x = 0; x < (unsigned int)pImage->ImageDimension; x++)   // Loop until all numbers are added
			size[x] = va_arg(arguments, unsigned int);                           // Adds the next value in argument list to sum.
		va_end(arguments);                                                       // Cleans up the list

		typename TInputImageType::RegionType region(start, size);

		pImage->SetRegions(region);
		pImage->Allocate();
		pImage->FillBuffer(uniValue);

		return pImage;
	}

	template <class TMaskType, unsigned int TDim>
	typename TMaskType::RegionType GetPaddedBoundingBox(typename TMaskType::Pointer pInputMask, typename TMaskType::SizeType paddingPixels, bool bInMM = false)
	{
		//typename TMaskType::RegionType outputRegion;
		typedef itk::ImageRegion< TDim > RegionType;  RegionType outputRegion;

		try
		{
			// get the bounding box
			typedef itk::ImageMaskSpatialObject<TDim> SpatialMaskType;
			typename SpatialMaskType::Pointer spatialMask = SpatialMaskType::New();
			spatialMask->SetImage(pInputMask);
			spatialMask->SetRequestedRegionToLargestPossibleRegion();
			typename SpatialMaskType::BoundingBoxPointer box = spatialMask->GetBoundingBox();
			//bool aa = spatialMask->ComputeBoundingBox();
			//typename SpatialMaskType:PointType cr = spatialMask->GetCenter();
			/*typename SpatialMaskType:PointType mn = spatialMask->GetMinimum();
			typename SpatialMaskType:PointType mx = spatialMask->GetMaximum();*/

			// prepare the output region
			outputRegion = spatialMask->GetAxisAlignedBoundingBoxRegion();

			// pad the bounding box

			if (bInMM)
			{
				typedef itk::Size< TDim > SizeType;
				typename TMaskType::SpacingType spacing = pInputMask->GetSpacing();
				//SizeType paddingPixels;
				for (unsigned int i = 0; i != TDim; ++i)
				{
					// we must deal with values outside the range of
					// unsigned int's, and also negative values
					double paddingPixel = std::fabs(paddingPixels[i] / spacing[i]);

					if (paddingPixel < 0)
					{
						std::cerr << "Error with absolute value!" << std::endl;
						return RegionType();
					}

					// It's interesting, because sometimes itk uses "int"s internally, and when doubling UINT_MAX,
					// the results actually end up being a negative int. Therefore, we won't allow any padding to be
					// larger than UINT_MAX / 10 instead of UINT_MAX.
					unsigned int maxValueInt = static_cast<unsigned int>(std::numeric_limits<int>::max() / 10);
					double maxValueFlt = static_cast<double>(maxValueInt);

					// actually calculate
					paddingPixels[i] = static_cast<unsigned int> (paddingPixel > maxValueFlt ? maxValueInt : paddingPixel);
				}
			}
			//else
			//{
			//    typename TMaskType::SizeType paddingPixels;
			//    paddingPixels.Fill(paddingRadius);
			//}

			outputRegion.PadByRadius(paddingPixels);

			// make sure the output region is not larger than the segmentation image
			bool cropped = outputRegion.Crop(pInputMask->GetLargestPossibleRegion());

			if (!cropped)
			{
				std::cerr << "Bounding box is outside the image! " << "Returning empty bounding box." << std::endl;
				typename TMaskType::RegionType emptyRegion;
				return emptyRegion;
			}
		}
		catch (itk::ExceptionObject & err)
		{
			std::cerr << "Error: Exception caught while creating bounding box ...\nOriginal region is returned." << std::endl << __FILE__ << "  " << __LINE__ << std::endl;
			std::cerr << err << std::endl;
		}

		// output our final region
		return outputRegion;
	}

	/** \brief  : Cropping function templated over image types of input, mask and output
	* \Created: Ahmad 8/18/2015
	* \Updated:
	* \ingroup: Images/Core
	* \param  : pInputImage: Input ITK image
	* \param  : pInputMask : Input Mask
	* \param  : paddingRadius: the padding radius
	* \return : the cropped output image
	* \notes  : This function will crop the given image to a
	*           padded bounding box formed from the given mask.
	*/
	template <class TInputImage, class TInputMask, class TOutputImage, unsigned int TDim>
	typename TOutputImage::Pointer
		CropITKImage(typename TInputImage::Pointer pInputImage, typename TInputMask::Pointer pInputMask, unsigned int paddingRadius = 0)
	{
		try
		{
			// Sanity Check
			if (!pInputImage)
			{
				throw itk::ExceptionObject(__FILE__, __LINE__, "Invalid Input Image ..."); // go to our catch statement
			}

			if (!pInputMask)
			{
				throw itk::ExceptionObject(__FILE__, __LINE__, "Invalid Input Mask ..."); // go to our catch statement
			}

			typename TInputMask::SizeType sz;
			sz.Fill(paddingRadius);
			typename TInputImage::RegionType pROI_padded = GetPaddedBoundingBox<TInputMask, TDim>(pInputMask, sz);

			typedef itk::ExtractImageFilter< TInputImage, TOutputImage > FilterType;
			typename FilterType::Pointer filter = FilterType::New();
			filter->SetExtractionRegion(pROI_padded);
			filter->SetInput(pInputImage);
			filter->SetDirectionCollapseToIdentity(); // This is required.
			filter->Update();

			return filter->GetOutput();
		}
		ccipdCatchExceptionMacro("", nullptr)
	}

	// A function which supports 2D as ITK Get Aligned Axis does not
	template <class TMaskImageType>
	typename TMaskImageType::RegionType GetBoundingBoxFromMask(typename TMaskImageType::Pointer pInputMask)
	{
		typename TMaskImageType::IndexType idxMin, idxMax;
		idxMin.Fill(0);
		idxMax.Fill(0);

		itk::ImageRegionIteratorWithIndex<TMaskImageType> imageIteratorBody(pInputMask, pInputMask->GetLargestPossibleRegion());
		bool bFoundNonZeroPixels = false;
		while (!imageIteratorBody.IsAtEnd())
		{
			typename TMaskImageType::IndexType idx = imageIteratorBody.GetIndex();
			typename TMaskImageType::PixelType pix1 = pInputMask->GetPixel(idx);
			if (pix1 != 0)
			{
				if (bFoundNonZeroPixels)
				{
					for (unsigned int i = 0; i < pInputMask->ImageDimension; i++)
					{
						if (idx[i] < idxMin[i]) idxMin[i] = idx[i];
						if (idx[i] > idxMax[i]) idxMax[i] = idx[i];
					}
				}
				else // first occurrence
				{
					idxMin = idxMax = idx;
				}
				bFoundNonZeroPixels = true;
			}
			++imageIteratorBody;
		}

		typename TMaskImageType::SizeType sizeIm;
		for (unsigned int i = 0; i < pInputMask->ImageDimension; i++)
		{
			sizeIm[i] = idxMax[i] - idxMin[i] + 1;
		}

		typename TMaskImageType::RegionType regionIm;
		regionIm.SetIndex(idxMin);
		regionIm.SetSize(sizeIm);

		return regionIm;
	}

	/*
	This function converts a Vector Image of Features to an Eigen m x n Matrix
	m is the the number of pixels/voxels
	n is the number of features
	It also excludes all the pixels outside the given mask (if not null)

	// ReForms the features and prepares them for classification - Converts from VolumeImageType to EigenMatrixTypeF
	// Prepare the data contain?memcpy_s? was not declared (m x n matrix, m:the number of pixels in the whole 3D Image, n number of components of each pixel in the 3D Image)

	*/
	template <class TInputImageType, class ScalarType>
	Eigen::Matrix<ScalarType, Dynamic, Dynamic, RowMajor, Dynamic, Dynamic>
		ConvertImageToMatrix(typename TInputImageType::Pointer & pImage)
	{
		if (!pImage)
		{
			std::cerr << "Error(19-13): Features Image is not valid ...";
			return Eigen::Matrix<ScalarType, Dynamic, Dynamic, RowMajor, Dynamic, Dynamic>();
		}

		unsigned int nChannels = pImage->GetNumberOfComponentsPerPixel();
		typename TInputImageType::SizeType imSize = pImage->GetBufferedRegion().GetSize(); // Gets the dimensions of the Feature Image
		unsigned int nCols = (unsigned int)(nChannels * pImage->GetBufferedRegion().GetNumberOfPixels() / imSize[0]);

		if (nChannels == 1)
		{
			Eigen::Matrix<ScalarType, Dynamic, Dynamic, ColMajor, Dynamic, Dynamic> outputMatrix(imSize[0], nCols);
			memcpy(outputMatrix.data(), pImage->GetBufferPointer(), imSize[0] * nCols * sizeof(ScalarType));
			return outputMatrix;
		}
		else
		{
			Eigen::Matrix<ScalarType, Dynamic, Dynamic, RowMajor, Dynamic, Dynamic> tempMatrix(imSize[0], nCols);
			memcpy(tempMatrix.data(), pImage->GetBufferPointer(), imSize[0] * nCols * sizeof(ScalarType));

			Eigen::Matrix<ScalarType, Dynamic, Dynamic, RowMajor, Dynamic, Dynamic> outputMatrix(imSize[0], nCols);

			// Now will swap columns to make each matrix block from the left a separate image component/channel
			for (unsigned int c = 0; c < nChannels; c++)
			{
				// Get the temporary block (which will be filled with the image component/channel
				Eigen::Matrix<ScalarType, Dynamic, Dynamic, RowMajor, Dynamic, Dynamic> tempBlockMatrix(imSize[0], imSize[1]);
				for (unsigned int i = 0; i < imSize[1]; i++)
				{
					tempBlockMatrix.col(i) = tempMatrix.col(c + nChannels * i);
				}
				outputMatrix.middleCols(c * imSize[1], imSize[1]) = tempBlockMatrix;
			}
			return outputMatrix;
		}
	}

	template<class TInputImage, class TOutputImage>
	typename TOutputImage::Pointer
		GetFeatureGradient(typename TInputImage::Pointer pInputImage)
	{
		try
		{
			if (!pInputImage)
			{
				std::cout << "Error: Null Image Pointer.\n";
				return typename TOutputImage::Pointer();
			}

			typedef itk::GradientImageFilter< TInputImage, typename TInputImage::PixelType, typename TInputImage::PixelType, TOutputImage >  filterType;
			typename filterType::Pointer gradientFilter = filterType::New();
			gradientFilter->SetInput(pInputImage);

			gradientFilter->OverrideBoundaryCondition(new itk::ZeroFluxNeumannBoundaryCondition<TInputImage>()); // AA deleted in the destructor of filter

			gradientFilter->UseImageDirectionOff();
			gradientFilter->SetUseImageSpacingOff();
			gradientFilter->Update();

			return gradientFilter->GetOutput();
		}
		ccipdCatchExceptionMacro("", typename TOutputImage::Pointer())
	}

	template<class TScalarImageType, unsigned int TDim>
	typename TScalarImageType::Pointer
		GetDirectionalGradient(typename TScalarImageType::Pointer pInputImage, const unsigned int direction) // 0: y, 1: x, 2: z
	{
		try
		{
			if (!pInputImage)
			{
				std::cout << "Error: Null Image Pointer.\n";
				return typename TScalarImageType::Pointer();
			}

			if ((direction) > ((unsigned int)pInputImage->ImageDimension - 1))
			{
				std::cout << "Error: Requested dimension mismatch.\n";
				return typename TScalarImageType::Pointer();
			}

			typedef itk::VectorImage<typename TScalarImageType::PixelType, TDim> TVectorImageType;
			typename TVectorImageType::Pointer pGradientImage = GetFeatureGradient<TScalarImageType, TVectorImageType>(pInputImage);

			//////// Multiply first and last rows/cols of the output Image by 2
			typename TScalarImageType::SizeType imSize = pInputImage->GetBufferedRegion().GetSize();
			EigenMatrixTypeD mat_I(imSize[0], imSize[1]);
			mat_I.setOnes();

			switch (direction)
			{
			case 0: //Gy
				mat_I.row(0).setConstant(2.0f);
				mat_I.row(imSize[0] - 1).setConstant(2.0f);
				break;
			case 1: //Gx
				mat_I.col(0).setConstant(2.0f);
				mat_I.col(imSize[1] - 1).setConstant(2.0f);
				break;
			case 2: // Gz
				break;
			default:
				throw itk::ExceptionObject(__FILE__, __LINE__, "Invalid gradient image ...");
			}

			typename TScalarImageType::Pointer pG = GetChannelByIndex<TVectorImageType, TScalarImageType>(pGradientImage, direction);
			EigenMatrixTypeD mat_G = ConvertImageToMatrix<TScalarImageType, double>(pG);

			// Multiply
			mat_G = mat_G.cwiseProduct(mat_I);

			typename TScalarImageType::Pointer pO = CreateITKImage<TScalarImageType>(0, imSize[0], imSize[1]);
			SetImageFromMatrix<TScalarImageType>(pO, mat_G);
			return pO;
		}
		ccipdCatchExceptionMacro("", typename TScalarImageType::Pointer())
	}

	/*
	If the image is 2D: each matrix element will map to its corresponding position in the image
	*/

	template <class TInputImageType, class Derived>
	void
		SetImageFromMatrix(typename TInputImageType::Pointer & pOutputImage, Eigen::MatrixBase<Derived> const & matrix)
	{
		// Check if the data types are similar
		typename TInputImageType::IndexType ii; ii.Fill(0);
		std::string a1 = typeid(pOutputImage->GetPixel(ii)).name();
		std::string a2 = typeid(matrix(0, 0)).name();
		if (a1.find(a2) == std::string::npos)
		{
			std::cout << "Error: data types mismatch ...";
			return;
		}

		unsigned int nChannels = pOutputImage->GetNumberOfComponentsPerPixel();

		if (nChannels == 1)
		{
			Eigen::Matrix<typename Derived::Scalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor, Eigen::Dynamic, Eigen::Dynamic>
				transposed = matrix.transpose();

			memcpy(pOutputImage->GetBufferPointer(), transposed.data(), matrix.rows() * matrix.cols() * sizeof(typename Derived::Scalar));
		}
		else
		{
			itk::ImageRegionIterator< TInputImageType >   It(pOutputImage, pOutputImage->GetBufferedRegion());

			unsigned int matRows = (unsigned int)matrix.rows();

			typename Derived::Scalar *pArr = new typename Derived::Scalar[matRows * matrix.cols()];

			unsigned int imCols = (unsigned int)pOutputImage->GetLargestPossibleRegion().GetSize()[1];

			for (unsigned int n = 0, c = 0, currentRow = 0, currentCol = 0; n < (matRows * imCols); n++, currentRow++)
			{
				if (currentRow == matRows)
				{
					currentRow = 0;
					currentCol++;
				}

				for (unsigned int i = 0; i < nChannels; i++)
				{
					pArr[c] = matrix(currentRow, currentCol + i * imCols);
					c++;
				}
			}

			memcpy(pOutputImage->GetBufferPointer(), pArr, matRows * matrix.cols() * sizeof(typename Derived::Scalar));

			delete[] pArr;
		}
	} // SetImageFromMatrix

	template<class ScalarType, int Rows, int Cols, int Options>
	Eigen::Matrix<ScalarType, Rows, Cols, Options, Rows, Cols>
		GetV_SVD(Eigen::Matrix<ScalarType, Rows, Cols, Options, Rows, Cols> & Gmat)
	{
		vnl_matrix<double> mat(Gmat.rows(), Gmat.cols());
		for (int r = 0; r < Gmat.rows(); r++)
			for (int c = 0; c < Gmat.cols(); c++)
				mat(r, c) = Gmat(r, c);

		//cout << "\nMAT:\n" << mat << "\n";

		vnl_svd<double> svd(mat);
		vnl_matrix<double> vnl_V = svd.V();

		EigenMatrixTypeD V(vnl_V.rows(), vnl_V.cols());
		for (int r = 0; r < V.rows(); r++)
			for (int c = 0; c < V.cols(); c++)
				V(r, c) = vnl_V(r, c);

		return V;
	}

	template <class TInputImageType>
	std::vector<typename TInputImageType::PixelType> GetUniquePixelValues(typename TInputImageType::Pointer pImage)
	{
		std::vector<typename TInputImageType::PixelType> vecVals;
		try
		{
			if (!pImage)
			{
				throw itk::ExceptionObject(__FILE__, __LINE__, "Error(3489-7450): Invalid image pointer ...");
			}

			itk::ImageRegionConstIterator<TInputImageType> imageIterator(pImage, pImage->GetLargestPossibleRegion());
			while (!imageIterator.IsAtEnd())
			{
				typename TInputImageType::PixelType currentPixel = imageIterator.Get();
				if (std::find(std::begin(vecVals), std::end(vecVals), currentPixel) == std::end(vecVals)) // if not already included in the output vector
				{
					vecVals.push_back(currentPixel);
				}
				++imageIterator;
			}
			return vecVals;
		}
		ccipdCatchExceptionMacro("", vecVals)
	}

	template<class TInputImage, class TInputMask, unsigned int TDim>
	typename SliceImageDoubleType::Pointer
		Collage2D(typename TInputImage::Pointer pInputImage, typename TInputMask::Pointer pInputMask, unsigned int wRadius, unsigned int whichHaralick, bool bOutputROIOnly)
	{
		try
		{
			if (!pInputImage)
			{
				throw itk::ExceptionObject(__FILE__, __LINE__, "Invalid Input Image ..."); // go to our catch statement
			}

			if (!pInputMask)
			{
				throw itk::ExceptionObject(__FILE__, __LINE__, "Invalid Input Mask ..."); // go to our catch statement
			}

			typename TInputMask::Pointer pMask = DuplicateITKImage<TInputMask>(pInputMask);
			std::vector<typename TInputMask::PixelType> vals = GetUniquePixelValues<TInputMask>(pMask);
			if (!isInside<typename TInputMask::PixelType>(vals, (typename TInputMask::PixelType) 1))
			{
				typename TInputMask::IndexType idx = { wRadius, wRadius };
				typename TInputMask::SizeType sz = pMask->GetLargestPossibleRegion().GetSize();
				sz[0] -= 2 * wRadius;
				sz[1] -= 2 * wRadius;
				typename TInputMask::RegionType regionIm;
				regionIm.SetIndex(idx);
				regionIm.SetSize(sz);
				itk::ImageRegionIterator<TInputMask> imageIteratorBody(pMask, regionIm);
				while (!imageIteratorBody.IsAtEnd())
				{
					imageIteratorBody.Set(1);
					++imageIteratorBody;
				}
			}

			// Step 1: Extract the Region of Interest (ROI) padded with radius size
			typename TInputImage::RegionType pROI_inner = GetBoundingBoxFromMask<TInputMask>(pMask);
			if ((0 == pROI_inner.GetSize()[0]) || (0 == pROI_inner.GetSize()[1]))
			{
				throw itk::ExceptionObject(__FILE__, __LINE__, "Empty bounding box ...");
			}
			typename TInputImage::Pointer extractedROI = CropITKImage<TInputImage, TInputMask, TInputImage, 2>(pInputImage, pMask, wRadius);

			// Step 2: Obtain gradients ?fX(c) and ?fY (c) along X- and Y - axes (Lx, Ly)
			typename TInputImage::Pointer pGradX = GetDirectionalGradient< TInputImage, TDim>(extractedROI, 1); // 0: y, 1 : x, 2 : z
			typename TInputImage::Pointer pGradY = GetDirectionalGradient< TInputImage, TDim>(extractedROI, 0); // 0: y, 1 : x, 2 : z
			EigenMatrixTypeD I_gradient_inner = EigenMatrixTypeD::Zero((int)pROI_inner.GetSize(0), (int)pROI_inner.GetSize(1));
			for (size_t i = pROI_inner.GetIndex(0), x = 0; i < pROI_inner.GetIndex(0) + pROI_inner.GetSize(0); i++, x++)
			{
				for (size_t j = pROI_inner.GetIndex(1), y = 0; j < pROI_inner.GetIndex(1) + pROI_inner.GetSize(1); j++, y++)
				{
					EigenMatrixTypeD Gmat((int)pow((2 * wRadius + 1), 2u), 2u);
					unsigned int n = 0;
					for (size_t a = i - wRadius; a < i + wRadius + 1; a++)
					{
						for (size_t b = j - wRadius; b < j + wRadius + 1; b++)
						{
							// Get the pixels of the current region in one column vector
							typename TInputImage::IndexType  index = { { a - pROI_inner.GetIndex(0) + wRadius, b - pROI_inner.GetIndex(1) + wRadius } };
							Gmat(n, 0) = pGradX->GetPixel(index);
							Gmat(n, 1) = pGradY->GetPixel(index);
							n++;
						}
					}

					EigenMatrixTypeD V = /*MatrixUtils::*/GetV_SVD(Gmat);
					I_gradient_inner(x, y) = atan(V(1, 0) / V(0, 0));
					if (abs(V(0, 0)) < 1e-5 || abs(V(1, 0)) < 1e-5) // AA handling a special case when atan(inf) is calculated) (test case added)
					{
						I_gradient_inner(x, y) = 1.570796326794897;
					}
				}
			}

			// Transform the orientation matrix to an image to get the Haralick entropy
			typename TInputImage::Pointer pOrient = CreateITKImage<TInputImage>(0, I_gradient_inner.rows(), I_gradient_inner.cols());
			SetImageFromMatrix<TInputImage>(pOrient, I_gradient_inner);

			// Quantizing the orientation image
			typename SliceImageDoubleType::Pointer pRescaledOrient = RescaleITKImage<TInputImage, SliceImageDoubleType>(pOrient, 0, 64 - 1);

			// Rounding the orientation image
			typename SliceImageDoubleType::Pointer pRoundedRescaledOrient = RoundITKImage<SliceImageDoubleType, SliceImageDoubleType>(pRescaledOrient);

			// Haralick
			typename SliceImageDoubleType::Pointer pColiage = GetTFHaralick2_2D<SliceImageDoubleType>(pRoundedRescaledOrient, 64, 5, 5, whichHaralick, -1);

			// Cast Input Image Type to Double Type, then Insert the image inside the original image (optional)
			if (!bOutputROIOnly)
			{
				typename SliceImageDoubleType::Pointer pInput_Double = CastImage<TInputImage, SliceImageDoubleType>(pInputImage);
				pColiage = InsertImage<SliceImageDoubleType, SliceImageDoubleType>(pColiage, pInput_Double, pROI_inner.GetIndex());
			}

			return pColiage;
		}

		ccipdCatchExceptionMacro("", nullptr);
	}
} // namespace

#endif // __ccipdColiage_hxx
