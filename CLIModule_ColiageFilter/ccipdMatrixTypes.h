#ifndef __ccipdMatrixTypes_h
#define __ccipdMatrixTypes_h
//////////////////////////////////////////////////////////////////////////////////////////
#include "ccipdCore.h"

ccipdDisableAllWarnings
#include <vector> // for containers
#include <memory> // for smart pointers
#include <Eigen/SparseCore>
#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>


using namespace Eigen;


namespace ccipd
{
//////////////////////////////////////////////////////////////////////////////////////////
// Matrix Types

typedef Eigen::Matrix<float, Dynamic, Dynamic, RowMajor, Dynamic, Dynamic> EigenMatrixTypeF; // easily define a dynamic Eigen matrix (Float)

typedef Eigen::Matrix<double, Dynamic, Dynamic, RowMajor, Dynamic, Dynamic> EigenMatrixTypeD; // easily define a dynamic Eigen matrix (Double)

typedef Eigen::Matrix< int, Dynamic, Dynamic, RowMajor, Dynamic, Dynamic> EigenMatrixTypeI; // easily define a dynamic Eigen matrix (int)

typedef Eigen::Matrix<unsigned int, Dynamic, Dynamic, RowMajor, Dynamic, Dynamic> EigenMatrixTypeU; // easily define a dynamic Eigen matrix (Unsigned Integer)

typedef Eigen::Matrix<unsigned char, Dynamic, Dynamic, RowMajor, Dynamic, Dynamic> EigenMatrixTypeUC; // easily define a dynamic Eigen matrix (Unsigned char)


// Vector Types

typedef Eigen::Matrix< float       , Dynamic, 1, ColMajor, Dynamic, 1> EigenVectorTypeF; // easily define a dynamic Eigen vector (Float)

typedef Eigen::Matrix< double      , Dynamic, 1, ColMajor, Dynamic, 1> EigenVectorTypeD; // easily define a dynamic Eigen vector (double)

typedef Eigen::Matrix< int         , Dynamic, 1, ColMajor, Dynamic, 1> EigenVectorTypeI; // easily define a dynamic Eigen vector (int)

typedef Eigen::Matrix< unsigned int, Dynamic, 1, ColMajor, Dynamic, 1> EigenVectorTypeU; // easily define a dynamic Eigen vector (Unsigned integer)

typedef Eigen::Matrix< unsigned char, Dynamic, 1, ColMajor, Dynamic, 1> EigenVectorTypeUC; // easily define a dynamic Eigen vector (Unsigned char)


typedef EigenVectorTypeU EigenLabelVector;

//////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////
// smart pointers
typedef std::shared_ptr<       EigenMatrixTypeF > EigenMatrixPointerF;
typedef std::shared_ptr< const EigenMatrixTypeF > EigenMatrixConstPointerF;
typedef std::shared_ptr<       EigenVectorTypeF > EigenVectorPointerF;
typedef std::shared_ptr< const EigenVectorTypeF > EigenVectorConstPointerF;

typedef std::shared_ptr<       EigenMatrixTypeD > EigenMatrixPointerD;
typedef std::shared_ptr< const EigenMatrixTypeD > EigenMatrixConstPointerD;
typedef std::shared_ptr<       EigenVectorTypeD > EigenVectorPointerD;
typedef std::shared_ptr< const EigenVectorTypeD > EigenVectorConstPointerD;

typedef std::shared_ptr<       EigenMatrixTypeU > EigenMatrixPointerU;
typedef std::shared_ptr< const EigenMatrixTypeU > EigenMatrixConstPointerU;
typedef std::shared_ptr<       EigenVectorTypeU > EigenVectorPointerU;
typedef std::shared_ptr< const EigenVectorTypeU > EigenVectorConstPointerU;

typedef std::shared_ptr<       EigenMatrixTypeUC > EigenMatrixPointerUC;
typedef std::shared_ptr< const EigenMatrixTypeUC > EigenMatrixConstPointerUC;
typedef std::shared_ptr<       EigenVectorTypeUC > EigenVectorPointerUC;
typedef std::shared_ptr< const EigenVectorTypeUC > EigenVectorConstPointerUC;
//////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////
// containers
typedef std::vector< EigenMatrixPointerF      > EigenMatrixCollectionF;
typedef std::vector< EigenMatrixConstPointerF > EigenMatrixConstCollectionF;
typedef std::vector< EigenVectorPointerF      > EigenVectorCollectionF;
typedef std::vector< EigenVectorConstPointerF > EigenVectorConstCollectionF;

typedef std::vector< EigenMatrixPointerD      > EigenMatrixCollectionD;
typedef std::vector< EigenMatrixConstPointerD > EigenMatrixConstCollectionD;
typedef std::vector< EigenVectorPointerD      > EigenVectorCollectionD;
typedef std::vector< EigenVectorConstPointerD > EigenVectorConstCollectionD;


typedef std::vector< EigenMatrixPointerU      > EigenMatrixCollectionU;
typedef std::vector< EigenMatrixConstPointerU > EigenMatrixConstCollectionU;
typedef std::vector< EigenVectorPointerU      > EigenVectorCollectionU;
typedef std::vector< EigenVectorConstPointerU > EigenVectorConstCollectionU;

typedef std::vector< EigenMatrixPointerUC      > EigenMatrixCollectionUC;
typedef std::vector< EigenMatrixConstPointerUC > EigenMatrixConstCollectionUC;
typedef std::vector< EigenVectorPointerUC      > EigenVectorCollectionUC;
typedef std::vector< EigenVectorConstPointerUC > EigenVectorConstCollectionUC;
//////////////////////////////////////////////////////////////////////////////////////////



} // namespace
#endif //__ccipdMatrixTypes_h