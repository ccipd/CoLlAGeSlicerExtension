#ifndef __ccipdRescaleImage_hxx
#define __ccipdRescaleImage_hxx

#include "ccipdCore.h"
ccipdDisableAllWarnings
#include <itkRescaleIntensityImageFilter.h>
ccipdEnableAllWarnings

namespace ccipd
{
	template <class TInputImageType, class TOutputImageType>
	typename TOutputImageType::Pointer RescaleITKImage(typename TInputImageType::Pointer pImage, typename TInputImageType::PixelType minVal, typename TInputImageType::PixelType maxVal)
	{
		try
		{
			if (!pImage)
			{
				throw itk::ExceptionObject(__FILE__, __LINE__, "Invalid Input Image ...");
			}

			typedef itk::RescaleIntensityImageFilter< TInputImageType, TOutputImageType > RescaleFilterType;
			typename RescaleFilterType::Pointer rescaleFilter = RescaleFilterType::New();
			rescaleFilter->SetInput(pImage);
			rescaleFilter->SetOutputMinimum(minVal);
			rescaleFilter->SetOutputMaximum(maxVal);
			rescaleFilter->Update();
			return rescaleFilter->GetOutput();
		}
		ccipdCatchExceptionMacro("", nullptr);
	}
} // namespace

#endif