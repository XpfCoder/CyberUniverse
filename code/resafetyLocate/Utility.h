#pragma once

#include "../DeepEyeCore/Utility.h"

#if defined RESAFRTYLOCATE_EXPORTS
	#define RESAFRTYLOCATE_EXPORT __declspec(dllexport)
	#define RESAFRTYLOCATE_TEMPLATE __declspec(dllexport)
#else
	#define RESAFRTYLOCATE_EXPORT __declspec(dllimport)
	#define RESAFRTYLOCATE_TEMPLATE
#endif



