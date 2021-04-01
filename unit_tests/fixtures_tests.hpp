#ifndef IZ2_FIXTURES_TESTS_HPP
#define IZ2_FIXTURES_TESTS_HPP

#include <gtest/gtest.h>
#include <fstream>

class DataFixture : public ::testing::Test {
public:
    FILE *f = nullptr;
protected:
    const char *filename = "test.txt";
    const char *data = nullptr;
    size_t answer = 0;

    void SetUp() {
        data = "21\n"
               "0 5 3.446\n"
               "1 79 4.24\n"
               "2 107 4.741\n"
               "3 122 0\n"
               "4 31 1.094\n"
               "5 12 3.696\n"
               "6 28 1.972\n"
               "7 73 0.289\n"
               "8 41 2.004\n"
               "9 102 1.084\n"
               "10 119 2.944\n"
               "11 47 4.698\n"
               "12 2 0\n"
               "13 48 3.204\n"
               "14 101 3.415\n"
               "15 86 4.872\n"
               "16 102 1.063\n"
               "17 37 3.67\n"
               "18 16 1.696\n"
               "19 42 3.052\n"
               "20 93 0.865\n";
        answer = 4;
        std::ofstream input(filename);
        input << data;
        input.close();

        f = fopen(filename, "r");
    }

    void TearDown() {
        fclose(f);
    }
};


#endif //IZ2_FIXTURES_TESTS_HPP
