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
public:
    struct node_t* frst;
    struct node_t* lst;

    int_list_t() { // O(1)
        frst = NULL;
        lst = NULL;
    }

    int_list_t(const int_list_t& other) { // COPY $other list O(other.size)
        for (int i = 0; i < other.size(); i++) {
            if (i != 0) {
                node_t* elem = new node_t;
                elem->field = other[i];
                elem->prev = lst;
                elem->next = NULL;
                lst = elem;
            } else {
                node_t* elem = new node_t;
                elem->field = other[i];
                elem->prev = NULL;
                elem->next = NULL;
                frst = elem;
                lst = elem;
            }
        }
    }

    int_list_t(size_t count, int value) { // create list $count size and fill it with $value O($count)
        node_t* elem = new node_t;
        elem->field = value;
        elem->next = NULL;
        elem->prev = NULL;
        frst = elem;
        lst = frst;

        for (int i = 0; i < int(count) - 1; i++) {
            node_t* temp = new node_t;
            //temp = (struct node_t*)malloc(sizeof(struct node_t));
            temp->field = value;
            lst->next = temp;
            temp->prev = lst;
            temp->next = NULL;
            lst = temp;
        }
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
        node_t* other_next = other.frst;
        for (int i = 0; i < int(other.size()); i++) {
            node_t* item = other_next;
            other_next = item->next;
            delete item;
        }
        return const_cast<int_list_t &>(other); //
    }

    //int& operator[](size_t pos); // O(min($pos, size - $pos))
    int& operator[](size_t pos) const { // O(min($pos, size - $pos))
        node_t* current = frst;
        for (int i = 0; i < pos; i++) {
            current = current->next;
        }
        return  current->field;
    }

    int& back() const {   // last element O(1)
        return lst->field;
    }
    //const int back() const; // O(1)

    int& front() const {  // first element O(1)
        return frst->field;
    }

    //const int front() const; // O(1)

    void clear() { // O(size)
        node_t* current = frst;
        while (true)
        {
            if (current->next != NULL) {
                node_t* nxt = current->next;
                delete current;
            }
            else {
                delete current;
                frst = lst = NULL;
                break;
            }
        }
    }

    size_t size() const { // O(1)
        if (frst == NULL) {
            return 0;
        }
        else {
            int count = 0;
            node_t* current = frst;
            while (true)
            {
                count++;
                if (current->next == NULL) {
                    break;
                }
                current = current->next;
            };
            return count;
        }
    }
    bool empty() const { // O(1)
        if (frst != NULL) {
            return false;
        }
        else {
            return true;
        }
    }

    void insert(size_t pos, int new_val){ // insert element $new_val BEFORE element with index $pos O(min($pos, size - $pos))
        node_t* ins = new node_t;
        ins->field = new_val;
        node_t* current = frst;
        if (size() != 0) {
            if (size() == 1) {
                push_front(new_val);
            } else {
                for (int i = 0; i < pos; i++) {
                    current = current->next;
                }
                std::cout<<current->field<<std::endl;
                ins->next = current;
                ins->prev = current->prev;
                current->prev->next = ins;
                current->prev = ins;
            }
        }
    }

    void push_front(int new_val) { // O(1) // добавить элемент в начало списка
        node_t* psh = new node_t;
        psh->field = new_val;
        psh->prev = NULL;
        psh->next = frst;
        frst = psh;
    }

    void push_back(int new_val) {    // O(1) // добавить элемент в конец списка
        node_t* psh = new node_t;
        psh->field = new_val;
        psh->prev = lst;
        lst->next = psh;
        psh->next = NULL;
        lst = psh;
    }

    void erase(size_t pos) { // remove element with index $pos O(min($pos, size - $pos))
        node_t* current = frst;
        for (int i = 0; i < pos; i++) {
            current = current->next;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;

        delete current;
    }

    void pop_front() { // O(1)
        node_t* p = frst;
        frst = frst->next;
        frst->prev = NULL;

        delete p;
    }
    void pop_back() {  // O(1)
        node_t* p = lst;
        lst = lst->prev;
        lst->next = NULL;

        delete p;
    }

    int_list_t splice(size_t start_pos, size_t count) { // splice part of list into result (not copy!) O($start_pos + $count)
      // не совсем понятно что данный метод должен делать;
    }

    int_list_t& merge(int_list_t& other) { // merge two lists, after operation $other must be valid empty list O(1)
        lst->next = other.frst;
        other.frst->prev = lst;
        lst = other.lst;
        other.frst = NULL;
        other.lst = NULL;

        return *this;
    }

    void reverse() { // O(size)
        node_t* prt = frst;
        node_t* prev = NULL;
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
        node_t* other_frst = other.frst;
        node_t* other_lst = other.lst;
        other.frst = frst;
        other.lst = lst;
        frst = other_frst;
        lst = other_lst;
    }

    friend std::istream& operator>>(std::istream& stream, int_list_t& list);    // O(size)
    friend std::ostream& operator<<(std::ostream& stream, const int_list_t& list); // O(size)

private:
    // any you want
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

void show_list(int_list_t& lst) {
    std::cout<<"[ ";
    for (int i = 0; i < lst.size(); i++) {
        std::cout << lst[i] << " ";
    }
    std::cout<<']' << std::endl;
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
    std::cin>>l;
    std::cout<<l;

}
