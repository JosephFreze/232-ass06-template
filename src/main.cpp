#include <stdio.h>

#ifndef UNITY_H
#define UNITY_H
#include "unity.h"
#endif

// ============================================================
// Test Declarations — implemented in tests.cpp
// ============================================================

// PART 2: DoublyLinkedList
void test_new_list_is_empty(void);
void test_push_increases_length(void);
void test_pop_on_empty_list(void);
void test_pop_order(void);
void test_delete_value_not_found(void);
void test_delete_middle_keeps_links(void);

// PART 3: StdDoublyLinkedList
void test_std_delete_only_first(void);
void test_std_pop_on_empty_list(void);

// ============================================================
// Required by Unity Framework
// ============================================================
void setUp(void)    {}
void tearDown(void) {}

// ============================================================
// Main Test Runner
// ============================================================
int main(void)
{
    UNITY_BEGIN();

    // ========== PART 2 ==========

    RUN_TEST(test_new_list_is_empty);
    RUN_TEST(test_push_increases_length);
    RUN_TEST(test_pop_on_empty_list);
    RUN_TEST(test_pop_order);
    RUN_TEST(test_delete_value_not_found);
    RUN_TEST(test_delete_middle_keeps_links);

    // ========== PART 3 ==========
    
    RUN_TEST(test_std_delete_only_first);
    RUN_TEST(test_std_pop_on_empty_list);

    int result = UNITY_END();
    return result;
}
