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

// Qt includes
#include <QtPlugin>

// LoadableModule_ColiageFilter Logic includes
#include <vtkSlicerLoadableModule_ColiageFilterLogic.h>

// LoadableModule_ColiageFilter includes
#include "qSlicerLoadableModule_ColiageFilterModule.h"
#include "qSlicerLoadableModule_ColiageFilterModuleWidget.h"

//-----------------------------------------------------------------------------
Q_EXPORT_PLUGIN2(qSlicerLoadableModule_ColiageFilterModule, qSlicerLoadableModule_ColiageFilterModule);

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_ExtensionTemplate
class qSlicerLoadableModule_ColiageFilterModulePrivate
{
public:
  qSlicerLoadableModule_ColiageFilterModulePrivate();
};

//-----------------------------------------------------------------------------
// qSlicerLoadableModule_ColiageFilterModulePrivate methods

//-----------------------------------------------------------------------------
qSlicerLoadableModule_ColiageFilterModulePrivate::qSlicerLoadableModule_ColiageFilterModulePrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerLoadableModule_ColiageFilterModule methods

//-----------------------------------------------------------------------------
qSlicerLoadableModule_ColiageFilterModule::qSlicerLoadableModule_ColiageFilterModule(QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerLoadableModule_ColiageFilterModulePrivate)
{
}

//-----------------------------------------------------------------------------
qSlicerLoadableModule_ColiageFilterModule::~qSlicerLoadableModule_ColiageFilterModule()
{
}

//-----------------------------------------------------------------------------
QString qSlicerLoadableModule_ColiageFilterModule::helpText() const
{
  return "This is a loadable module that can be bundled in an extension";
}

//-----------------------------------------------------------------------------
QString qSlicerLoadableModule_ColiageFilterModule::acknowledgementText() const
{
  return "This work was partially funded by NIH grant NXNNXXNNNNNN-NNXN";
}

//-----------------------------------------------------------------------------
QStringList qSlicerLoadableModule_ColiageFilterModule::contributors() const
{
  QStringList moduleContributors;
  moduleContributors << QString("John Doe (AnyWare Corp.)");
  return moduleContributors;
}

//-----------------------------------------------------------------------------
QIcon qSlicerLoadableModule_ColiageFilterModule::icon() const
{
  return QIcon(":/Icons/LoadableModule_ColiageFilter.png");
}

//-----------------------------------------------------------------------------
QStringList qSlicerLoadableModule_ColiageFilterModule::categories() const
{
  return QStringList() << "Examples";
}

//-----------------------------------------------------------------------------
QStringList qSlicerLoadableModule_ColiageFilterModule::dependencies() const
{
  return QStringList();
}

//-----------------------------------------------------------------------------
void qSlicerLoadableModule_ColiageFilterModule::setup()
{
  this->Superclass::setup();
}

//-----------------------------------------------------------------------------
qSlicerAbstractModuleRepresentation* qSlicerLoadableModule_ColiageFilterModule
::createWidgetRepresentation()
{
  return new qSlicerLoadableModule_ColiageFilterModuleWidget;
}

//-----------------------------------------------------------------------------
vtkMRMLAbstractLogic* qSlicerLoadableModule_ColiageFilterModule::createLogic()
{
  return vtkSlicerLoadableModule_ColiageFilterLogic::New();
}
