#define NON_MATLAB_PARSING
#define MAX_EXT_API_CONNECTIONS 255
#define PORT 19998

#include <iostream>
#include <extApi.h>
#include <extApi.c>
#include <extApiPlatform.h>
#include <extApiPlatform.c>
#include <extApiCustom.c>
#include <extApiCustom.h>
#include <extApiCustomConst.h>
#include <QtCore/QList>
#include "Tree.h"

using namespace std;

int main()
{
    RobotComponent* c1 = new Joint(1, Joint::Revolute, 0.0);
    RobotComponent* c2 = new Joint(2, Joint::Revolute, 0.0);
    Tree<RobotComponent*> tree;
    tree.setRoot(c1);
    cout << tree.addChild(c1, c2) << endl;
    
//    int connection = simxStart("127.0.0.1", 19998, true, true, 2000,5 );
//
//    if (connection == -1) {
//        cerr << "Error creating connection" << endl;
//        return -1;
//    }
//    
//    simxInt objCount = 0;
//    simxInt **objHandles = new simxInt*;
//    
//    simxGetObjects(connection, sim_object_joint_type, &objCount, objHandles, simx_opmode_oneshot_wait);
//    simxInt* actualHandles = new simxInt[objCount];
//    
//    for (int i = 0; i < objCount; i++) {
//        actualHandles[i] = objHandles[0][i];
//    }
//    
//    simxInt handlesCount;
//    simxInt** handles = new simxInt *;
//
//    simxInt stringCount;
//    simxChar** names = new simxChar*;
//
//    simxGetObjectGroupData(connection, sim_object_joint_type, 0, &handlesCount, handles, NULL, NULL, NULL, NULL, &stringCount, names, simx_opmode_oneshot_wait);
//
//    cout << "Returned handles " << handlesCount << endl;
//    
//    int numStrings = 0;
//    int currentIndex = 0;
//    while (numStrings != stringCount) {
//        if (names[0][currentIndex] == 0) {
//            numStrings++;
//            cout << "  " << numStrings << endl;
//        } else {
//            cout << names[0][currentIndex];
//        }
//        currentIndex++;
//    }
//    
//    delete[] names;
    
//    for(int i=0; i<objCount; i++) {
//        simxFloat *euler = new simxFloat[3];
//        simxFloat *position = new simxFloat[3];
//        simxInt id = actualHandles[i];
//        
//        cout << "DATA FOR ID " << id << endl;
//
//        simxSetObjectSelection(connection, &id, 1, simx_opmode_oneshot_wait);
//        simxGetObjectOrientation(connection,id,-1,euler,simx_opmode_oneshot_wait);
//        simxGetObjectPosition(connection,id,-1,position,simx_opmode_oneshot_wait);
//
//        std::cout << "Orientation:\n";
//
//        for(int j=0;j<3;j++){
//            std::cout  << euler[j] << "\t";
//        }
//
//        std::cout << "\nPosition:\n";
//        for(int j=0;j<3;j++){
//            std::cout << position[j] << "\t";
//        }
//        
//        std::cout << "\n";
//        delete [] euler;
//    }
    
//    delete objHandles;
//    delete actualHandles;
    return 0;
}
