#pragma once

#ifndef _IFVRCOMPOSITOR_H
#define _IFVRCOMPOSITOR_H

#include "FoveTypes.h"

namespace Fove
{
	class IFVRCompositor
	{
	public:
		//-- Submit a frame to the compositor
		virtual EFVR_CompositorError Submit(void* pTexture, EFVR_GraphicsAPI api, EFVR_Eye whichEye, SFVR_TextureBounds bounds) = 0;
		//-- Set whether or not to show a mirror window of what's being sent to the compositor
		virtual void ShowMirrorWindow(bool shouldShow) = 0;
		//-- Shut down the compositor, making the pointer to this object unusable
		virtual void Shutdown() = 0;
	};

	__declspec(dllexport) IFVRCompositor* GetFVRCompositor();
}

#endif // _IFVRCOMPOSITOR_H