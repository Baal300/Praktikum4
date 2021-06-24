#ifndef LISTE_H
#define LISTE_H
#include "item.h"
#include "iostream"

using namespace std;

template <class T>
class Liste
{
private:
    Item<T>* m_firstElement;    //Head / Beginning of list
    Item<T>* m_currentElement;  //Position pointer
    Item<T>* m_lastElement;     //End pointer
public:
    Liste(){    //Creates an empty list
        m_firstElement = nullptr;
        m_currentElement = nullptr;
        m_lastElement = nullptr;
    };

    Item<T>* get() const
    {
        if(m_currentElement != nullptr){
            return m_currentElement;
        } else {
            cerr << "Element doesn't exist.\n";
            return nullptr;
        }
    };

    bool empty()
    {
        if (m_firstElement == nullptr){
            return true;
        }
        else{
            return false;
        }
    };

    void print()
    {
        //Only if the list is not empty print something
        if(m_firstElement != nullptr) {  //using empty() here doesn't work for sume reason
            cout << "******LIST******\n";

            Item<T>* printElement;
            printElement = m_firstElement; //Start at the beginning
            int i{1};

            while(printElement != nullptr){
                cout << "Node " << i << ": " << printElement->m_information;
                if (printElement->m_prevElement != nullptr)
                {
                    cout << " Previous element: " << printElement->m_prevElement->m_information;
                }
                if (printElement->m_nextElement != nullptr)
                {
                    cout << " Next element: " << printElement->m_nextElement->m_information;
                }
                cout << '\n';
                printElement = printElement->m_nextElement;     //Set next node to be printed
                i++;
            }
        }
        else{
            cout << "List is empty!\n";
        }

    };

    bool end()
    {
        if(!empty())
        {
            return m_currentElement == m_lastElement;
        } else {
            cerr << "Can't determine end if list is empty!\n";
        }
    }

    void display()
    {
        Item<T>* temp = new Item<T>;
        temp=m_firstElement;
        while(temp!=NULL)
        {
          cout<<temp->m_information<<"\t";
          temp=temp->m_nextElement;
        }
    }

    //Insert and sort the list
    void sortIns(T value)
    {
        Item<T>* newItem = new Item<T>; //Creates new item object
        newItem->m_information = value;
        newItem->m_nextElement = nullptr;


        if(m_firstElement == nullptr) //If list is still empty
        {
            newItem->m_prevElement = nullptr;
            m_firstElement = newItem;
            m_currentElement = newItem;
            m_lastElement = newItem;
        }
        else
        {
            //Sort list
            m_currentElement = m_firstElement;
            while(true)
            {
                if(newItem->m_information < m_currentElement->m_information)
                {
                    newItem->m_prevElement = m_currentElement->m_prevElement;
                    newItem->m_nextElement = m_currentElement;
                    m_currentElement->m_prevElement = newItem;
                    m_currentElement = newItem;       //Insert our new element before the compared element if it's smaller

                    if(m_currentElement->m_prevElement != nullptr){    //If there was a previous element to our compared element it gets the new item as next element
                        m_currentElement->m_prevElement->m_nextElement = m_currentElement;
                    }
                    break;
                }
                if(end()){  //Element is inserted at the end if it's greater than all other elements
                    m_currentElement->m_nextElement = newItem;  //We want to add a node next to our position pointer
                    newItem->m_prevElement = m_currentElement; //Position pointer becomes previous node of new node
                    m_currentElement = newItem; //The new item/node is our position pointer now
                    break;
                }
                m_currentElement = m_currentElement->m_nextElement;  //Check next element
            }

            if(newItem->m_prevElement == nullptr){  //In case the new element got inserted at the beginning
                m_firstElement = newItem;
            }

            if(m_currentElement->m_nextElement == nullptr){ //If the next element of our new element is null, it is our last element
                m_lastElement = m_currentElement;
            }
        }
    }


