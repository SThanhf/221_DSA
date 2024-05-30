#ifndef __CONCAT_STRING_LIST_H__
#define __CONCAT_STRING_LIST_H__

#include "main.h"

class ConcatStringList
{
public:
    class ReferencesList;   // forward declaration
    class DeleteStringList; // forward declaration

public:
    static ReferencesList refList;
    static DeleteStringList delStrList;
    // end first
public:
    int count;
    struct Node
    {
        Node *next;
        string CharArrayList;
    };

protected:
    Node CharALNode;
    Node *head;
    Node *tail;
    int len;

public:
    ConcatStringList(const char *);
    int length() const;
    char get(int index) const;
    int indexOf(char c) const;
    std::string toString() const;
    ConcatStringList concat(const ConcatStringList &otherS) const;
    ConcatStringList subString(int from, int to) const;
    ConcatStringList reverse() const;
    ~ConcatStringList();

    // last period
public:
    class ReferencesList
    {
        // TODO: may provide some attributes
    public:
        struct refNode
        {
            /* data */
            Node *Node_address;
            refNode *refNode_next;
            int refC;
        };
        refNode *refHead;
        refNode *refTail;
        int refNodeCount;

    public:
        int size() const { return this->refNodeCount; };
        int refCountAt(int index) const
        {
            if (index >= this->refNodeCount)
                throw std::out_of_range("Index of references list is invalid!");
            refNode *temp = this->refHead;
            for (int i = 0; i < index; ++i)
                temp = temp->refNode_next;
            return temp->refC;
        };
        std::string refCountsString() const
        {
            if (this->refNodeCount == 0)
                return "RefCounts[]";
            string res = "RefCounts[";
            for (int i = 0; i < this->refNodeCount; ++i)
            {
                res += to_string(this->refCountAt(i));
            }
            res += "]";
            return res;
        };
    };

    class DeleteStringList
    {
        // TODO: may provide some attributes
    public:
        struct delNode
        {
            ReferencesList::refNode *refNodeHead;
            ReferencesList::refNode *refNodeTail;
            delNode *delNode_next;
        };
        delNode *delHead;
        delNode *delTail;
        int delNodeCount;

    public:
        int size() const { return this->delNodeCount; };
        std::string totalRefCountsString() const
        {
            if (this->delNodeCount == 0)
                return "TotalRefCounts[]";
            string temp = "TotalRefCounts[";
            temp += to_string(this->delNodeCount);
            temp += "]";
            return temp;
        };
    };
};

#endif // __CONCAT_STRING_LIST_H__