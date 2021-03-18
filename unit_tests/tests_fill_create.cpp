#include "gtest/gtest.h"

extern "C" {
#include <string.h>
#include "read_write.h"
#include "grouping.h"
#include "packing.h"
#include "retcodes.h"
}

TEST(Create, create_table_valid) {
    table *tb = create_table();
    EXPECT_NE(nullptr, tb);
    free(tb);
}

TEST(Init, init_table_invalid_ptr) {
    ASSERT_EQ(ARG_ERR, init_table(nullptr, 'a'));
}

TEST(Init, init_table_valid_data) {
    table *tb = create_table();
    EXPECT_NE(tb, nullptr);
    int size = 10;
    int rc = init_table(tb, size);
    EXPECT_EQ(rc, EXIT_SUCCESS);
    EXPECT_NE(nullptr, tb);
    EXPECT_EQ(tb->capacity, size);
    EXPECT_EQ(tb->size, 0);
    free(tb->list);
    free(tb);
}

TEST(Create, create_container_invalid_type_str) {
    container *res = create_container(nullptr, 0, 0);
    ASSERT_EQ(res,
              nullptr);
}

TEST(Create, create_container_invalid_weight) {
    char type[] = "box";
    container *res = create_container(type, -10, 10);
    ASSERT_EQ(res, nullptr);
}

TEST(Create, create_container_invalid_capacity) {
    char type[] = "box";
    container *res = create_container(type, 10, -10);
    ASSERT_EQ(res, nullptr);
}

TEST(Create, create_container_valid_data) {
    char type[] = "box";
    int weight = 10;
    int capacity = 20;

    container *res = create_container(type, weight, capacity);
    EXPECT_NE(res, nullptr);
    EXPECT_EQ(res->type, type);
    EXPECT_EQ(res->weight, weight);
    EXPECT_EQ(res->max_capacity, capacity);
    free_container(res);
}

TEST(Fill, fill_table_invalid_args) {
    ASSERT_EQ(fill_table(nullptr, nullptr, nullptr), ARG_ERR);
}