/***************************************************************************************
Author: lvke
Date:2022/9/30 09:35
Description:
The base class that implements serialization
****************************************************************************************/
#pragma once

#include <rttr/registration>
namespace Resafety {
	namespace DeepStar {
		class __declspec(dllexport) Reference
		{
		public:
			Reference() = default;
			virtual ~Reference() = default;

		};
		
	}
}