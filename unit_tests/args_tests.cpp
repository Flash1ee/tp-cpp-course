#include <gtest/gtest.h>

extern "C" {
#include "args.h"
}

TEST(Args, init_args_test) {
    args_t *args = init_args();
    EXPECT_NE(args, nullptr);
}

TEST(Args, get_args_invalid_count) {
    EXPECT_EQ(nullptr, get_args(0, nullptr));
}

TEST(Args, get_args_invalid_argv) {
    EXPECT_EQ(nullptr, get_args(1, nullptr));
}

TEST(Args, get_args_invalid_flags) {
    char *argv[] = {strdup("mail"), strdup("yandex")};
    int argc = 2;
    args_t *args = get_args(argc, argv);
    EXPECT_NE(nullptr, args);
    EXPECT_EQ(args->help, true);
    for (auto &i : argv) {
        free(i);
    }
    free_args(args);
}

TEST(Args, get_args_valid_flags) {
    int argc = 7;
    size_t cnt_processes = 100;
    int mode = 1;
    char *argv[] = {strdup("./main.out"), strdup("-f"), strdup("./filename.txt"), strdup("-o"), strdup("1"),
                    strdup("-s"), strdup("100")};

    args_t *args = get_args(argc, argv);
    EXPECT_NE(nullptr, args);
    EXPECT_EQ(args->help, false);
    EXPECT_STREQ(args->filename, "./filename.txt");
    EXPECT_EQ(args->mode, mode);
    EXPECT_EQ(args->streams, cnt_processes);

    for (auto &i : argv) {
        free(i);
    }
    free_args(args);
}

