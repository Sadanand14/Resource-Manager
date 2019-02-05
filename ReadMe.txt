This project was created in the 2nd week of february 2018 (using CodeBlocks IDE) which I have created as a challenge exercise for myself after I got a little more comfortable with C++.
The task is to read a resource.txt file and create a graph based on the content of the .txt file as requested. 
The primary focus of the project is on creating,storing and deleting a network of nodes and links as the user pleases.
It constantly shows the graph after each alteration as well as lists all the nodes along with their usability status.

Please note that I have declared a Node which is dependent on an unusable node as Unusable as well.
I have also assigned any resource which is not linked "to" another node as base resource while creating the graph from .txt file. Any new nodes which are unlinked will be declared as unusable as well. 
You can insert a few commmands in the program to delete/ Add nodes or links(Links cant be individually deleted by user) or also get a new view of the graph.
The default view of the graph is a simple collection of all the links in the graph.

Below is the list of commands:

q/Q  ->  This command quits the execution.

Name of prexisting node -> Entering the name of an already existing node deletes that node along with any links to or from it.

ADDNODE NAME -> This Command adds a new node with the name as "NAME". Please ensure that the keyword ADDNODE stays all caps.

ADDLINK NAME1 NAME2 -> This command adds new link from an already existing node named "NAME1" to an already existing node named "NAME2". Please ensure all caps for keyword.

ADJACENCY -> This command gives the adjacencly list view of the graph which is the more standard view of graph.

Please take a look at the function called "TakeInput" if any issue arises regarding commmand input response.
Please open the .cbp file to access the complete project.