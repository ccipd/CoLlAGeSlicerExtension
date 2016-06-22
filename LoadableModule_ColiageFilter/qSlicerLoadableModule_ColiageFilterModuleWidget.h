/*==============================================================================

  Program: 3D Slicer

  Portions (c) Copyright Brigham and Women's Hospital (BWH) All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

==============================================================================*/

#ifndef __qSlicerLoadableModule_ColiageFilterModuleWidget_h
#define __qSlicerLoadableModule_ColiageFilterModuleWidget_h

// SlicerQt includes
#include "qSlicerAbstractModuleWidget.h"

#include "qSlicerLoadableModule_ColiageFilterModuleExport.h"

class qSlicerLoadableModule_ColiageFilterModuleWidgetPrivate;
class vtkMRMLNode;

/// \ingroup Slicer_QtModules_ExtensionTemplate
class Q_SLICER_QTMODULES_LOADABLEMODULE_COLIAGEFILTER_EXPORT qSlicerLoadableModule_ColiageFilterModuleWidget :
  public qSlicerAbstractModuleWidget
{
  Q_OBJECT

public:

  typedef qSlicerAbstractModuleWidget Superclass;
  qSlicerLoadableModule_ColiageFilterModuleWidget(QWidget *parent=0);
  virtual ~qSlicerLoadableModule_ColiageFilterModuleWidget();

public slots:


protected:
  QScopedPointer<qSlicerLoadableModule_ColiageFilterModuleWidgetPrivate> d_ptr;

  virtual void setup();

private:
  Q_DECLARE_PRIVATE(qSlicerLoadableModule_ColiageFilterModuleWidget);
  Q_DISABLE_COPY(qSlicerLoadableModule_ColiageFilterModuleWidget);
};

#endif
