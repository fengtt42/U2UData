#ifndef msr_airlib_FumeBase_hpp
#define msr_airlib_FumeBase_hpp

#include "sensors/SensorBase.hpp"

namespace msr
{
namespace airlib
{
    class FumeBase : public SensorBase
    {
    public:
        FumeBase(const std::string& sensor_name = "")
            : SensorBase(sensor_name)
        {
        }

        virtual void reportState(StateReporter& reporter) override
        {
            UpdatableObject::reportState(reporter);
            reporter.writeValue("Fume-Centigrade", output_.fume);
        }

        const FumeSensorData& getOutput() const
        {
            return output_;
        }

    protected:
        void setOutput(const FumeSensorData& output)
        {
            output_ = output;
        }

    private:
        FumeSensorData output_;
    };
}
}

#endif