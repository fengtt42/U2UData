#ifndef msr_airlib_HeightBase_hpp
#define msr_airlib_HeightBase_hpp

#include "sensors/SensorBase.hpp"

namespace msr
{
namespace airlib
{
    class HeightBase : public SensorBase
    {
    public:
        HeightBase(const std::string& sensor_name = "")
            : SensorBase(sensor_name)
        {
        }

        virtual void reportState(StateReporter& reporter) override
        {
            UpdatableObject::reportState(reporter);
            reporter.writeValue("Height-Centigrade", output_.height);
        }

        const HeightSensorData& getOutput() const
        {
            return output_;
        }

    protected:
        void setOutput(const HeightSensorData& output)
        {
            output_ = output;
        }

    private:
        HeightSensorData output_;
    };
}
}

#endif