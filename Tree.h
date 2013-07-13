/* 
 * File:   Tree.h
 * Author: shainer
 */

#ifndef TREE_H
#define	TREE_H

#include <QtCore/QList>
#include <iostream>
#include "RobotComponents.h"

using namespace std;

/*
 * TODO
 * Better error handling 
 */

template <class T>
class Tree
{
private:
    class Node {
    public:
        T value;
        QList< Node* > children;
        Node* parent;
        
        Node(T v)
            : value(v)
            , parent(0)
        {}
        
        Node(T v, Node* p)
            : value(v)
            , parent(p)
        {}
        
        ~Node()
        {
            Q_FOREACH (Node* child, children) {
                delete child;
            }
        }
    };
    
    Node* m_root;
    typedef bool (*ComparisonFunction)(T, T);
    ComparisonFunction m_comparison;
    
    bool compareNodes(Node* n1, Node* n2)
    {
        return (n1->value == n2->value);
    }
    
public:
    Tree(T rootValue, ComparisonFunction f = Tree<T>::defaultComparison)
        : m_root( new Node(rootValue, 0) )
        , m_comparison(f)
    {}
        
    Tree(ComparisonFunction f = Tree<T>::componentComparison)
        : m_root(0)
        , m_comparison(f)
    {}
    
    ~Tree() {}
    
    void setRoot(T rootValue)
    {
        if (m_root) {
            delete m_root;
        }

        m_root = new Node(rootValue, 0);
    }
    
    bool addChild(T parent, T nValue)
    {
        QList< Node* > nodeQueue;
        
        if (!m_root) {
            return false;
        }
        
        cout << nodeQueue.size() << endl;
        nodeQueue.append(m_root);
        cout << nodeQueue.size() << endl;
        
        while (!nodeQueue.isEmpty()) {
            Node* n = nodeQueue.takeFirst();
            
            if (m_comparison(n->value, parent)) {
                n->children.append( new Node(nValue, n) );
                return true;
            }
            
            nodeQueue.append(n->children);
        }
        
        return false;
    }
    
    bool removeChild(T parent, T nValue)
    {
        QList< Node* > nodeQueue;
        
        if (!m_root) {
            return false;
        }
        
        nodeQueue.append(m_root);
        
        while (!nodeQueue.isEmpty()) {
            Node* n = nodeQueue.takeFirst();
            
            if (n->value == parent) {
                for (typename QList< Tree<T>::Node* >::iterator it = n->children.begin(); it != n->children.end(); it++) {
                    if ((*it)->value == nValue) {
                        n->children.erase(it);
                        return true;
                    }
                }
                
                return false;
            }
            
            nodeQueue.append(n->children);
        }
        
        return false;
    }
    
    QList<T> getChildren(T node) const
    {
        QList< Node* > nodeQueue;
        
        if (!m_root) {
            return QList<T>();
        }
        
        nodeQueue.append(m_root);
        
        while (!nodeQueue.isEmpty()) {
            Node* n = nodeQueue.takeFirst();
            
            if (n->value == node) {
                QList<T> values;
                
                Q_FOREACH (Node* child, n->children) {
                    values.append( child->value );
                }
                
                return values;
            }
            
            nodeQueue.append(n->children);
        }
        
        return QList<T>();
    }
    
    T getParent(T node) const
    {
        QList< Node* > nodeQueue;
        
        if (!m_root) {
            return T();
        }
        
        nodeQueue.append(m_root);
        
        while (!nodeQueue.isEmpty()) {
            Node* n = nodeQueue.takeFirst();
            
            if (n->value == node) {
                Q_ASSERT(n->parent != 0);
                return n->parent->value;
            }
            
            nodeQueue.append(n->children);
        }
        
        return T();
    }
    
    QList<T> breadthfirst() const
    {
        QList< Node* > nodeQueue;
        QList<T> result;
        
        if (!m_root) {
            return QList<T>();
        }
        
        nodeQueue.append(m_root);
        
        while (!nodeQueue.isEmpty()) {
            Node* n = nodeQueue.takeFirst();
            result.append( n->value );
            
            nodeQueue.append(n->children);
        }
        
        return result;
    }
    
    static bool defaultComparison(T a, T b)
    {
        cout << "default called" << endl;
        return (a == b);
    }
    
    static bool componentComparison(RobotComponent* c1, RobotComponent* c2)
    {
        cout << "component called" << endl;
        return c1->getId() == c2->getId();
    }
};

#endif	/* TREE_H */

