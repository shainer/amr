/* 
 * File:   Tree.h
 * Author: shainer
 */

#ifndef TREE_H
#define	TREE_H

#include <QtCore/QList>
#include "RobotComponents.h"

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
            qDeleteAll(children);
        }
    };
    
    /* Used to compare nodes inside the tree */
    typedef bool (*ComparisonFunction)(T, T);
    ComparisonFunction m_comparison;
    
    Node* m_root;

public:
    Tree(T rootValue, ComparisonFunction f = Tree<T>::defaultComparison)
        : m_root( new Node(rootValue, 0) )
        , m_comparison(f)
    {}

    Tree(ComparisonFunction f = Tree<T>::defaultComparison)
        : m_root(0)
        , m_comparison(f)
    {}
    
    ~Tree()
    {
        delete m_root;
    }
    
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
        
        nodeQueue.append(m_root);
        
        while (!nodeQueue.isEmpty()) {
            Node* p = nodeQueue.takeFirst();
            
            if (m_comparison(p->value, parent)) {
                p->children.append( new Node(nValue, p) );
                return true;
            }
            
            nodeQueue.append(p->children);
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
            
            if (m_comparison(n->value, parent)) {
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
            
            if (m_comparison(n->value, node)) {
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
            
            if (m_comparison(n->value, node)) {
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
        return (a == b);
    }
    
    static bool componentComparison(RobotComponent* c1, RobotComponent* c2)
    {
        return (c1->getName() == c2->getName());
    }
};

#endif	/* TREE_H */

