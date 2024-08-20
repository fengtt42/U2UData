#ifndef msr_airlib_HeightSimpleParams_hpp
#define msr_airlib_HeightSimpleParams_hpp

#include "common/AirSimSettings.hpp"
#include "common/Common.hpp"

namespace msr
{
namespace airlib
{
    struct HeightSimpleParams
    {
        float height = 0; // centigrage
        real_T update_latency = 0.5f; // sec
        real_T update_frequency = 1; // hz
        real_T startup_delay = 1; // sec  use these to set sample frequece

        void initializeFromSettings(const AirSimSettings::HeightSetting& Setting)
        {
            const auto& json = Setting.settings;
            height = json.getFloat("Height", height);
        }
    };
}
}

#endif