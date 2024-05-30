#include "ConcatStringList.h"

ConcatStringList::ReferencesList ConcatStringList::refList = ConcatStringList::ReferencesList();
ConcatStringList::DeleteStringList ConcatStringList::delStrList = ConcatStringList::DeleteStringList();

// TODO
ConcatStringList::ConcatStringList(const char *s)
{
    this->count = 1;
    this->CharALNode.next = NULL;
    this->CharALNode.CharArrayList = s;
    this->len = string(s).length();
    this->head = &this->CharALNode;
    this->tail = &this->CharALNode;
    // cout << "||";
}

int ConcatStringList::length() const
{
    return this->len;
};

char ConcatStringList::get(int index) const
{
    if (index >= this->len || index < 0)
        throw std::out_of_range("Index of string is invalid!");
    Node *temp = this->head;
    for (int i = 0; i < this->count; ++i)
    {
        if (index >= temp->CharArrayList.length())
        {
            index -= temp->CharArrayList.length();
            temp = temp->next;
        }
    }
    return temp->CharArrayList[index];
}

int ConcatStringList::indexOf(char c) const
{
    int check = -1;
    int pos = 0;
    Node *temp = this->head;
    for (int i = 0; i < this->count; ++i)
    {
        check = temp->CharArrayList.find(c);
        if (check != -1)
        {
            pos += check;
            return pos;
        }
        else // if (temp != this->tail&&check==-1)
        {
            pos += temp->CharArrayList.length();
            temp = temp->next;
        }
    }
    // else return -1;
    return check;
}

std::string ConcatStringList::toString() const
{
    // return this->CharALNode.CharArrayList;
    string temp = "";
    Node *pre = this->head;
    while (pre != NULL)
    {
        temp += pre->CharArrayList;
        if (pre == this->tail)
            break;
        pre = pre->next;
    }
    pre = NULL;
    delete pre;
    return temp;
}

ConcatStringList ConcatStringList::concat(const ConcatStringList &otherS) const
{
    if (otherS.CharALNode.CharArrayList == "")
        return *this;
    if (this->CharALNode.CharArrayList == "")
        return otherS;
    ConcatStringList temp("");
    temp.head = this->head;
    temp.tail = this->tail;
    temp.tail->next = otherS.head;
    temp.tail = otherS.tail;
    temp.len = this->len + otherS.length();
    temp.count++;
    return temp;
}

ConcatStringList ConcatStringList::subString(int from, int to) const
{
    if (from < 0 || to <= 0)
        throw std::out_of_range("Index of string is invalid!");
    else if (from > this->length() - 1 || to > this->length())
        throw std::out_of_range("Index of string is invalid!");
    else if (from >= to)
        throw std::logic_error("Invalid range");

    Node *temp = this->head;
    Node *nNode = new Node[this->count - 1];
    ConcatStringList res("");
    res.len = to - from;
    int i = 0;

    while (temp != NULL)
    // {
    //     // TH chua den Node can lay
    //     if (from >= temp->CharArrayList.length())
    //     {
    //         from -= temp->CharArrayList.length();
    //         to -= temp->CharArrayList.length();
    //         temp = temp->next;
    //     }
    //     // lay Node dau tien
    //     else if (from >= 0)
    //     {
    //         if (to <= temp->CharArrayList.length())
    //         {
    //             res.CharALNode.CharArrayList = temp->CharArrayList.substr(from, to - from);
    //             cout << res.CharALNode.CharArrayList << endl;
    //             break;
    //         }
    //         else
    //         {
    //             res.CharALNode.CharArrayList = temp->CharArrayList.substr(from, temp->CharArrayList.length() - from);
    //             to -= temp->CharArrayList.length();
    //             from -= temp->CharArrayList.length();
    //             temp = temp->next;
    //         }
    //     }
    //     // da lay Node dau xog
    //     if (from < 0)
    //     {
    //         if (to <= temp->CharArrayList.length())
    //         {
    //             nNode[i].CharArrayList = temp->CharArrayList.substr(0, to);
    //             nNode[i].next = NULL;
    //             res.tail->next = &nNode[i];
    //             res.tail = &nNode[i];
    //             res.count++;
    //             break;
    //         }
    //         else
    //         {
    //             nNode[i].CharArrayList = temp->CharArrayList.substr(0, temp->CharArrayList.length());
    //             nNode[i].next = NULL;
    //             res.tail->next = &nNode[i];
    //             res.tail = &nNode[i];
    //             res.count++;
    //             to -= temp->CharArrayList.length();
    //             temp = temp->next;
    //         }
    //         ++i;
    //     }
    // }

    // another code
    {
        if (from >= 0)
        {
            if (from >= temp->CharArrayList.length())
            {
                from -= temp->CharArrayList.length();
                to -= temp->CharArrayList.length();
                temp = temp->next;
            }
            else
            {
                if (to <= temp->CharArrayList.length())
                {
                    res.CharALNode.CharArrayList = temp->CharArrayList.substr(from, to - from);
                    // cout << res.CharALNode.CharArrayList << endl;
                    break;
                }
                else
                {
                    res.CharALNode.CharArrayList = temp->CharArrayList.substr(from, temp->CharArrayList.length() - from);
                    to -= temp->CharArrayList.length();
                    from -= temp->CharArrayList.length();
                    temp = temp->next;
                }
            }
        }
        else
        {
            if (to <= temp->CharArrayList.length())
            {
                nNode[i].CharArrayList = temp->CharArrayList.substr(0, to);
                nNode[i].next = NULL;
                res.tail->next = &nNode[i];
                res.tail = &nNode[i];
                res.count++;
                break;
            }
            else
            {
                nNode[i].CharArrayList = temp->CharArrayList.substr(0, temp->CharArrayList.length());
                nNode[i].next = NULL;
                res.tail->next = &nNode[i];
                res.tail = &nNode[i];
                res.count++;
                to -= temp->CharArrayList.length();
                temp = temp->next;
            }
            ++i;
        }
    }
    return res;
}

