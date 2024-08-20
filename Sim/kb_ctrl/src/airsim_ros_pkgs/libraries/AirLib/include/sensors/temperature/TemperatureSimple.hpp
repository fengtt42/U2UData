#ifndef msr_airlib_Temperature_hpp
#define msr_airlib_Temperature_hpp

#include "TemperatureBase.hpp"
#include "TemperatureSimpleParams.hpp"
#include "common/DelayLine.hpp"
#include "common/FrequencyLimiter.hpp"

namespace msr
{
    namespace airlib
    {
        class TemperatureSimple : public TemperatureBase
        {
        public:
            TemperatureSimple(const AirSimSettings::TemperatureSetting& setting = AirSimSettings::TemperatureSetting())
                : TemperatureBase(setting.sensor_name)
            {
                params_.initializeFromSettings(setting);

                delay_line_.initialize(params_.update_latency); // init from json data
                freq_limiter_.initialize(params_.update_frequency, params_.startup_delay);
            }

            TemperatureSensorData getOutputInternal()
            {
                TemperatureSensorData output;
                params_.temperature = getTemperature();

                output.time_stamp = clock()->nowNanos();
                output.temperature = params_.temperature;   
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
                TemperatureBase::update();

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

            virtual ~TemperatureSimple() = default;

            virtual void reportState(StateReporter& reporter) override
            {
                TemperatureBase::reportState(reporter);
                reporter.writeValue("Temperature", params_.temperature);
            }

            const TemperatureSimpleParams& getParams() const
            {
                return params_;
            }

        protected:
            virtual float getTemperature() = 0; // use UnrealTemperatureSensor to override
        private:
            TemperatureSimpleParams params_;

            DelayLine<TemperatureSensorData> delay_line_;
            FrequencyLimiter freq_limiter_;
        };
    };
};

#endif