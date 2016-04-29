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

		//
		// DON'T INCLUDE THIS IN RELEASES!!
		//
		virtual float GetDistortionZoom() const = 0;
		virtual float GetDistortionStrength() const = 0;
		virtual float GetDistortionOffsetX() const = 0;
		virtual float GetDistortionOffsetY() const = 0;
		virtual int GetDistortionNumColumns() const = 0;
		virtual int GetDistortionNumRows() const = 0;
		virtual float GetDistortionUVOffsetRed() const = 0;
		virtual float GetDistortionUVOffsetBlue() const = 0;

		virtual void SetDistortionZoom(float value) = 0;
		virtual void SetDistortionStrength(float value) = 0;
		virtual void SetDistortionOffsetX(float value) = 0;
		virtual void SetDistortionOffsetY(float value) = 0;
		virtual void SetDistortionNumColumns(int value) = 0;
		virtual void SetDistortionNumRows(int value) = 0;
		virtual void SetDistortionUVOffsetRed(float value) = 0;
		virtual void SetDistortionUVOffsetBlue(float value) = 0;
	};

	__declspec(dllexport) IFVRCompositor* GetFVRCompositor();
}

#endif // _IFVRCOMPOSITOR_H