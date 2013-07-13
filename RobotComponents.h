/* 
 * File:   RobotComponents.h
 * Author: shainer
 *
 * Created on 13 luglio 2013, 1.39
 */

#ifndef ROBOTCOMPONENTS_H
#define	ROBOTCOMPONENTS_H

#include <QtCore/QList>
#include <QtCore/QString>

class RobotComponent
{    
public:
    enum ComponentType { Dummy = 0, Joint };
    
    explicit RobotComponent(QString name, ComponentType t);
    virtual ~RobotComponent();
    
    virtual void setParameters(const QList<double>& params);
    virtual void setParameter(int i, double param);
    virtual void appendParameter(double param);
    virtual double getParameter(int i) const;
    virtual ComponentType getType();
    virtual QString getName();
    
private:
    ComponentType m_type;
    QList<double> m_configParameters;
    QString m_name;
};

class Joint : public RobotComponent
{
public:
    enum JointType {Prismatic, Revolute};
    
    explicit Joint(QString name, JointType t, double p);
    virtual ~Joint();
    
    virtual JointType getJointType() const;
    
private:
    JointType m_jointType;
};

class DummyComponent : public RobotComponent
{
public:
    explicit DummyComponent(QString name);
    virtual ~DummyComponent();
};

#endif	/* ROBOTCOMPONENTS_H */

