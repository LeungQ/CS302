/*
Name: Queenie Leung, NSHE 1007386899, CS 302 1004, Ast 1
Description: Create a connect four game with
             R = Red and B = Blue
Input: User 1 input then User 2 input and etc
Output: Program outputs and stacks a visual of
        connect
*/

#include <iostream>

template <typename T>
class LL
{
    //contents of each node
    struct node
    {
        T data;
        node* prev;
        node* next;
    };
    //iterator class to allow access of each node in main
public:
    class Iterator
    {
    public:
        friend class LL;
        Iterator();
        Iterator(node*);
        T operator*() const;
        Iterator operator++(int);
        Iterator operator++();
        Iterator operator--(int);
        Iterator operator--();
        bool operator==(const Iterator&) const;
        bool operator!=(const Iterator&) const;

    private:
        node* current;
    };

    LL();
    LL(const LL<T>&);
    const LL<T>& operator=(const LL<T>&);
    ~LL();
    void headInsert(const T&);
    void tailInsert(const T&);
    void headRemove();
    bool isEmpty() const;
    std::size_t size() const;
    Iterator begin() const;
    Iterator end() const;

private:
    node* portal;
};

//iterator class implementation
template <typename T>
LL<T>::Iterator::Iterator()
{
    //default constructor that sets current w/ NULL or Nullptr
    current = NULL;
}

template <typename T>
LL<T>::Iterator::Iterator(node* ptr)
{
    //constructor that sets current = ptr
    current = ptr;
}

template <typename T>
T LL<T>::Iterator::operator*() const
{
    //overloads the dereference operator, just returns
    //data field of the node the Iterator obj is pointing to
    return current->data;
}

template <typename T>
typename LL<T>::Iterator LL<T>::Iterator::operator++(int)
{
    //postfix ++ operator that moves the iterator object one node
    //over to the right (sets -> this current = this current->next)
    //and returns an iterator object that has its current set to 
    //this->current 

    
    current = current->next;
    return *this;
  
}

template <typename T>
typename LL<T>::Iterator LL<T>::Iterator::operator++()
{
    //prefix ++ operator that moves the iterator one node
    //over to the right (sets this -> current = this -> current-> next)
    //and then returns an iterator object whose pointed to the prev node,
    //returns an iterator whose current is set to this -> current-> prev

    current = current->next;
    return *this;

}

template <typename T>
typename LL<T>::Iterator LL<T>::Iterator::operator--(int)
{
    /*postfix –- operator that moves
    the Iterator object one node over to the left (sets this
    ->current = this->current->prev) and returns an Iterator
    object that has its current set to this->current
    */
   
    current = current->prev;
    return *this;
  
}

template <typename T>
typename LL<T>::Iterator LL<T>::Iterator::operator--()
{
    /* prefix -– operator that moves the Iterator object one
    node over to the left (sets this->current = this
    ->current->prev) and then returns an iterator object
    whose current pointed to the previous node, returns an
    iterator whose current is set to this->current->next
    */
    current = current->prev;
    return *this;
}

template <typename T>
bool LL<T>::Iterator::operator==(const Iterator& rhs) const
{
    /*comparison operator, compares if the *this Iterator
    and the rhs Iterator point to the same node, if they do
    return true else return false
    */
    if (this->current == rhs.current)
    {
        return true;
    }
    return false;

}

template <typename T>
bool LL<T>::Iterator::operator!=(const Iterator& rhs) const
{
    /* comparison operator, compares if the *this Iterator and
    the rhs Iterator point to a different node, if they point
    to different nodes return true else return false
    */

    if (this->current != rhs.current)
    {
        return true;
    }
    return false;
}

//Linked list class implementation
template <typename T>
LL<T>::LL()
{
    //default constructor, allocates a node to portal and 
    //sets portal->prev = portal->next = portal;
    portal = new node();
    portal->next = portal;
    portal->prev = portal;

    // portal prev points to portal and portal next points to portal
    //thus portal points to itself
   // portal->prev = portal->next = portal;
}

//copy constructor
/*
    deep copy constructor, deep copies the copy object into the *this
    object
*/
template <typename T>
LL<T>::LL(const LL<T>& copy)
{   //creates the portal dummy node and sets it
    //pointing to itself
    portal = new node();
    portal->next = portal; 
    portal->prev = portal;

    //loop - iterator "it" is equal to begin() [element 0]
    //and it is not equal to end () [element 6] 
    //increment iterator "it"
    for (auto it = copy.begin(); it != copy.end(); it++)
    {
        tailInsert(*it); //deref to get value of iterator "it"
                        //calling tailInsert function
    } 
}

