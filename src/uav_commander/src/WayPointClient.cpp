#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <uav_commander/WayPointAction.h>
#include <geometry_msgs/PoseStamped.h>
#include <Eigen/Eigen>
geometry_msgs::PoseStamped current_pose_;
double eps = 0.01;

int main (int argc, char **argv)
{
    int x;
    geometry_msgs::PoseStamped Position1,Position2,Position3,Home;
    Home.pose.position.x = 0;
    Home.pose.position.y = 0;
    Home.pose.position.z = 1;

    Position1.pose.position.x = 1;
    Position1.pose.position.y = 0;
    Position1.pose.position.z = 1;

    Position2.pose.position.x = 1;
    Position2.pose.position.y = 1;
    Position2.pose.position.z = 1;

    Position3.pose.position.x = 0;
    Position3.pose.position.y = 0;
    Position3.pose.position.z = 1;

    ros::init(argc, argv, "way_point_client");
    ros::NodeHandle n_;
    actionlib::SimpleActionClient<uav_commander::WayPointAction> ac("/uav/uav_commander", true);

    ROS_INFO("Waiting for action server to start.");
    ac.waitForServer();

    ROS_INFO("Action server started, sending goal.");

    uav_commander::WayPointGoal way_point;
    for (x=1;x<5;x++)
    {
        switch (x)
        {
        case 1:
            way_point.goal = Home;
            break;
        case 2:
            way_point.goal = Position1;
            break;
        case 3:
            way_point.goal = Position2;
            break;
        case 4:
            way_point.goal = Position3;
            break;
        }

        ac.sendGoal(way_point);
        bool finished_before_timeout = ac.waitForResult(ros::Duration(20.0));
        if (finished_before_timeout)
        {
            actionlib::SimpleClientGoalState state = ac.getState();
            ROS_INFO("The way point number %d has been reached: %s",x,state.toString().c_str());
        }
        else
        {
            ROS_INFO("The way point has been reached before the time out.");
            break;
        }
    }
    return 0;

}
