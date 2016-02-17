#include <cstdio>
#include <stdexcept>
#include <assert.h>

class LinkedListImpl {
public:
    struct Node;
    class BaseIteratorImpl;
    class IteratorImpl;
    class ConstIteratorImpl;

	LinkedListImpl() : list_length(0) { head = last = createNode(); }

    LinkedListImpl(const LinkedListImpl &other) {
        head = last = createNode();
        LinkedListImpl::IteratorImpl iter;
        iter = other.begin();

        for (; iter != other.end(); iter++) {
            try {
                push_back(*iter);
            }
            catch (std::bad_alloc &Err) {
                clear();
                throw Err;
            }
        }
	}

	~LinkedListImpl() {
        Node *i = head;
        Node *pTemp = head;
        while (i != nullptr) { 
            pTemp = i;
            if (!(i->next)) {
                delete pTemp;
                break;
            }

            i = i->next;
            delete pTemp;
        }   
	}

	Node *createNode(int _value =0) { return new Node(_value); }
	int &front(); 
	const int &front() const;
	int &back();
	const int &back() const;
	
	IteratorImpl begin();
	const IteratorImpl begin() const;
	//const IteratorImpl cbegin() const;
	IteratorImpl end(); 
	const IteratorImpl end() const;
	/*const IteratorImpl cend() const;*/

	bool contains(const int & value) const;
	size_t count(const int & value) const;

	size_t size() const { return list_length; }
	bool empty() const { return list_length == 0; }

	IteratorImpl erase(IteratorImpl pos);
    IteratorImpl erase(IteratorImpl begin, IteratorImpl end);
	void clear();
	size_t remove_all(const int & value);
	bool remove_one(const int & value);
	void pop_back();
	void pop_front();

	void push_back(const int & value); 
	void push_front(const int & value); 
	IteratorImpl insert(IteratorImpl before, const int & value);

	bool operator!=(const LinkedListImpl & other) const; 
	bool operator==(const LinkedListImpl & other) const;
	LinkedListImpl operator+(const LinkedListImpl & other) const; 
	LinkedListImpl & operator+=(const LinkedListImpl &other); 
	LinkedListImpl & operator+=(const int & value); 
	LinkedListImpl & operator=(const LinkedListImpl &other);
	LinkedListImpl & operator=(LinkedListImpl &&other);

    class BaseIteratorImpl {
    public:
        bool operator==(const BaseIteratorImpl &other) { return pCurrentNode == other.pCurrentNode; }
        bool operator!=(const BaseIteratorImpl &other) { return pCurrentNode != other.pCurrentNode; }
    protected:
        friend class LinkedListImpl;
        Node *pCurrentNode = nullptr;
        void moveStraight();
        void moveBack();
        void equated(const BaseIteratorImpl &other) { pCurrentNode = other.pCurrentNode; }
    private:
        BaseIteratorImpl() : pCurrentNode(nullptr) {}
        BaseIteratorImpl(Node *_pCurrentNode) { pCurrentNode = _pCurrentNode; }
        BaseIteratorImpl(const BaseIteratorImpl &other) { pCurrentNode = other.pCurrentNode; }
    };

    class IteratorImpl: public BaseIteratorImpl {
    public:
        friend class LinkedListImpl;
        IteratorImpl() { pCurrentNode = nullptr;  }
        IteratorImpl(Node *pNode) { pCurrentNode = pNode; }
        IteratorImpl(const IteratorImpl &other) { pCurrentNode = other.pCurrentNode; }
        IteratorImpl &operator=(const IteratorImpl &other) { pCurrentNode = other.pCurrentNode; return *this; }
        /*Возвращает ссылку на текущий элемент коллекции*/
        int &operator*() const { return pCurrentNode->value; }
        /*Возвращает указатель на текущий элемент коллекции*/
        Node *operator->() const { return pCurrentNode; }
        IteratorImpl &operator++() { moveStraight(); return *this; }
        IteratorImpl operator++(int) { IteratorImpl temp(pCurrentNode); moveStraight(); return temp; }
        IteratorImpl &operator--() { moveBack(); return *this; }
        IteratorImpl operator--(int) { IteratorImpl temp(pCurrentNode); moveBack(); return temp; }
    };

    class ConstIteratorImpl: public BaseIteratorImpl {
    public:
        friend class LinkedListImpl;
        ConstIteratorImpl() { pCurrentNode = nullptr; }
        ConstIteratorImpl(Node *pNode) { pCurrentNode = pNode; }
        ConstIteratorImpl(const IteratorImpl &other) { pCurrentNode = other.pCurrentNode; }
        ConstIteratorImpl(const ConstIteratorImpl &other) { pCurrentNode = other.pCurrentNode; }
        ConstIteratorImpl &operator=(const IteratorImpl &other) { pCurrentNode = other.pCurrentNode; return *this; }
        /*Возвращает ссылку на текущий элемент коллекции*/
        const int &operator*() const { return pCurrentNode->value; }
        /*Возвращает указатель на текущий элемент коллекции*/
        const Node *operator->() const { return pCurrentNode; }
        ConstIteratorImpl &operator++() { moveStraight(); return *this; }
        ConstIteratorImpl operator++(int) { ConstIteratorImpl temp(pCurrentNode); moveStraight(); return temp; }
        ConstIteratorImpl &operator--() { moveBack(); return *this; }
        ConstIteratorImpl operator--(int) { ConstIteratorImpl temp(pCurrentNode); moveBack(); return temp; }
    };

    struct Node {
        int value;
        Node *next;
        Node *prev;
        Node(int _value) { value = _value; next = prev = nullptr; }
    };
private:


	Node *head;
	Node *last;
	size_t list_length;
};