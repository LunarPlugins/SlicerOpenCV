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

// OpenCV Logic includes
#include "vtkSlicerOpenCVLogic.h"

// MRML includes
#include <vtkMRMLScene.h>

// VTK includes
#include <vtkIntArray.h>
#include <vtkNew.h>
#include <vtkObjectFactory.h>

// STD includes
#include <cassert>
#include <iostream>

// OpenCV includes
#include <cv.h>
#include <highgui.h>

// ITK includes
#include <itkVideoIOFactory.h>
#include <itkOpenCVVideoIOFactory.h>
#include <itkOpenCVVideoIO.h>

//----------------------------------------------------------------------------
vtkStandardNewMacro(vtkSlicerOpenCVLogic);

//----------------------------------------------------------------------------
vtkSlicerOpenCVLogic::vtkSlicerOpenCVLogic()
{
  std::cout << "Logic!" << std::endl;

  // register the OpenCV ITK IO factory
  itk::ObjectFactoryBase::RegisterFactory( itk::OpenCVVideoIOFactory::New() );
  itk::OpenCVVideoIO *videoIO = itk::OpenCVVideoIO::New();

  if (0)
    {
    // will cause a crash on start up without proper settings
    std::cout << "Trying to create IO for reading from file..." << std::endl;
    char *input = NULL;
    itk::VideoIOBase::Pointer ioReadFile = itk::VideoIOFactory::CreateVideoIO(
      itk::VideoIOFactory::ReadFileMode, input);
    if (!ioReadFile)
      {
      std::cerr << "Did not create valid VideoIO for reading from file " << std::endl;
      return;
      }


    itk::SizeValueType cameraNumber = 0;
    // Use openCV to see if we can even try to open the camera
    CvCapture* cameraCapture = cvCaptureFromCAM( cameraNumber );
    if (cameraCapture == ITK_NULLPTR)
      {
      std::cerr << "Unable to create a camera to capture from" << std::endl;
      return;
      }
    }

}

//----------------------------------------------------------------------------
vtkSlicerOpenCVLogic::~vtkSlicerOpenCVLogic()
{
}

//----------------------------------------------------------------------------
void vtkSlicerOpenCVLogic::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

//---------------------------------------------------------------------------
void vtkSlicerOpenCVLogic::SetMRMLSceneInternal(vtkMRMLScene * newScene)
{
  vtkNew<vtkIntArray> events;
  events->InsertNextValue(vtkMRMLScene::NodeAddedEvent);
  events->InsertNextValue(vtkMRMLScene::NodeRemovedEvent);
  events->InsertNextValue(vtkMRMLScene::EndBatchProcessEvent);
  this->SetAndObserveMRMLSceneEventsInternal(newScene, events.GetPointer());
}

//-----------------------------------------------------------------------------
void vtkSlicerOpenCVLogic::RegisterNodes()
{
  assert(this->GetMRMLScene() != 0);
}

//---------------------------------------------------------------------------
void vtkSlicerOpenCVLogic::UpdateFromMRMLScene()
{
  assert(this->GetMRMLScene() != 0);
}

//---------------------------------------------------------------------------
void vtkSlicerOpenCVLogic
::OnMRMLSceneNodeAdded(vtkMRMLNode* vtkNotUsed(node))
{
}

//---------------------------------------------------------------------------
void vtkSlicerOpenCVLogic
::OnMRMLSceneNodeRemoved(vtkMRMLNode* vtkNotUsed(node))
{
}
