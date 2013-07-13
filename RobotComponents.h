/* 
 * File:   RobotComponents.h
 * Author: shainer
 *
 * Created on 13 luglio 2013, 1.39
 */

#ifndef ROBOTCOMPONENTS_H
#define	ROBOTCOMPONENTS_H

#include <QtCore/QList>

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

#endif	/* ROBOTCOMPONENTS_H */

