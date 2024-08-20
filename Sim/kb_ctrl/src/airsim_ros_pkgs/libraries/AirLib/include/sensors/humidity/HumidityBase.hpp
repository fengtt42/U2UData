#ifndef msr_airlib_HumidityBase_hpp
#define msr_airlib_HumidityBase_hpp

#include "sensors/SensorBase.hpp"

namespace msr
{
namespace airlib
{
    class HumidityBase : public SensorBase
    {
    public:
        HumidityBase(const std::string& sensor_name = "")
            : SensorBase(sensor_name)
        {
        }

        virtual void reportState(StateReporter& reporter) override
        {
            UpdatableObject::reportState(reporter);
            reporter.writeValue("Humidity-Centigrade", output_.humidity);
        }

        const HumiditySensorData& getOutput() const
        {
            return output_;
        }

    protected:
        void setOutput(const HumiditySensorData& output)
        {
            output_ = output;
        }

    private:
        HumiditySensorData output_;
    };
}
}

#endif