    //Insert without sorting
    void ins(T value)
    {
        Item<T>* newItem = new Item<T>; //Creates new item object
        newItem->m_information = value;
        newItem->m_nextElement = nullptr;


        if(m_firstElement == nullptr) //If list is still empty
        {
            newItem->m_prevElement = nullptr;
            m_firstElement = newItem;
            m_currentElement = newItem;
            m_lastElement = newItem;
        }
        else
        {
            m_currentElement->m_nextElement = newItem;  //We want to add a node next to our position pointer
            newItem->m_prevElement = m_currentElement; //Position pointer becomes previous node of new node
            m_currentElement = m_currentElement->m_nextElement; //The new item/node is our position pointer now

            if(m_currentElement->m_nextElement == nullptr){ //If the next element of our new element is null, it is our last element
                m_lastElement = m_currentElement;
            }
        }
    }


    void adv()
    {
        if(!empty()){
            if(m_currentElement->m_nextElement != nullptr){
            //    cout << "***ADVANCE BY ONE POSITION***\n";
                m_currentElement = m_currentElement->m_nextElement;     //Set position pointer to next element
            }
            else{
                cerr << "Couldn't advance further. Position pointer is already at end of list.\n";
            }
        } else {
            cerr << "Can't advance on an empty list!\n";
        }
    };

    void reset()
    {
        m_currentElement = m_firstElement;
    }

    void del()
    {
        try {
            if(m_firstElement == nullptr){
                throw runtime_error("List is already empty!");      //Don't do anything if list is empty
            }
            else if (m_firstElement == m_currentElement && m_currentElement->m_nextElement == nullptr){   //If there is only one element
                m_firstElement = nullptr;       //To avoid dangling pointer first element is nullptr
                m_lastElement = nullptr;
                delete m_currentElement;        //previous and next should be in this case nullptr as well already
            }
            else if(m_currentElement == m_firstElement){       //If position pointer points to first element/beginning and there are elements after that
                m_firstElement = m_currentElement->m_nextElement;      //Set first element pointer to next element before it gets deleted
                delete m_currentElement;
                m_currentElement = m_firstElement;
                m_firstElement->m_prevElement = nullptr; // First element's prevPointer should be null
            }
            else{
                Item<T>* beforeElement = m_currentElement->m_prevElement;     //New pointer to find out node before position pointer
                beforeElement->m_nextElement = m_currentElement->m_nextElement; //The next element for the node before the deleted element is now set
                delete m_currentElement;
                m_currentElement = beforeElement; //Our position pointer points to the node before the deleted node now
            }
        }  catch (runtime_error e) {
           cerr << e.what() << '\n';
        }
    }

    void menu()
    {
        do{
            int menuSelection;

            //Try and Catch, in case user enters an invalid number
            do{
                try
                {
                    cout << "*************MENU*************\n"
                         << "Please select an option from the menu by entering one of the following numbers\n"
                         << "(1) Get current element\n"
                         << "(2) Empty?\n"
                         << "(3) End?\n"
                         << "(4) Advance one node\n"
                         << "(5) Put position pointer at start\n"
                         << "(6) Insert a node at position pointer\n"
                         << "(7) Delete a node at position pointer\n"
                         << "(8) Print list\n"
                         << "(9) Quit\n"
                         << "\nMenu selection: ";

                    cin >> menuSelection;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //In case we have extraneous inputs

                    if (cin.fail())
                    {
                        cin.clear(); //clears error flags
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //removes bad input from stream
                        throw invalid_argument("Enter only valid numbers please!");
                    }
                    else if (menuSelection < 1 || menuSelection > 9)
                    {
                        throw invalid_argument("Please enter a valid number from 1-8!");
                    }

                }
                catch (invalid_argument &invalidNumber)
                {
                    cerr << invalidNumber.what() << '\n';
                    continue;
                }

                break;
            }while(true);

            switch (menuSelection) {
            case 1:
            {
                Item<T>* getElement {get()};
                if(getElement != nullptr){
                    cout << "The current element is: " << getElement->m_information  << '\n';
                }
                break;
            }
            case 2:
                if(empty() == true){
                    cout << "The list is currently empty.\n";
                }
                else{
                    cout << "The list is not empty.\n";
                }
                break;
            case 3:
                if(end()){
                    cout << "The position pointer points to the end of the list.\n";
                }
                else{
                    cout << "The position pointer doesn't point to the end of the list.\n";
                }
                break;
            case 4:
                adv();
                break;
            case 5:
                cout << "Position pointer is set to beginning of list.\n";
                reset();
                break;
            case 6:
                T value;
                cout << "Enter a value to insert: ";
                cin >> value;
                ins(value);
                break;
            case 7:
                del();
                cout << "***NODE DELETED***\n";
                break;
            case 8:
                print();
                break;
            case 9:
                break;
            default:
                cerr << "ERROR\n";
                break;
            }

            //If user enters 6 loop is broken and user quits menu, otherwise menu opens again
            if(menuSelection == 9)
            {
                break;
            }

        }while(true);
    }

