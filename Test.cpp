#include "doctest.h"
#include "FamilyTree.hpp"
#include <string>
#include <iostream>
using namespace std;
using namespace family;

TEST_CASE("Test case 1") {
   	Tree T("Yosef");
	T.addMother("Yosef","Sarah")
	.addFather("Yosef","Adam")
	.addFather("Sarah","Adam")
	.addMother("Adam","Ronit")
	.addMother("Adam", "Zeava")
	.addFather("Zeava","Shmuel")
	.addFather("Adam", "Tom")
	.addMother("Sarah", "Revital");
	
	CHECK(T.relation("Yosef") == string("me"));
    CHECK(T.relation("Sarah") == string("mother"));
    CHECK(T.relation("Adam") == string("father"));
    CHECK(T.relation("Revital") == string("grandmother"));
    CHECK(T.relation("Zeava") == string("great-grandmother"));
    CHECK(T.relation("Tom") == string("grandfather"));
    CHECK(T.relation("Ronit") == string("grandmother"));
    CHECK(T.relation("Shmuel") == string("great-great-grandfather"));
    CHECK(T.relation("Dani") == string("unrelated"));
    CHECK(T.relation("Zeev") == string("unrelated"));
    CHECK(T.relation("abcd") == string("unrelated"));
  
    CHECK(T.find("mother") == string("Sarah"));
    CHECK(T.find("father") == string("Adam")); 
    CHECK(T.find("grandfather") == string("Tom"));
    CHECK(T.find("great-grandmother") == string("Zeava"));
    CHECK(T.find("great-great-grandfather") == string("Shmuel"));
    CHECK_THROWS(T.find("great-great-great-grandmother"));
}

TEST_CASE("Test case 2") {
    Tree T("b");
    T.addMother("b","c")
	.addFather("c","d")
	.addMother("d","e")
	.addFather("e","f")
	.addMother("f", "g")
	.addFather("g","h")
	.addMother("h", "i")
	.addFather("i", "j")
	.addMother("j","k")
	.addFather("k","l");
	
	CHECK(T.relation("b") == string("me"));
    CHECK(T.relation("c") == string("mother"));
    CHECK(T.relation("d") == string("grandfather"));
    CHECK(T.relation("e") == string("great-grandmother"));
    CHECK(T.relation("f") == string("great-great-grandfater"));
    CHECK(T.relation("g") == string("great-great-great-grandmother"));
    CHECK(T.relation("h") == string("great-great-great-great-grandfather"));
    CHECK(T.relation("i") == string("great-great-great-great-great-grandmother"));
    CHECK(T.relation("j") == string("great-great-great-great-great-great-grandfather"));
    CHECK(T.relation("k") == string("great-great-great-great-great-great-great-grandmother"));
    CHECK(T.relation("l") == string("great-great-great-great-great-great-great-great-grandfather"));
    CHECK(T.relation("m") == string("unrelated"));
    
    CHECK(T.find("me") == string("b"));
    CHECK(T.find("mother") == string("c")); 
    CHECK(T.find("grandfather") == string("d"));
    CHECK(T.find("great-grandmother") == string("e"));
    CHECK(T.find("great-great-grandfather") == string("f"));
    CHECK(T.find("great-great-great-grandmother") == string("g"));
    CHECK(T.find("great-great-great-great-grandfather") == string("h")); 
    CHECK(T.find("great-great-great-great-great-grandmother") == string("i"));
    CHECK(T.find("great-great-great-great-great-great-grandfather") == string("j"));
    CHECK(T.find("great-great-great-great-great-great-great-grandmother") == string("k"));
    CHECK(T.find("great-great-great-great-great-great-great-great-grandfather") == string("l"));
    
    CHECK_THROWS(T.find("father")); 
    CHECK_THROWS(T.find("grandmother") );
    CHECK_THROWS(T.find("great-grandfather") );
    CHECK_THROWS(T.find("great-great-grandmother") );
    CHECK_THROWS(T.find("great-great-great-grandfather") );
    CHECK_THROWS(T.find("great-great-great-great-grandmother")  );
    CHECK_THROWS(T.find("great-great-great-great-great-grandfather") );
    CHECK_THROWS(T.find("great-great-great-great-great-great-grandmother") );
    CHECK_THROWS(T.find("great-great-great-great-great-great-great-grandfather") );
    CHECK_THROWS(T.find("great-great-great-great-great-great-great-great-grandmother") );
    CHECK_THROWS(T.find("uncle"));
    
    T.remove("b");
    
    CHECK_THROWS(T.find("me") );
    CHECK_THROWS(T.find("mother")); 
    CHECK_THROWS(T.find("grandfather"));
    CHECK_THROWS(T.find("great-grandmother") );
    CHECK_THROWS(T.find("great-great-grandfather"));
    CHECK_THROWS(T.find("great-great-great-grandmother"));
    CHECK_THROWS(T.find("great-great-great-great-grandfather") ); 
    CHECK_THROWS(T.find("great-great-great-great-great-grandmother") );
    CHECK_THROWS(T.find("great-great-great-great-great-great-grandfather") );
    CHECK_THROWS(T.find("great-great-great-great-great-great-great-grandmother"));
    CHECK_THROWS(T.find("great-great-great-great-great-great-great-great-grandfather") );
    
    CHECK(T.relation("b") == string("unrelated"));
    CHECK(T.relation("c") == string("unrelated"));
    CHECK(T.relation("d") == string("unrelated"));
    CHECK(T.relation("e") == string("unrelated"));
    CHECK(T.relation("f") == string("unrelated"));
    CHECK(T.relation("g") == string("unrelated"));
    CHECK(T.relation("h") == string("unrelated"));
    CHECK(T.relation("i") == string("unrelated"));
    CHECK(T.relation("j") == string("unrelated"));
    CHECK(T.relation("k") == string("unrelated"));
    CHECK(T.relation("l") == string("unrelated"));
    CHECK(T.relation("z") == string("unrelated"));
    CHECK(T.relation("n") == string("unrelated"));
    CHECK(T.relation("o") == string("unrelated"));
    
}

