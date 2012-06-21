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

// Standard includes
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>

// Qt includes
#include <QFileDialog>
#include <QDir>

// SlicerQt includes
#include "qSlicerOCTReaderModuleWidget.h"
#include "ui_qSlicerOCTReaderModule.h"

// Slicer includes
#include "vtkMRMLScalarVolumeNode.h"
#include "vtkMRMLScalarVolumeDisplayNode.h"
#include "vtkImageData.h"
#include "vtkSmartPointer.h"
#include "vtkMRMLScene.h"
#include "vtkMRMLVolumeNode.h"

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_OCTReader
class qSlicerOCTReaderModuleWidgetPrivate: public Ui_qSlicerOCTReaderModule
{
public:
  qSlicerOCTReaderModuleWidgetPrivate();
};

//-----------------------------------------------------------------------------
// qSlicerOCTReaderModuleWidgetPrivate methods

//-----------------------------------------------------------------------------
qSlicerOCTReaderModuleWidgetPrivate::qSlicerOCTReaderModuleWidgetPrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerOCTReaderModuleWidget methods

//-----------------------------------------------------------------------------
qSlicerOCTReaderModuleWidget::qSlicerOCTReaderModuleWidget(QWidget* _parent)
  : Superclass( _parent )
  , d_ptr( new qSlicerOCTReaderModuleWidgetPrivate )
{
}

//-----------------------------------------------------------------------------
qSlicerOCTReaderModuleWidget::~qSlicerOCTReaderModuleWidget()
{
}

//-----------------------------------------------------------------------------
void qSlicerOCTReaderModuleWidget::setup()
{
  Q_D(qSlicerOCTReaderModuleWidget);
  d->setupUi(this);
  this->Superclass::setup();

  connect(d->selectFileButton, SIGNAL(clicked()),
	  this, SLOT(OpenFileDialog()));

  connect(d->createVolumeButton, SIGNAL(clicked()),
	  this, SLOT(CreateVolume()));

  this->strToScalarTypeMap.insert("Int 8",int8);
  this->strToScalarTypeMap.insert("Unsigned Int 8",uint8);
  this->strToScalarTypeMap.insert("Int 16",int16);
  this->strToScalarTypeMap.insert("Unsigned Int 16",uint16);
  this->strToScalarTypeMap.insert("Int 32",int32);
  this->strToScalarTypeMap.insert("Unsigned Int 32",uint32);
  this->strToScalarTypeMap.insert("Float 32",float32);
  this->strToScalarTypeMap.insert("Double 64",float64);
  

}

//-----------------------------------------------------------------------------
void qSlicerOCTReaderModuleWidget::OpenFileDialog()
{
  Q_D(qSlicerOCTReaderModuleWidget);

  this->binaryFilename = QFileDialog::getOpenFileName(this,
						      tr("Open Binary File"),
						      QDir::homePath(),
						      tr("Binary file (*.bin)"));
						      
  if(!this->binaryFilename.isNull() && !this->binaryFilename.isEmpty())
    {
      QFileInfo fInfo = QFileInfo(this->binaryFilename);
      d->selectFileButton->setText(fInfo.fileName());
    }
}

