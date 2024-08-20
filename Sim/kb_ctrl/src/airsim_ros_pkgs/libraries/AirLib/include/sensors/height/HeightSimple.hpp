#ifndef msr_airlib_Height_hpp
#define msr_airlib_Height_hpp

#include "HeightBase.hpp"
#include "HeightSimpleParams.hpp"
#include "common/DelayLine.hpp"
#include "common/FrequencyLimiter.hpp"

namespace msr
{
namespace airlib
{
    class HeightSimple : public HeightBase
    {
    public:
        HeightSimple(const AirSimSettings::HeightSetting& setting = AirSimSettings::HeightSetting())
            : HeightBase(setting.sensor_name)
        {
            params_.initializeFromSettings(setting);

            delay_line_.initialize(params_.update_latency); // init from json data
            freq_limiter_.initialize(params_.update_frequency, params_.startup_delay);
        }

        HeightSensorData getOutputInternal()
        {
            HeightSensorData output;
            params_.height = getHeight();

            output.time_stamp = clock()->nowNanos();
            output.height = params_.height;
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
            HeightBase::update();

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

        virtual ~HeightSimple() = default;

        virtual void reportState(StateReporter& reporter) override
        {
            HeightBase::reportState(reporter);
            reporter.writeValue("Height", params_.height);
        }

        const HeightSimpleParams& getParams() const
        {
            return params_;
        }

    protected:
        virtual float getHeight() = 0; // use UnrealHeightSensor to override
    private:
        HeightSimpleParams params_;

        DelayLine<HeightSensorData> delay_line_;
        FrequencyLimiter freq_limiter_;
    };
};
};

#endif