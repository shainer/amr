#include "RobotComponents.h"

RobotComponent::RobotComponent(int id, ComponentType t)
    : m_type(t)
    , m_id(id)
{}

RobotComponent::~RobotComponent()
{}

int RobotComponent::getId()
{
    return m_id;
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
    if (i >= m_configParameters.size()) {
        m_configParameters.insert(i, param);
    } else {
        m_configParameters[i] = param;
    }
}

void RobotComponent::setParameters(const QList<double>& params)
{
    m_configParameters = params;
}

Joint::Joint(int id, JointType t, double p)
    : RobotComponent(id, RobotComponent::Joint)
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
