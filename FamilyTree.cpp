#include <iostream>
#include <string>
#include <exception>
#include "FamilyTree.hpp"
using namespace std;
using namespace family;

//https://stackoverflow.com/questions/134569/c-exception-throwing-stdstring
//struct for an exception 
struct MyException : public std::exception
{
   std::string s;
   MyException(std::string ss) : s(ss) {}
   ~MyException() throw () {} // Updated
   const char* what() const throw() { return s.c_str(); }
};

//empty Node constructor
    Tree::Node::Node()
    {
        
    }

/**
Tree object constructor
*/
    Tree::Tree(string name)
    {
        Node* node = new Node();
        node->_name = name;
        _root = node; 
        _root->_relation="me";
        _root->_height=0;
        _root->_child=NULL;
    }
    
    Tree::Node* Tree::getRoot()
    {
        return _root;
    }
 
 /**
Makes a new 'father' Node object and connects it to a 'child' Node 
*/   
    Tree Tree::addFather(string childName ,string fatherName)
    {
        if(fatherName=="")
         throw MyException("Can't add an empty string to the tree");
       
        Node* newNode = new Node(); //create a father node and find the child node
        newNode->_name = fatherName;
        Node* childNode = findNodeByName(_root,childName);
        
        if(childNode == NULL) //if theres no such node, throw exception
         throw MyException("Node with the name '"+childName+"' was not found");
        
        if(childNode->getFather() != NULL) //if child node has a father node throw exception
         throw MyException(childName+" already has a father node");
        else //else connect the father node to the child node
        childNode->_father = newNode;
        childNode->getFather()->_height= childNode->getHeight()+1;
        childNode->getFather()->_relation=calcRelation('m',childNode->getFather()->getHeight());
        childNode->_father->_child = childNode;
        
        return *this;
    }
    
   /**
   Makes a new 'mother' Node object and connects it to a 'child' Node
   Same implementation as 'addFather'
  */
    Tree Tree::addMother(string childName,string motherName)
    {
        Node* newNode = new Node();
        newNode->_name = motherName;
        Node* childNode = findNodeByName(_root,childName);
       
        if(childNode == NULL)
         throw MyException("Node with the name '"+childName+"' was not found");
        
        if(childNode->getMother() != NULL)
         throw MyException(childName+" already has a mother node");
        else
         childNode->_mother = newNode;
        childNode->getMother()->_height=childNode->getHeight()+1;
        childNode->getMother()->_relation=calcRelation('f',childNode->getMother()->getHeight());
        childNode->_mother->_child = childNode;
        
        return *this;
    }
    
    /**
    Finds a specific Node on the tree based on the name
   */
    Tree::Node* Tree::findNodeByName(Node* node, string name)
    {
        //base conditions for recursion
        if(node == NULL)
         return NULL;
        if(node->getName() == name) 
         return node;
        //go over all the nodes in the tree
        Node* found = findNodeByName(node->getFather(),name);
        if(found != NULL) 
         return found;
        return findNodeByName(node->getMother(),name);
    }
    
    /**
     Finds a specific Node on the tree based on the relation
      Same implementation as 'findNodeByName'
   */
    Tree::Node* Tree::findNodeByRelation(Node* node, string relation)
    {
        if(node == NULL)
         return NULL;
        if(node->getRelation() == relation) 
         return node;
        Node* found = findNodeByRelation(node->getFather(),relation);
        if(found != NULL) 
         return found;
        return findNodeByRelation(node->getMother(),relation);
    }
    
    /**
    Calculates the relation of a node by it's gender and height on the tree 
   */
    string Tree::calcRelation(char gender,int height)
    {
        if(gender == 'm') //'m' represents 'male'
        {
            //height 1 and 2 special cases
            if(height == 1)
              return "father";
            else if(height == 2)
               return "grandfather";
            else
               {
                   string rel = "";
                   for(int i=0; i<height-2; i=i+1)
                    rel = rel + "great-"; //add great- for every generation
                
                    return rel + "grandfather";
               }
        }
        else //else 'f' represents 'female'
        {
            //height 1 and 2 special cases
            if(height == 1)
              return "mother";
            else if(height == 2)
              return "grandmother";
            else
               {
                   string rel = "";
                   for(int i=0; i<height-2; i=i+1)
                    rel = rel + "great-"; //add great- for every generation
                
                    return rel + "grandmother";
               } 
        }
    }
    
    
    /**
    Finds a specific node based on name and returns it's relation
    if it doesn't find it, it returns "unrelated"
    */
    string Tree::relation(string name)
    {
        Node* node = findNodeByName(_root,name);
        if(node == NULL)
          return "unrelated" ;
        else
          return node->getRelation();
    }
    
    /**
    Prints the tree horizontaly
    */
//https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/    
void Tree::print2DUtil(Node *root, int space)  
{  
    // Base case  
    if (root == NULL)  
        return;  
  
    // Increase distance between levels  
    space += 15;  
  
    // Process right child first  
    print2DUtil(root->getMother(), space);  
  
    // Print current node after space  
    // count  
    cout<<endl;  
    for (int i = 15; i < space; i++)  
        cout<<" ";  
    cout<<root->getName()<<"\n";  
  
    // Process left child  
    print2DUtil(root->getFather(), space);  
}  

/**
Wrapper function
*/
 void Tree::display()
 {
   print2DUtil(_root,0);
 }
 
 
 /**
Removes a specific node based on a name and deletes the sub tree starting from that node
*/
 void Tree::remove(string name)
 {
        Node *node = findNodeByName(_root, name);
        if (node == NULL) 
            throw MyException("No such node in the tree");
        if (node == _root)
            throw MyException("Can't remove root");
       
       //change the child's father/mother node to null 
        if(node == node->_child->_father)
         node->_child->_father = NULL;
        if(node == node->_child->_mother)
         node->_child->_mother = NULL;
        
        deleteSubtree(node);
 }
 
 
 /**
Recursive fuction that deletes the subtree that starts from a node
*/
 void Tree::deleteSubtree(Node* node)  
{  
        if (node == NULL) 
            return;
        deleteSubtree(node->getFather()); //go over all the father nodes
        deleteSubtree(node->getMother()); //go over all the mother nodes
        node->_father = NULL; //set father node of every node to null
        node->_mother = NULL; // set mother node of every node to null
        delete node; // delete the node itself
        node = NULL; // set it to null also
}  

/**
Finds the name of the node of a specific relation
*/
string Tree::find(string relation)
{
    Node* node = findNodeByRelation(_root, relation); //finds the node
    if (node == NULL)
      throw MyException("The tree cannot handle the '" + relation + "' relation");
    else
      return node->getName();
}




