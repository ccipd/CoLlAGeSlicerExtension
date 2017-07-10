# CoLlAGe Filter Extension

This extension provides user-friendly implementation of CoLlAGe filter.

# Co-occurrence of Local Anisotropic Gradient Orientations (CoLlAGe)

CoLlAGe captures subtle anisotropic differences in disease pathologies by measuring entropy of co-occurrences of voxel-level gradient orientations on imaging computed within a local neighborhood. CoLlAGe is based on the hypothesis that disruption in tissue microarchitecture can be quantified on imaging by measuring the disorder in voxel-wise gradient orientations. CoLlAGe involves assigning every image voxel a ‘disorder value’ associated with the co-occurrence matrix of gradient orientations computed around every voxel. Details on extraction of CoLlAGe features are included in [1, 2].
After feature extraction, the subsequent distribution or different statistics such as mean, median, variance etc can be computed and used in conjunction with a machine learning classifier to distinguish similar appearing pathologies. 
The feasibility of CoLlAGe in distinguishing cancer from treatment confounders/benign conditions and characterizing molecular subtypes of cancers has been demonstrated in the context of three challenging clinical problems [1, 2].

# References

[1] Prasanna, P., Tiwari, P., & Madabhushi, A. (2016). Co-occurrence of Local Anisotropic Gradient Orientations (CoLlAGe): A new radiomics descriptor. Scientific Reports, 6.
[2] Prasanna, P., Tiwari, P., & Madabhushi, A. (2014, September). Co-occurrence of Local Anisotropic Gradient Orientations (CoLlAGe): distinguishing tumor confounders and molecular subtypes on MRI. In International Conference on Medical Image Computing and Computer-Assisted Intervention (pp. 73-80). Springer International Publishing.

# Licenses

This code comes under the following license

 * Apache 2.0 - Read file: LICENSE