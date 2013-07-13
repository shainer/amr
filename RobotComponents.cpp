#include "RobotComponents.h"

RobotComponent::RobotComponent(QString name, ComponentType t)
    : m_type(t)
    , m_name(name)
{}

RobotComponent::~RobotComponent()
{}

int RobotComponent::getName()
{
    return m_name;
}

double RobotComponent::getParameter(int i) const
{
    return m_configParameters[i];
}

RobotComponent::ComponentType RobotComponent::getType()
{
    return m_type;
}

void RobotComponent::setParameter(int i, double param)
{
    m_configParameters.insert(i, param);
}

void RobotComponent::appendParameter(double param)
{
    m_configParameters.append(param);
}

void RobotComponent::setParameters(const QList<double>& params)
{
    m_configParameters = params;
}

Joint::Joint(QString name, JointType t, double p)
    : RobotComponent(name, RobotComponent::Joint)
    , m_jointType(t)
{
    setParameter(0, p);
}

Joint::~Joint()
{}

Joint::JointType Joint::getJointType() const
{
    return m_jointType;
}

DummyComponent::DummyComponent(QString name)
    : RobotComponent(name, RobotComponent::Dummy)
{}

DummyComponent::~DummyComponent()
{}