#ifndef msr_airlib_LumianceSimpleParams_hpp
#define msr_airlib_LumianceSimpleParams_hpp

#include "common/AirSimSettings.hpp"
#include "common/Common.hpp"

namespace msr
{
	namespace airlib
	{
		struct LuminanceSimpleParams
		{
			float luminance = 0; // lux
			real_T update_latency = 0.1f; // sec
			real_T update_frequency = 100; // hz
			real_T startup_delay = 1; // sec  use these to set sample frequece

			void initializeFromSettings(const AirSimSettings::LuminanceSetting& Setting)
			{
				const auto& json = Setting.settings;
				luminance = json.getFloat("Luminance", luminance);
			}
		};
	}
}

#endif
