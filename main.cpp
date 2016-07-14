/*
Neal Viswanath
CSE 240, MTWTF
Professor Selgrad

Assignment#3:
A templated Node-class is used to build a templated LinkedList interface. Testing of the interface is done through a simple console input
Josepheus problem that outputs the survivor until the user quits.
*/


#include <iostream>
#include <cstdlib>
#include <stdio.h>




using namespace std;

/*
The following is a rudimentary Node class that is used to build a Linked List class further below. It acts almost as a struct because it is using primarily
public visibility modifiers.
*/

template<class T>
class Node
{
    public:
        T data;
        Node<T>* next;
        Node(); //default constructor
        Node(const T&); //1 variable constructor
        Node(const T&, Node<T>*); //2 variable constructor
        virtual ~Node(); //destructor
        T getData(); //getter for T data
        void setData(T); //setter for T data
        Node<T>* getNext(); //getter for next
        void setNext(Node<T>*); //setter for next
        Node<T>* copyNode();
        Node<T>* getNode(const T&, Node<T>*);
};

template<class T>
Node<T>::Node()
{
    //default constructor allows to instantiate an object without initializing any variables
    next = NULL;
}

template<class T>
Node<T>::Node(const T& item) //secondary constuctor initializing a data value when passed through
{
    data = item;
    next = NULL;
}

template<class T>
Node<T>::Node(const T& item, Node<T>* nextptr) //tertiary constructor that initializes both the data value and the pointer when passed
{
    data = item;
    next = nextptr;
}

template<class T>
Node<T>::~Node() //destructor
{
    free(next);
}

template<class T>
T Node<T>::getData() //getter for data
{
    return data;
}

template<class T>
void Node<T>::setData(T item) //setter for data
{
    data = item;
}

template<class T>
Node<T>* Node<T>::getNext() //getter for next pointer
{
    return next;
}

template<class T>
void Node<T>::setNext(Node<T>* nextptr) //setter for next pointer
{
    if (nextptr == NULL) {next = NULL;}
    else {next = nextptr;}
}

template<class T>
Node<T>* Node<T>::copyNode() //copies the acted on node and returns the copy
{
    Node<T>* newNode = new Node<T>;
    newNode->setData(data);
    newNode->setNext(next);
    return newNode;
}

template<class T>
Node<T>* Node<T>::getNode(const T& item, Node<T>* nextptr) //returns a node with the data value and the pointer
{
    Node<T>* newNode = new Node<T>(item,nextptr);
    return newNode;
}









/*
The below class is a full Linked List interface allowing the user to initialize, destruct and command a Linked List of any size. The framework is a Node class.
*/





template<class T>
class LinkedList
{
    private:
        Node<T>* head;
        Node<T>* current;
        int sizeOfList;
    public:
        LinkedList(); //default constructor
        virtual ~LinkedList(); //destructor
        void addToFront(T data); //create a node containing T data and add it to the front of the list
        void addToEnd(T data); //create a node containing T data and add it to eh end of the list
        bool addAtIndexBefore(T data, int index);  //create a node containing T data and add it to the list at index, return boolean for success or failure
        bool addAtIndexAfter(T data, int index);
        void nextNode(); // Move the current pointer to the next node, wraps to front if it navigates past the end
        void insertAfterCurrent(T data); //Create a node containing T data and insert it after wherever the current pointer is pointing
        int removeCurrent(); //Delete the current item and return its contents
        int removeAtIndex(int index); //delete the index # node in the list and return its contents
        int removeFromFront(); //Delete first item and return its contents
        int removeFromEnd(); //Delete last item and return its contents
        void removeFirst(T data); //find first instance of T data and remove it
        void removeAll(T data); //find each instance of T data and remove it
        bool elementExists(T data); //Returns a T/F if element exists in list
        Node<T>* findElement(T data); //Look for data in the list, return a pointer to its node
        int indexOf(T data); //returns an index of the item in the list (zero-based)
        T retrieveFront(); //returns the data contained in the first node, does not delete it
        T retrieveEnd(); //returns the data contained in the last node, does not delete it
        T retrieve(int index); //returns the data contained in node # index, does not delete it, returns null if index is out of bounds or data does not exist
        void toArray(); //Create an array from the contents of the list and return it
        void emptyList(); //Empty out the list, delete everything
        void length(); //How many elements are in the list
        int getSize(); //getter for size
};


template<class T>
LinkedList<T>::LinkedList() //constructor, initializes the private variables
{
    head = NULL;
    current = NULL;
    sizeOfList = 0;
}


template<class T>
LinkedList<T>::~LinkedList() //destructor calls the emptyList function to remove all elements of the list
{
    emptyList();
}

template<class T>
void LinkedList<T>::emptyList() //uses a head-to-tail method to free and clear the entire list
{
    Node<T>* temp = head;
    Node<T>* next;
    while(temp != NULL)
    {
        next = temp->next;
        free(temp);
        temp = next;
    }
    head = NULL;
    current = NULL;
}