    //Merge two lists into a new list (with deep copies)
    Liste merge(Liste<T> &list_a, Liste<T> &list_b)
    {
        Liste<T> mergedList;

        list_a.reset();         //Position pointer should point at first element for this
        //Insert first list into mergedList
        if(list_a.m_firstElement != nullptr)
        {
            mergedList.sortIns(list_a.m_currentElement->information());     //First element gets inserted
            if(list_a.m_currentElement->m_nextElement != nullptr){
                do
                {
                    list_a.adv();
                    mergedList.sortIns(list_a.m_currentElement->information());
                }while(list_a.m_currentElement->m_nextElement != nullptr);    //We're done with inserting when position pointer points here to last element
            }

            list_a.reset();     //For safety list gets reset
        }

        list_b.reset();         //Position pointer should point at first element for this
        //Insert second list into mergedList
        if(list_b.m_firstElement != nullptr)
        {
            mergedList.sortIns(list_b.m_currentElement->information());

            if(list_b.m_currentElement->m_nextElement != nullptr){
                do
                {
                    list_b.adv();
                    mergedList.sortIns(list_b.m_currentElement->information());
                }while(list_b.m_currentElement->m_nextElement != nullptr);    //We're done with inserting when position pointer points here to last element
            }

            list_b.reset();     //For safety list gets reset
        }

        cout << "****Lists merged****\n";
        mergedList.print();
        cout << "*********************\n";

        return mergedList;
    }



    int length()
    {
        int listLength{0};     //Need to inquire length of list first

        //Find out length
        reset();
        if( !empty() && m_currentElement->m_nextElement != nullptr)
        {
            listLength++;
            do{
                adv();
                listLength++;
            }while (m_currentElement != m_lastElement);
        }
        else
        {
            listLength = 1;
        }
        reset();

        //cout << "Length: " << listLength << '\n';

        return listLength;
    }

    void splitLists(Liste<T> &source, Liste<T> &leftHalf, Liste<T> &rightHalf)
    {
        Item<T>* fast;
        Item<T>* slow;
        slow = source.m_firstElement;
        fast = source.m_firstElement->m_nextElement;

        rightHalf.m_lastElement = source.m_lastElement;

        //fast pointer is double as fast as slow pointer and should reach the end of list when slow is before the middle
        while (fast != nullptr) {
            fast = fast->m_nextElement;
            if (fast != nullptr) {
                slow = slow->m_nextElement;
                fast = fast->m_nextElement;
            }
        }

        source.m_lastElement = slow;
        leftHalf = source;
        rightHalf.m_firstElement = slow->m_nextElement;
        slow->m_nextElement = nullptr;  //End of left half

        //Need to reassign prev pointer if it is split
        leftHalf.m_firstElement->m_prevElement = nullptr;
        rightHalf.m_firstElement->m_prevElement = nullptr;

        cout << "*****LISTS SPLIT*****\n";
        leftHalf.print();
        rightHalf.print();
    }

    void mergeSort()
    {
        cout << "*****CURRENT LIST CALLING MERGESORT*****\n";
        print();
        Item<T>* head = m_firstElement;
        Liste<T> a;
        Liste<T> b;

        //If length of list is 1 or 0 return
        if ((head == NULL) || (head->m_nextElement == NULL)) {
            return;
        }

        /* Split head into 'a' and 'b' sublists */
        splitLists(*this, a, b);

        /* Recursively sort the sublists */
        a.m_firstElement = m_firstElement;
        a.m_lastElement = m_lastElement;
        a.mergeSort();
        b.mergeSort();

        /* answer = merge the two sorted lists together */
        *this = merge(a, b);
    }


