// ============================================================
// CSCI 232 Assignment 06 – Doubly Linked List vs. std::list
// Student Implementation
// ============================================================

#include "code.hpp"
#include <algorithm>
#include <iostream>

// Uncomment the author block below and fill in your name:

std::string AUTHOR_NAME       = "Joseph Freze";
std::string AUTHOR_AUTHORSHIP = "I acknowledge that I have worked on this "
"assignment independently, except where explicitly noted and referenced. "
"Any collaboration or use of external resources has been properly cited. "
"I am fully aware of the consequences of academic dishonesty and agree "
"to abide by the university's academic integrity policy.";

// ============================================================
// PART 1: Class DoubleNode
// ============================================================

/// Constructor: initialize ALL THREE fields with a member initializer list.
/// value <- newValue, prevPtr <- nullptr, nextPtr <- nullptr.
DoubleNode::DoubleNode(NodeValue newValue)
    : prevPtr(nullptr), value(newValue), nextPtr(nullptr)
{
    // TODO: move the initialization of all three fields into an initializer list
}

/// Const getter: return the stored value.
NodeValue DoubleNode::getValue() const
{
    // TODO: return the value field
    return NodeValue{value};
}

/// Const getter: return the previous node (or nullptr).
DoubleNode *DoubleNode::getPrev() const
{
    // TODO: return the prevPtr field
    return prevPtr;
}

/// Const getter: return the next node (or nullptr).
DoubleNode *DoubleNode::getNext() const
{
    // TODO: return the nextPtr field
    return nextPtr;
}

/// Setter: store newPrevPtr in prevPtr.
void DoubleNode::setPrev(DoubleNode *newPrevPtr)
{
    // TODO: assign the field
    prevPtr = newPrevPtr;
}

/// Setter: store newNextPtr in nextPtr.
void DoubleNode::setNext(DoubleNode *newNextPtr)
{
    // TODO: assign the field
    nextPtr = newNextPtr;
}

// ============================================================
// PART 2: Class DoublyLinkedList
// ============================================================

/// Empty list: headPtr = nullptr, tailPtr = nullptr, count = 0.
DoublyLinkedList::DoublyLinkedList()
    :headPtr(nullptr), tailPtr(nullptr), count(0)
{
    // TODO: initialize all three fields (use an initializer list)
}

/// RAII: delete ALL nodes. Save the next pointer BEFORE delete.
DoublyLinkedList::~DoublyLinkedList()
{
    // TODO: walk through the list and delete every node
    DoubleNode *currentPtr = headPtr;
    while (currentPtr != nullptr)
    {
        DoubleNode *nextPtr = currentPtr->getNext();  // save BEFORE delete
        delete currentPtr;
        currentPtr = nextPtr;
    }
    headPtr = nullptr;
    tailPtr = nullptr;
    count   = 0;
}

/// Unlink the first node and RETURN it (do not delete it).
/// Fix headPtr, tailPtr, count. Clear the node's own prevPtr and nextPtr.
/// Return nullptr if the list is empty.
DoubleNode *DoublyLinkedList::detachFirst()
{
    if (headPtr == nullptr)
        return nullptr;

    DoubleNode *detachedPtr = headPtr;
    headPtr = headPtr->getNext();

    if (headPtr != nullptr)
        headPtr->setPrev(nullptr);
    else
        tailPtr = nullptr;

    detachedPtr->setPrev(nullptr);
    detachedPtr->setNext(nullptr);

    --count;
    return detachedPtr;
}

/// Unlink the last node and RETURN it (do not delete it).
/// Use the tail's prev link. Return nullptr if the list is empty.
DoubleNode *DoublyLinkedList::detachLast()
{
    if (tailPtr == nullptr)
        return nullptr;

    DoubleNode *detachedPtr = tailPtr;
    tailPtr = tailPtr->getPrev();

    if (tailPtr != nullptr)
        tailPtr->setNext(nullptr);
    else
        headPtr = nullptr;

    detachedPtr->setPrev(nullptr);
    detachedPtr->setNext(nullptr);

    --count;
    return detachedPtr;
}

/// Find the FIRST node equal to value and unlink it (head, tail, only node
/// or middle node). Return nullptr if not found. Reuse detachFirst/detachLast.
DoubleNode *DoublyLinkedList::detachValue(NodeValue value)
{
    DoubleNode *currentPtr = headPtr;

    while (currentPtr != nullptr)
    {
        if (currentPtr->getValue() == value)
        {
            if (currentPtr == headPtr)
                return detachFirst();

            if (currentPtr == tailPtr)
                return detachLast();

            DoubleNode *prevPtr = currentPtr->getPrev();
            DoubleNode *nextPtr = currentPtr->getNext();

            prevPtr->setNext(nextPtr);
            nextPtr->setPrev(prevPtr);

            currentPtr->setPrev(nullptr);
            currentPtr->setNext(nullptr);

            --count;
            return currentPtr;
        }

        currentPtr = currentPtr->getNext();
    }

    return nullptr;
}

/// Create a node with new and link it in front. Handle the empty list.
void DoublyLinkedList::pushFrontValue(NodeValue value)
{
    DoubleNode *newPtr = new DoubleNode(value);

    newPtr->setNext(headPtr);

    if (headPtr != nullptr)
        headPtr->setPrev(newPtr);
    else
        tailPtr = newPtr;

    headPtr = newPtr;
    ++count;
}

