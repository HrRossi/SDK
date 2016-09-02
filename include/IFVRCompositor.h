#pragma once

#ifndef _IFVRCOMPOSITOR_H
#define _IFVRCOMPOSITOR_H

#include "FoveTypes.h"

namespace Fove
{
	class IFVRCompositor
	{
	public:

		//!-- Submit a frame to the compositor
		/*! This functions takes your feed from your game engine to render the texture to each eye
			\param pTexture		The Texture pointer pointing to the location of the actualt texture to be rendered to the FoveHMD
			\param api			Type of Graphics API: DirectX or OpenGL
			\param whichEye		Defines which eye to render the given texture to, Note: You will need to render for each eye seperately since the view vector for each eye is different
			\param bounds		The bounds for the texture to be displayed
			\param orientation	The orientation used to render this frame
		*/
		// Deprecated in v0.6.2 released 2nd Sep 2016
		virtual FVR_DEPRECATED(EFVR_CompositorError Submit(
			void* pTexture,
			EFVR_GraphicsAPI api,
			EFVR_Eye whichEye,
			SFVR_TextureBounds bounds,
			SFVR_HeadOrientation pose)) = 0;

		//!-- Submit a frame to the compositor
		/*! This functions takes your feed from your game engine to render the texture to each eye
			\param pTexture The Texture pointer pointing to the location of the actualt texture to be rendered to the FoveHMD
			\param api		Type of Graphics API: DirectX or OpenGL
			\param whichEye	Defines which eye to render the given texture to, Note: You will need to render for each eye seperately since the view vector for each eye is different
			\param bounds	The bounds for the texture to be displayed
			\param pose		The pose struct used for rendering this frame
		*/
		virtual EFVR_CompositorError Submit(
			void* pTexture,
			EFVR_GraphicsAPI api,
			EFVR_Eye whichEye,
			SFVR_TextureBounds bounds,
			SFVR_Pose pose) = 0;

		//!-- Set whether or not to show a mirror window of what's being sent to the compositor
		/*! Opens a window if the option is set to true or not
			Currently, this function is broken and causes things to crash. Do not use yet!
			\param shouldShow bool variable to show or not show the Fove HMD mirror on Desktop system
		*/
		virtual void ShowMirrorWindow(bool shouldShow) = 0;

		//!-- Shut down the compositor
		/*! This function releases the threads, closes the mirrow window, and the closes the backend renderer*/
		virtual void Shutdown() = 0;
		
		//!-- Destructor
		virtual ~IFVRCompositor() {}
	};

	__declspec(dllexport) IFVRCompositor* GetFVRCompositor();
}

#endif // _IFVRCOMPOSITOR_H