TEST_CASE("Test case 3") {
    Tree T("a");
    T.addMother("a","b")
	.addFather("a","a")
	.addMother("b","c")
	.addFather("c","a")
	.addMother("c", "d")
	.addFather("d","a")
	.addMother("d", "b")
	.addFather("b", "a");
	
	CHECK(T.relation("a") == string("me"));
    CHECK(T.relation("b") == string("mother"));
    CHECK(T.relation("c") == string("grandmother"));
    CHECK(T.relation("d") == string("great-grandmother"));
    CHECK(T.relation("e") == string("unrelated"));
    
    CHECK(T.find("me") == string("a"));
    CHECK(T.find("father") == string("a")); 
    CHECK(T.find("grandfather") == string("a"));
    CHECK(T.find("great-grandfather") == string("a"));
    CHECK(T.find("great-great-grandfather") == string("a"));
    CHECK(T.find("mother") == string("b"));
    CHECK(T.find("grandmother") == string("c")); 
    CHECK(T.find("great-grandmother") == string("d"));
    CHECK(T.find("great-great-grandmother") == string("b"));
    
    T.remove("d");
    CHECK_THROWS(T.find("great-great-grandfather"));
    CHECK_THROWS(T.find("great-great-grandmother"));
    CHECK_THROWS(T.find("great-grandmother"));
    
    T.addMother("c","x")
    .addMother("x","y")
    .addFather("y","z");
    
    CHECK(T.find("great-great-grandfather") == string("x"));
    CHECK(T.find("great-great-grandmother") == string("y"));
    CHECK(T.find("great-grandmother") == string("z"));
      
    T.remove("b");
    
    CHECK(T.relation("b") == string("unrelated"));
    CHECK(T.relation("c") == string("unrelated"));
    CHECK(T.relation("d") == string("unrelated"));
         
    T.addMother("a","d");
    
    CHECK_THROWS(T.find("grandfather"));
    CHECK_THROWS(T.find("grandmother") );
    CHECK_THROWS(T.find("great-grandfather"));
    CHECK_THROWS(T.find("great-grandmother"));
    
    CHECK(T.relation("x") == string("unrelated"));
    CHECK(T.relation("y") == string("unrelated"));
    CHECK(T.relation("z") == string("unrelated"));
    CHECK(T.relation("w") == string("unrelated"));
    
}