#ifndef __ccipdRoundITKImage_hxx
#define __ccipdRoundITKImage_hxx

#include "ccipdCore.h"
ccipdDisableAllWarnings
#include <itkRoundImageFilter.h>
ccipdEnableAllWarnings

namespace ccipd
{
	template <class TInputImageType, class TOutputImageType>
	typename TOutputImageType::Pointer RoundITKImage(typename TInputImageType::Pointer pImage)
	{
		try
		{
			if (!pImage)
			{
				throw itk::ExceptionObject(__FILE__, __LINE__, "Invalid Input Image ...");
			}

			typedef itk::RoundImageFilter< TInputImageType, TOutputImageType > FilterType;
			typename FilterType::Pointer pFilter = FilterType::New();
			pFilter->SetInput(pImage);
			pFilter->Update();
			return pFilter->GetOutput();
		}
		ccipdCatchExceptionMacro("", nullptr);
	}
} // namespace

#endif