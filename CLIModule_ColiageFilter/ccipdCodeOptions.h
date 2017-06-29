

/**
 * Cmake will define CCIPD_DLL_EXPORT on Windows when it configures to build a shared library.
 * We will also have CMake manually define BUILD_SHARED_LIBRARIES so that others can easily use our DLLs.
 */

/* #undef BUILD_SHARED_LIBRARIES */

// We are using the Visual Studio Compiler and building Shared libraries
#if	( defined( _WIN32 ) &&  defined ( BUILD_SHARED_LIBRARIES ) )
  #define CCIPD_DLL_EXPORT __declspec(dllexport)
#else
  // Only with Windows DLL's do we need special considerations
  #define CCIPD_DLL_EXPORT
#endif

