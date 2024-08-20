
#ifndef msr_airlib_Luminance_hpp
#define msr_airlib_Luminance_hpp

#include "LuminanceBase.hpp"
#include "LuminanceSimpleParams.hpp"
#include "common/DelayLine.hpp"
#include "common/FrequencyLimiter.hpp"

namespace msr
{
	namespace airlib
	{
		class LuminanceSimple : public LuminanceBase
		{
		public:
			LuminanceSimple(const AirSimSettings::LuminanceSetting& setting = AirSimSettings::LuminanceSetting())
				: LuminanceBase(setting.sensor_name)
			{
				params_.initializeFromSettings(setting);

				delay_line_.initialize(params_.update_latency); // init from json data
				freq_limiter_.initialize(params_.update_frequency, params_.startup_delay);
				
			}

			LuminanceSensorData getOutputInternal()
			{
				LuminanceSensorData output;
				params_.luminance = getLuminance();


				output.time_stamp = clock()->nowNanos();
				output.luminance = params_.luminance;
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
				LuminanceBase::update();

				freq_limiter_.update();
				if (freq_limiter_.isWaitComplete()) {
					delay_line_.push_back(getOutputInternal());
				}

				delay_line_.update();
				if (freq_limiter_.isWaitComplete())
					setOutput(delay_line_.getOutput());
			}

			//*** End: UpdatableState implementation ***//

			virtual ~LuminanceSimple() = default;

			virtual void reportState(StateReporter& reporter) override
			{
				LuminanceBase::reportState(reporter);
				reporter.writeValue("Luminance", params_.luminance);
			}
			
			const LuminanceSimpleParams& getParams() const
			{
				return params_;
			}
		protected:
			virtual float getLuminance() = 0; // use UnrealLuminanceSensor to override
		private:
			LuminanceSimpleParams params_;

			DelayLine<LuminanceSensorData> delay_line_;
			FrequencyLimiter freq_limiter_;
		};
	};
};

#endif