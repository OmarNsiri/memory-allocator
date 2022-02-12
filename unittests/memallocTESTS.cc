#include<gtest/gtest.h>
#include "memalloc.h"

void copyToBlock(void* block, size_t size, const char* string_val)
{
    for(int i = 0; i < size; i++)
    {
        *((char*)block + i) = string_val[i];
        ASSERT_TRUE(*((char*)block + i) == string_val[i]);
    }
}

TEST(MallocTests, Test1)
{
    size_t lenth_1 = 10;
    const char string_1[lenth_1] = "123456789";
    char* arr_1 = (char*)allocate_memory(lenth_1);

    copyToBlock(arr_1, lenth_1, string_1);

    free_memory(arr_1);
}

TEST(MallocTests, Test2)
{
    size_t lenth_1 = 10;
    size_t lenth_2 = 10;
    size_t lenth_3 = 5;

    char* arr_1 = (char*)allocate_memory(lenth_1);
    char* arr_2 = (char*)allocate_memory(lenth_2);

    free_memory(arr_2);

    char* arr_3 = (char*)allocate_memory(lenth_3);

    ASSERT_TRUE(arr_3 == arr_2);
}

TEST(MallocTests, Test3)
{
    size_t lenth_1 = 10;
    size_t lenth_2 = 10;
    size_t lenth_3 = 11;

    char* arr_1 = (char*)allocate_memory(lenth_1);
    char* arr_2 = (char*)allocate_memory(lenth_2);

    free_memory(arr_2);

    char* arr_3 = (char*)allocate_memory(lenth_3);

    ASSERT_FALSE(arr_3 == arr_2);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}