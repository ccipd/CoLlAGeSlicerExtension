# DEPRECATED

Please note that CoLlAGe has been fully rebuilt as a Python module and is available as a PIP/Docker install. We are currently testing integrating the new version of CoLlAGe into 3D Slicer, as well as other platforms.

Please visit/star the NEW UPDATED repository at: https://github.com/radxtools/collageradiomics
 
# CoLlAGe Extension

This release is an alpha implementation of the CoLlAGe radiomics descriptor built as a 3D Slicer plugin. An alpha version of a command-line executable is also available under [Releases](https://github.com/ccipd/CoLlAGeSlicerExtension/releases)

# Co-occurrence of Local Anisotropic Gradient Orientations (CoLlAGe)

CoLlAGe captures subtle anisotropic differences in disease pathologies by measuring entropy of co-occurrences of voxel-level gradient orientations on imaging computed within a local neighborhood. CoLlAGe is based on the hypothesis that disruption in tissue microarchitecture can be quantified on imaging by measuring the disorder in voxel-wise gradient orientations. CoLlAGe involves assigning every image voxel a ‘disorder value’ associated with the co-occurrence matrix of gradient orientations computed around every voxel. Details on extraction of CoLlAGe features are included in [1]. After feature extraction, the subsequent distribution or different statistics such as mean, median, variance etc can be computed and used in conjunction with a machine learning classifier to distinguish similar appearing pathologies. The feasibility of CoLlAGe in distinguishing cancer from treatment confounders/benign conditions and characterizing molecular subtypes of cancers has been demonstrated in the context of multiple challenging clinical problems.

# References

[1] Prasanna, P., Tiwari, P., & Madabhushi, A. (2016). Co-occurrence of Local Anisotropic Gradient Orientations (CoLlAGe): A new radiomics descriptor. Scientific Reports, 6:37241.

# Licenses

This code comes under the following license: Apache 2.0 - Read file: LICENSE
