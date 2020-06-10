/*
* robot_base.h
*/

#ifndef ROBOT_BASE_H
#define ROBOT_BASE_H

class RobotBase {
public:
	RobotBase(void);
	~RobotBase(void);
	virtual void sense() = 0;
	virtual void move() = 0;
};
#endif