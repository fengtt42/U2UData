#ifndef msr_airlib_AltitudeBase_hpp
#define msr_airlib_AltitudeBase_hpp

#include "sensors/SensorBase.hpp"

namespace msr
{
namespace airlib
{
    class AltitudeBase : public SensorBase
    {
    public:
        AltitudeBase(const std::string& sensor_name = "")
            : SensorBase(sensor_name)
        {
        }

        virtual void reportState(StateReporter& reporter) override
        {
            UpdatableObject::reportState(reporter);
            reporter.writeValue("Altitude-Centigrade", output_.altitude);
        }

        const AltitudeSensorData& getOutput() const
        {
            return output_;
        }

    protected:
        void setOutput(const AltitudeSensorData& output)
        {
            output_ = output;
        }

    private:
        AltitudeSensorData output_;
    };
}
}

#endif