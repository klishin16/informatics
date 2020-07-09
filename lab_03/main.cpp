// lab_03.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

class int_list_t {
private:
    struct node_t {
        int field;
        node_t *next;
        node_t *prev;
        // use this structure for nodes of list
    };
    size_t _size = 0;
public:
    struct node_t* frst;
    struct node_t* lst;

    int_list_t() { // O(1)
        frst = nullptr;
        lst = nullptr;
        _size = 0;
    }

    int_list_t(const int_list_t& other) { // COPY $other list O(other.size)
        if (other.empty()) {
            frst = nullptr;
            lst = nullptr;
        } else {
            for (int i = 0; i < other.size(); i++) {
                if (i == 0) {
                    push_first(other[i]);
                } else {
                    auto* elem1 = new node_t;
                    elem1->field = other[i];
                    lst->next = elem1;
                    elem1->prev = lst;
                    elem1->next = nullptr;
                    lst = elem1;
                }
            }
        }
        _size = other.size();
    }

    int_list_t(size_t count, int value) { // create list $count size and fill it with $value O($count)
        if(count == 0) {
            frst = nullptr;
            lst = nullptr;
        }
        else {
            auto* elem = new node_t;
            elem->field = value;
            elem->next = nullptr;
            elem->prev = nullptr;
            frst = elem;
            lst = frst;

            for (int i = 0; i < int(count) - 1; i++) {
                auto* temp = new node_t;
                temp->field = value;
                lst->next = temp;
                temp->prev = lst;
                temp->next = nullptr;
                lst = temp;
            }
        }
        _size = count;
    }

    ~int_list_t() {    // O(size)
        node_t* current = frst;
        node_t* c_next = frst;
        int s = size();
        for (int i = 0; i < s - 1; i++) {
            current = c_next;
            c_next = current->next;
            delete current;
        }
        delete c_next;
    }

    int_list_t& operator=(const int_list_t& other) { // O(size + other.size())
        if (!this->empty()) {
            this->clear();
        }
        if (other.empty()) {
            frst = nullptr;
            lst = nullptr;
        }
        else {
            for (int i = 0; i < other.size(); i++) {
                if (i != 0) {
                    auto* elem1 = new node_t;
                    elem1->field = other[i];
                    lst->next = elem1;
                    elem1->prev = lst;
                    elem1->next = nullptr;
                    lst = elem1;
                } else {
                    auto* elem = new node_t;
                    elem->field = other[i];
                    elem->prev = nullptr;
                    elem->next = nullptr;
                    frst = elem;
                    lst = frst;
                }
            }
        }

        return *this;
    }

    int& operator[](size_t pos) const { // O(min($pos, size - $pos))
        return get_ptr(pos)->field;
    }

    int& back() const {   // last element O(1)
        return lst->field;
    }

    int& front() const {  // first element O(1)
        return frst->field;
    }

    void clear() { // O(size)
        this->~int_list_t();
        frst = nullptr;
        lst = nullptr;
        _size = 0;
    }

    size_t size() const { // O(1)
        return _size;
    }

    bool empty() const { // O(1)
        return frst == nullptr;
    }

    void insert(size_t pos, int new_val){ // insert element $new_val BEFORE element with index $pos O(min($pos, size - $pos))
        auto* ins = new node_t;
        ins->field = new_val;
        try {
            if (empty()) {
                if (pos != 0) {
                    throw "Insertion to a non-existing position";
                } else {
                    push_first(new_val);
                }
            } else {
                if (pos == 0) {
                    push_front(new_val);
                } else if (pos == size()) {
                    push_back(new_val);
                } else if (pos < 0 || pos > size()) {
                    throw "Insertion out of range";
                } else {
                    node_t* current = get_ptr(pos);
                    ins->next = current;
                    ins->prev = current->prev;
                    current->prev->next = ins;
                    current->prev = ins;
                }
            }
        } catch (const char* exception) {
            std::cout << "Error: " << exception << std::endl;
        }
    }

    void push_front(int new_val) { // O(1) // добавить элемент в начало списка
        if (empty()) {
            push_first(new_val);
        }
        else {
            auto* psh = new node_t;
            psh->field = new_val;
            psh->prev = nullptr;
            psh->next = frst;
            frst = psh;
        }
    }

    void push_back(int new_val) {    // O(1) // добавить элемент в конец списка
        if (empty()) {
            push_first(new_val);
        }
        else {
            auto* psh = new node_t;
            psh->field = new_val;
            psh->prev = lst;
            lst->next = psh;
            psh->next = nullptr;
            lst = psh;
        }
    }

    void erase(size_t pos) { // remove element with index $pos O(min($pos, size - $pos))
        try {
            if(empty()) {
                throw "Erase empty list";
            }
            if(pos < 0 || pos >= size()) {
                throw "Erase element out of range";
            }
            if (pos == 0) {
                pop_front();
            } else if (pos == size() - 1) {
                pop_back();
            } else {
                node_t *current = get_ptr(pos);
                std::cout << "here";
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
            }
            _size++;
        } catch (const char* exception) {
            std::cout << "Error: " << exception << std::endl;
        }
    }

    void pop_front() { // O(1)
        try {
            if (empty()) {
                throw "Erase element from empty list";
            }
            if (size() == 1) {
                clear();
            } else {
                node_t *p = frst;
                frst = frst->next;
                frst->prev = nullptr;
                delete p;
                _size--;
            }
        } catch (const char* exception) {
            std::cout << "Error: " << exception;
        }
    }

