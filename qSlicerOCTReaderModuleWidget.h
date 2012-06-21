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

#ifndef __qSlicerOCTReaderModuleWidget_h
#define __qSlicerOCTReaderModuleWidget_h

// SlicerQt includes
#include "qSlicerAbstractModuleWidget.h"
#include <QMap>

#include "qSlicerOCTReaderModuleExport.h"

class qSlicerOCTReaderModuleWidgetPrivate;
class vtkMRMLNode;
class vtkMRMLScene;
class vtkMRMLVolumeNode;

/// \ingroup Slicer_QtModules_OCTReader
class Q_SLICER_QTMODULES_OCTREADER_EXPORT qSlicerOCTReaderModuleWidget :
  public qSlicerAbstractModuleWidget
{
  Q_OBJECT

public:

  typedef qSlicerAbstractModuleWidget Superclass;
  qSlicerOCTReaderModuleWidget(QWidget *parent=0);
  virtual ~qSlicerOCTReaderModuleWidget();

public slots:
  void OpenFileDialog();
  void CreateVolume();
  void CenterVolume(vtkMRMLVolumeNode* volumeNode);

protected:
  QScopedPointer<qSlicerOCTReaderModuleWidgetPrivate> d_ptr;
  
  virtual void setup();

private:
  Q_DECLARE_PRIVATE(qSlicerOCTReaderModuleWidget);
  Q_DISABLE_COPY(qSlicerOCTReaderModuleWidget);

  QString binaryFilename;

  enum scalarType{
    int8,
    uint8,
    int16,
    uint16,
    int32,
    uint32,
    float32,
    float64
  };
  typedef QMap<QString, scalarType> StringToScalarTypeMap;
  StringToScalarTypeMap strToScalarTypeMap;

};

#endif
