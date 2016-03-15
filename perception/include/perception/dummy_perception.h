/*********************************************************************
 *
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2015, Hochschule Bonn-Rhein-Sieg, Germany
 *                      Inria, France
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Hochschule Bonn-Rhein-Sieg, Germany and Inria, 
 *     France nor the names of its contributors may be used to 
 *     endorse or promote products derived from this software without 
 *     specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 * Author: Niranjan Vilas Deshpande
 *         (niranjan.deshpande187@gmail.com)
 *
 * Supervised by: Sven Schneider (Hochschule Bonn-Rhein-Sieg)
 *                Prof. Dr. Paul G. Ploeger (Hochschule Bonn-Rhein-Sieg)
 *		          Dr. Anne Spalanzani (Inria)
 *********************************************************************/

#ifndef _DUMMY_PERCEPTION_H
#define _DUMMY_PERCEPTION_H

#include <boost/algorithm/string.hpp>
#include <boost/thread.hpp>
#include <list>
#include <string.h>
#include <math.h> 
#include <iostream> 
#include <vector> 

// ROS related 
#include <ros/ros.h>
#include <semantic_map/ObjectList.h>
#include <semantic_map/Object.h>
#include <semantic_map/semantic_map.h>
#include <perception/2DOBB.h>
#include <perception/Vector2.h>
#include <perception/ObjectsState.h> 
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <gazebo/physics/BoxShape.hh>
#include <geometry_msgs/Vector3.h> 

using namespace std;
using namespace semantic_map;

typedef struct ObjectDataTag
{
    double width;
    double height;
    string category;
    string subcategory;

} ObjectData;


class DummyPerception
{
public:
	DummyPerception(const ros::NodeHandle &nh);

	~DummyPerception();

	void updateMap();

private:

	void objectsStateCallback(const perception::ObjectsState::ConstPtr& msg);

	void updateMapLoop(double frequency);

	void computeValues();

	void computeBbAndSp(const Vector2& center, const double w, const double h, double angle, semantic_map::Object& obj);

    void printUpdates(std::list<Object>& list);

    double precision(double number);

	ros::NodeHandle nh_;

	ros::Subscriber gazebo_ros_objects_state_subscriber;

	perception::ObjectsState objects_state_; 

	perception::ObjectsState objects_state_temp_; 

	semantic_map::SemanticMap* semantic_map;

	std::list<Object> object_list_;

    typedef boost::recursive_mutex mutex_t;
    mutex_t* access_;

    /** Corners of the box, where 0 is the lower left. */
    Vector2 corner[4];

    /** Semantic positions of object, where 0 is the lower side. */
    geometry_msgs::Vector3 sp[4];
    //std::vector<geometry_msgs::Vector3> sp;

    bool map_update_thread_shutdown_, map_create;

	boost::thread* map_update_thread_; // @brief A thread for updating the semantic map

};

#endif