    void pop_back() {  // O(1)
        try {
            if (empty()) {
                throw "Erase element from empty list";
            }
            if (size() == 1) {
                clear();
            } else {
                node_t* p = lst;
                lst = lst->prev;
                lst->next = nullptr;
                delete p;
                _size--;
            }
        } catch (const char* exception) {
            std::cout << "Error: " << exception;
        }
    }

    int_list_t splice(size_t start_pos, size_t count) { // splice part of list into result (not copy!) O($start_pos + $count)
      int_list_t res;
      node_t* current = frst;
      for (int i = 0; i < start_pos; i++) {
            current = current->next;
      }
      node_t* from = current;
      node_t* to = current;
      for(int i = 0; i < count - 1; i++) {
          current = current->next;
      }
      to = current;
      res.frst = from;
      res.lst = to;
      node_t* from_prev = from->prev;
      from_prev->next = to->next;
      to->prev = from_prev;
      res.frst->prev = nullptr;
      res.lst->next = nullptr;
      _size-=count;
      return res;
    }

    int_list_t& merge(int_list_t& other) { // merge two lists, after operation $other must be valid empty list O(1)
        _size+=other._size;
        lst->next = other.frst;
        other.frst->prev = lst;
        lst = other.lst;
        other.frst = nullptr;
        other.lst = nullptr;
        other._size = 0;
        return *this;
    }

    void reverse() { // O(size)
        node_t* prt = frst;
        node_t* prev = nullptr;
        frst = lst;
        lst = prt;
        while (prt != frst) {
            node_t* tmp = prt->next;
            prt->next = prev;
            prev = prt;
            prt = tmp;
        }
        frst->next = prev;
    }

    void swap(int_list_t& other) { // O(1)
        int temp = other.size();
        node_t* other_frst = other.frst;
        node_t* other_lst = other.lst;
        other.frst = frst;
        other.lst = lst;
        frst = other_frst;
        lst = other_lst;
        other._size = _size;
        _size = temp;
    }

    friend std::istream& operator>>(std::istream& stream, int_list_t& list);    // O(size)
    friend std::ostream& operator<<(std::ostream& stream, const int_list_t& list); // O(size)

private:
    node_t* get_ptr(size_t pos) const {
        node_t* current = frst;
        for (int i = 0; i < pos; i++) {
            current = current->next;
        }
        return current;
    }

    void push_first(int val) {
        auto* elem = new node_t;
        elem->field = val;
        elem->next = nullptr;
        elem->prev = nullptr;
        frst = elem;
        lst = frst;
        _size = 1;
    }
};

std::istream& operator>>(std::istream& stream, int_list_t& list) {
    int value;
    stream >> value;
    list.push_back(value);
    return stream;
}

std::ostream& operator<< (std::ostream& stream, const int_list_t& list) {
    stream << "[ ";
    for (int i = 0; i < list.size(); i++) {
        stream << list[i] << " ";
    }
    stream << ']' << std::endl;
    return stream;
}

void comment(std::string txt) {
    std::cout << txt << std::endl;
}

int main()
{
    int_list_t l = int_list_t(3, 5);
    std::cout<<"First list len: " << l.size() << std::endl;
    std::cout<<l;
    std::cout << "First elem: " << l.front() << std::endl;
    std::cout << "Last elem: " << l.back() << std::endl;
    comment("Add elem to front with value { 11 }");
    l.push_front(11);
    std::cout << "First elem: " << l.front() << std::endl;
    comment("Pop element from back");
    l.pop_back();
    std::cout<<l;
    int_list_t l1(5, 9);
    std::cout<<l1;
    comment("Inset element to 1 pos with value { 16 }");
    l.insert(2, 16);
    std::cout<<l;
    std::cout<<l.back();
    comment("Erase elem from 3 pos");
    l.erase(2);
    std::cout<<l;
    comment("Reverse list");
    l.reverse();
    std::cout<<l;
    comment("Swap list");
    int_list_t l2(5, 9);
    l.swap(l2);
    std::cout<<l;
    std::cout << "[0]: " << l[0] << std::endl;
    std::cout << "[2]: " << l[2] << std::endl;


    std::cout << "Test 1:" << std::endl;
    int_list_t test1(0, 1);
    std::cout << test1;
    std::cout << "Test 2:" << std::endl;
    int_list_t test2 = test1;
    std::cout << test2;
    std::cout << "Test 3:" << std::endl;
    int_list_t test3;
    test3 = test2;
    test3.push_front(42);
    std::cout << test3;
    std::cout << "Test 4: push/pop" << std::endl;
    int_list_t test4(1, 35);
    std::cout << test4;
    test4.pop_front();
    std::cout << test4;
    test4.push_back(38);
    std::cout << test4;

    std::cout << "Test 5: insert" << std::endl;
    int_list_t test5(5, 14);
    test5.insert(-1, 42);
    std::cout << test5;
    int_list_t test52;
    test52.insert(1, 1);
    std::cout << test52;

    std::cout << "Test 6: erase" << std::endl;
    int_list_t test6(1, 14);
    test6.push_back(16);
    test6.push_back(18);
    std::cout << test6;
    test6.erase(3);
    std::cout << test6;


    std::cin>>l;
    std::cout<<l;

    int_list_t t1(7, 5);
    int_list_t t2;
    t2 = t1;
    std::cout << t1;
    std::cout << t2;
    t2.insert(2, 7);
    t2.insert(5, 14);
    std::cout << t2;
    int_list_t t3 = t2.splice(2, 3);
    std::cout << t3;
}
