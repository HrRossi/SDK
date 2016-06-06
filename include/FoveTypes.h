#pragma once

#ifndef _FOVETYPES_H
#define _FOVETYPES_H

#include <cstdint>
#include <vector>

using std::int32_t;
using std::uint32_t;
using std::uint64_t;

namespace Fove
{
	//! EFVR_ClientCapabilities
	/*! To be passed to the initialisation function of the client library to  */
	enum class EFVR_ClientCapabilities
	{
		Gaze = 1,
		Orientation = 2,
		Position = 4
	};
	inline EFVR_ClientCapabilities operator|(EFVR_ClientCapabilities a, EFVR_ClientCapabilities b)
	{
		return static_cast<EFVR_ClientCapabilities>(static_cast<int>(a) | static_cast<int>(b));
	}

	//! EFVR_ErrorCode enum
	/*! An enum of error codes that the system may return from GetLastError(). These will eventually be mapped to localised strings. */
	enum class EFVR_ErrorCode
	{
		None = 0,

		//! Connection Errors
		Connection_General = 1,
		Connect_NotConnected = 7,
		Connect_ServerUnreachable = 2,
		Connect_RegisterFailed = 3,
		Connect_DeregisterFailed = 6,
		Connect_WrongRuntimeVersion = 4,
		Connect_HeartbeatNoReply = 5,

		//! Data Errors
		Data_General = 10,
		Data_RegisteredWrongVersion = 11,
		Data_UnreadableNotFound = 12,
		Data_NoUpdate = 13,

		//! Hardware Errors
		Hardware_General = 20,
		Hardware_CoreFault = 21,
		Hardware_CameraFault = 22,
		Hardware_IMUFault = 23,
		Hardware_ScreenFault = 24,
		Hardware_SecurityFault = 25,
		Hardware_Disconnected = 26,

		//! Server Response Errors
		Server_General = 30,
		Server_HardwareInterfaceInvalid = 31,
		Server_HeartbeatNotRegistered = 32,
		Server_DataCreationError = 33,
		Server_ModuleError_ET = 34,

		//! Code and placeholders
		Code_NotImplementedYet = 40,
		Code_FunctionDepricated = 41
	};

	//! EFVR_DataType enum
	/*! The different data types that are passed internally within the FoveVR system.
		Clients can subscribe to these (the default is to subscribe all at the moment).
	*/
	enum class EFVR_DataType
	{
		HeadsetState = 0,
		Orientation = 1,
		Position = 2,
		Gaze = 3,
		ImageData = 4,
		Message = 5
	};

	//! SFVR_Quaternion struct
	/*! A quaternion represents an orientation in 3d space.*/
	struct SFVR_Quaternion
	{
		float x = 0;
		float y = 0;
		float z = 0;
		float w = 1;

		SFVR_Quaternion(float ix, float iy, float iz, float iw) : x(ix), y(iy), z(iz), w(iw) {}
	};

	//! SFVR_HeadOrientation struct
	/*! Represents the orientation of the Fove headset in 3d space along with some meta-information about how old this data is. */
	struct SFVR_HeadOrientation
	{
		//! Error Code
		/*! error:	if true => the rest of the data is in an unknown state. */
		EFVR_ErrorCode error = EFVR_ErrorCode::None;
		//! ID
		/*! Incremental counter which tells if the coord captured is a fresh value at a given frame */
		uint64_t id;
		//! Timestamp
		/*! The time at which the coord was captured, based on system time */
		uint64_t timestamp;
		//! Quaternion
		/*! The Quaternion which represents the orientation of the head. */
		SFVR_Quaternion quat;

		SFVR_HeadOrientation() : quat(0, 0, 0, 1){}
	};

	//! SFVR_Vec3 struct
	/*! A vector that represents an position in 3d space. */
	struct SFVR_Vec3
	{
		float x;
		float y;
		float z;

		SFVR_Vec3(float ix, float iy, float iz) : x(ix), y(iy), z(iz) {}
	};

	//! SFVR_Vec2 struct
	/*! A vector that represents an position in 2d space. Usually used when refering to screen or image coordinates. */
	struct SFVR_Vec2
	{
		float x;
		float y;

		SFVR_Vec2() : x(0), y(0) {}
		SFVR_Vec2(float ix, float iy) : x(ix), y(iy) {}
	};

