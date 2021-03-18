#include "gtest/gtest.h"

extern "C" {
    #include "grouping.h"
    #include "retcodes.h"
}

TEST(Grouping, group_data_invalid_args) {
    EXPECT_EQ(group_by_name(nullptr, nullptr), ARG_ERR);
}

TEST(Grouping, group_data_invalid_arg_first) {
    table *tb = create_table();
    EXPECT_NE(tb, nullptr);
    EXPECT_EQ(group_by_name(nullptr, tb), ARG_ERR);
    free(tb);
}

TEST(Grouping, group_data_invalid_arg_second) {
    table *tb = create_table();
    EXPECT_NE(tb, nullptr);
    EXPECT_EQ(group_by_name(tb, nullptr), ARG_ERR);
    free(tb);
}

TEST(Grouping, group_data_one_record) {
    table *tb = create_table();
    EXPECT_NE(tb, nullptr);
    int size = 1;
    int rc = init_table(tb, size);
    EXPECT_EQ(rc, EXIT_SUCCESS);
    EXPECT_EQ(tb->capacity, size);
    EXPECT_NE(tb->list, nullptr);
    char *type = strdup("box");
    EXPECT_NE(type, nullptr);
    int weight = 10;
    int capacity = 20;
    tb->list[0] = create_container(type, weight, capacity);
    tb->size = size;
    EXPECT_NE(tb->list[0], nullptr);
    table *tb_group = create_table();
    EXPECT_NE(tb_group, nullptr);
    rc = group_by_name(tb, tb_group);
    EXPECT_EQ(rc, EXIT_SUCCESS);
    EXPECT_EQ(tb_group->size, tb->size);
    EXPECT_STREQ(tb_group->list[0]->type, tb->list[0]->type);
    EXPECT_EQ(tb_group->list[0]->weight, tb->list[0]->weight);
    EXPECT_EQ(tb_group->list[0]->max_capacity, tb->list[0]->max_capacity);
    free_table(tb);
    free_table(tb_group);
}

TEST(Grouping, without_group_data_three_multy) {
    table *tb = create_table();
    EXPECT_NE(tb, nullptr);
    int size = 3;
    int rc = init_table(tb, size);
    EXPECT_EQ(rc, EXIT_SUCCESS);
    EXPECT_EQ(tb->capacity, size);
    EXPECT_NE(tb->list, nullptr);

    char *type = strdup("box");
    char *type_two = strdup("coffer");
    char *type_three = strdup("case");

    EXPECT_NE(type, nullptr);
    EXPECT_NE(type_two, nullptr);
    EXPECT_NE(type_three, nullptr);

    int weight = 10;
    int capacity = 20;

    tb->list[0] = create_container(type, weight, capacity);
    tb->list[1] = create_container(type_two, weight, capacity);
    tb->list[2] = create_container(type_three, weight, capacity);

    tb->size = size;
    EXPECT_NE(tb->list[0], nullptr);
    EXPECT_NE(tb->list[1], nullptr);
    EXPECT_NE(tb->list[2], nullptr);

    table *tb_group = create_table();
    EXPECT_NE(tb_group, nullptr);
    rc = group_by_name(tb, tb_group);
    EXPECT_EQ(rc, EXIT_SUCCESS);
    EXPECT_EQ(tb_group->size, tb->size);
    EXPECT_STREQ(tb_group->list[0]->type, tb->list[0]->type);
    EXPECT_EQ(tb_group->list[0]->weight, tb->list[0]->weight);
    EXPECT_EQ(tb_group->list[0]->max_capacity, tb->list[0]->max_capacity);

    EXPECT_STREQ(tb_group->list[1]->type, tb->list[1]->type);
    EXPECT_EQ(tb_group->list[1]->weight, tb->list[1]->weight);
    EXPECT_EQ(tb_group->list[1]->max_capacity, tb->list[1]->max_capacity);

    EXPECT_STREQ(tb_group->list[2]->type, tb->list[2]->type);
    EXPECT_EQ(tb_group->list[2]->weight, tb->list[2]->weight);
    EXPECT_EQ(tb_group->list[2]->max_capacity, tb->list[2]->max_capacity);

    free_table(tb);
    free_table(tb_group);
}

