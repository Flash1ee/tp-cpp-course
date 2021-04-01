#include "fixtures_tests.hpp"
#include <gtest/gtest.h>

extern "C" {
#include "args.h"
#include "worker.h"
}

class DefaultLib : public DataFixture {
public:
    args_t *args = nullptr;
    worker_t usage_worker = nullptr;

    DefaultLib() {
        args = init_args();
        args->filename = strdup(filename);
        args->streams = 4;
        args->mode = SINGLE;

        usage_worker = worker;
    }

    ~DefaultLib() {
        free_args(args);
    }
};

class DefaultDataALlZeroes : public DefaultLib {
public:
    DefaultDataALlZeroes() {
        data = "10\n"
               "0 5 0.446\n"
               "1 79 0.24\n"
               "2 107 0.741\n"
               "3 122 0\n"
               "4 31 0.094\n"
               "5 12 0.696\n"
               "6 28 0.972\n"
               "7 73 0.289\n"
               "8 41 0.004\n"
               "9 102 0.084\n";
        answer = 10;
    }
};

TEST_F(DefaultLib, correct_test_single_process_common) {
    std::size_t received = 0;
    retcodes rc = usage_worker(&received, args);
    EXPECT_EQ(rc, OK);
    EXPECT_EQ(received, answer);
}

TEST_F(DefaultLib, correct_test_single_process_empty_file) {
    std::size_t received = 0;
    free(args->filename);
    args->filename = strdup("./empty.txt");
    answer = 0;

    retcodes rc = usage_worker(&received, args);
    EXPECT_EQ(rc, OPEN_ERR);
    EXPECT_EQ(received, answer);
}

TEST_F(DefaultDataALlZeroes, correct_test_single_process_all_zeroes) {
    std::size_t received = 0;

    retcodes rc = usage_worker(&received, args);
    EXPECT_EQ(rc, OK);
    EXPECT_EQ(received, answer);
}
