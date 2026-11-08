#ifndef UNITY_H
#define UNITY_H
#include "unity.h"
#endif

#include "code.hpp"
#include <iostream>

// ============================================================
// PART 2 Tests: DoublyLinkedList
// ============================================================

/// Create a DoublyLinkedList. Verify length() is 0 on a new list.
void test_new_list_is_empty(void)
{
    DoublyLinkedList list;

    int len = list.length();

    TEST_ASSERT_EQUAL_INT(0, len);
}

/// Create a DoublyLinkedList. Call pushFrontValue and pushBackValue.
/// Verify length() is 2.
void test_push_increases_length(void)
{
    DoublyLinkedList list;

    list.pushFrontValue(10);
    list.pushBackValue(20);

    int len = list.length();

    TEST_ASSERT_EQUAL_INT(2, len);
}

/// Create an EMPTY DoublyLinkedList.
/// Verify popFrontValue() and popBackValue() both have NO value (has_value() is false).
void test_pop_on_empty_list(void)
{
    DoublyLinkedList list;

    std::optional<NodeValue> front = list.popFrontValue();
    std::optional<NodeValue> back = list.popBackValue();

    bool frontEmpty = front.has_value();
    bool backEmpty = back.has_value();

    TEST_ASSERT_FALSE(frontEmpty);
    TEST_ASSERT_FALSE(backEmpty);
}

/// Push 1, 2, 3 with pushBackValue.
/// Verify popBackValue() gives 3, then popFrontValue() gives 1, then length() is 1.
void test_pop_order(void)
{
    DoublyLinkedList list;
    list.pushBackValue(1);
    list.pushBackValue(2);
    list.pushBackValue(3);

    std::optional<NodeValue> back = list.popBackValue();
    std::optional<NodeValue> front = list.popFrontValue();

    int backValue = back.has_value() ? std::get<int>(back.value()) : 0;
    int frontValue = front.has_value() ? std::get<int>(front.value()) : 0;
    int len = list.length();

    TEST_ASSERT_EQUAL_INT(3, backValue);
    TEST_ASSERT_EQUAL_INT(1, frontValue);
    TEST_ASSERT_EQUAL_INT(1, len);
}

/// Push one value, then call deleteValue with a value that is NOT in the list.
/// Verify it returns false and length() does not change.
void test_delete_value_not_found(void)
{
    DoublyLinkedList list;
    list.pushBackValue(10);

    bool removed = list.deleteValue(20);
    int len = list.length();

    TEST_ASSERT_FALSE(removed);
    TEST_ASSERT_EQUAL_INT(1, len);
}

/// Push 1, 2, 3 with pushBackValue. Call deleteValue(2).
/// Verify popBackValue() gives 3 and the next popBackValue() gives 1.
/// (popBackValue follows prevPtr: this fails if you forgot to repair the backward link.)
void test_delete_middle_keeps_links(void)
{
    DoublyLinkedList list;
    list.pushBackValue(1);
    list.pushBackValue(2);
    list.pushBackValue(3);

    list.deleteValue(2);

    std::optional<NodeValue> back = list.popBackValue();
    std::optional<NodeValue> nextBack = list.popBackValue();

    int backValue = back.has_value() ? std::get<int>(back.value()) : 0;
    int nextBackValue = nextBack.has_value() ? std::get<int>(nextBack.value()) : 0;

    TEST_ASSERT_EQUAL_INT(3, backValue);
    TEST_ASSERT_EQUAL_INT(1, nextBackValue);
}

// ============================================================
// PART 3 Tests: StdDoublyLinkedList
// ============================================================

/// Push 1, 2, 1 with pushBackValue. Call deleteValue(NodeValue{1}).
/// Verify length() is 2 and popFrontValue() gives 2 (only the FIRST 1 was removed).
void test_std_delete_only_first(void)
{
    StdDoublyLinkedList list;
    list.pushBackValue(1);
    list.pushBackValue(2);
    list.pushBackValue(1);

    list.deleteValue(1);

    int len = list.length();
    std::optional<NodeValue> front = list.popFrontValue();
    int frontValue = front.has_value() ? std::get<int>(front.value()) : 0;

    TEST_ASSERT_EQUAL_INT(2, len);
    TEST_ASSERT_EQUAL_INT(2, frontValue);
}

/// Create an EMPTY StdDoublyLinkedList.
/// Verify popFrontValue() and popBackValue() have NO value and do not crash.
void test_std_pop_on_empty_list(void)
{
    StdDoublyLinkedList list;

    std::optional<NodeValue> front = list.popFrontValue();
    std::optional<NodeValue> back = list.popBackValue();

    bool frontEmpty = front.has_value();
    bool backEmpty = back.has_value();

    TEST_ASSERT_FALSE(frontEmpty);
    TEST_ASSERT_FALSE(backEmpty);
}
