cppcheck -I./inc/  --inconclusive --enable=all --language=c --check-config \
--suppress=missingInclude ./src/*.c ./unit_tests/*.cpp

