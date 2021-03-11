#include "gtest/gtest.h"

extern "C" {
    #include "input.h"
    #include "grouping.h"
    #include "packing.h"
    #include "retcodes.h"
    #include <string.h>
}

TEST(Create, create_table_valid) {
    table *tb = create_table();
    ASSERT_NE(nullptr, tb);
    free(tb);
}
TEST(Init, init_table_invalid_ptr) {
    ASSERT_EQ(ARG_ERR,init_table(nullptr, 'a'));
}
TEST(Init, init_table_valid_data) {
    table *tb = create_table();
    ASSERT_NE(tb, nullptr);
    int size = 10;
    int rc = init_table(tb, size);
    ASSERT_EQ(rc, EXIT_SUCCESS);
    ASSERT_NE(nullptr,tb);
    ASSERT_EQ(tb->capacity, size);
    ASSERT_EQ(tb->size, 0);
    free(tb->list);
    free(tb);
}
TEST(Create, create_container_invalid_type_str) {
    container *res = create_container(nullptr, 0, 0);
    ASSERT_EQ(res, nullptr);
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
    ASSERT_NE(res, nullptr);
    ASSERT_EQ(res->type, type);
    ASSERT_EQ(res->weight, weight);
    ASSERT_EQ(res->max_capacity, capacity);
    free_container(res);
}

TEST(Fill, fill_table_invalid_args) {
    ASSERT_EQ(fill_table(nullptr), ARG_ERR);
}

TEST(Grouping, group_data_invalid_args) {
    ASSERT_EQ(group_by_type(nullptr, nullptr), ARG_ERR);
}

TEST(Grouping, group_data_invalid_arg_first) {
    table* tb = create_table();
    ASSERT_NE(tb, nullptr);
    ASSERT_EQ(group_by_type(nullptr, tb), ARG_ERR);
}

