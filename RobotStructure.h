/* 
 * File:   RobotConfiguration.h
 * Author: shainer
 */

#ifndef ROBOTSTRUCTURE_H
#define	ROBOTSTRUCTURE_H

#include "Tree.h"

class RobotStructure
{
private:    
   Tree< RobotComponent* > m_robotTree;

public:
    RobotStructure();
    ~RobotStructure();
    
    void addComponent(RobotComponent* comp, QString parent = "");
    
    RobotComponent* getComponent(QString name) const;
    QList< RobotComponent* > getChildrenOf(QString name) const;
    RobotComponent* getParentOf(QString name) const;
};

#endif
