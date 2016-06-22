/*==============================================================================

  Program: 3D Slicer

  Copyright (c) Kitware Inc.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Jean-Christophe Fillion-Robin, Kitware Inc.
  and was partially funded by NIH grant 3P41RR013218-12S1

==============================================================================*/

// FooBar Widgets includes
#include "qSlicerLoadableModule_ColiageFilterFooBarWidget.h"
#include "ui_qSlicerLoadableModule_ColiageFilterFooBarWidget.h"

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_LoadableModule_ColiageFilter
class qSlicerLoadableModule_ColiageFilterFooBarWidgetPrivate
  : public Ui_qSlicerLoadableModule_ColiageFilterFooBarWidget
{
  Q_DECLARE_PUBLIC(qSlicerLoadableModule_ColiageFilterFooBarWidget);
protected:
  qSlicerLoadableModule_ColiageFilterFooBarWidget* const q_ptr;

public:
  qSlicerLoadableModule_ColiageFilterFooBarWidgetPrivate(
    qSlicerLoadableModule_ColiageFilterFooBarWidget& object);
  virtual void setupUi(qSlicerLoadableModule_ColiageFilterFooBarWidget*);
};

// --------------------------------------------------------------------------
qSlicerLoadableModule_ColiageFilterFooBarWidgetPrivate
::qSlicerLoadableModule_ColiageFilterFooBarWidgetPrivate(
  qSlicerLoadableModule_ColiageFilterFooBarWidget& object)
  : q_ptr(&object)
{
}

// --------------------------------------------------------------------------
void qSlicerLoadableModule_ColiageFilterFooBarWidgetPrivate
::setupUi(qSlicerLoadableModule_ColiageFilterFooBarWidget* widget)
{
  this->Ui_qSlicerLoadableModule_ColiageFilterFooBarWidget::setupUi(widget);
}

//-----------------------------------------------------------------------------
// qSlicerLoadableModule_ColiageFilterFooBarWidget methods

//-----------------------------------------------------------------------------
qSlicerLoadableModule_ColiageFilterFooBarWidget
::qSlicerLoadableModule_ColiageFilterFooBarWidget(QWidget* parentWidget)
  : Superclass( parentWidget )
  , d_ptr( new qSlicerLoadableModule_ColiageFilterFooBarWidgetPrivate(*this) )
{
  Q_D(qSlicerLoadableModule_ColiageFilterFooBarWidget);
  d->setupUi(this);
}

//-----------------------------------------------------------------------------
qSlicerLoadableModule_ColiageFilterFooBarWidget
::~qSlicerLoadableModule_ColiageFilterFooBarWidget()
{
}
