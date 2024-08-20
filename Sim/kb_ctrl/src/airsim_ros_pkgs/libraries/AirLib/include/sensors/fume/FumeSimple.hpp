#ifndef msr_airlib_Fume_hpp
#define msr_airlib_Fume_hpp

#include "FumeBase.hpp"
#include "FumeSimpleParams.hpp"
#include "common/DelayLine.hpp"
#include "common/FrequencyLimiter.hpp"

namespace msr
{
namespace airlib
{
    class FumeSimple : public FumeBase
    {
    public:
        FumeSimple(const AirSimSettings::FumeSetting& setting = AirSimSettings::FumeSetting())
            : FumeBase(setting.sensor_name)
        {
            params_.initializeFromSettings(setting);

            delay_line_.initialize(params_.update_latency); // init from json data
            freq_limiter_.initialize(params_.update_frequency, params_.startup_delay);
        }

        FumeSensorData getOutputInternal()
        {
            FumeSensorData output;
            params_.fume = getFume();

            output.time_stamp = clock()->nowNanos();
            output.fume = params_.fume;
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
            FumeBase::update();

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

        virtual ~FumeSimple() = default;

        virtual void reportState(StateReporter& reporter) override
        {
            FumeBase::reportState(reporter);
            reporter.writeValue("Fume", params_.fume);
        }

        const FumeSimpleParams& getParams() const
        {
            return params_;
        }

    protected:
        virtual float getFume() = 0; // use UnrealFumeSensor to override
    private:
        FumeSimpleParams params_;

        DelayLine<FumeSensorData> delay_line_;
        FrequencyLimiter freq_limiter_;
    };
};
};

#endif