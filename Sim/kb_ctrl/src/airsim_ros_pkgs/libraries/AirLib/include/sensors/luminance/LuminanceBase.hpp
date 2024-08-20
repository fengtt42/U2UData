
#ifndef msr_airlib_LuminanceBase_hpp
#define msr_airlib_LuminanceBase_hpp

#include "sensors/SensorBase.hpp"

namespace msr
{
	namespace airlib
	{
		class LuminanceBase : public SensorBase
		{
		public:
			LuminanceBase(const std::string& sensor_name = "") : SensorBase(sensor_name)
			{
			}

			virtual void reportState(StateReporter& reporter) override
			{
				UpdatableObject::reportState(reporter);
				reporter.writeValue("Luminance-Lux", output_.luminance);
				
			}

			const LuminanceSensorData& getOutput() const
			{
				return output_;
			}
		protected:
			void setOutput(const LuminanceSensorData& output)
			{
				output_ = output;
			}
		private:
			LuminanceSensorData output_;

			
		};
	}
}

#endif
