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
 *                Dr. Anne Spalanzani (Inria)
 *********************************************************************/


#ifndef OBJECT_STATES_PUBLISHER_PLUGIN_HH
#define OBJECT_STATES_PUBLISHER_PLUGIN_HH

#include <boost/bind.hpp>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh> 

// ROS
#include <ros/ros.h> 

#include <perception/ObjectsState.h> 

using namespace gazebo;
using namespace physics;

namespace gazebo 
{
	class GazeboRosObjectsStatePublisher : public WorldPlugin 
	{
	public:
		GazeboRosObjectsStatePublisher();
		~GazeboRosObjectsStatePublisher();

		void Load ( physics::WorldPtr _world, sdf::ElementPtr _sdf );
        void OnUpdate ( const common::UpdateInfo & _info );
        void publishObjectsState();

    private:
    	event::ConnectionPtr updateConnection;
    	physics::WorldPtr world_;
    	physics::ModelPtr model_;
        Model_V models_;

    	// ROS STUFF
        boost::shared_ptr<ros::NodeHandle> rosnode_;
        std::string namespace_;
        ros::Publisher objects_state_publisher_;
        perception::ObjectsState objects_state_;

        // Update Rate
    	double update_rate_;
    	double update_period_;
    	common::Time last_update_time_;

	};

// Register this plugin with the simulator
GZ_REGISTER_WORLD_PLUGIN ( GazeboRosObjectsStatePublisher )
}

#endif // OBJECT_STATES_PUBLISHER_PLUGIN_HH