#include<iostream>
#include<list>
#include<fstream>
#include <conio.h>
#include <string>
#include<vector>
#include <sstream>
using namespace std;

vector<string> Words;
bool exitRequest = false;

class Node {// Class defining the properties of a node.
private:
    string NodeName;
public :
    void addName(string XX){NodeName = XX;}
    string getName(){return NodeName;}
};
                                //list of class NODE type being created below
list<Node*> NodeList;           // To keep a track of all nodes.
list<Node*> UnusableNodes;      //To keep track of all unusable nodes specifically.
list<Node*> BaseResources;      // To keep track of all basic resources as explained in the portfolio description.

struct Link{                    // simple structure storing pointers of class node type serving as links between the nodes.
    Node* From;
    Node* To;
};
list<Link*> EdgeList;           // A list of type link to keep track of all links between different nodes.

void AssignBaseResources(){     // This function differentiates which resources are base resources and which are not.
    BaseResources.clear();
    for(list<Node*>::iterator It = NodeList.begin(); It!=NodeList.end();It++){
        bool isBasic = true;
        for(list<Link*>::iterator IT = EdgeList.begin(); IT!= EdgeList.end(); IT++){
            if((*It)==(*IT)->From){
                isBasic = false;
            }
        }
        if(isBasic){
            BaseResources.push_back(*It);
        }
    }
}

void readFile(){                // This function reads a .txt file as requested in the assignment and splits the words into a vector.
    ifstream InFile;
    string Word;


    InFile.open("Resources.txt");

    if(!InFile){
        cout<<"Coudnt Open Text File"<<endl;
    }
    while(InFile>>Word){
        Words.push_back(Word);
    }
}

void CreateGraph(){// uses the words stored in the vector while reading the .txt file to create graph as requested in the assignment
    readFile();
    int counter=0;
    for(int i = 0; i < Words.size()/2; i++){
        bool XX= false;
        list<Node*>::iterator it = NodeList.begin();
        for(it;it!=NodeList.end();it++){
            if((*it)->getName()==Words[counter]){
                XX= true;
                break;
            }
        }
        Link *newLink = new Link;
        if(!XX){
            Node *newNode = new Node;
            newNode->addName(Words[counter++]);
            NodeList.push_back(newNode);
            newLink->From = newNode;
        }else{
            counter++;
            newLink->From = *it;
        }

        XX=false;
        for(it = NodeList.begin();it!=NodeList.end();it++){
            if((*it)->getName()==Words[counter]){
                XX= true;
                break;
            }
        }
        if(!XX){
            Node *newNode = new Node;
            newNode->addName(Words[counter++]);
            NodeList.push_back(newNode);
            newLink->To = newNode;

        }else{
            counter++;
            newLink->To = *it;
        }
        EdgeList.push_back(newLink);
    }
}

void checkUsability(){    //Checks whether all resources are usable or not based on the specifications mentioned in the description
    UnusableNodes.clear();
    for(int  i = 0 ; i <2 ; i++){
        list<Node*>::iterator It = NodeList.begin();
        for(It; It!=NodeList.end(); It++){
            bool isUsable =false;
            for(list<Link*>::iterator it = EdgeList.begin(); it!= EdgeList.end(); it++){
                if((*It)==(*it)->From){
                    bool linkedToUsable = true;
                    for(list<Node*>::iterator IT= UnusableNodes.begin(); IT!= UnusableNodes.end();IT++){
                        if((*IT==(*it)->To)){
                            bool isBase = false;
                            for(list<Node*>::iterator XX = BaseResources.begin(); XX!= BaseResources.end();XX++){
                                if(*XX==(*it)->To){
                                    isBase= true;
                                }
                            }
                            if(!isBase){
                                linkedToUsable =false;
                            }
                        }
                    }
                    if(linkedToUsable){
                        isUsable=true;
                    }
                }
            }
            if(!isUsable){
                UnusableNodes.push_back(*It);
            }
        }
    }
//    for(It=NodeList.begin; It!=NodeList.end(); It++){
//
//    }
}

void ShowAllNodes(){ // Shows all node names present(this function is unused and was there for utility purposes)
    for(list<Node*>::iterator IT = NodeList.begin();IT != NodeList.end(); IT++){
        cout<<(*IT)->getName()<<endl;
    }
}

void ShowNodes(){   // Creates a simple display showing all nodes and whether or not they are usable.
    cout<<endl<<"List of all Nodes:"<<endl;
    checkUsability();
    for(list<Node*>::iterator IT = NodeList.begin();IT != NodeList.end(); IT++){
        bool isUsable = true;
        for(list<Node*>::iterator it = UnusableNodes.begin(); it != UnusableNodes.end(); it++){
            if((*IT)->getName() == (*it)->getName()){
                isUsable = false;
            }
        }
        if(isUsable){
            cout << (*IT)->getName()<< "   -- Usable."<<endl;
        }else{
            bool isBasic = false;
            for(list<Node*>::iterator XX = BaseResources.begin(); XX != BaseResources.end(); XX++){
                if(*XX == *IT){
                    isBasic = true;
                }
            }
            if(isBasic){
                cout << (*IT)->getName()<< "   -- Usable(Base Resource)"<<endl;
            }else{
                cout << (*IT)->getName()<< "   -- Unusable."<<endl;
            }
        }
    }
}

