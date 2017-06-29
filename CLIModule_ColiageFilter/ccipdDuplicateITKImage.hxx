#ifndef __ccipdDuplicateITKImage_hxx
#define __ccipdDuplicateITKImage_hxx

//////////////////////////////////////////////////////////////////////////////////////////
#include "ccipdCore.h"
ccipdDisableAllWarnings
#include <itkImageDuplicator.h>
ccipdEnableAllWarnings
//////////////////////////////////////////////////////////////////////////////////////////

namespace ccipd
{
	template< class TImageType >
	typename TImageType::Pointer DuplicateITKImage(typename TImageType::Pointer pImage)
	{
		try
		{
			typedef itk::ImageDuplicator< TImageType  > DuplicatorType;
			typename DuplicatorType::Pointer duplicator = DuplicatorType::New();
			duplicator->SetInputImage(pImage);
			duplicator->Update();
			return duplicator->GetOutput();
		}
		ccipdCatchExceptionMacro("", nullptr)
	}
} // namespace
#endif // __ccipdDuplicateImage_hxx