TEST(Grouping, group_data_invalid_arg_second) {
    table* tb = create_table();
    ASSERT_NE(tb, nullptr);
    ASSERT_EQ(group_by_type(tb, nullptr), ARG_ERR);
}
TEST(Grouping, group_data_one_record) {
    table *tb = create_table();
    ASSERT_NE(tb, nullptr);
    int size = 1;
    int rc = init_table(tb, size);
    ASSERT_EQ(rc, EXIT_SUCCESS);
    ASSERT_EQ(tb->capacity, size);
    ASSERT_NE(tb->list, nullptr);
    char *type = strdup("box");
    ASSERT_NE(type, nullptr);
    int weight = 10;
    int capacity = 20;
    tb->list[0] = create_container(type, weight, capacity);
    tb->size = size;
    ASSERT_NE(tb->list[0], nullptr);
    table *tb_group = create_table();
    ASSERT_NE(tb_group, nullptr);
    rc = group_by_type(tb, tb_group);
    ASSERT_EQ(rc, EXIT_SUCCESS);
    EXPECT_EQ(tb_group->size, tb->size);
    ASSERT_STREQ(tb_group->list[0]->type, tb->list[0]->type);
    ASSERT_EQ(tb_group->list[0]->weight, tb->list[0]->weight);
    ASSERT_EQ(tb_group->list[0]->max_capacity, tb->list[0]->max_capacity);
    free_table(tb);
    free_table(tb_group);
}
TEST(Grouping, without_group_data_three_multy) {
    table *tb = create_table();
    ASSERT_NE(tb, nullptr);
    int size = 3;
    int rc = init_table(tb, size);
    ASSERT_EQ(rc, EXIT_SUCCESS);
    ASSERT_EQ(tb->capacity, size);
    ASSERT_NE(tb->list, nullptr);

    char *type = strdup("box");
    char *type_two = strdup("coffer");
    char *type_three = strdup("case");

    ASSERT_NE(type, nullptr);
    ASSERT_NE(type_two, nullptr);
    ASSERT_NE(type_three, nullptr);

    int weight = 10;
    int capacity = 20;

    tb->list[0] = create_container(type, weight, capacity);
    tb->list[1] = create_container(type_two, weight, capacity);
    tb->list[2] = create_container(type_three, weight, capacity);

    tb->size = size;
    ASSERT_NE(tb->list[0], nullptr);
    ASSERT_NE(tb->list[1], nullptr);
    ASSERT_NE(tb->list[2], nullptr);

    table *tb_group = create_table();
    ASSERT_NE(tb_group, nullptr);
    rc = group_by_type(tb, tb_group);
    ASSERT_EQ(rc, EXIT_SUCCESS);
    EXPECT_EQ(tb_group->size, tb->size);
    ASSERT_STREQ(tb_group->list[0]->type, tb->list[0]->type);
    ASSERT_EQ(tb_group->list[0]->weight, tb->list[0]->weight);
    ASSERT_EQ(tb_group->list[0]->max_capacity, tb->list[0]->max_capacity);

    ASSERT_STREQ(tb_group->list[1]->type, tb->list[1]->type);
    ASSERT_EQ(tb_group->list[1]->weight, tb->list[1]->weight);
    ASSERT_EQ(tb_group->list[1]->max_capacity, tb->list[1]->max_capacity);

    ASSERT_STREQ(tb_group->list[2]->type, tb->list[2]->type);
    ASSERT_EQ(tb_group->list[2]->weight, tb->list[2]->weight);
    ASSERT_EQ(tb_group->list[2]->max_capacity, tb->list[2]->max_capacity);

    free_table(tb);
    free_table(tb_group);
}
TEST(Grouping, group_with_sort_and_integration) {
    table *tb = create_table();
    ASSERT_NE(tb, nullptr);
    int size = 3;
    int rc = init_table(tb, size);
    ASSERT_EQ(rc, EXIT_SUCCESS);
    ASSERT_EQ(tb->capacity, size);
    ASSERT_NE(tb->list, nullptr);

    char *type = strdup("box");
    char *type_two = strdup("box");
    char *type_three = strdup("case");

    ASSERT_NE(type, nullptr);
    ASSERT_NE(type_two, nullptr);
    ASSERT_NE(type_three, nullptr);

    int weight = 10;
    int capacity = 20;

    tb->list[0] = create_container(type, weight, capacity);
    tb->list[1] = create_container(type_two, weight, capacity);
    tb->list[2] = create_container(type_three, weight, capacity);

    tb->size = size;
    ASSERT_NE(tb->list[0], nullptr);
    ASSERT_NE(tb->list[1], nullptr);
    ASSERT_NE(tb->list[2], nullptr);

    table *tb_group = create_table();
    ASSERT_NE(tb_group, nullptr);
    rc = group_by_type(tb, tb_group);
    ASSERT_EQ(rc, EXIT_SUCCESS);
    EXPECT_EQ(tb_group->size, tb->size - 1);

    ASSERT_STREQ(tb_group->list[1]->type, tb->list[0]->type);
    ASSERT_EQ(tb_group->list[1]->weight, tb->list[0]->weight * 2);
    ASSERT_EQ(tb_group->list[1]->max_capacity, tb->list[0]->max_capacity * 2);

    ASSERT_STREQ(tb_group->list[0]->type, tb->list[2]->type);
    ASSERT_EQ(tb_group->list[0]->weight, tb->list[2]->weight);
    ASSERT_EQ(tb_group->list[0]->max_capacity, tb->list[2]->max_capacity);

    free_table(tb);
    free_table(tb_group);
}
TEST(Grouping, group_with_sort_all_in_one) {
    table *tb = create_table();
    ASSERT_NE(tb, nullptr);
    int size = 3;
    int rc = init_table(tb, size);
    ASSERT_EQ(rc, EXIT_SUCCESS);
    ASSERT_EQ(tb->capacity, size);
    ASSERT_NE(tb->list, nullptr);

    char *type = strdup("box");
    char *type_two = strdup("box");
    char *type_three = strdup("box");

    ASSERT_NE(type, nullptr);
    ASSERT_NE(type_two, nullptr);
    ASSERT_NE(type_three, nullptr);

    int weight = 10;
    int capacity = 20;

    tb->list[0] = create_container(type, weight, capacity);
    tb->list[1] = create_container(type_two, weight, capacity);
    tb->list[2] = create_container(type_three, weight, capacity);

    tb->size = size;
    ASSERT_NE(tb->list[0], nullptr);
    ASSERT_NE(tb->list[1], nullptr);
    ASSERT_NE(tb->list[2], nullptr);

    table *tb_group = create_table();
    ASSERT_NE(tb_group, nullptr);
    rc = group_by_type(tb, tb_group);

    ASSERT_EQ(rc, EXIT_SUCCESS);
    EXPECT_EQ(tb_group->size, tb->size - 2);
    ASSERT_STREQ(tb_group->list[0]->type, tb->list[0]->type);
    ASSERT_EQ(tb_group->list[0]->weight, tb->list[0]->weight * 3);
    ASSERT_EQ(tb_group->list[0]->max_capacity, tb->list[0]->max_capacity * 3);

    free_table(tb);
    free_table(tb_group);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}