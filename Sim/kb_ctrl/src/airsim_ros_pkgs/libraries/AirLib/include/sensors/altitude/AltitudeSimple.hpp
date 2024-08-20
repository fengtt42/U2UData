#ifndef msr_airlib_Altitude_hpp
#define msr_airlib_Altitude_hpp

#include "AltitudeBase.hpp"
#include "AltitudeSimpleParams.hpp"
#include "common/DelayLine.hpp"
#include "common/FrequencyLimiter.hpp"

namespace msr
{
namespace airlib
{
    class AltitudeSimple : public AltitudeBase
    {
    public:
        AltitudeSimple(const AirSimSettings::AltitudeSetting& setting = AirSimSettings::AltitudeSetting())
            : AltitudeBase(setting.sensor_name)
        {
            params_.initializeFromSettings(setting);

            delay_line_.initialize(params_.update_latency); // init from json data
            freq_limiter_.initialize(params_.update_frequency, params_.startup_delay);
        }

        AltitudeSensorData getOutputInternal()
        {
            AltitudeSensorData output;
            params_.altitude = getAltitude();

            output.time_stamp = clock()->nowNanos();
            output.altitude = params_.altitude;
            return output;
        }

        //*** Start: UpdatableState implementation ***//
        virtual void resetImplementation() override
        {
            freq_limiter_.reset();
            delay_line_.reset();

            delay_line_.push_back(getOutputInternal());
        }

        virtual void update() override // just update for the data
        {
            AltitudeBase::update();

            freq_limiter_.update();
            if (freq_limiter_.isWaitComplete()) {
                delay_line_.push_back(getOutputInternal());
            }

            delay_line_.update();
            if (freq_limiter_.isWaitComplete()) {
                setOutput(delay_line_.getOutput());
            }
        }

        //*** End: UpdatableState implementation ***//

        virtual ~AltitudeSimple() = default;

        virtual void reportState(StateReporter& reporter) override
        {
            AltitudeBase::reportState(reporter);
            reporter.writeValue("Altitude", params_.altitude);
        }

        const AltitudeSimpleParams& getParams() const
        {
            return params_;
        }

    protected:
        virtual float getAltitude() = 0; // use UnrealAltitudeSensor to override
    private:
        AltitudeSimpleParams params_;

        DelayLine<AltitudeSensorData> delay_line_;
        FrequencyLimiter freq_limiter_;
    };
};
};

#endif