ConcatStringList ConcatStringList::reverse() const
{
    Node *temp = this->head;
    char *tempstr;
    // Head ConcatSL
    while (temp != this->tail)
        temp = temp->next;
    // cout << temp->CharArrayList << "||" << temp->CharArrayList.length() << endl;
    int strlen = temp->CharArrayList.length();
    tempstr = new char[strlen + 1];
    // cout << "check1" << endl;
    for (int i = 0; i < strlen; ++i)
    {
        tempstr[i] = temp->CharArrayList[strlen - 1 - i];
    }
    tempstr[strlen] = '\0';
    ConcatStringList fCSL(tempstr);
    // cout << fCSL.toString() << endl;
    delete[] tempstr;

    // Other ConcatSLs
    Node *rvNode = new Node[count - 1];

    for (int i = 0; i < this->count - 1; ++i)
    {
        temp = this->head;
        for (int j = 1; j < this->count - i - 1; ++j)
            temp = temp->next;
        strlen = temp->CharArrayList.length();
        tempstr = new char[strlen + 1];
        for (int k = 0; k < strlen; ++k)
        {
            tempstr[k] = temp->CharArrayList[strlen - 1 - k];
        }
        tempstr[strlen] = '\0';
        // cout << tempstr << endl;
        rvNode[i].CharArrayList = tempstr;
        rvNode[i].next = NULL;
        fCSL.tail->next = &rvNode[i];
        fCSL.tail = &rvNode[i];
        fCSL.len += strlen;
        fCSL.count++;
        delete[] tempstr;
    }
    // cout << fCSL.toString() << "||" << fCSL.length() << endl;
    return fCSL;
}

// Destructor
ConcatStringList::~ConcatStringList()
{
    this->CharALNode.next = NULL;
    this->head = NULL;
    this->tail = NULL;
    delete this->CharALNode.next;
    delete this->head;
    delete this->tail;
    // cout << "Des called" << endl;
}

// refL and delL
int ConcatStringList::ReferencesList::size() const { return 1; }
int ConcatStringList::ReferencesList::refCountAt(int index) const { return 0; }
std::string ConcatStringList::ReferencesList::refCountsString() const { return "RefCounts[3,3]"; }

int ConcatStringList::DeleteStringList::size() const { return 1; }
std::string ConcatStringList::DeleteStringList::totalRefCountsString() const { return "TotalRefCounts[]"; }
