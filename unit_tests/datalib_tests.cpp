#include <gtest/gtest.h>

extern "C" {
#include "args.h"
#include "data.h"
#include "read_data.h"
#include "retcodes.h"
}
user_record tests[3] = {{0, 10, 1.23},
                        {1, 20, 1.8},
                        {2, 5,  4.22}};

TEST(Create, create_record_one_valid) {
    int id = 0;
    size_t votes = 10;
    float rating = 0.8;

    user_record *record = create_record(id, rating, votes);
    ASSERT_NE(record, nullptr);
    EXPECT_EQ(record->id, id);
    EXPECT_EQ(record->votes, votes);
    EXPECT_EQ(record->rating_nan, NAN);
}

TEST(Create, create_record_one_invalid_id) {
    int id = -1;
    size_t votes = 10;
    float rating = 0.8;

    user_record *record = create_record(id, rating, votes);
    ASSERT_EQ(record, nullptr);
}

TEST(Create, create_record_one_invalid_rating) {
    int id = 1;
    size_t votes = 10;
    float rating = -0.8;

    user_record *record = create_record(id, rating, votes);
    ASSERT_EQ(record, nullptr);
}

TEST(Create, create_records_valid) {
    records_t *records = create_records();
    ASSERT_NE(records, nullptr);
    size_t cnt_records = 3;
    int rc = init_records(records, cnt_records);
    EXPECT_EQ(rc, OK);
    EXPECT_EQ(records->size, cnt_records);
    EXPECT_NE(records->arr, nullptr);

    user_record *tmp = nullptr;
    for (size_t i = 0; i < cnt_records; ++i) {
        tmp = create_record(tests[i].id, tests[i].rating, tests[i].votes);
        EXPECT_NE(tmp, nullptr);
        EXPECT_EQ(tmp->id, tests[i].id);
        EXPECT_EQ(tmp->votes, tests[i].votes);
        EXPECT_EQ(tmp->rating, tests[i].rating);
        rc = add_record(records, tmp);
        EXPECT_EQ(rc, OK);
        EXPECT_EQ(records->count, i + 1);
    }
    free_records(records);
}

TEST(Init, init_record_invalid_records) {
    records_t *records = nullptr;
    retcodes rc = init_records(nullptr, 1);
    ASSERT_NE(rc, OK);
    ASSERT_EQ(records, nullptr);
    free(records);
}

TEST(Get, get_count_nan_test) {
    user_record tests[3] = {{0, 10, 0.8},
                            {1, 20, 0.7},
                            {2, 5,  0.2}};
    records_t *records = create_records();
    ASSERT_NE(records, nullptr);
    size_t cnt_records = 3;
    int rc = init_records(records, cnt_records);
    EXPECT_EQ(rc, OK);
    EXPECT_EQ(records->size, cnt_records);
    EXPECT_NE(records->arr, nullptr);

    user_record *tmp = nullptr;
    for (size_t i = 0; i < cnt_records; ++i) {
        tmp = create_record(tests[i].id, tests[i].rating, tests[i].votes);
        EXPECT_NE(tmp, nullptr);
        EXPECT_EQ(tmp->id, tests[i].id);
        EXPECT_EQ(tmp->votes, tests[i].votes);
        EXPECT_EQ(tmp->rating, NAN);
        rc = add_record(records, tmp);
        EXPECT_EQ(rc, OK);
        EXPECT_EQ(records->count, i + 1);
    }
    size_t res = 0;
    size_t exp_res = 3;
    rc = get_count_nan(records->arr, cnt_records, &res);
    EXPECT_EQ(rc, OK);
    EXPECT_EQ(res, exp_res);
    free_records(records);

}

TEST(Create, create_records_invalid) {
    records_t *records = create_records();
    ASSERT_NE(records, nullptr);
    size_t cnt_records = 3;
    int rc = init_records(records, cnt_records);
    EXPECT_EQ(rc, OK);
    EXPECT_EQ(records->size, cnt_records);
    EXPECT_NE(records->arr, nullptr);

    user_record *tmp = nullptr;
    for (size_t i = 0; i < cnt_records; ++i) {
        tmp = create_record(tests[i].id, tests[i].rating, tests[i].votes);
        EXPECT_NE(tmp, nullptr);
        EXPECT_EQ(tmp->id, tests[i].id);
        EXPECT_EQ(tmp->votes, tests[i].votes);
        EXPECT_EQ(tmp->rating, tests[i].rating);
        rc = add_record(records, tmp);
        EXPECT_EQ(rc, OK);
        EXPECT_EQ(records->count, i + 1);
    }
    free_records(records);
}
