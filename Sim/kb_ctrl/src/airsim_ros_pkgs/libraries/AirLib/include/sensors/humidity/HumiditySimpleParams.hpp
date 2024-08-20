#ifndef msr_airlib_HumiditySimpleParams_hpp
#define msr_airlib_HumiditySimpleParams_hpp

#include "common/AirSimSettings.hpp"
#include "common/Common.hpp"

namespace msr
{
namespace airlib
{
    struct HumiditySimpleParams
    {
        float humidity = 0; // centigrage
        real_T update_latency = 0.5f; // sec
        real_T update_frequency = 1 / 60; // hz
        real_T startup_delay = 1; // sec  use these to set sample frequece

        void initializeFromSettings(const AirSimSettings::HumiditySetting& Setting)
        {
            const auto& json = Setting.settings;
            humidity = json.getFloat("Humidity", humidity);
        }
    };
}
}

#endif