#ifndef CODE_HPP
#define CODE_HPP

#include <list>
#include <optional>
#include <string>
#include <variant>

// ============================================================
// Shared type
// ============================================================

/// The value stored in a node: an int, a double or a std::string.
/// NOTE: NodeValue{1} and NodeValue{1.0} are NOT equal. A variant compares
/// the active type first, and only then the value.
using NodeValue = std::variant<int, double, std::string>;

// ============================================================
// PART 1: Class DoubleNode
// ============================================================

/// A node of a doubly linked list. It is a class, not a struct.
/// Every field is declared separately, with its own access modifier.
/// A node knows NOTHING about the list: it does not print, search or delete.
///
/// YOUR TASK (in src/code.cpp):
/// - Constructor: initialize ALL THREE fields using a member initializer list.
///   'value' gets 'newValue'. A new node has no neighbours, so 'prevPtr'
///   and 'nextPtr' are nullptr.
/// - getValue, getPrev, getNext: const getters, return the matching field.
/// - setPrev, setNext: store the given pointer in the matching field.
class DoubleNode
{
   private: NodeValue   value;
   private: DoubleNode *prevPtr;
   private: DoubleNode *nextPtr;

   public:  explicit DoubleNode(NodeValue newValue);

   public:  NodeValue   getValue() const;
   public:  DoubleNode *getPrev() const;
   public:  DoubleNode *getNext() const;

   public:  void setPrev(DoubleNode *newPrevPtr);
   public:  void setNext(DoubleNode *newNextPtr);

   // given: copying a node is forbidden (explained in a later lecture)
   public:  DoubleNode(const DoubleNode &) = delete;
   public:  DoubleNode &operator=(const DoubleNode &) = delete;
};

// ============================================================
// PART 2: Class DoublyLinkedList (you own the nodes)
// ============================================================

/// A doubly linked list that OWNS its nodes (composition).
///
/// COMPOSITION RULE: the outside world works only with VALUES.
/// No public method may take, return or expose a DoubleNode*.
/// Every 'new' and every 'delete' of a node happens INSIDE this class.
///
/// YOUR TASK (in src/code.cpp): implement every method below.
///
/// Private building blocks. The caller of a detach* method OWNS the returned
/// node and must delete it. A detach* method never deletes anything itself.
///
///  detachFirst : Unlink the first node and RETURN it (do not delete it).
///                Fix headPtr, tailPtr and count. Clear the node's own prevPtr
///                and nextPtr. Return nullptr if the list is empty.
///                (If the list had one node, both headPtr and tailPtr become
///                nullptr. Otherwise the new head's prev link becomes nullptr.)
///  detachLast  : Same for the last node. Use the tail's prev link, so no
///                walking through the list is needed.
///  detachValue : Find the FIRST node equal to 'value' and unlink it. It can be
///                the head, the tail, the only node or a middle node. Return
///                nullptr if not found. Reuse detachFirst and detachLast
///                where you can. A middle node needs TWO link repairs.
///
/// Public methods:
///
///  DoublyLinkedList()  : Empty list: headPtr and tailPtr are nullptr, count is 0.
///  ~DoublyLinkedList() : Delete ALL nodes (RAII). Save the next pointer BEFORE
///                        you delete a node. Never read a node after delete.
///  pushFrontValue      : Create a node with 'new' and link it in front of the
///                        list. Handle the EMPTY list (the new node is both head
///                        and tail). Increment count.
///  pushBackValue       : Same, at the end of the list.
///  popFrontValue       : Detach the first node, read its value, delete the node,
///                        return the value. Empty list -> return std::nullopt.
///  popBackValue        : Same, for the last node.
///  deleteValue         : Remove the FIRST node equal to 'value' and free it.
///                        Return true if something was removed, false otherwise.
///  containsValue       : Return true if any node holds 'value'.
///  printForward        : Print values from head to tail to std::cout (use
///                        std::visit), each followed by a space, then one
///                        newline. Return the number of printed values.
///  printBackward       : Same, from tail to head, following prevPtr.
///  length              : Return count.
class DoublyLinkedList
{
   private: DoubleNode *headPtr;
   private: DoubleNode *tailPtr;
   private: int         count;

   // internal building blocks: the caller never sees a node
   private: DoubleNode *detachFirst();
   private: DoubleNode *detachLast();
   private: DoubleNode *detachValue(NodeValue value);

   public:  DoublyLinkedList();
   public:  ~DoublyLinkedList();

   public:  void pushFrontValue(NodeValue value);
   public:  void pushBackValue(NodeValue value);

   public:  std::optional<NodeValue> popFrontValue();
   public:  std::optional<NodeValue> popBackValue();
   public:  bool deleteValue(NodeValue value);

   public:  bool containsValue(NodeValue value) const;
   public:  int  printForward() const;
   public:  int  printBackward() const;
   public:  int  length() const;

   // given: copying a list is forbidden
   public:  DoublyLinkedList(const DoublyLinkedList &) = delete;
   public:  DoublyLinkedList &operator=(const DoublyLinkedList &) = delete;
};

// ============================================================
// PART 3: Class StdDoublyLinkedList (a wrapper around std::list)
// ============================================================

/// A thin wrapper that holds ONE std::list and behaves EXACTLY like
/// DoublyLinkedList: the same calls give the same results.
/// There is no constructor, no destructor and no detach* here: std::list
/// cleans up after itself, the compiler-generated versions are enough.
///
/// YOUR TASK (in src/code.cpp, between the BEGIN PART 3 / END PART 3 markers):
/// implement every method in a FEW LINES, built from library calls.
/// Read cppreference.com to find the right tool for each method.
///
///  pushFrontValue, pushBackValue : insert at either end of 'data'.
///  popFrontValue, popBackValue   : read the end element and remove it.
///                                  An EMPTY list must return std::nullopt
///                                  (front() and back() on an empty list are
///                                  undefined behavior!).
///  deleteValue   : remove only the FIRST element equal to 'value'.
///                  Return true if something was removed.
///                  (Careful: one of the std::list tools removes ALL matches.)
///  containsValue : search WITHOUT writing your own loop (<algorithm>).
///  printForward  : print head to tail, same format as in Part 2. Return count.
///  printBackward : print tail to head (think about reverse iterators).
///  length        : size() returns size_t, length() returns int: static_cast.
///
/// FORBIDDEN in the Part 3 section of src/code.cpp: new, delete, DoubleNode,
/// any pointer variable (names containing "Ptr"), and your own while/for loops
/// that SEARCH or REMOVE. A loop is allowed ONLY for printing. CI checks it.
class StdDoublyLinkedList
{
   private: std::list<NodeValue> data;

   public:  void pushFrontValue(NodeValue value);
   public:  void pushBackValue(NodeValue value);

   public:  std::optional<NodeValue> popFrontValue();
   public:  std::optional<NodeValue> popBackValue();
   public:  bool deleteValue(NodeValue value);

   public:  bool containsValue(NodeValue value) const;
   public:  int  printForward() const;
   public:  int  printBackward() const;
   public:  int  length() const;
};

#endif