/*
deep copy assignment operator, deep copies
the rhs object into the *this object, make sure you deallocate 
the *this object first before performing the deep copy, also 
check for self assignment, then return *this at the end

*/
template <typename T>
const LL<T>& LL<T>::operator=(const LL<T>& rhs)
{
   // node* temp = portal->next;
    if (this != &rhs)//self assignment
    {
        // while link list not empty call head remove
        while (isEmpty()==false)
        {
            headRemove(); //call head remove function  
        }
     
        //loop while iterator "it" is set to 
        //rhs.begin() until it not equal rhs.end() 
        //increment "it"
        for (auto it = rhs.begin(); it != rhs.end(); it++)
        {
            tailInsert(*it); //inserts the deference
                            //value of iterator which
                            //is B or R
        } 

    }
    //portal = rhs.portal // shallow copy //DEBUG
    //returns the value of the linked list iterator
    return *this;
}

//destructor
/*
    removes all the nodes including portal
    this checks if the linked list is empty
    if it is not empty it keeps calling the function
    remove head and after the list is empty
    to delete portal
*/
template <typename T>
LL<T>::~LL()
{ 
    while (isEmpty() == false) //check to see if list is not empty
    {
        headRemove(); //calls headRemove function
    }
    delete portal; //after exit while loop to delete portal linked list
}

//head insert
/*
    inserts a new node to be placed before portal
    as portal is the end dummy node
    resets the pointers so that the node named tmp
    is inserted in this order [tmp] <=> [portal]
    which should be the same for any other additional
    nodes
*/
template <typename T>
void LL<T>::headInsert(const T& item)

{  //portal will be dummy and because of default constructor is existing
    if (portal->next == portal)
    {   //head points at new Node created
        node* tmp = new node;
        tmp->data = item;   //item within data

        portal->next = tmp; //sets portal next to tmp
        portal->prev = tmp; //sets portal prev to tmp

        tmp->next = portal; //sets tmp next to portal
        tmp->prev = portal; //sets tmp prev to portal

    }

    //else if the list is not empty you want to 
    //add new node to the front of the linked list
    //and nodes data field must contain the contents
    //of the item parameter 

    else
    {
        //create a new temporary node
        node* tmp;
        tmp = new node;

        //tmp data now contains item param
        tmp->data = item;
        tmp->next = portal->next; //sets portal next to tmp and tmp points next
        portal->next->prev = tmp; //sets tmp to portal pointing to next pointing to prev
        tmp->prev = portal; //sets portal to tmp prev
        portal->next = tmp; //sets tmp to portal next
    }

}

//tail insert
template <typename T>
void LL<T>::tailInsert(const T& item)
{
    //portal will be dummy and because of default constructor is existing
    if (portal->next == portal)
    {   //head points at new Node created
        headInsert(item);
    }

    //else if the list is not empty you want to 
    //add new node to the front of the linked list
    //and nodes data field must contain the contents
    //of the item parameter 

    else
    {
        //create a new temporary node
        node* tmp;
        tmp = new node;
        //tmp data now contains item param

        tmp->data = item;
        tmp->next = portal;     //[1]<=>[2]<=>          [portal] 
                                    //insert// [tmp]^<=>[portal]
        tmp->prev = portal->prev;
        portal->prev->next = tmp;
        portal->prev = tmp;
    }
}

template <typename T>
void LL<T>::headRemove()
{
    if (isEmpty() == true) { return; }
    else
    {
        node* tmp1 = portal->next; //create temp ptr to store head
        portal->next = tmp1->next; //point head ptr to point to next node on list
        tmp1->next->prev = tmp1->next; // reallocate next ptr of
        // tail to point to new head
        delete tmp1;
    }
}

/*
    checks if the link list is empty
    if portal next is just portal, it is empty
    as portal is the default "dummy" node
    returns true if the above statement is true
    else it returns false as there are more nodes 
    thus not empty
*/
template <typename T>
bool LL<T>::isEmpty() const
{
    if (portal->next == portal) //if it is equal to portal
    {
        return true; //return true
    }
    return false; //else it is false and not equal to portal
}

/*
    This checks the size of the linked list
    using a int (size_t) counter 
    set to 0 then creating a pointer curr1 
    set it to portal next.

    while the temp pointer curr1 is not equal
    to portal it will traverse to the next node
    and increment count by 1

    while loop statement breaks when curr1 is
    equal to portal to return the int count

*/
template <typename T> 
std::size_t LL<T>::size() const
{
    size_t count = 0;
    node* curr1 = portal->next;
    while (curr1 != portal)
    {
        curr1 = curr1->next; //curr was portal next 
                             //now curr is portal->next->next
        count++; //counter increment
    }

    return count; //returns the total number of linked list nodes
}

template <typename T>
typename LL<T>::Iterator LL<T>::begin() const
{
    //returns an Iterator object whose current field
    //contains portal->next(address of head node)
    return Iterator(portal->next);
}

template <typename T>
typename LL<T>::Iterator LL<T>::end() const
{
    //returns an Iterator object whose current field
    //contains portal(the address of the dummy node)
    return Iterator(portal);
}
