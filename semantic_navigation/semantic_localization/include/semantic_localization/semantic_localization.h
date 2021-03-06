/*********************************************************************
*
* Software License Agreement (BSD License)
*
* Copyright (c) 2008, Willow Garage, Inc.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
* * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following
* disclaimer in the documentation and/or other materials provided
* with the distribution.
* * Neither the name of the Willow Garage nor the names of its
* contributors may be used to endorse or promote products derived
* from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
* Author: Niranjan Deshpande
*********************************************************************/


#ifndef _SEMANTIC_LOCALIZATION_
#define _SEMANTIC_LOCALIZATION_

#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/PoseStamped.h>
#include <semantic_map/RegionList.h>
#include <semantic_map/query_regions.h>
#include <semantic_map/SemanticMapMessage.h>
#include <sem_nav_msgs/SemanticPose.h>
#include <semantic_map/Region.h>
#include <semantic_map/semantic_map.h>


namespace semantic_localization
{
	class SemanticLocalization
	{
	public:

		SemanticLocalization();
		
		~SemanticLocalization();

		void executeCycle();

		semantic_map::RegionInstance getSemanticPose(geometry_msgs::PoseStamped& geometric_pose);

		geometry_msgs::PoseStamped getGeometricPose();

		void publishSemanticLocalization();

		void querySemanticMap();

	protected:
		void semanticMapMessageCallback(const semantic_map::SemanticMapMessage& semantic_map);

	private:
		bool inObjectBoundingBox(semantic_map::Region& region_, unsigned int x, unsigned int y);

		float  polyX[4], polyY[4];
     	bool  oddNodes_;
     	bool inside_;
     	int i_, j_, k_, l_;

		sem_nav_msgs::SemanticPose robot_pose;
		semantic_map::RegionList regions_list;

		tf::TransformListener listener;
		tf::StampedTransform transform;
		std::string tf_prefix;

		query_semantic_map::QueryRegions* query_regions;

		double publish_frequency;
  		std::string map_frame, base_frame;
  		ros::Publisher semantic_localization_publisher;
  		ros::Publisher pose_publisher;
  		ros::Subscriber semantic_map_sub_;

  		//Instance of SemanticMap class to query the semantic map
		semantic_map::SemanticMap* semantic_map_query_; 
		std::list<semantic_map::Region> region_list;

	};



};
#endif
