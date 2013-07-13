/* 
 * File:   RobotConfiguration.h
 * Author: shainer
 */

#ifndef ROBOTSTRUCTURE_H
#define	ROBOTSTRUCTURE_H

#include <QtCore/QList>
#include "Tree.h"

class RobotComponent
{    
public:
    enum ComponentType { Joint, MobileBase };
    
    explicit RobotComponent(int id, ComponentType t);
    virtual ~RobotComponent();
    
    virtual void setParameters(const QList<double>& params);
    virtual void setParameter(int i, double param);
    virtual double getParameter(int i) const;
    virtual ComponentType getType();
    virtual int getId();
    
private:
    ComponentType m_type;
    QList<double> m_configParameters;
    int m_id;
};

class Joint : public RobotComponent
{
public:
    enum JointType {Prismatic, Revolute};
    
    explicit Joint(int id, JointType t, double p);
    virtual ~Joint();
    
    virtual JointType getJointType() const;
    
private:
    JointType m_jointType;
};

/*
 * ROBOT:
 * - Robot structure: joints of two types, rigid links, mobile components, etc...
 * - Robot configuration: set of values to assign to those components. Check if colliding, etc...
 */

class RobotStructure
{
private:
    class RobotComponentNode
    {
    public:
        RobotComponent* component;
        
        RobotComponentNode(RobotComponent* c)
            : component(c)
        {}
        
        bool operator==( const RobotComponentNode& other )
        {
            return component->getId() == other.component->getId();
        }
    };
    
   Tree<RobotComponentNode> jointTree;

public:
    RobotStructure(int n_joints);
    ~RobotStructure();
    
    void insertJoint(int pos, Joint j);
    void appendJoint(Joint j);
    void setJoint(Joint j, double p);
    Joint getJoint(int identifier);
};

#endif

