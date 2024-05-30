// 1
template <class T>
void SLinkedList<T>::add(const T& e) {
    /* Insert an element into the end of the list. */
    Node *newNode = new Node(e, 0);
    if (head == NULL) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    count++;
}

template<class T>
void SLinkedList<T>::add(int index, const T& e) {
    /* Insert an element into the list at given index. */
    if (index < 0 || index > count) throw out_of_range("Index out of range.");
    if (index == 0) {
        head = new Node(e, head);
        if (tail == NULL) tail = head;
    } else {
        Node *p = head;
        for (int i = 1; i < index; i++) {
            p = p->next;
        }
        p->next = new Node(e, p->next);
        if (p == tail) tail = p->next;
    }
    count++;
}

template<class T>
int SLinkedList<T>::size() {
    /* Return the length (size) of list */
    return count;
}

// 2
template<class T>
T SLinkedList<T>::get(int index) {
    /* Give the data of the element at given index in the list. */
    if (index < 0 || index > count) throw out_of_range("Index out of range.");
    Node *p = head;
    for (int i = 0; i < index; i++) {
        p = p->next;
    }
    return p->data;
}

template <class T>
void SLinkedList<T>::set(int index, const T& e) {
    /* Assign new value for element at given index in the list */
    if (index < 0 || index > count) throw out_of_range("Index out of range.");
    Node *p = head;
    for (int i = 0; i < index; i++) {
        p = p->next;
    }
    p->data = e;
}

template<class T>
bool SLinkedList<T>::empty() {
    /* Check if the list is empty or not. */
    return count == 0 ? true : false;
}

template<class T>
int SLinkedList<T>::indexOf(const T& item) {
    /* Return the first index wheter item appears in list, otherwise return -1 */
    Node *p = head;
    int idx = 0;
    while (p != NULL) {
        if (p->data == item) return idx;
        p = p->next;
        idx++;
    }
    return -1;
}

template<class T>
bool SLinkedList<T>::contains(const T& item) {
    /* Check if item appears in the list */
    Node *p = head;
    while (p != NULL) {
        if (p->data == item) return true;
        p = p->next;
    }
    return false;
}

// 3
template <class T>
T SLinkedList<T>::removeAt(int index) {
    /* Remove element at index and return removed value */
    if (index < 0 || index > count - 1) throw out_of_range("Index out of range.");
    Node *prev = NULL;
    Node *p = head;
    for (int i = 0; i < index; i++) {
        prev = p;
        p = p->next;
    }
    if (prev == NULL) head = p->next;
    else if (p == tail) tail = prev;
    else prev->next = p->next;
    T result = p->data;
    delete p;
    count--;
    return result;
}

template <class T>
bool SLinkedList<T>::removeItem(const T& item) {
    /* Remove the first apperance of item in list and return true, otherwise return false */
    Node *prev = NULL;
    Node *p = head;
    while (p != NULL) {
        if (p->data == item) {
            if (prev == NULL) head = p->next;
            else if (p == tail) tail = prev;
            else prev->next = p->next;
            delete p;
            count--;
            return true;
        }
        prev = p;
        p = p->next;
    }
    return false;
}

template<class T>
void SLinkedList<T>::clear() {
    /* Remove all elements in list */
    Node *p = head;
    while (p != tail->next) {
        Node *temp = p;
        p = p->next;
        delete temp;
    }
    head = tail = NULL;
    count = 0;
}

// 5
LLNode* reverseLinkedList(LLNode* head) {
    // STUDENT ANSWER
    LLNode *current = head;
    LLNode *prev = NULL, *next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
    return head;
}

// 6
LLNode* newNode(int value) {
    LLNode* new_node = new LLNode();
    new_node->val = value;
    new_node->next = NULL;
    return new_node;
}

LLNode* addLinkedList(LLNode* lst1, LLNode* lst2) {
    // STUDENT ANSWER
    LLNode *result = NULL;
    LLNode *temp = NULL, *prev = NULL;
    int c_out = 0, sum;
    while (lst1 != NULL || lst2 != NULL) {
        sum = c_out + (lst1 ? lst1->val : 0) + (lst2 ? lst2->val : 0);
        c_out = (sum >= 10) ? 1 : 0;
        sum %= 10;
        temp = newNode(sum);
        if (result == NULL) result = temp;
        else prev->next = temp;
        prev = temp;
        if (lst1) lst1 = lst1->next;
        if (lst2) lst2 = lst2->next;
    }
    if (c_out > 0) temp->next = newNode(c_out);
    return result;
}

// 7
LLNode* rotateLinkedList(LLNode* head, int k) {
    // STUDENT ANSWER
    if (!head) return head;
    int length = 1;
    LLNode *newHead, *tail;
    newHead = tail = head;
    while(tail->next) {
        tail = tail->next;
        length++;
    }
    tail->next = head;
    if(k %= length) {
        for(auto i = 0; i < length - k; i++) {
            tail = tail->next;
        }
    }
    newHead = tail->next;
    tail->next = NULL;
    return newHead;
}

// 8
void LinkedList::partition(int k) {
    if (head == nullptr || head->next == nullptr) return;
    Node *leftList = new Node(0);
    Node *midList = new Node(0);
    Node *rightList = new Node(0);

    Node *leftTail = leftList;
    Node *midTail = midList;
    Node *rightTail = rightList;

    while (head != tail->next) {
        if (head->value < k) {
            leftTail->next = head;
            leftTail = leftTail->next;
        } else if (head->value == k) {
            midTail->next = head;
            midTail = midTail->next;
        } else {
            rightTail->next = head;
            rightTail = rightTail->next;
        }
        head = head->next;
    }

    if (leftTail == leftList) {
        if(midTail == midList) {
            head = rightList->next;
            tail = rightTail;
        } else {
            midTail->next = rightList->next;
            head = midList->next;
            if(rightTail == rightList) tail = midTail;
            else tail = rightTail;
        }
    } else {
        head = leftList->next;
        if(midTail == midList) {
            leftTail->next = rightList->next;
            if(rightTail == rightList) tail = leftTail;
            else tail = rightTail;
        } else {
            leftTail->next = midList->next;
            midTail->next = rightList->next;
            if(rightTail == rightList) tail = midTail;
            else tail = rightTail;
        }
    }
}
