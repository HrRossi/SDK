#include <string>
#include <iostream>
#include <fstream>
#include <thread>
#include <conio.h>
#include "FoveTypes.h"
#include "IFVRHeadset.h"
#include "IFVRCompositor.h"
#include "LogManager.h"


int main(int argc, char* argv)
{
	// Initialize the FoveVR Headset Instance
	Fove::IFVRHeadset* hInstance = Fove::GetFVRHeadset();

	if (hInstance != NULL && !hInstance->Initialise())
	{
		std::cout << "failed to init client" << std::endl;
		getchar();
		return 1;
	}

	// Check if we have detected Fove Hardware
	while (!hInstance->IsHardwareReady())
	{
		// Press ESC to quit while you are still trying to detect hardware
		if (_kbhit())
		{
			if (_getch() == 27)
			{
				hInstance->Destroy();
				return 1;
			}
		}
		std::cout << "headset not ready" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	// Using Tare Orientation Sensor
	// The sensor's reading may differ from the actual orientation of the device by a constant angle until
	//		it has been given a reference orientation
	// TareOrientationSensor() function sets the sensor orientation to zero orientation
	if (hInstance->TareOrientationSensor())
	{
		std::cout << "Successfully set the Tared the sensor" << std::endl;
	}
	else
	{
		std::cout << "Unable to Tare the sensor" << std::endl;
	}

	// Setup the Compositor, get the Instance of the Compositor
	Fove::IFVRCompositor* cInstance = Fove::GetFVRCompositor();

	// Make sure the FoveCompositorApplication.exe is running in the background
	if (!cInstance)
	{
		std::cout << "failed to get compositor instance, please make sure you have run the FoveCompositorApplication.exe in the background" << std::endl;
		getchar();
		return 1;
	}

	// If this is set to true, the compositor will also render the textures to a window on your primary monitor.
	//		This allows you to see what the headset is displaying without putting it on (for debug and demo).
	//cInstance->ShowMirrorWindow(true);

	// Main loop to play with the VR
	// Press ESC to quit Application
	while (true)
	{
		if (_kbhit())
		{
			if (_getch() == 27)
				break;
		}

		std::cout << "dumping data" << std::endl;

		// normally the following functions would be called at appropriate times during the rendering loop to retrieve
		//		data that allows the scene to be rendered. Calling those as late as possible will give you the most
		//		up to date information possible (until we implement prediction and/or timewarp)

		// GetOrientation returns the users head orientation on Fove VR
		Fove::SFVR_HeadOrientation ho = hInstance->GetOrientation();
		if (ho.error != Fove::EFVR_ErrorCode::None)
		{
			// Retrieve the last error generated in the runtime
			std::cout << (int)hInstance->GetLastError() << std::endl;
		}
		else
		{
			// Printing out the Quaternion(x, y, z, w) values
			// this should be linked to the orientation of the object that contains the view cameras to rotate the 
			//		world based on the headset orientation
			std::cout << ho.timestamp << ": " << ho.quat.x << ", " << ho.quat.y << ", " << ho.quat.z << ", " << ho.quat.w << std::endl;
		}

		// GetGazePoint returns the users eye position on a Normalized -1,1 plane
		// -1,-1 is the top left corner of the screen. 1,1 is the bottom right corner.
		// this function will be deprecated in v0.5.0 in favour of GetGazeVector
		Fove::SFVR_GazeScreenCoord gp = hInstance->GetGazePoint();
		
		if (gp.error != Fove::EFVR_ErrorCode::None)
		{
			// Retrieve the last error generated in the runtime
			std::cout << (int)hInstance->GetLastError() << std::endl;
		}
		else
		{
			// Printing out the 2D Vector Coordinate of the eyes
			// This is the position on the screen that the user is looking at, use it to position a crosshair 
			//		or project into 3d space to see what object the user is looking at.
			std::cout << gp.timestamp << ": " << gp.coord.x << ", " << gp.coord.y << std::endl;
		}

		/************** Working with the Compositor ******************/
		// At the end of the rendering loop, the textures need to be submitted to the compositor to be displayed
		//		on the HMD. 

		// Perform the Rendering Texture to the Screen using Submit() function:
		// Example:
		//
		// Set your screen bounds
		// Fove::SFVR_TextureBounds bounds;
		// Set your textures to be rendered.
		// void *leTexture = NULL;
		// cInstance->Submit(leTexture, Fove::EFVR_GraphicsAPI::DirectX, Fove::EFVR_Eye::Left, bounds);
		// void *reTexture = NULL;
		// cInstance->Submit(reTexture, Fove::EFVR_GraphicsAPI::DirectX, Fove::EFVR_Eye::Right, bounds);


		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	// Once the application / game is shutting down, clean up the resources.
	cInstance->Shutdown();
	hInstance->Destroy();
}