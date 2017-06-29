#include "itkImageFileWriter.h"
#include "itkPluginUtilities.h"
#include "CLIModule_ColiageFilterCLP.h"

#include "ccipdCollage2D.hxx"

// Use an anonymous namespace to keep class types and function names
// from colliding when module is used as shared object module.  Every
// thing should be in an anonymous namespace except for the module
// entry point, e.g. main()
//
namespace
{
	template <typename TPixel>
	int DoIt(int argc, char * argv[], TPixel)
	{
		//////////////////////////////////////////////////////////////////////////
		// Parse arguments and define required types
		PARSE_ARGS;
		const unsigned int SliceDimension = 2;
		const unsigned int VolumeDimension = 3;

		// Pixel types
		typedef TPixel         InputPixelType;
		typedef double         OutputPixelType;
		typedef unsigned char  MaskPixelType;

		// Image types
		typedef itk::Image<InputPixelType, SliceDimension> InputImageType;
		typedef itk::Image<double, SliceDimension> OutputImageType;
		typedef itk::Image<MaskPixelType, SliceDimension> InputSliceMaskType;

		// Reading Input Image
		typedef itk::ImageFileReader<InputImageType>  inImReaderType;
		typename inImReaderType::Pointer pInImReader = inImReaderType::New();
		pInImReader->SetFileName(inputImage.c_str());
		typename InputImageType::Pointer pInImage = pInImReader->GetOutput();

		// Reading Input Mask
		typedef itk::ImageFileReader<InputSliceMaskType>  inMskReaderType;
		typename inMskReaderType::Pointer pInMskReader = inMskReaderType::New();
		pInMskReader->SetFileName(inputMask.c_str());
		typename InputSliceMaskType::Pointer pInMask = pInMskReader->GetOutput();

		//std::cout << "test1\n" << inputImage.c_str() << "\n";

		// Extracting Coliage
		typename OutputImageType::Pointer pColiage = ccipd::Collage2D<InputImageType, InputSliceMaskType, 2>(pInImage, pInMask, radius, 1, false);

		if (!pColiage->GetBufferPointer())
		{
			//std::cout << "test2\n" << inputImage.c_str() << "\n";
			return EXIT_FAILURE;
		}

		////////////////////////////////////////////////////////////////////////////
		// Writing output image to file

		typedef itk::ImageFileWriter<OutputImageType> WriterType;
		typename WriterType::Pointer writer = WriterType::New();
		writer->SetFileName(outputImage.c_str());
		writer->SetInput(pColiage);
		writer->SetUseCompression(1);
		writer->Update();

		return EXIT_SUCCESS;
	}
} // end of anonymous namespace

int main(int argc, char * argv[])
{
	PARSE_ARGS;

	itk::ImageIOBase::IOPixelType     pixelType;
	itk::ImageIOBase::IOComponentType componentType;

	try
	{
		itk::GetImageType(inputImage, pixelType, componentType);

		// This filter handles all types on input, but only produces
		// signed types
		switch (componentType)
		{
		case itk::ImageIOBase::UCHAR:
			return DoIt(argc, argv, static_cast<unsigned char>(0));
			break;
		case itk::ImageIOBase::CHAR:
			return DoIt(argc, argv, static_cast<signed char>(0));
			break;
		case itk::ImageIOBase::USHORT:
			return DoIt(argc, argv, static_cast<unsigned short>(0));
			break;
		case itk::ImageIOBase::SHORT:
			return DoIt(argc, argv, static_cast<short>(0));
			break;
		case itk::ImageIOBase::UINT:
			return DoIt(argc, argv, static_cast<unsigned int>(0));
			break;
		case itk::ImageIOBase::INT:
			return DoIt(argc, argv, static_cast<int>(0));
			break;
		case itk::ImageIOBase::ULONG:
			return DoIt(argc, argv, static_cast<unsigned long>(0));
			break;
		case itk::ImageIOBase::LONG:
			return DoIt(argc, argv, static_cast<long>(0));
			break;
		case itk::ImageIOBase::FLOAT:
			return DoIt(argc, argv, static_cast<float>(0));
			break;
		case itk::ImageIOBase::DOUBLE:
			return DoIt(argc, argv, static_cast<double>(0));
			break;
		case itk::ImageIOBase::UNKNOWNCOMPONENTTYPE:
		default:
			std::cerr << "Unknown input image pixel component type: ";
			std::cerr << itk::ImageIOBase::GetComponentTypeAsString(componentType);
			std::cerr << std::endl;
			return EXIT_FAILURE;
			break;
		}
	}

	catch (itk::ExceptionObject & excep)
	{
		std::cerr << argv[0] << ": exception caught !" << std::endl;
		std::cerr << excep << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}