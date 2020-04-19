#include <iostream>
#include <string>
#include <exception>
#include "FamilyTree.hpp"
using namespace std;
using namespace family;

    Tree::Node::Node()
    {
        
    }

    Tree::Tree(string name)
    {
        Node* node = new Node();
        node->_name = name;
        _root = node; 
        _root->_relation="me";
        _root->_height=0;
    }
    
    Tree::Node* Tree::getRoot()
    {
        return _root;
    }
    
    Tree Tree::addFather(string childName ,string fatherName)
    {
        Node* newNode = new Node();
        newNode->_name = fatherName;
        Node* childNode = findNodeByName(_root,childName);
        if(childNode->getFather()==NULL)
        childNode->_father = newNode;
        
        childNode->getFather()->_height= childNode->getHeight()+1;
        childNode->getFather()->_relation=calcRelation('m',childNode->getFather()->getHeight());
        return *this;
    }
    
    Tree Tree::addMother(string childName,string motherName)
    {
        Node* newNode = new Node();
        newNode->_name = motherName;
        Node* childNode = findNodeByName(_root,childName);
        if(childNode->getMother()==NULL)
        childNode->_mother = newNode;
        
        childNode->getMother()->_height=childNode->getHeight()+1;
        childNode->getMother()->_relation=calcRelation('f',childNode->getMother()->getHeight());
        return *this;
    }
    
    Tree::Node* Tree::findNodeByName(Node* node, string name)
    {
        if(node == nullptr) return nullptr;
        if(node->getName() == name) return node;
        
        Node* found = findNodeByName(node->getFather(),name);
        if(found != nullptr) return found;
        return findNodeByName(node->getMother(),name);
    }
    
    Tree::Node* Tree::findNodeByRelation(Node* node, string relation)
    {
        if(node == nullptr) return nullptr;
        if(node->getRelation() == relation) return node;
        
        Node* found = findNodeByRelation(node->getFather(),relation);
        if(found != nullptr) return found;
        return findNodeByRelation(node->getMother(),relation);
    }
       
    string Tree::calcRelation(char gender,int height)
    {
        if(gender == 'm')
        {
            if(height == 1)
              return "father";
            else if(height == 2)
               return "grandfather";
               else
               {
                   string rel = "";
                   for(int i=0; i<height-2; i=i+1)
                    rel = rel + "great-";
                
                    return rel + "grandfather";
                    
               }
        }
        else
        {
            if(height == 1)
              return "mother";
            else if(height == 2)
              return "grandmother";
             else
               {
                   string rel = "";
                   for(int i=0; i<height-2; i=i+1)
                    rel = rel + "great-";
                
                    return rel + "grandmother";
               } 
        }
    }
    
    string Tree::relation(string name)
    {
        Node* node = findNodeByName(_root,name);
        if(node == NULL)
          return "unrelated" ;
        else
          return node->getRelation();
    }
    
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

//wrapper function
 void Tree::display()
 {
   print2DUtil(_root,0);
 }
 
 void Tree::remove(string name)
 {
//    Node* node = findNodeByName(_root,name);
   // deleteNode(node);
   cout<<"not wrk" << endl;
 }
 
 void Tree::deleteNode(Node* node)  
{  
    
      if (node == NULL) return;
    /* first delete both subtrees */
    deleteNode(node->getFather());  
    deleteNode(node->getMother());  
    /* then delete the node */
    delete node;
}  


string Tree::find(string relation)
{

//https://stackoverflow.com/questions/134569/c-exception-throwing-stdstring
struct MyException : public std::exception
{
   std::string s;
   MyException(std::string ss) : s(ss) {}
   ~MyException() throw () {} // Updated
   const char* what() const throw() { return s.c_str(); }
};
    
    Node* node = findNodeByRelation(_root, relation);
   
    if (node == NULL)
      throw MyException("The tree cannot handle the '" + relation + "' relation");
    else
      return node->getName();
}










int main() {
	family::Tree T ("Yosef"); // Yosef is the "root" of the tree (the youngest person).
	T.addFather("Yosef", "Yaakov")   // Tells the tree that the father of Yosef is Yaakov.
	 .addMother("Yosef", "Rachel")   // Tells the tree that the mother of Yosef is Rachel.
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka")
	 .addFather("Isaac", "Avraham")
	 .addFather("Avraham", "Terah");

	T.display();                        // displays the tree in a human-friendly format.

	cout << T.relation("Yaakov") << endl;  // prints "father"
	cout << T.relation("Rachel") << endl;  // prints "mother"
	cout << T.relation("Rivka") << endl;  // prints "grandmother"
	cout << T.relation("Avraham") << endl;  // prints "great-grandfather"
	cout << T.relation("Terah") << endl;  // prints "great-great-grandfather"
	cout << T.relation("xyz") << endl;  // prints "unrelated"
	cout << T.relation("Yosef") << endl;  // prints "me"

	 cout << T.find("mother") << endl;  // prints "Rachel"
	 cout << T.find("great-great-grandfather") << endl;  // prints "Avraham"
 	 try {
 	 	cout << T.find("uncle") << endl;  // throws an exception
 	 } catch (const exception& ex) {
 	  	cout << ex.what() << endl;  // prints "The tree cannot handle the 'uncle' relation"
 	 }

	T.remove("Avraham"); // removes Avraham and Terah
	cout << T.relation("Terah") << endl;  // prints "unrelated"

    return 0;
}