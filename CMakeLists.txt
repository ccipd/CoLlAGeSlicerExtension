cmake_minimum_required(VERSION 2.8.9)

project(SlicerExtension_ColiageFilter)

#-----------------------------------------------------------------------------
# Extension meta-information
set(EXTENSION_HOMEPAGE "http://slicer.org/slicerWiki/index.php/Documentation/Nightly/Extensions/SlicerExtension_ColiageFilter")
set(EXTENSION_CATEGORY "Examples")
set(EXTENSION_CONTRIBUTORS "Ahmad Algohary (Case Western Reserve University)")
set(EXTENSION_DESCRIPTION "This is an example of a simple extension for extracting Coliage filter.")
set(EXTENSION_ICONURL "http://www.example.com/Slicer/Extensions/SlicerExtension_ColiageFilter.png")
set(EXTENSION_SCREENSHOTURLS "http://www.example.com/Slicer/Extensions/SlicerExtension_ColiageFilter/Screenshots/1.png")

#-----------------------------------------------------------------------------
# Extension dependencies
find_package(Slicer REQUIRED)
include(${Slicer_USE_FILE})

#-----------------------------------------------------------------------------
# Extension modules
add_subdirectory(LoadableModule_ColiageFilter)
add_subdirectory(CLIModule_ColiageFilter)
add_subdirectory(ScriptedModule_ColiageFilter)
## NEXT_MODULE

#-----------------------------------------------------------------------------
include(${Slicer_EXTENSION_CPACK})
