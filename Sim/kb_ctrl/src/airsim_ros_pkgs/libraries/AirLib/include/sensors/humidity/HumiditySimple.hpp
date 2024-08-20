#ifndef msr_airlib_Humidity_hpp
#define msr_airlib_Humidity_hpp

#include "HumidityBase.hpp"
#include "HumiditySimpleParams.hpp"
#include "common/DelayLine.hpp"
#include "common/FrequencyLimiter.hpp"

namespace msr
{
namespace airlib
{
    class HumiditySimple : public HumidityBase
    {
    public:
        HumiditySimple(const AirSimSettings::HumiditySetting& setting = AirSimSettings::HumiditySetting())
            : HumidityBase(setting.sensor_name)
        {
            params_.initializeFromSettings(setting);

            delay_line_.initialize(params_.update_latency); // init from json data
            freq_limiter_.initialize(params_.update_frequency, params_.startup_delay);
        }

        HumiditySensorData getOutputInternal()
        {
            HumiditySensorData output;
            params_.humidity = getHumidity();

            output.time_stamp = clock()->nowNanos();
            output.humidity = params_.humidity;
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
            HumidityBase::update();

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

        virtual ~HumiditySimple() = default;

        virtual void reportState(StateReporter& reporter) override
        {
            HumidityBase::reportState(reporter);
            reporter.writeValue("Humidity", params_.humidity);
        }

        const HumiditySimpleParams& getParams() const
        {
            return params_;
        }

    protected:
        virtual float getHumidity() = 0; // use UnrealHumiditySensor to override
    private:
        HumiditySimpleParams params_;

        DelayLine<HumiditySensorData> delay_line_;
        FrequencyLimiter freq_limiter_;
    };
};
};

#endif