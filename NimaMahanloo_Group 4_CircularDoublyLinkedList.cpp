// Nima Mahanloo
// Circular Linked List
// CISP 430
#include <iostream>
#include <fstream>
using namespace std;
// A structure as linked list a node
struct node
{
    bool firstNode = false;
    char* name = (char*)malloc(sizeof(char));
    node* next = nullptr;
    node* prev = nullptr;
};
// A module to add new node on head of list
void addNode (node* (&head), node* tail)
{
    head->next = new node;
    head->next->next = tail;
    head->next->prev = head;
    head = head->next;
    head->name = "\0";
}
// A module to push read names on the list
void pushList (node* (&head), node* tail, char* readName)
{
    if (head->firstNode == false)
    {
        addNode (head, tail);
    }
    head->name = readName;
    if (head->firstNode == true)
    {
        head->firstNode = false;
    }
}
// A module to delete nodes from tail
void popRList (node* (&head), node* (&tail))
{
    if (head != tail)
    {
        node* temp = tail;
        tail = tail->next;
        head->next = tail;
        tail->prev = head;
        delete temp;
        temp = nullptr;
    }
    else
    {
        delete head;
        head = nullptr;
        delete tail;
        tail = nullptr;
    }
}
// A module to pop nodes from list
void popList (node* (&head), node* (&tail))
{
    if (head != tail)
    {
        node* temp = head;
        head = head->prev;
        head->next = tail;
        tail->prev = head;
        delete temp;
        temp = nullptr;
    }
    else
    {
        delete head;
        head = nullptr;
        delete tail;
        tail = nullptr;
    }
}
// A module to delete user selected nodes from tail and head
void delNodes (node* (&head), node* (&tail), int nodes)
{
    int counter, frontNodes;
    node* curr = tail;
    frontNodes = (nodes / 2) + (nodes % 2);
    for (counter = 0; counter < frontNodes; counter++)
    {
        popRList (head, tail);
    }
    for (counter = 0; counter < (nodes - frontNodes); counter++)
    {
        popList (head, tail);
    }
}
// A module to read names from input file and push them to list
void readFile (node* (&head), node* tail)
{
    char* readName = (char*)malloc(sizeof(char));
    ifstream read ("input.txt");
    if (read.is_open())
    {
        while (!(read.eof()))
        {
            read >> readName;
            pushList (head, tail, readName);
            readName = (char*)malloc(sizeof(char));
        }
    }
    else
    {
        cout << "Error: Can not open file!" << endl;
    }
}
// A module to display list nodes data
void printList (node* tail)
{
    int index = 1;
    node* curr = tail;
    if (curr != nullptr)
    {
        cout << "Circular Linked List >" << endl << endl;
        while ((curr->next != tail) && (curr->name != "\0"))
        {
            cout << index << ": " << curr->name << endl;
            curr = curr->next;
            index++;
        }
        cout << index << ": " << curr->name << endl;
    }
    else
    {
        cout << "List cleared!" << endl;
    }
}
// A module to delete entire of linked list
void delList (node* (&head), node* (&tail))
{
    while (head != tail)
    {
        popList(head, tail);
    }
    popRList (head, tail);
}

int main()
{
    // An integer to hold number of nodes which needs to be deleted
    int nodes = 0;
    // An object from structure 'node' as circular doubly linked list tail
    node* tail = new node;
    // An object from node as list head
    node* head = tail;
    // Head and tail Initials
    tail->next = head;
    head->next = tail;
    tail->prev = head;
    head->prev = tail;
    // Set first node flag on
    head->firstNode = true;
    // Call a module to read names from input file and push them to the list
    readFile (head, tail);
    // Call a module to display linked list contains
    printList (tail);
    // Ask from user about nodes to delete
    cout << endl << "Please enter how many nodes needs to be deleted from the list? ";
    cin >> nodes;
    cout << endl;
    // Call a module to delete user selected nodes from list
    delNodes (head, tail, nodes);
    // Call a module to display final linked list contains
    printList (tail);
    // Clear heap and memory
    if (tail != nullptr)
    {
        delList (head, tail);
    }
    return 0;
}