    void printTree()
    {
        int treeSize{ length() };

        if (!empty())
        {
            reset();
            for (int i{0}; i < treeSize; i++){
                switch (i)
                {
                    case 0:
                        cout << "             ___________" << m_currentElement->m_information <<"___________\n";
                        break;
                    case 1:
                        cout << "            /                       \\\n"
                             << "       ____" << m_currentElement->m_information << "____";
                        break;
                    case 2:
                        cout << "                 ____" << m_currentElement->m_information << "____\n";
                        break;
                    case 3:
                        cout << "      /         \\               /         \\\n"
                             << "    _" << m_currentElement->m_information << "_ ";
                        break;
                    case 4:
                        cout << "        _" << m_currentElement->m_information << "_";
                        break;
                    case 5:
                        cout << "           _" << m_currentElement->m_information << "_";
                        break;
                    case 6:
                        cout << "         _" << m_currentElement->m_information << "_\n";
                        break;
                    case 7:
                        cout << "   /   \\       /   \\         /   \\       /   \\\n";
                        cout << "  " << m_currentElement->m_information;
                        break;
                    case 8:
                        cout << "     " << m_currentElement->m_information;
                        break;
                    case 9:
                        cout << "     " << m_currentElement->m_information;
                        break;
                    case 10:
                        cout << "     " << m_currentElement->m_information;
                        break;
                    case 11:
                        cout << "       " << m_currentElement->m_information;
                        break;
                    case 12:
                        cout << "     " << m_currentElement->m_information;
                        break;
                    case 13:
                        cout << "     " << m_currentElement->m_information << " ";
                        break;
                    case 14:
                        cout << "    " << m_currentElement->m_information << '\n';
                        break;
                    default:
                        cerr << "ERROR\n";
                        break;
                }

                if(m_currentElement->m_nextElement != nullptr)
                {
                    adv();
                }
            }
            cout << '\n';
        }
    }

    Item<T>* getParent(int index)
    {
        cout << "****GETPARENT****\n";
        //Node = root
        if(index == 0)
        {
            cerr << "Node has no parent!\n";
            return nullptr;
        }

        Item<T>* node;
        reset();
        //Find out which node we look at via index
        for(int i{0}; i < index; i++)
        {
            adv();
        }
        node = m_currentElement;


        int parentIndex{(index-1)/2};
        reset();
        //Find out which node is parent
        for(int i{0}; i < parentIndex; i++)
        {
            adv();
        }
        Item<T>* parentNode{m_currentElement};

        cout << "Parent element: " << parentNode->m_information << " Index : " << parentIndex << '\n';
        return parentNode;
    }

    Item<T>* getLeftChild(int index)
    {
        cout << "****GETLEFTCHILD****\n";
        Item<T>* node;

        reset();
        //Find out which node we look at via index
        for(int i{0}; i < index; i++)
        {
            adv();
        }
        node = m_currentElement;

        int childIndex{2*index+1};

        int treeSize{ length() };

        //THERE IS NO LEFT CHILD
        if(childIndex > treeSize-1){
            cout << "There is no left child.\n";
            return nullptr;
        }

        reset();
        //Find out which node is left child
        for(int i{0}; i < childIndex; i++)
        {
            adv();
        }

        Item<T>* childNode{m_currentElement};

        cout << "Left child element: " << childNode->m_information << " Index : " << childIndex << '\n';
        return childNode;
    }

