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
#include <QDebug>

// SlicerQt includes
#include "qSlicerLoadableModule_ColiageFilterModuleWidget.h"
#include "ui_qSlicerLoadableModule_ColiageFilterModuleWidget.h"

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_ExtensionTemplate
class qSlicerLoadableModule_ColiageFilterModuleWidgetPrivate: public Ui_qSlicerLoadableModule_ColiageFilterModuleWidget
{
public:
  qSlicerLoadableModule_ColiageFilterModuleWidgetPrivate();
};

//-----------------------------------------------------------------------------
// qSlicerLoadableModule_ColiageFilterModuleWidgetPrivate methods

//-----------------------------------------------------------------------------
qSlicerLoadableModule_ColiageFilterModuleWidgetPrivate::qSlicerLoadableModule_ColiageFilterModuleWidgetPrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerLoadableModule_ColiageFilterModuleWidget methods

//-----------------------------------------------------------------------------
qSlicerLoadableModule_ColiageFilterModuleWidget::qSlicerLoadableModule_ColiageFilterModuleWidget(QWidget* _parent)
  : Superclass( _parent )
  , d_ptr( new qSlicerLoadableModule_ColiageFilterModuleWidgetPrivate )
{
}

//-----------------------------------------------------------------------------
qSlicerLoadableModule_ColiageFilterModuleWidget::~qSlicerLoadableModule_ColiageFilterModuleWidget()
{
}

//-----------------------------------------------------------------------------
void qSlicerLoadableModule_ColiageFilterModuleWidget::setup()
{
  Q_D(qSlicerLoadableModule_ColiageFilterModuleWidget);
  d->setupUi(this);
  this->Superclass::setup();
}