	//! SFVR_Pose struct
	/*! This structure is a combination of the Fove headset position and orientation in 3d space, collectively known as the "pose".
		In the future this may also contain accelleration information for the headset, and may also be used for controllers.
	*/
	struct SFVR_Pose
	{
		//! Error Code
		/*! error:	if true => the rest of the data is in an unknown state. */
		EFVR_ErrorCode error = EFVR_ErrorCode::None;
		//! ID
		/*! Incremental counter which tells if the coord captured is a fresh value at a given frame */
		uint64_t id;
		//! Timestamp
		/*! The time at which the coord was captured, based on system time */
		uint64_t timestamp;
		//! Quaternion
		/*! The Quaternion which represents the orientation of the head. */
		SFVR_Quaternion orientation;
		//! Vector3
		/*! The position of headset in 3D space */
		SFVR_Vec3 position;

		SFVR_Pose() : orientation(0, 0, 0, 1), position(0, 0, 0){}
	};

	//! SFVR_GazeVector struct
	/*! FUTURE USE ONLY: The vector (from the center of the player's head in game space) that represents the point that the user is looking at.
		The accuracy is the radius of the sphere in meters of this information.
	*/
	struct SFVR_GazeVector
	{
		EFVR_ErrorCode error = EFVR_ErrorCode::None;
		uint64_t id;
		uint64_t timestamp;
		float accuracy;
		SFVR_Vec3 vec;
	};

	//! SFVR_GazeScreenCoord struct
	/*! The coordinate on the screen that the user is looking at. (0,0 is the top left) */
	struct SFVR_GazeScreenCoord
	{
		//! Error Code
		/*! error:	if true => the rest of the data is in an unknown state. */
		EFVR_ErrorCode error = EFVR_ErrorCode::None;
		//! ID
		/*! Incremental counter which tells if the coord captured is a fresh value at a given frame */
		uint64_t id;
		//! Timestamp
		/*! The time at which the coord was captured, based on system time */
		uint64_t timestamp;
		//! Vector2
		/*! The Coordinate position is based on the Normalized 0,1 plane */
		SFVR_Vec2 coord;
	};

	//! SFVR_EyeImage struct
	/*! DEPRICATED: For researcher use only, To be Moved to Fove Internal Types */
	struct SFVR_EyeImage
	{
		EFVR_ErrorCode error = EFVR_ErrorCode::None;
		uint8_t eye;
		uint64_t frameNumber;
		uint32_t length;
		uint64_t timestamp;
		std::vector<unsigned char> imageData;
	};

	//! SFVR_CalibrationTarget struct
	/*! To be Moved to Fove Internal Types */
	struct SFVR_CalibrationTarget
	{
		bool isCalibrationComplete;
		float x;
		float y;
		float z;
		float scale;
	};

	//! EFVR_Eye enum
	/*! This is usually returned with any eye tracking information and tells the client which eye(s) the information is based on. */
	enum class EFVR_Eye : uint8_t
	{
		Neither = 0,
		Left = 1,
		Right = 2,
		Both = 3
	};

	//! SFVR_Matrix44 struct
	/*! A rectangular array of numbers, symbols, or expressions, arranged in rows and columns.  */
	struct SFVR_Matrix44
	{
		float mat[4][4];
	};

	//! SFVR_Matrix34 struct
	/*! A rectangular array of numbers, symbols, or expressions, arranged in rows and columns.  */
	struct SFVR_Matrix34
	{
		float mat[3][4];
	};

	//! EFVR_CompositorError enum
	/*! Errors pertaining to Compositor */
	enum class EFVR_CompositorError
	{
		None = 0,

		UnableToCreateDeviceAndContext = 100,
		UnableToUseTexture = 101,
		DeviceMismatch = 102,

		UnableToFindRuntime = 200,
		RuntimeAlreadyClaimed = 201,
		DisconnectedFromRuntime = 202,

		ErrorCreatingShaders = 300,
		ErrorCreatingTexturesOnDevice = 301,

		UnknownError = 99999,
	};

	//! EFVR_GraphicsAPI enum
	/*! Type of Graphics API */
	enum class EFVR_GraphicsAPI
	{
		DirectX,
		OpenGL
	};

	//! SFVR_CompositorTexture struct
	/*! Texture structure used by the Compositor */
	struct SFVR_CompositorTexture
	{
		//! Texture Pointer
		/*! D3D: Native texture pointer
			OpenGL: Pointer to a texture ID */
		void* pTexture;
		EFVR_GraphicsAPI api;
	};

	//! SFVR_TextureBounds struct
	/*! Coordinates in normalized space where 0 is left/top and 1 is bottom/right */
	struct SFVR_TextureBounds
	{
		float left, top, right, bottom;
	};
}
#endif // _FOVETYPES_H