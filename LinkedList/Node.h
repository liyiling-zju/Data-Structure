#include <cstdlib>

template <typename T>
class Node
{
private:
    T data;
    Node* next;
public:
    Node();
    Node(T _val);
    ~Node();
    T get_data() const;
    void set_data(T _val);
    Node* get_next() const;
    void set_next(Node* _add);
    T pop_front();
};

template<typename T>
Node<T>::Node()
{
    next = NULL;
};

template<typename T>
Node<T>::Node(T _val)
{
    data = _val;
    next = NULL;
};

template<typename T>
Node<T>::~Node()
{
};

template<typename T>
T Node<T>::get_data() const
{
    return data;
};

template<typename T>
void Node<T>::set_data(T _val)
{
    data = _val;
};

template<typename T>
Node<T>* Node<T>::get_next() const
{
    return next;
};

template<typename T>
void Node<T>::set_next(Node<T>* _add)
{
    next = _add;
};
