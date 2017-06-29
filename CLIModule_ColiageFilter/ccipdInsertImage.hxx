#ifndef __ccipdInsertImage_hxx
#define __ccipdInsertImage_hxx

////////////////////////////////////////////////////////////////////////////////////////////////////
// ccipd includes
#include "ccipdCore.h"
#include "ccipdVolumeTypes.h"

ccipdDisableAllWarnings
// itk includes
#include <itkImageRegion.h>
#include <itkImage.h>
#include <itkFixedArray.h>
#include <itkRegionOfInterestImageFilter.h>
#include <itkPasteImageFilter.h>

ccipdEnableAllWarnings

// std includes
#include <cmath> // for floor and ceil
////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ccipd
{
	/** \brief  : Takes a section of one image and paste into another image.
	* \Created: Ahmad 1/17/2014
	* \Updated:
	* \ingroup: Common Images
	* \param  : pDestinationImage: The destinationtion image into which a region will be inserted
	* \param  : pSourceImage     : The source image from which a region will be copied
	* \param  : destinationIndex : The index of the destination image at which insertion starts
	* \param  : sourceRegion     : The region to be copied from the source image
	* \return : A smart pointer to the modified destination image
	* \Note(s): If the sourceRegion is NULL, then the whole sourceImage will be inserted into
	*           the destinationImage at the given destinationIndex
	*/
	template <class TInputImage, class TOutputImage>
	typename TOutputImage::Pointer
		InsertRegion(typename TInputImage::Pointer    pSourceImage
		, typename TOutputImage::Pointer   pDestinationImage
		, typename TOutputImage::IndexType destinationIndex
		, typename TInputImage::RegionType sourceRegion
		)
	{
		// Check if pointers are valid
		if (!pSourceImage || !pDestinationImage)
		{
			std::cerr << "\nError: Invalid input Images ... \n"
				<< __FILE__ << "  " << __LINE__;
			return NULL;
		}

		// Check if sourceRegion (if not null) lies inside the pSourceImage
		if (!sourceRegion.GetSize()[0])
		{
			sourceRegion = pSourceImage->GetLargestPossibleRegion();
		}
		else
		{
			if (!sourceRegion.IsInside(pSourceImage->GetBufferedRegion()))
			{
				std::cerr << "\\nError: Source region is not totally inside the source image ... \n"
					<< __FILE__ << "  " << __LINE__;
				return NULL;
			}
		}

		// Check if destinationIndex lies inside the pDestinationImage

		// Check if source region is inside the destination image at the given index

		typedef itk::PasteImageFilter <TInputImage, TOutputImage > PasteImageFilterType;
		typename PasteImageFilterType::Pointer pasteFilter = PasteImageFilterType::New();
		pasteFilter->SetSourceImage(pSourceImage);
		pasteFilter->SetDestinationImage(pDestinationImage);
		pasteFilter->SetDestinationIndex(destinationIndex);
		pasteFilter->SetSourceRegion(sourceRegion);
		pasteFilter->Update();
		return pasteFilter->GetOutput();
	}

	/** \brief  : A special case of InsertRegion where the whole source image is inserted into the destination image.
	* \Created: Ahmad 1/17/2014
	* \Updated:
	* \ingroup: Common Images
	* \param  : pDestinationImage: The destination image into which a region will be inserted
	* \param  : pSourceImage     : The source image from which a region will be copied
	* \param  : destinationIndex : The index of the destination image at which insertion starts
	* \return : A smart pointer to the modified destination image
	*/
	template <class TInputImageType, class TOutputImage>
	typename TOutputImage::Pointer
		InsertImage(typename TInputImageType::Pointer    pSourceImage
		, typename TOutputImage::Pointer       pDestinationImage
		, typename TOutputImage::IndexType     destinationIndex
		)
	{
		// Check only if source image pointer is valid, additional checks will be applied in the InsertRegion function
		if (!pSourceImage || !pDestinationImage)
		{
			std::cerr << "\nError: Invalid input Images ... \n"
				<< __FILE__ << "  " << __LINE__;
			return NULL;
		}

		return InsertRegion<TInputImageType, TOutputImage>(pSourceImage, pDestinationImage, destinationIndex, pSourceImage->GetBufferedRegion());
	}
} // namespace
#endif // __ccipdInsertImage_hxx