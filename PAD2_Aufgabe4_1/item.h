#ifndef ITEM_H
#define ITEM_H
#include <iostream>

using namespace std;

template <class T>
class Item
{
private:
    T m_information;
    Item* m_prevElement{nullptr};
    Item* m_nextElement{nullptr};   //If there is no next element = nullptr
public:
    Item(){ };
    Item(T value) : m_information(value) { };
    void print() const{
        cout << "Value of item: " << m_information << '\n'
             << "Next element: " << m_nextElement->m_information << '\n';
    };



    template<class listeT>
    friend class Liste;
    friend bool operator==(Item<T> a, Item<T> b);
    friend bool operator<(Item<T> a, Item<T> b);
    friend bool operator>(Item<T> a, Item<T> b);
    friend bool operator<=(Item<T> a, Item<T> b);
    friend bool operator>=(Item<T> a, Item<T> b);           //friend template declaration don't work???
    T information() const{
        return m_information;
    };
};

template<typename T>
bool operator==(Item<T> a, Item<T> b)
{
    return a.m_information == b.m_information;
}

template<typename T>
bool operator<(Item<T> a, Item<T> b)
{
    return a.m_information < b.m_information;
}

template<typename T>
bool operator>(Item<T> a, Item<T> b)
{
    return a.m_information > b.m_information;
}

template<typename T>
bool operator<=(Item<T> a, Item<T> b)
{
    return a.m_information <= b.m_information;
}

template<typename T>
bool operator>=(Item<T> a, Item<T> b)
{
    return a.m_information >= b.m_information;
}



#endif // ITEM_H