/// Create a node with new and link it at the end. Handle the empty list.
void DoublyLinkedList::pushBackValue(NodeValue value)
{
    DoubleNode *newPtr = new DoubleNode(value);

    newPtr->setPrev(tailPtr);

    if (tailPtr != nullptr)
        tailPtr->setNext(newPtr);
    else
        headPtr = newPtr;

    tailPtr = newPtr;
    ++count;
}

/// Detach the first node, read its value, delete the node, return the value.
/// Empty list -> std::nullopt.
std::optional<NodeValue> DoublyLinkedList::popFrontValue()
{
    DoubleNode *detachedPtr = detachFirst();

    if (detachedPtr == nullptr)
        return std::nullopt;

    NodeValue value = detachedPtr->getValue();

    delete detachedPtr;

    return value;
}

/// Detach the last node, read its value, delete the node, return the value.
/// Empty list -> std::nullopt.
std::optional<NodeValue> DoublyLinkedList::popBackValue()
{
    DoubleNode *detachedPtr = detachLast();

    if (detachedPtr == nullptr)
        return std::nullopt;

    NodeValue value = detachedPtr->getValue();

    delete detachedPtr;

    return value;
}

/// Remove the FIRST node equal to value and free it.
/// Return true if something was removed.
bool DoublyLinkedList::deleteValue(NodeValue value)
{
    DoubleNode *detachedPtr = detachValue(value);

    if (detachedPtr == nullptr)
        return false;

    delete detachedPtr;

    return true;
}

/// Return true if any node holds value.
bool DoublyLinkedList::containsValue(NodeValue value) const
{
    DoubleNode *currentPtr = headPtr;

    while (currentPtr != nullptr)
    {
        if (currentPtr->getValue() == value)
            return true;

        currentPtr = currentPtr->getNext();
    }

    return false;
}

/// Print values head -> tail with std::visit (each followed by a space,
/// then a newline). Return the number of printed values.
int DoublyLinkedList::printForward() const
{
    DoubleNode *currentPtr = headPtr;
    int printed = 0;

    while (currentPtr != nullptr)
    {
        std::visit([](const auto &value) {
            std::cout << value << " ";
        }, currentPtr->getValue());

        ++printed;
        currentPtr = currentPtr->getNext();
    }

    std::cout << std::endl;

    return printed;
}

/// Print values tail -> head using prevPtr. Return the number of printed values.
int DoublyLinkedList::printBackward() const
{
    DoubleNode *currentPtr = tailPtr;
    int printed = 0;

    while (currentPtr != nullptr)
    {
        std::visit([](const auto &value) {
            std::cout << value << " ";
        }, currentPtr->getValue());

        ++printed;
        currentPtr = currentPtr->getPrev();
    }

    std::cout << std::endl;

    return printed;
}

/// Return count.
int DoublyLinkedList::length() const
{
    return count;
}

// ===== BEGIN PART 3 (do not remove this marker) =====
// ============================================================
// PART 3: Class StdDoublyLinkedList
// ============================================================
// Only std::list methods, <algorithm>, iterators and std::visit.
// A loop is allowed ONLY for printing.

/// Which std::list method inserts at the front?
void StdDoublyLinkedList::pushFrontValue(NodeValue value)
{
    data.push_front(value);
}

/// Which std::list method inserts at the back?
void StdDoublyLinkedList::pushBackValue(NodeValue value)
{
    data.push_back(value);
}

/// Read the front element, remove it, return it. Empty -> std::nullopt.
std::optional<NodeValue> StdDoublyLinkedList::popFrontValue()
{
    if (data.empty())
        return std::nullopt;

    NodeValue value = data.front();
    data.pop_front();

    return value;
}

/// Read the back element, remove it, return it. Empty -> std::nullopt.
std::optional<NodeValue> StdDoublyLinkedList::popBackValue()
{
    if (data.empty())
        return std::nullopt;

    NodeValue value = data.back();
    data.pop_back();

    return value;
}

/// Remove only the FIRST element equal to value. Return true if removed.
bool StdDoublyLinkedList::deleteValue(NodeValue value)
{
    auto it = std::find(data.begin(), data.end(), value);

    if (it == data.end())
        return false;

    data.erase(it);

    return true;
}

/// Search without writing your own loop.
bool StdDoublyLinkedList::containsValue(NodeValue value) const
{
    return std::find(data.begin(), data.end(), value) != data.end();
}

/// Print head -> tail (same format as Part 2). Return the number of values.
int StdDoublyLinkedList::printForward() const
{
    for (const auto &value : data)
    {
        std::visit([](const auto &item) {
            std::cout << item << " ";
        }, value);
    }

    std::cout << std::endl;

    return static_cast<int>(data.size());
}

/// Print tail -> head (same format as Part 2). Return the number of values.
int StdDoublyLinkedList::printBackward() const
{
    for (auto it = data.rbegin(); it != data.rend(); ++it)
    {
        std::visit([](const auto &item) {
            std::cout << item << " ";
        }, *it);
    }

    std::cout << std::endl;

    return static_cast<int>(data.size());
}

/// size() returns size_t, length() returns int.
int StdDoublyLinkedList::length() const
{
    return static_cast<int>(data.size());
}
// ===== END PART 3 (do not remove this marker) =====
