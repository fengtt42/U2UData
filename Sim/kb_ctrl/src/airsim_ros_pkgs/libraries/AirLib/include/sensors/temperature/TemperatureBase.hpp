#ifndef msr_airlib_TemperatureBase_hpp
#define msr_airlib_TemperatureBase_hpp

#include "sensors/SensorBase.hpp"

namespace msr
{
namespace airlib
{
    class TemperatureBase : public SensorBase
    {
    public:
        TemperatureBase(const std::string& sensor_name = "")
            : SensorBase(sensor_name)
        {
        }

        virtual void reportState(StateReporter& reporter) override
        {
            UpdatableObject::reportState(reporter);
            reporter.writeValue("Temperature-Centigrade", output_.temperature);
        }

        const TemperatureSensorData& getOutput() const
        {
            return output_;
        }

    protected:
        void setOutput(const TemperatureSensorData& output)
        {
            output_ = output;
        }

    private:
        TemperatureSensorData output_;
    };
}
}

#endif