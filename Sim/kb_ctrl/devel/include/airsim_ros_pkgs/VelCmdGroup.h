// Generated by gencpp from file airsim_ros_pkgs/VelCmdGroup.msg
// DO NOT EDIT!


#ifndef AIRSIM_ROS_PKGS_MESSAGE_VELCMDGROUP_H
#define AIRSIM_ROS_PKGS_MESSAGE_VELCMDGROUP_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <geometry_msgs/Twist.h>

namespace airsim_ros_pkgs
{
template <class ContainerAllocator>
struct VelCmdGroup_
{
  typedef VelCmdGroup_<ContainerAllocator> Type;

  VelCmdGroup_()
    : twist()
    , vehicle_names()  {
    }
  VelCmdGroup_(const ContainerAllocator& _alloc)
    : twist(_alloc)
    , vehicle_names(_alloc)  {
  (void)_alloc;
    }



   typedef  ::geometry_msgs::Twist_<ContainerAllocator>  _twist_type;
  _twist_type twist;

   typedef std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> _vehicle_names_type;
  _vehicle_names_type vehicle_names;





  typedef boost::shared_ptr< ::airsim_ros_pkgs::VelCmdGroup_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::airsim_ros_pkgs::VelCmdGroup_<ContainerAllocator> const> ConstPtr;

}; // struct VelCmdGroup_

typedef ::airsim_ros_pkgs::VelCmdGroup_<std::allocator<void> > VelCmdGroup;

typedef boost::shared_ptr< ::airsim_ros_pkgs::VelCmdGroup > VelCmdGroupPtr;
typedef boost::shared_ptr< ::airsim_ros_pkgs::VelCmdGroup const> VelCmdGroupConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::airsim_ros_pkgs::VelCmdGroup_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::airsim_ros_pkgs::VelCmdGroup_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::airsim_ros_pkgs::VelCmdGroup_<ContainerAllocator1> & lhs, const ::airsim_ros_pkgs::VelCmdGroup_<ContainerAllocator2> & rhs)
{
  return lhs.twist == rhs.twist &&
    lhs.vehicle_names == rhs.vehicle_names;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::airsim_ros_pkgs::VelCmdGroup_<ContainerAllocator1> & lhs, const ::airsim_ros_pkgs::VelCmdGroup_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace airsim_ros_pkgs

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::airsim_ros_pkgs::VelCmdGroup_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::airsim_ros_pkgs::VelCmdGroup_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::airsim_ros_pkgs::VelCmdGroup_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::airsim_ros_pkgs::VelCmdGroup_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::airsim_ros_pkgs::VelCmdGroup_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::airsim_ros_pkgs::VelCmdGroup_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::airsim_ros_pkgs::VelCmdGroup_<ContainerAllocator> >
{
  static const char* value()
  {
    return "8799472a9188ceedb7e4a4fc4acaa96d";
  }

  static const char* value(const ::airsim_ros_pkgs::VelCmdGroup_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x8799472a9188ceedULL;
  static const uint64_t static_value2 = 0xb7e4a4fc4acaa96dULL;
};

template<class ContainerAllocator>
struct DataType< ::airsim_ros_pkgs::VelCmdGroup_<ContainerAllocator> >
{
  static const char* value()
  {
    return "airsim_ros_pkgs/VelCmdGroup";
  }

  static const char* value(const ::airsim_ros_pkgs::VelCmdGroup_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::airsim_ros_pkgs::VelCmdGroup_<ContainerAllocator> >
{
  static const char* value()
  {
    return "geometry_msgs/Twist twist\n"
"string[] vehicle_names\n"
"================================================================================\n"
"MSG: geometry_msgs/Twist\n"
"# This expresses velocity in free space broken into its linear and angular parts.\n"
"Vector3  linear\n"
"Vector3  angular\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Vector3\n"
"# This represents a vector in free space. \n"
"# It is only meant to represent a direction. Therefore, it does not\n"
"# make sense to apply a translation to it (e.g., when applying a \n"
"# generic rigid transformation to a Vector3, tf2 will only apply the\n"
"# rotation). If you want your data to be translatable too, use the\n"
"# geometry_msgs/Point message instead.\n"
"\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
;
  }

  static const char* value(const ::airsim_ros_pkgs::VelCmdGroup_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::airsim_ros_pkgs::VelCmdGroup_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.twist);
      stream.next(m.vehicle_names);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct VelCmdGroup_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::airsim_ros_pkgs::VelCmdGroup_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::airsim_ros_pkgs::VelCmdGroup_<ContainerAllocator>& v)
  {
    s << indent << "twist: ";
    s << std::endl;
    Printer< ::geometry_msgs::Twist_<ContainerAllocator> >::stream(s, indent + "  ", v.twist);
    s << indent << "vehicle_names[]" << std::endl;
    for (size_t i = 0; i < v.vehicle_names.size(); ++i)
    {
      s << indent << "  vehicle_names[" << i << "]: ";
      Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.vehicle_names[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // AIRSIM_ROS_PKGS_MESSAGE_VELCMDGROUP_H
