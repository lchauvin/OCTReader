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

#ifndef __qSlicerOCTReaderModule_h
#define __qSlicerOCTReaderModule_h

// SlicerQt includes
#include "qSlicerLoadableModule.h"

#include "qSlicerOCTReaderModuleExport.h"

class qSlicerOCTReaderModulePrivate;

/// \ingroup Slicer_QtModules_OCTReader
class Q_SLICER_QTMODULES_OCTREADER_EXPORT qSlicerOCTReaderModule :
  public qSlicerLoadableModule
{
  Q_OBJECT
  Q_INTERFACES(qSlicerLoadableModule);

public:

  typedef qSlicerLoadableModule Superclass;
  explicit qSlicerOCTReaderModule(QObject *parent=0);
  virtual ~qSlicerOCTReaderModule();

  qSlicerGetTitleMacro(QTMODULE_TITLE);
  
  /// Help to use the module
  virtual QString helpText()const;

  /// Return acknowledgements
  virtual QString acknowledgementText()const;

  /// Return the authors of the module
  virtual QStringList  contributors()const;

  /// Return a custom icon for the module
  virtual QIcon icon()const;

  /// Return the categories for the module
  virtual QStringList categories()const;

protected:

  /// Initialize the module. Register the volumes reader/writer
  virtual void setup();

  /// Create and return the widget representation associated to this module
  virtual qSlicerAbstractModuleRepresentation * createWidgetRepresentation();

  /// Create and return the logic associated to this module
  virtual vtkMRMLAbstractLogic* createLogic();

protected:
  QScopedPointer<qSlicerOCTReaderModulePrivate> d_ptr;

private:
  Q_DECLARE_PRIVATE(qSlicerOCTReaderModule);
  Q_DISABLE_COPY(qSlicerOCTReaderModule);

};

#endif
