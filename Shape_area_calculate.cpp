#include<iostream>

class quadrangle
{
protected:
    std::string name;
public:
    quadrangle(std::string n="quadrangle"): name(n) {}
    virtual ~quadrangle(){}

    std::string myName() const
    {
        return name;
    }

    bool result;
    double input;
    virtual double area() const = 0;
    virtual void print() const = 0;
};

class parallelogram : public quadrangle
{
protected:
    size_t width, height;
public:
    parallelogram(size_t w = 1+rand()%10, size_t h = 1+rand()%10, std::string n = "parallelogram") : quadrangle(n), width(w), height(h)  {}
    double area() const override
    { 
        return double(width * height); 
    }
    void print() const override
    {
        std::cout<<name<<":width="<<width<<",height="<<height<<",area=";
    }
};

class trapezoid : public quadrangle
{
private:
    size_t width1, width2, height;
public:
    trapezoid(size_t w1 = 1+rand()%10, size_t w2 = 1+rand()%10, size_t h = 1+rand()%10, std::string n = "trapezoid") : quadrangle(n), width1(w1), width2(w2), height(h)  {}
    double area() const override
    { 
        return double(((width1+width2) * height)/2.0); 
    }
    void print() const override
    {
        std::cout<<name<<":width1="<<width1<<",width2="<<width2<<",height="<<height<<",area=";
    }
};

class rectangle : virtual public parallelogram
{
public:
    rectangle(size_t w = 1+rand()%10, size_t h = 1+rand()%10, std::string n = "rectangle") : parallelogram(w, h, n) {}
};

class diamond : virtual public parallelogram
{
public:
    diamond(size_t w = 1+rand()%10, size_t h = 1+rand()%10, std::string n = "diamond") : parallelogram(w, h, n) {}
    double area() const override{ return parallelogram::area() / 2.0; }
    void print() const override
    {
        std::cout<<name<<":diagnal1="<<width<<",diagnal2="<<height<<",area=";
    }
};

class square: public rectangle, public diamond
{
public:
    square(size_t w = 1+rand()%10, std::string n = "square") : parallelogram(w, w, n) {}
    double area() const override{ return rectangle::area(); }
    void print() const override
    {
        std::cout<<name<<":width="<<width<<",area=";
    }
};

template <typename value_t>
class list
{
public:
    using value_type = value_t;
    using reference = value_type&;
    using pointer = value_type*;

private:
    struct node
    {
        value_type data;
        node * next = nullptr;
    };

    using nodeptr = node *;

    nodeptr head, tail;
    size_t len;

public:
    list() : head(nullptr), tail(nullptr), len(0) {}    //默认构造函数

    list(const list& l) : list() //复制构造函数
    {
        for (auto p = l.head; p != nullptr; p = p->next) 
            push_back(p->data);
    }

    list(list&& l) : list() //转移赋值构造函数
    {
        std::swap(head, l.head);
        std::swap(tail, l.tail);
        std::swap(len, l.len);
    }

    list& operator =(const list& l) 
    {
        clear();

        for (auto p = l.head; p != nullptr; p = p->next) 
            push_back(p->data);

        return *this;
    }


    list& operator =(list&& l)
    {
        std::swap(head, l.head);
        std::swap(tail, l.tail);
        std::swap(len, l.len);

        return *this;
    }

    ~list() { clear(); }    //析构函数

    void clear()
    {
        for (auto p = head; head != nullptr; )
        {
            head = head->next;
            delete p;
            p = head;
        }

        head = tail = nullptr;
        len = 0;
    }

    void push_back(value_type v)
    {
        auto p = new node{v, nullptr};
        
        head == nullptr ? head = p : tail->next = p;
        tail = p;

        ++len;
    }

    size_t size() const { return this->len; }

    class iterator
    {
    private:
        nodeptr p;

    public:
        using value_type = list::value_type;
        using reference = list::reference;
        using pointer = list::pointer;

        iterator(nodeptr t = nullptr) : p(t) { }

        bool operator !=(const iterator& i)
        {
            return p != i.p;
        }

        iterator& operator++()
        {
            p = p->next;
            return *this;
        }

        reference operator *()
        {
            return p->data;
        }
    };

    iterator begin() { return iterator(head); }
    iterator end() { return iterator(); }
};

quadrangle* generateShape()
{
    quadrangle* q=nullptr;
    srand(static_cast<unsigned int>(time(NULL)));
    int i = rand()%5;
    switch (i)
    {
        case 0:
            q = new parallelogram();
            break;
        case 1:
            q = new rectangle();
            break;
        case 2:
            q = new diamond();
            break;
        case 3:
            q = new square();
            break;
        case 4:
            q = new trapezoid();
            break;
    }
    return q;
}

int main()
{
    list<quadrangle*> shape;
    std::cout<<"Practicing.Input negative value to halt."<<std::endl;
    while(1)
    {
        quadrangle *p= generateShape();
        p->print();
        std::cout<<"?";
        std::cin>>p->input;
        if(p->input<0) 
        {
            delete p;
            break;
        }
        if(p->input==p->area())
        {
            std::cout<<"Your answer is correct"<<std::endl;
            p->result=true;
        }
        else
        {
            std::cout<<"Your answer is incorrect"<<std::endl;
            p->result=false;
        }
        shape.push_back(p);
        std::cout<<std::endl;
    }
    
    std::cout<<std::endl<<"Reviewing..."<<std::endl;
    int count_of_correct=0;
    for(auto i=shape.begin();i!=shape.end();++i)
    {
        (*i)->print();
        std::cout<<(*i)->area()<<",answer="<<(*i)->input;
        if((*i)->result) 
        {
            std::cout<<"√"<<std::endl;
            count_of_correct++;
        }
        else std::cout<<"×"<<std::endl;
    }
    std::cout<<std::endl;
    std::cout<<"Tatal:"<<shape.size()<<",Correct:"<<count_of_correct;
    for(auto i:shape) delete i;
}