//-----------------------------------------------------------------------------
void qSlicerOCTReaderModuleWidget::CreateVolume()
{
  Q_D(qSlicerOCTReaderModuleWidget);

  if(!this->binaryFilename.isNull() && !this->binaryFilename.isEmpty())
    {
      // Get values from GUI
      int dimensions[3];
      double spacing[3];
      double range[2];
      
      dimensions[0] = d->DimX->value();
      dimensions[1] = d->DimY->value();
      dimensions[2] = d->DimZ->value();

      spacing[0] = d->SpX->value();
      spacing[1] = d->SpY->value();
      spacing[2] = d->SpZ->value();

      QFileInfo fInfo = QFileInfo(this->binaryFilename);

      // Create and configure nodes
      vtkSmartPointer<vtkMRMLScalarVolumeDisplayNode> displayNode = vtkSmartPointer<vtkMRMLScalarVolumeDisplayNode>::New();
      vtkSmartPointer<vtkMRMLScalarVolumeNode> scalarNode = vtkSmartPointer<vtkMRMLScalarVolumeNode>::New();
      vtkSmartPointer<vtkImageData> imData = vtkSmartPointer<vtkImageData>::New();
      imData->SetDimensions(dimensions);
      imData->SetExtent(0,dimensions[0]-1, 0, dimensions[1]-1, 0, dimensions[2]-1);
      imData->SetSpacing(spacing);
      imData->SetOrigin(0,0,0);
      imData->SetNumberOfScalarComponents(1);
      
      switch(this->strToScalarTypeMap[d->scalarTypeSelector->currentText()])
	{
	case int8:   imData->SetScalarTypeToChar(); break;              // 8 bits = 1 bytes
	case uint8:  imData->SetScalarTypeToUnsignedChar();break;       // 8 bits = 1 bytes
	case int16:  imData->SetScalarTypeToShort();break;              // 16 bits = 2 bytes
	case uint16: imData->SetScalarTypeToUnsignedShort();break;      // 16 bits = 2 bytes
	case int32:  imData->SetScalarTypeToLong();break;               // 32 bits = 4 bytes
	case uint32: imData->SetScalarTypeToUnsignedLong();break;       // 32 bits = 4 bytes
	case float32:imData->SetScalarTypeToFloat(); break;             // 32 bits = 4 bytes  
	case float64:imData->SetScalarTypeToDouble(); break;            // 64 bits = 8 bytes
	default: imData->SetScalarTypeToUnsignedShort();break;          
	}
      imData->AllocateScalars();

      // Read data and put them in the ImageData
      if(imData->GetScalarPointer())
	{
	  std::ifstream ifs;
	  ifs.open(this->binaryFilename.toStdString().c_str(), std::ios::binary);
	  if(ifs.is_open())
	    {
	      ifs.read((char*)(imData->GetScalarPointer()), dimensions[0]*dimensions[1]*dimensions[2]*imData->GetScalarSize());

        // If checking read function, if data are smaller than expected, volume is not created

	//    if(!)
	//	{
	//	  // Reading failed
	//	  ifs.close();
	//	  return;
	//	}
	      ifs.close();
	      imData->Update();
	      imData->Modified(); // Difference between Update and Modified ?
	      
	      //range[0] = 50;
	      //range[1] = 32767;
	      displayNode->SetScene(this->mrmlScene());
	      //displayNode->SetLowerThreshold(range[0]);
	      //displayNode->SetUpperThreshold(range[1]);
	      
	      scalarNode->SetAndObserveImageData(imData);
	      scalarNode->SetLabelMap(0);
	      scalarNode->SetName(fInfo.fileName().toStdString().c_str());
	      scalarNode->SetScene(this->mrmlScene());
	      scalarNode->SetAndObserveDisplayNodeID(displayNode->GetID());
	      
	      this->CenterVolume(scalarNode);

	      this->mrmlScene()->AddNode(displayNode);
	      this->mrmlScene()->AddNode(scalarNode);
	    }
	  else
	    {
	      // Opening failed
	      return;
	    }
	}
    }
}

//-----------------------------------------------------------------------------
void qSlicerOCTReaderModuleWidget::CenterVolume(vtkMRMLVolumeNode* volumeNode)
{
  if(volumeNode)
    {
      vtkImageData* image = volumeNode->GetImageData();
      if(image)
	{
	  double dimsH[4];
	  double rasCorner[4];
	  int *dims = image->GetDimensions();
	  dimsH[0] = dims[0] - 1;
	  dimsH[1] = dims[1] - 1;
	  dimsH[2] = dims[2] - 1;
	  dimsH[3] = 0;

	  double origin[3];
	  for(int i = 0; i < 3; i++)
	    {
	      origin[i] = -0.5 * dimsH[i];
	    }
	  volumeNode->SetDisableModifiedEvent(1);
	  volumeNode->SetOrigin(origin);
	  volumeNode->SetDisableModifiedEvent(0);
	  volumeNode->InvokePendingModifiedEvent();
	}

    }

}

