#ifndef __ccipdGetChannelByIndex_hxx__
#define __ccipdGetChannelByIndex_hxx__

#include "ccipdVolumeTypes.h"
#include "ccipdCore.h"
ccipdDisableAllWarnings

		// itk includes
		#include <itkImage.h>
		#include <itkVectorImage.h>
		#include <itkVectorIndexSelectionCastImageFilter.h>

		// std includes
		#include <iostream>		

ccipdEnableAllWarnings

namespace ccipd
{

/**
 * Gets an indexed component from a given vector image
 * 
 * \author  Ahmad
 * \ingroup Common Images
 */
template< class TVectorImage, class TScalarImage >
typename TScalarImage::Pointer 
GetChannelByIndex(  const typename TVectorImage::Pointer input
                  , const unsigned int                   index 
			     )
{
    try
    {
	    // safety checks
	    if(!input)
	    {
		    std::cout << "\nError(899-36-34): Invalid input ...";
		    return nullptr;
	    }

	    if ( index >= (unsigned int)input->GetNumberOfComponentsPerPixel() )
	    {
		    std::cout << "\nError(119-36-34): Invalid channel index ...";
		    return nullptr;
	    }

	    // objects
	    typedef itk::VectorIndexSelectionCastImageFilter< TVectorImage, TScalarImage > FeatureExtractorType;
	    typename FeatureExtractorType::Pointer featureExtractor = FeatureExtractorType::New();

	    // inputs
	    featureExtractor->SetInput( input );
	    featureExtractor->SetIndex( index );
        featureExtractor->SetNumberOfThreads(1);

	    // update and output
	    featureExtractor->Update();
	    return featureExtractor->GetOutput();
    }
    ccipdCatchExceptionMacro("", nullptr)
} // GetChannelByIndex




}


#endif