void ShowGraph(){  // Creates a simple display of graph showing a collection of links from nodes to nodes as dictated
    cout<<endl<<"Current view of the graph :"<<endl;
    int counter = 1 ;
    for(list<Link*>::iterator IT = EdgeList.begin();IT!=EdgeList.end();IT++){
        cout<<"Link "<<counter<<":  "<<((*IT)->From)->getName()<<" ->  "<<((*IT)->To)->getName()<<endl;
        counter++;
    }
}


void RemoveNode(string NODE){ // Removes a node with the input as name.
    list<Node* >::iterator It = NodeList.begin();
    for(It; It != NodeList.end(); It++){
        if(NODE.compare((*It)->getName())==0){
            for(list<Link*>::iterator IT = EdgeList.begin();IT!=EdgeList.end();IT++){
                if((*IT)->From==(*It)||(*IT)->To==(*It)){
                    Link *ptr= *IT;
                    IT = EdgeList.erase(IT);
                    delete ptr;
                    IT--;
                }
            }
            Node* PTR = *It;
            It = NodeList.erase(It);
            delete PTR;
        }
    }
}

void AddNode(string NAME){ // creates a node with the argument as the name of the node.
    Node* newNode = new Node;
    newNode->addName(NAME);
    NodeList.push_back(newNode);
}

void AddLink(string X1,string X2){ // creates a link from the first argument to the second argument.
    list<Node*>::iterator It = NodeList.begin();
    Node *to,*from;
    bool nodeFound1 = false;
    bool nodeFound2 = false;
    for(It; It != NodeList.end(); It++){
        if(X1==(*It)->getName()){
            nodeFound1 = true;
            from = (*It);
            break;
        }
    }

    for(It =  NodeList.begin(); It != NodeList.end(); It++){
        if(X2==(*It)->getName()){
            nodeFound2 = true;
            to = (*It);
            break;
        }
    }
    if(!nodeFound1){
        cout<< "node1 was not found.Please create the node first and try again." << endl;
        return;
    }
    if(!nodeFound2){
        cout<< "node2 was not found. Please create the node first and try again." << endl;
        return;
    }
    if(nodeFound1&&nodeFound2){
        Link* newLink = new Link;
        newLink->From = from;
        newLink->To = to;
        EdgeList.push_back(newLink);
    }
}

void ShowAdjacencyList(){  // On command, displays the graph in a standard adjacency list view.
    cout<<endl<<"The adjacency List view of the graph is shown below"<<endl;
    for(list<Node*>::iterator It = NodeList.begin(); It!= NodeList.end(); It++){
        cout<<"["<<(*It)->getName() << "] -> [";
        for(list<Link*>::iterator IT = EdgeList.begin();IT != EdgeList.end();IT++){
            if((*It)==(*IT)->From){
                cout<<((*IT)->To)->getName()<<"] -> [";
            }
        }
        cout<<"]"<<endl;
    }
}

void TakeInput(){ // function that governs the actions to perform after input command is given.
    cout<<endl<<endl<<"What is your command??"<<endl;
    bool correctCommand = false;
    string Command;
    getline(cin,Command);
    if(Command == "Q"||Command == "q"){
        exitRequest = true;
        return;
    }else{
        for(list<Node*>::iterator It = NodeList.begin(); It != NodeList.end(); It++){
            if((*It)->getName() == Command){
                RemoveNode(Command);
                correctCommand = true;
                break;
            }
        }
        if(Command.compare(0,7,"ADDNODE")==0){
            correctCommand = true;
            string Input = Command.substr(8,Command.size()-8);
            AddNode(Input);
        }
        if(Command.compare(0,7,"ADDLINK")==0){
            correctCommand = true;
            vector<string> linkInput;
            string buffer;
            stringstream ss(Command);
            while(ss>>buffer){
                linkInput.push_back(buffer);
            }
            vector<string>::iterator XX = linkInput.begin();
            XX++;
            string Input1 = (*XX);
            XX++;
            string Input2 = (*XX);
            AddLink(Input1,Input2);
        }
        if(Command.compare(0,9,"ADJACENCY")==0){
            correctCommand = true;
            ShowAdjacencyList();
        }
        if(!correctCommand){
            cout<<"The Command you entered was invalid. Please try again."<<endl;
        }
    }
    cin.clear();
}




int main(){  // MAIN Function
    CreateGraph();
    AssignBaseResources();
    while(!exitRequest){
        ShowGraph();
        ShowNodes();
        TakeInput();
    }
    //ShowAllNodes();
    return 0;
}
