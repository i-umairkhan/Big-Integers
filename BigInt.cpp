#include <iostream>
#include <vector>
#include <string>
using namespace std;

template <class itemtype>
class list
{
public:
    struct node
    {
        itemtype info;
        node *next;
    };
    typedef node *NODEPTR;
    NODEPTR listptr;

    list()
    {
        listptr = 0;
    }
    ~list()
    {
        NODEPTR p, q;
        if (isempty())
        {
            exit(0);
        }
        for (p = listptr, q = p->next; p != 0; p = q, q = p->next)
        {
            delete p;
        }
    }
    void insertAfter(itemtype oldvalue, itemtype newvalue)
    {
        NODEPTR p, q;
        for (p = listptr; p != 0 && p->info != oldvalue; p = p->next)
            ;
        if (p == 0)
        {
            cout << "ERROR : Valur not found" << endl;
            exit(1);
        }
        q = new node;
        q->info = newvalue;
        q->next = p->next;
        p->next = q;
    }
    int isempty()
    {
        return (listptr == 0);
    }
    void push(itemtype value)
    {
        NODEPTR p;
        p = new node;
        p->info = value;
        p->next = listptr;
        listptr = p;
    }
    void deletItem(itemtype oldvalue)
    {
        NODEPTR p, q;
        for (q = 0, p = listptr; p != 0 && p->info != oldvalue; q = p, p = p->next)
            ;
        if (p == 0)
        {
            cout << "Value is not in list" << endl;
            exit(1);
        }
        if (q == 0)
        {
            listptr = p->next;
        }
        else
        {
            q->next = p->next;
        }
        delete p;
    }
    itemtype pop()
    {
        NODEPTR p;
        itemtype x;
        if (isempty())
        {
            cout << "Error List is empty" << endl;
            exit(1);
        }
        p = listptr;
        x = p->info;
        listptr = p->next;
        delete p;
        return x;
    }
    void display()
    {
        NODEPTR p;
        if (isempty())
        {
            cout << " Error List is Empty ." << endl;
            exit(1);
        }
        p = listptr;
        while (p != NULL)
        {
            cout << p->info;
            p = p->next;
        }
    }
};
// ---------------------------------------- MULTIPLICATION FUNCTION ----------------------------------------
string multiply(string num1, string num2)
{
    if (num1 == "0" || num2 == "0")
        return "0";
    vector<int> num(num1.size() + num2.size(), 0);
    for (int i = num1.size() - 1; i >= 0; --i)
    {
        for (int j = num2.size() - 1; j >= 0; --j)
        {
            num[i + j + 1] += (num1[i] - '0') * (num2[j] - '0');
            num[i + j] += num[i + j + 1] / 10;
            num[i + j + 1] %= 10;
        }
    }
    int i = 0;
    while (i < num.size() && num[i] == 0)
        ++i;
    string res = "";
    while (i < num.size())
        res.push_back(num[i++] + '0');

    return res;
}
int main()
{
    string n1, n2;
    cout << endl
         << endl
         << endl;
    cout << "------------ BIG INT CALCULATOR -----------------" << endl;
    cout << "Enter First Number : ";
    cin >> n1;
    cout << "Enter Second Number : ";
    cin >> n2;
    list<int> l1;             //A link list in which long integer is stored
    list<int> l2;             //A link list in which long integer is stored
    string big_1 = n1;        // Given long integer
    string big_2 = n2;        // Given long integer
    string str = "";          // String used to copy 5 numbers from 'big' to make them int
    int val = 0;              // Int that copies values from 'str' and push them in nodes of list
    list<int> bigsum;         // LIST TO STORE SUM
    list<int> bigsubtraction; // LIST TO STORE SUBTRACTION
    list<int> bigdivision;    // LIST TO STORE DIVISION
    int n;
    string signs = "+";
    // --------------------------------- swapping strings to make first string bigger ----------------------
    if (big_2.length() > big_1.length())
    {
        swap(big_2, big_1);
        signs = "-";
    }
    if (big_1.length() > big_2.length())
    {
        n = big_1.length();
    }
    if (big_1.length() < big_2.length())
    {
        n = big_2.length();
    }
    if (big_1.length() == big_2.length())
    {
        n = 5;
    }

    // -------------------------  CONVERTING BIG 1 INTO LINK LIST ------------------------------------------
    while (big_1.length() % n != 0) // Making 'big1' Multiple of 5 to insert properly in list
    {
        big_1.insert(0, "0"); // Inserting 0 at position 0
    }
    for (int i = 0; i < big_1.length(); i++) // Pushing 5 int values in every node of List
    {
        if (str.length() <= 5)
        {
            str += big_1[i];
        }
        if (str.length() == 5)
        {
            int val = stoi(str);
            l1.push(val);
            str = "";
            val = 0;
        }
    }
    // -------------------------  CONVERTING BIG 2 INTO LINK LIST ------------------------------------------
    str = "";
    val = 0;
    while (big_2.length() % n != 0) // Making 'big' Multiple of 5 to insert properly in list
    {
        big_2.insert(0, "0"); // Inserting 0 at position 0
    }
    for (int i = 0; i < big_2.length(); i++) // Pushing 5 int values in every node of List
    {
        if (str.length() <= 5)
        {
            str += big_2[i];
        }
        if (str.length() == 5)
        {
            int val = stoi(str);
            l2.push(val);
            str = "";
            val = 0;
        }
    }
    // ----------------------------------  MAIN PROCESS ----------------------------------------------------
    int x = 0, y = 0, sum = 0, carry = 0, minus = 0, barrrow = 0, divide = 0;
    string s, c;
    // -------------------------------- ADDITIN AND SUTRACTION ---------------------------------------------
    while (!l1.isempty() && !l2.isempty())
    {
        x = l1.pop();
        y = l2.pop();
        // ------------------------------- Addition --------------------------------------------------------
        sum = (carry + x + y);
        if (sum > 99999)
        {
            s = to_string(sum);
            s.erase(0, 1);
            sum = stoi(s);
            bigsum.push(sum);
            carry = 1;
        }
        else if (sum <= 99999)
        {
            bigsum.push(sum);
            carry = 0;
        }
        // --------------------------------------SUBTRACTION -----------------------------------------------
        if (x < y)
        {
            s = to_string(x);
            s.insert(0, "1");
            x = stoi(s);
            minus = ((x - barrrow) - y);
            barrrow = 1;
        }
        else
        {
            minus = ((x - barrrow) - y);
            barrrow = 0;
        }
        bigsubtraction.push(minus);
    }
    // ------------------------------------ SHOWING RESULTS ------------------------------------------------
    cout << endl;
    cout << "----------------- ADDITION ------------------" << endl
         << endl;
    bigsum.display();
    cout << endl;
    cout << "----------------- SUBTRACTION ---------------" << endl
         << endl;
    cout << signs;
    bigsubtraction.display();
    cout << endl;
    cout << "----------------- MULTIPLICATION ------------" << endl
         << endl;
    cout << multiply(big_1, big_2);
    cout << endl;
    cout << "----------------- DIVISION ------------------" << endl
         << endl;
    bigdivision.display();
    cout << endl
         << endl
         << endl;
}