template<class T>
void LinkedList<T>::addToFront(T data) //adds data to the Front of the list under a series of conditions
{
    Node<T>* newNode = new Node<T>(data);

    if (head == NULL) //if the list is empty
    {
        head = newNode;
    }
    else {
        Node<T>* temp = new Node<T>();
        temp->data = data;
        temp->next = head;
        head = temp;
    }
}

template<class T>
void LinkedList<T>::addToEnd(T data) //adds data to the End of the list or creates a new list if empty
{
    Node<T>* newNode = new Node<T>(data);

    if (head == NULL)
    {
        head = newNode;
    }
    else {
        Node<T>* temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = NULL;
    }
}


template<class T>
bool LinkedList<T>::addAtIndexBefore(T data, int index) //assuming the first element of the linked list is located at an index of 0
{
    length();
    if (index == 0)
        {
            addToFront(data);
            return true;
        }
    /*else if (index > sizeOfList) {return false;}
    else if (index == sizeOfList)
        {
            addToEnd(data);
            return true;
        }*/
    else {
        Node<T>* newNode = new Node<T>(data);
        Node<T>* temp = head;
        for (int i = 0; i < index-1; i++)
        {
                temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        return true;
    }
}


template<class T>
bool LinkedList<T>::addAtIndexAfter(T data, int index) //assuming the first element of the linked list is located at an index of 0
{
    length();
    if (index == 0)
    {
        addToFront(data);
        return true;
    }
    /*else if (index > sizeOfList) {return false;}
    else if (index == sizeOfList)
        {
            addToEnd(data);
            return true;
        }*/
    else {
        Node<T>* newNode = new Node<T>(data);
        Node<T>* temp = head;
        for (int i = 0; i <= index-1; i++)
        {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        return true;
    }
}


template<class T>
void LinkedList<T>::nextNode() //moves the Current pointer to the next node in the list under a series of conditions
{
    if (current == NULL)
    {
        current = head;
    }
    else if (current->next == NULL)
    {
        current = head;
    }
    else
    {
        current = current->next;
    }
}


template<class T>
void LinkedList<T>::insertAfterCurrent(T data) //inserts a Node after the current pointer
{
    if (current->next == NULL) {addToEnd(data);}
    else {
    Node<T>* newNode = new Node<T>(data);
    newNode->next = current->next;
    current->next = newNode;
    }

}

template<class T>
int LinkedList<T>::removeCurrent() //removes the Node pointed at by Current under a series of conditions
{
    int contents;
    Node<T>* temp = head;

    if (current == head) {
        contents = removeFromFront();
        current = head;
        return contents;
    }

    else if (current->next == NULL)
    {
        contents = removeFromEnd();
        while (temp->next != NULL) {
            temp = temp->next;
        }
        current = temp;
        return contents;
    }
    else {

    while (temp->next != current)
    {
        temp = temp->next;
    }

    temp->next = current->next;
    contents = current->getData();
    free(current);
    current = temp; //updates current back to the exact location it was pointing at previously
    return contents;
    }
}


template<class T>
int LinkedList<T>::removeAtIndex(int index) //removes the Node at a certain index, zero-based; returns the contents
{
    int contents;

        Node<T>* temp = head;
        Node<T>* hold = new Node<T>();
        for (int i = 0; i < index-1; i++)
        {
                temp = temp->next;
        }
        hold = temp->next;
        temp->next = temp->next->next;
        contents = temp->next->getData();
        free(hold);
        return contents;
}

template<class T>
int LinkedList<T>::removeFromFront() //removes the first Node and resets the head, then returns hte contents
{
        int contents;

        Node<T>* temp;
        temp = head;
        head = head->next;
        contents = temp->getData();
        free(temp);
        return contents;
}


template<class T>
int LinkedList<T>::removeFromEnd() //removes the last Node, returns the contents
{
    int contents;
    Node<T>* temp = new Node<T>();
    Node<T>* hold;
    temp = head;

    while (temp->next != NULL) {
        hold = temp;
        temp = temp->next;
    }

    contents = temp->getData();
    free(temp);
    hold->next = NULL;
    return contents;
}


template<class T>
void LinkedList<T>::removeFirst(T data) //removes the first instance of a certain data
{
    Node<T>* temp = head;
    Node<T>* hold = new Node<T>();

    while (temp->next->getData() != data)
    {
        temp = temp->next;
    }

    hold = temp->next;
    temp->next = temp->next->next;
    free(hold);
}


template<class T>
bool LinkedList<T>::elementExists(T data) //returns true or false based on whether a certain data element exists in the list
{
    Node<T>* temp = head;
    while (temp != NULL)
    {
        if (temp->getData() == data)
        {
            return true;
            break;
        }
        temp = temp->next;
    }
    return false;
}


template<class T>
void LinkedList<T>::removeAll(T data) //removes all instances of a certain T data passed to it
{

    Node<T>* temp = head;
    Node<T>* hold;

    while (temp != NULL && temp->data == data)
    {
        head = temp->next;
        free(temp);
        temp = head;
    }
    while (temp != NULL) {
        while (temp != NULL && temp->data != data)
        {
            hold = temp;
            temp = temp->next;
        }
        if (temp == NULL) return;
        hold->next = temp->next;
        free(temp);
        temp=hold->next;
    }
}


template<class T>
Node<T>* LinkedList<T>::findElement(T data) //finds the first instance of T data and returns the Node it is at
{
    Node<T>* temp = head;
    while (temp->next->getData() != data && temp->next != NULL)
    {
        temp = temp->next;
    }
    return temp->next;
}


template<class T>
int LinkedList<T>::indexOf(T data) //returns the index of the first instance of T data
{
    int index = 0;
    Node<T>* temp = head;
    while (temp->getData() != data)
    {
        if (temp->next == NULL) {return 0;}

        temp = temp->next;
        index=index+1;

    }
    return index;
}


template<class T>
T LinkedList<T>::retrieveFront() //retrieves the first Node's data and returns it
{
    return head->getData();
}

template<class T>
T LinkedList<T>::retrieveEnd() //retrives the last Node's data and returns it
{
    Node<T>* temp = head;

    while(temp->next != NULL)
    {
        temp = temp->next;
    }

    return temp->getData();
}


template<class T>
T LinkedList<T>::retrieve(int index) //retrieves the data of the Node at the index passed and returns it
{
    length();
    if (index > sizeOfList)
    {
        return NULL;
    }
    else
    {
        Node<T>* temp = head;
        for (int i = 0; i < index-1; i++)
        {
            temp = temp->next;
        }
        return temp->next->getData();
    }
}

template<class T>
void LinkedList<T>::toArray() //prints an Array of the list to console
{
    length();
    T* LinkedListArray = new T[sizeOfList];
    Node<T>* temp = head;

    cout << "[";

    for (int i = 0; temp != NULL && i < sizeOfList; i++)
    {
        LinkedListArray[i] = temp->getData();
        temp = temp->next;
        cout << LinkedListArray[i] << ", ";
    }
    cout << "]" << endl;
}

template<class T>
int LinkedList<T>::getSize() //getter for sizeOfList
{
    return sizeOfList;
}


template<class T>
void LinkedList<T>::length() //calculates the sizeOfList
{
    if (head == NULL) {sizeOfList = 0;}
    sizeOfList = 0;
    Node<T>* temp = head;
    while (temp != NULL)
    {
        sizeOfList++;
        temp = temp->next;

    }
}








void Josepheus(int persons, int nth_person) //function call for the Josepheus problem algorithm
{
    if (persons == 0) {return;} //if the number of people is 0, then it exits the function

    LinkedList<int>* Link = new LinkedList<int>(); //creates a LinkedList object

    for (int i = 1; i <= persons; i++) //fills the list least to greatest with the amount of people
    {
        Link->addToEnd(i);
    }
    Link->toArray(); //prints an array of the list

    cout << endl << endl << endl;

    //move nth nodes
    //eliminate person
    //repeat until only one remains

    int temp;
    while (Link->getSize() != 1)
    {

        for (int j = 0; j <= nth_person; j++) //this method is the skip then eliminate. The Node eliminated is the node after the specified nth person
        {
            Link->nextNode();
        }

        temp = Link->removeCurrent();
        Link->length();
        Link->toArray();
    }

    Link->~LinkedList(); //empty's the list
}












int main(int argc, char *argv[])
{
    char command;
    int persons;
    int nthelement;
    cout << "The number of people that may be in the circle can be any number from one to one hundred." << endl;
    cout << "Every Nth person that is killed can be any number from one to twenty." << endl;
    cout << "The person that is killed is done by skipping N-elements and then removing the next person." << endl;
    while (true)
    {
        if (command == 'q') {break;} //reads previous switch-case command and exists entire statement
        cout << endl << endl;
        cout << "Press 'j' for Josepheus Problem algorithm." << endl;
        cout << "Press 'q' to quit." << endl;
        cin >> command; //takes input from the user until reads a valid command
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(256,'\n');
                    cin >> command;
                }


        switch(command) //switch cases for both commands
        {
            case 'q': //exits switch cases
                break;

            case 'j':

                cout << endl << "total people: ";
                cin >> persons; //reads input from the user until number is input
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(256,'\n');
                    cin >> persons;
                }
                cout << endl;

                cout << "nth element to remove: ";
                cin >> nthelement; //reads until number is input
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(256,'\n');
                    cin >> nthelement;
                }
                cout << endl;
                if (persons > 100 || persons < 0) {break;} //verifies the numbers and exits switch cases if an invalid number is input
                if (nthelement > 20 || nthelement < 1) {break;}
                Josepheus(persons, nthelement); //calls the Josepheus algorithm to create a LinkedList object and perform the necessary functions
        }
    }
    system("PAUSE");
    return EXIT_SUCCESS;
}