    Item<T>* getRightChild(int index)
    {
        cout << "****GETRIGHTCHILD****\n";
        Item<T>* node;

        reset();
        //Find out which node we look at via index
        for(int i{0}; i < index; i++)
        {
            adv();
        }
        node = m_currentElement;

        int childIndex{2*index+2};

        int treeSize{ length() };

        //THERE IS NO right CHILD
        if(childIndex > treeSize-1){
            cout << "There is no right child.\n";
            return nullptr;
        }

        reset();
        //Find out which node is right child
        for(int i{0}; i < childIndex; i++)
        {
            adv();
        }

        Item<T>* childNode{m_currentElement};

        cout << "Right child element: " << childNode->m_information << " Index : " << childIndex << '\n';
        return childNode;
    }

    Item<T>* getNode(int index)
    {
        cout << "*****GETNODE*****\n";
        Item<T>* node;

        reset();
        //Find out which node we look at via index
        for(int i{0}; i < index; i++)
        {
            adv();
        }
        node = m_currentElement;
    }

    void heapSort()
    {
        //n = tree size
        int treeSize{length()};

        //Build heap; n/2 - 1 is index of last node that is not a leave
        for(int i{treeSize/2 - 1}; i >= 0; i--)
        {
            heapify(treeSize, i);
        }

        // One by one extract an element from heap
        for (int i{treeSize - 1}; i > 0; i--) {
            // Swapping first element with last element
            swap(getNode(0), getNode(i));

            // call max heapify on the reduced heap
            heapify(i, 0);
        }

    }

    void heapify(int treeSize, int index)
    {
        int largestIndex {index};    //Root of subtree
        int leftIndex {2*index+1};
        int rightIndex {2*index+2};

        Item<T>* largest{getNode(index)};
        Item<T>* leftChild{getLeftChild(index)};
        Item<T>* rightChild{getRightChild(index)};

        //If left is greater than root
        if ( leftIndex < treeSize && leftChild->m_information > largest->m_information)
        {
            swap(leftChild, largest);
            printTree();
            //Recursively heapify subtree
            heapify(treeSize, leftIndex);
        }

        //If right is greater than root
        if ( rightIndex < treeSize && rightChild->m_information > largest->m_information)
        {
            swap(rightChild, largest);
            printTree();
            //Recursively heapify subtree
            heapify(treeSize, rightIndex);
        }

    }

    void swap(Item<T>* a, Item<T>* b)
    {
        T tmp = a->m_information;
        a->m_information = b->m_information;
        b->m_information = tmp;
    }

    //Dysfunctional methods
    /*
    void mergeSort()
    {
        cout << "*****MERGESORT CALLED*****\n";
        int length = this->length();
        int middle = length/2;

        if(length == 1)
        {
            return;
        }

        if(empty())     //try, throw and catch here
        {

        }

        //Divide the list into two new lists
        Liste<T> lList;
        Liste<T> rList;

        //Insert left half to a new list
        reset();
        for (int i{0}; i < middle; i++)
        {
            lList.ins(m_currentElement->information());
            if(i < middle)
            {
            adv();
            }
        }

        cout << "LEFT HALF\n";
        lList.print();
        cout << '\n';

        //Insert right half to a new list
        for (int i{middle}; i < (length); i++)
        {
            adv();
            rList.ins(m_currentElement->information());
        }

        reset();

        cout << "RIGHT HALF\n";
        rList.print();
        cout << '\n';

        if(!(lList.empty())){
            lList.mergeSort();
        }

        if(!(rList.empty())){
            rList.mergeSort();
        }

        merge(lList, rList);
        //No dividing possible anymore
    }
    */

    /*Item<T>* SortedMerge(Item<T>* a, Item<T>* b)
    {
        Item<T>* result = NULL;

        if (a == NULL)
            return (b);
        else if (b == NULL)
            return (a);

        if (a->data <= b->data) {
            result = a;
            result->next = SortedMerge(a->next, b);
        }
        else {
            result = b;
            result->next = SortedMerge(a, b->next);
        }
        return (result);
    }
    */

    /*~Liste()
    {
        m_currentElement = m_firstElement;
        cout << "Starting to delete list.\n";

        while(m_currentElement != nullptr){ //As long list is not empty the elements get deleted
            delete m_currentElement;    //Debugger stops here
            m_currentElement = m_currentElement->m_nextElement;
        }

        cout << "List was destroyed.\n";
    }*/

};

#endif // LISTE_H
