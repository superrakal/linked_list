#include "LinkedListImpl.hpp"
#include <cstdio>

class LinkedList {
public:
    class Iterator;
    class ConstIterator;

    LinkedList() { list = new LinkedListImpl; }

    LinkedList(const LinkedList &other) {
        list = new LinkedListImpl(*(other.list));
    }

    ~LinkedList() {
        delete list;
    }

    int &front(); 
    const int &front() const;
    int &back();
    const int &back() const;
    
    Iterator begin();
    const Iterator begin() const;
    //const Iterator cbegin() const;
    Iterator end(); 
    const Iterator end() const;
    /*const Iterator cend() const;*/

    bool contains(const int & value) const;
    size_t count(const int & value) const;

    size_t size() const { return list->size(); }
    bool empty() const { return list->size() == 0; }

    Iterator erase(Iterator pos);
    Iterator erase(Iterator begin, Iterator end);
    void clear();
    size_t remove_all(const int & value);
    bool remove_one(const int & value);
    void pop_back();
    void pop_front();

    void push_back(const int & value); 
    void push_front(const int & value); 
    Iterator insert(Iterator before, const int & value);

    bool operator!=(const LinkedList & other) const; 
    bool operator==(const LinkedList & other) const;
    LinkedList operator+(const LinkedList & other) const; 
    LinkedList & operator+=(const LinkedList &other); 
    LinkedList & operator+=(const int & value); 
    LinkedList & operator=(const LinkedList &other);
    LinkedList & operator=(LinkedList &&other);

    class Iterator {
        LinkedListImpl::IteratorImpl *iterImpl;
    public:
        friend class LinkedList;
        Iterator() { iterImpl = new LinkedListImpl::IteratorImpl;  }
        Iterator(const Iterator &other) { iterImpl = new LinkedListImpl::IteratorImpl(*other.iterImpl); }
        ~Iterator() { delete iterImpl; }
        bool operator==(const Iterator &other) { return iterImpl == other.iterImpl; }
        bool operator!=(Iterator &other) const { return iterImpl != other.iterImpl; }
        const Iterator &operator=(const Iterator &other) const {  iterImpl->operator=(*other.iterImpl); return *this; }
        /*Возвращает ссылку на текущий элемент коллекции*/
        int &operator*() const { return iterImpl->operator*(); }
        /*Возвращает указатель на текущий элемент коллекции*/
        LinkedListImpl::Node *operator->() const { return iterImpl->operator->(); }
        Iterator &operator++() { iterImpl->operator++(); return *this; }
        Iterator operator++(int) { iterImpl->operator++(1); return *this; }
        Iterator &operator--() { iterImpl->operator--(); return *this; }
        Iterator operator--(int) { iterImpl->operator--(1); return *this; }
    };

     class ConstIterator {
        LinkedListImpl::ConstIteratorImpl *iterImpl;
     public:
        friend class LinkedList;
        ConstIterator() { iterImpl = new LinkedListImpl::ConstIteratorImpl;  }
        ConstIterator(const ConstIterator &other) { iterImpl = new LinkedListImpl::ConstIteratorImpl(*other.iterImpl); }
        ~ConstIterator() { delete iterImpl; }
        bool operator==(const ConstIterator &other) { return iterImpl == other.iterImpl; }
        bool operator!=(ConstIterator &other) const { return iterImpl != other.iterImpl; }
        const ConstIterator &operator=(const ConstIterator &other) const {  iterImpl->operator=(*other.iterImpl); return *this; }
        /*Возвращает ссылку на текущий элемент коллекции*/
        const int &operator*() const { return iterImpl->operator*(); }
        /*Возвращает указатель на текущий элемент коллекции*/
        const LinkedListImpl::Node *operator->() const { return iterImpl->operator->(); }
        ConstIterator &operator++() { iterImpl->operator++(); return *this; }
        ConstIterator operator++(int) { iterImpl->operator++(1); return *this; }
        ConstIterator &operator--() { iterImpl->operator--(); return *this; }
        ConstIterator operator--(int) { iterImpl->operator--(1); return *this; }
    };
private:
    LinkedListImpl *list;
};