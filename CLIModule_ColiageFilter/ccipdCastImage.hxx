#ifndef __ccipdCastImage_hxx
#define __ccipdCastImage_hxx

//////////////////////////////////////////////////////////////////////////////////////////////////
#include "ccipdCore.h"
ccipdDisableAllWarnings
#include <itkCastImageFilter.h>
#include <cstddef>
ccipdEnableAllWarnings
//////////////////////////////////////////////////////////////////////////////////////////////////

namespace ccipd
{
	template<class TInputImage, class TOutputImage>
	typename TOutputImage::Pointer
		CastImage(typename TInputImage::Pointer inImage)
	{
		try
		{
			if (!inImage)
			{
				throw itk::ExceptionObject(__FILE__, __LINE__, "Error(34-750): Invalid Image pointer ..."); // go to our catch statement
			}

			typedef itk::CastImageFilter< TInputImage, TOutputImage> CastImageFilterType;
			typename CastImageFilterType::Pointer castFilter = CastImageFilterType::New();

			castFilter->SetInput(inImage);
			castFilter->Update();

			return castFilter->GetOutput();
		}
		ccipdCatchExceptionMacro("", nullptr)
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace ccipd
#endif // ccipdCastImage_hxx