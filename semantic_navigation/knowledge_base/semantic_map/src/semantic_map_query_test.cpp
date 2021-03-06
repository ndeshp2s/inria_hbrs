// Include the ROS C++ APIs
#include <ros/ros.h>

// Include the declaration of our library function
#include <semantic_map/semantic_map.h>
#include <semantic_map/Object.h>
#include <list>

#include <costmap_2d/costmap_2d_ros.h> 

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

typedef boost::geometry::model::d2::point_xy<double> point_type;
typedef boost::geometry::model::polygon<point_type> polygon_type;

using namespace std;
using namespace semantic_map;



// Standard C++ entry point
int main(int argc, char** argv) 
{
  // Initialize ROS
  ros::init(argc, argv, "semantic_map_query_node");
  ROS_INFO_STREAM("semantic_map_query_node running");
  ros::NodeHandle nh;
  tf::TransformListener tf_(ros::Duration(10));

  unsigned int mx_, my_; // associated map coordinates of the costmap index under consideration.
  unsigned int omx_, omy_; // associated map coordinates of the object bounding box descibed in world coordinates.
  double owx_, owy_; // world coordinates of the object to be converted into world coordinates.

  polygon_type poly;
  
  semantic_map::SemanticMap* semantic_map = new semantic_map::SemanticMap(nh);

  costmap_2d::Costmap2DROS* global_costmap_ = new costmap_2d::Costmap2DROS("global_costmap", tf_);

  unsigned char* costs;
  costs = global_costmap_->getCostmap()->getCharMap();
  //semantic_map->createMap();
  //while (ros::ok())
  //{
      std::list<Object> object_list = semantic_map->getSemanticMap();

      //ROS_INFO_STREAM(object_list.size());

      list<Object>::iterator obs_it;

      for (obs_it = object_list.begin(); obs_it != object_list.end(); ++obs_it)
      {
          semantic_map::Object& object = *obs_it;
          
          ROS_INFO_STREAM("object");

          

          
    
          //costmap_->indexToCells(n, mx_, my_); 

          for (int i = 0; i < 4; i++) 
          {
               owx_ = object.geometry.bounding_box.vertices[i].x;
               owy_ =  object.geometry.bounding_box.vertices[i].y;

               global_costmap_->getCostmap()->worldToMap(owx_, owy_, omx_, omy_);

               ROS_INFO_STREAM(omx_);
               ROS_INFO_STREAM(omy_);  
               ROS_INFO_STREAM("--------------------------------------");

               
               poly.outer().push_back(point_type(omx_,omy_));

        
           }
      }
      //ROS_INFO_STREAM("--------------------------------------");
      //ros::Duration(3.0).sleep();
  //}
  
  // Wait for SIGINT/Ctrl-C

  //
  float max = 0; 
  for (unsigned int n = 0; n < 1000000; n++)
  {
      float c = costs[n];
      if (c > 0 )
      {
          global_costmap_->getCostmap()->indexToCells(n, mx_, my_); 
          point_type p(mx_,my_);
          double distance = boost::geometry::distance(p, poly);
          
          if ( distance > max)
          {
              max = distance;
          }

          
          
      }
  }
  ROS_INFO_STREAM(max); 
  

  ros::spin();

  return 0;
}
