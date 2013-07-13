#include "RobotStructure.h"

RobotStructure::RobotStructure()
    : m_robotTree( Tree< RobotComponent* >::componentComparison )
{}

RobotStructure::~RobotStructure()
{}

void RobotStructure::addComponent(RobotComponent* comp, QString parent)
{
    if (parent.isEmpty()) {
        m_robotTree.setRoot(comp);
    } else {
        RobotComponent* d = new DummyComponent(parent);
        m_robotTree.addChild(d, comp);
        delete d;
    }
}

RobotComponent* RobotStructure::getComponent(QString name) const
{
    Q_FOREACH (RobotComponent* c, m_robotTree.breadthfirst())
    {
        if (c->getName() == name) {
            return c;
        }
    }
    
    return NULL;
}

QList< RobotComponent* > RobotStructure::getChildrenOf(QString name) const
{
    RobotComponent* d = new DummyComponent(name);
    QList< RobotComponent* > children = m_robotTree.getChildren(d);
    delete d;
    return children;
}

RobotComponent* RobotStructure::getParentOf(QString name) const
{
    RobotComponent* d = new DummyComponent(name);
    RobotComponent* parent = m_robotTree.getParent(d);
    delete d;
    return parent;
}