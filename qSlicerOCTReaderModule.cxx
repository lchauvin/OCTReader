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

// OCTReader Logic includes
#include <vtkSlicerOCTReaderLogic.h>

// OCTReader includes
#include "qSlicerOCTReaderModule.h"
#include "qSlicerOCTReaderModuleWidget.h"

//-----------------------------------------------------------------------------
Q_EXPORT_PLUGIN2(qSlicerOCTReaderModule, qSlicerOCTReaderModule);

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_OCTReader
class qSlicerOCTReaderModulePrivate
{
public:
  qSlicerOCTReaderModulePrivate();
};

//-----------------------------------------------------------------------------
// qSlicerOCTReaderModulePrivate methods

//-----------------------------------------------------------------------------
qSlicerOCTReaderModulePrivate::qSlicerOCTReaderModulePrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerOCTReaderModule methods

//-----------------------------------------------------------------------------
qSlicerOCTReaderModule::qSlicerOCTReaderModule(QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerOCTReaderModulePrivate)
{
}

//-----------------------------------------------------------------------------
QStringList qSlicerOCTReaderModule::categories()const
{
  return QStringList() << "IGT";
}

//-----------------------------------------------------------------------------
qSlicerOCTReaderModule::~qSlicerOCTReaderModule()
{
}

//-----------------------------------------------------------------------------
QString qSlicerOCTReaderModule::helpText()const
{
  QString help = 
    "This template module is meant to be used with the"
    "with the ModuleWizard.py script distributed with the"
    "Slicer source code (starting with version 4)."
    "Developers can generate their own source code using the"
    "wizard and then customize it to fit their needs.";
  return help;
}

//-----------------------------------------------------------------------------
QString qSlicerOCTReaderModule::acknowledgementText()const
{
  return "This work was supported by NAMIC, NAC, and the Slicer Community...";
}

//-----------------------------------------------------------------------------
QStringList qSlicerOCTReaderModule::contributors()const
{
  QStringList moduleContributors;
  moduleContributors << QString("John Doe (Organization)");
  // moduleContributors << QString("Richard Roe (Organization2)");
  // ...
  return moduleContributors;
}

//-----------------------------------------------------------------------------
QIcon qSlicerOCTReaderModule::icon()const
{
  return QIcon(":/Icons/OCTReader.png");
}

//-----------------------------------------------------------------------------
void qSlicerOCTReaderModule::setup()
{
  this->Superclass::setup();
}

//-----------------------------------------------------------------------------
qSlicerAbstractModuleRepresentation * qSlicerOCTReaderModule::createWidgetRepresentation()
{
  return new qSlicerOCTReaderModuleWidget;
}

//-----------------------------------------------------------------------------
vtkMRMLAbstractLogic* qSlicerOCTReaderModule::createLogic()
{
  return vtkSlicerOCTReaderLogic::New();
}
