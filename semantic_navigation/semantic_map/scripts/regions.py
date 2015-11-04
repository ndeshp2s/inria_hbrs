#!/usr/bin/env python

import rospy
import yaml
import copy

from semantic_map_ros import SemanticMapROS
from semantic_map.srv import *

from rospy_message_converter import message_converter
from yocs_msgs.msg import *
from semantic_map.msg import *
from geometry_msgs.msg import *
from std_msgs.msg import *

'''
This class waits for a query about information about different regions of the environment stored in the semantic map. 
	
The response of the class is a RegionsList message which contains different form of information about regions existing in the robot environment.
'''

class RegionsList(SemanticMapROS):
	def __init__(self):
		filename = rospy.get_param('~filename')
		with open(filename) as f:
			self.data = yaml.load(f)

		self.server = rospy.Service('query_region_instances', QueryRegionInstances, self.service_callback)	


	def service_callback(self, request):
		rospy.loginfo("Regions information is available") 

		regions_list = RegionList()

		for t in self.data:
			regions = Region()

			regions.instance.name = t['instance']

			regions.geometry.pose = message_converter.convert_dictionary_to_ros_message('geometry_msgs/Pose',t['geometry']['pose'])
			regions.geometry.bounding_box = message_converter.convert_dictionary_to_ros_message('semantic_knowledgebase/BoundingBox',t['geometry']['bounding_box'])

			regions.semantics.category = t['semantics']['category']
			regions.semantics.sub_category = t['semantics']['sub_category']

			regions_list.regions.append(regions)

			
		return QueryRegionInstancesResponse(regions_list)

	


def initialize_node():
	'''
	Initialize the RegionsList class and spin to keep python from exiting untill this node is stopped.
	'''

	rospy.init_node('regions_list_node', anonymous=False)
	#rospy.loginfo("regions_node is now running")

	regions_list = RegionsList()

	rospy.spin()

if __name__ == '__main__':
	initialize_node()