TEST(Grouping, group_with_sort_and_integration) {
    table *tb = create_table();
    EXPECT_NE(tb, nullptr);
    int size = 3;
    int rc = init_table(tb, size);
    EXPECT_EQ(rc, EXIT_SUCCESS);
    EXPECT_EQ(tb->capacity, size);
    EXPECT_NE(tb->list, nullptr);

    char *type = strdup("box");
    char *type_two = strdup("box");
    char *type_three = strdup("case");

    EXPECT_NE(type, nullptr);
    EXPECT_NE(type_two, nullptr);
    EXPECT_NE(type_three, nullptr);

    int weight = 10;
    int capacity = 20;

    tb->list[0] = create_container(type, weight, capacity);
    tb->list[1] = create_container(type_two, weight, capacity);
    tb->list[2] = create_container(type_three, weight, capacity);

    tb->size = size;
    EXPECT_NE(tb->list[0], nullptr);
    EXPECT_NE(tb->list[1], nullptr);
    EXPECT_NE(tb->list[2], nullptr);

    table *tb_group = create_table();
    EXPECT_NE(tb_group, nullptr);
    rc = group_by_name(tb, tb_group);
    EXPECT_EQ(rc, EXIT_SUCCESS);
    EXPECT_EQ(tb_group->size, tb->size - 1);

    EXPECT_STREQ(tb_group->list[1]->type, tb->list[0]->type);
    EXPECT_EQ(tb_group->list[1]->weight, tb->list[0]->weight * 2);
    EXPECT_EQ(tb_group->list[1]->max_capacity, tb->list[0]->max_capacity * 2);

    EXPECT_STREQ(tb_group->list[0]->type, tb->list[2]->type);
    EXPECT_EQ(tb_group->list[0]->weight, tb->list[2]->weight);
    EXPECT_EQ(tb_group->list[0]->max_capacity, tb->list[2]->max_capacity);

    free_table(tb);
    free_table(tb_group);
}

TEST(Grouping, group_with_sort_all_in_one) {
    table *tb = create_table();
    EXPECT_NE(tb, nullptr);
    int size = 3;
    int rc = init_table(tb, size);
    EXPECT_EQ(rc, EXIT_SUCCESS);
    EXPECT_EQ(tb->capacity, size);
    EXPECT_NE(tb->list, nullptr);

    char *type = strdup("box");
    char *type_two = strdup("box");
    char *type_three = strdup("box");

    EXPECT_NE(type, nullptr);
    EXPECT_NE(type_two, nullptr);
    EXPECT_NE(type_three, nullptr);

    int weight = 10;
    int capacity = 20;

    tb->list[0] = create_container(type, weight, capacity);
    tb->list[1] = create_container(type_two, weight, capacity);
    tb->list[2] = create_container(type_three, weight, capacity);

    tb->size = size;
    EXPECT_NE(tb->list[0], nullptr);
    EXPECT_NE(tb->list[1], nullptr);
    EXPECT_NE(tb->list[2], nullptr);

    table *tb_group = create_table();
    EXPECT_NE(tb_group, nullptr);
    rc = group_by_name(tb, tb_group);

    EXPECT_EQ(rc, EXIT_SUCCESS);
    EXPECT_EQ(tb_group->size, tb->size - 2);
    EXPECT_STREQ(tb_group->list[0]->type, tb->list[0]->type);
    EXPECT_EQ(tb_group->list[0]->weight, tb->list[0]->weight * 3);
    EXPECT_EQ(tb_group->list[0]->max_capacity, tb->list[0]->max_capacity * 3);

    free_table(tb);
    free_table(tb_group);
}
