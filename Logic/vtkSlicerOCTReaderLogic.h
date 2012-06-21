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

// .NAME vtkSlicerOCTReaderLogic - slicer logic class for volumes manipulation
// .SECTION Description
// This class manages the logic associated with reading, saving,
// and changing propertied of the volumes


#ifndef __vtkSlicerOCTReaderLogic_h
#define __vtkSlicerOCTReaderLogic_h

// Slicer includes
#include "vtkSlicerModuleLogic.h"

// MRML includes

// STD includes
#include <cstdlib>

#include "vtkSlicerOCTReaderModuleLogicExport.h"


/// \ingroup Slicer_QtModules_OCTReader
class VTK_SLICER_OCTREADER_MODULE_LOGIC_EXPORT vtkSlicerOCTReaderLogic :
  public vtkSlicerModuleLogic
{
public:
  
  static vtkSlicerOCTReaderLogic *New();
  vtkTypeMacro(vtkSlicerOCTReaderLogic,vtkSlicerModuleLogic);
  void PrintSelf(ostream& os, vtkIndent indent);

protected:
  vtkSlicerOCTReaderLogic();
  virtual ~vtkSlicerOCTReaderLogic();

  virtual void SetMRMLSceneInternal(vtkMRMLScene * newScene);
  /// Register MRML Node classes to Scene. Gets called automatically when the MRMLScene is attached to this logic class.
  virtual void RegisterNodes();
  virtual void UpdateFromMRMLScene();
  virtual void OnMRMLSceneNodeAdded(vtkMRMLNode* node);
  virtual void OnMRMLSceneNodeRemoved(vtkMRMLNode* node);
private:

  vtkSlicerOCTReaderLogic(const vtkSlicerOCTReaderLogic&); // Not implemented
  void operator=(const vtkSlicerOCTReaderLogic&);               // Not implemented
};

#endif

