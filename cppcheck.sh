cppcheck -I./inc/  --inconclusive --enable=all --language=c --check-config \
--suppress=missingInclude -UCOUNT_PROCESSES ./src/*.c ./lib/* ./unit_tests/*.cpp

