#include "array_operations.hh"

int greatest_v1(int *itemptr, int size)
{
    int greatest = *itemptr;

    for (int i = 0; i < size; i++)
    {
        int current = *(itemptr + i);
        if (current > greatest)
        {
            greatest = current;
        }

    }
    return greatest;
}

int greatest_v2(int *itemptr, int *endptr)
{
    int greatest = *itemptr;

    while (itemptr != endptr)
    {
        int current = *(itemptr++);
        if (current > greatest)
        {
            greatest = current;
        }
    }
    return greatest;
}

void copy(int *itemptr, int *endptr, int *targetptr)
{
    while (itemptr != endptr)
    {
        *targetptr = *itemptr;
        itemptr++;
        targetptr++;
    }
}

void reverse(int *leftptr, int *rightptr)
{
    rightptr--;

    int temp;

    while (leftptr < rightptr)
    {
        temp = *leftptr;
        *leftptr = *rightptr;
        *rightptr = temp;

        leftptr++;
        rightptr--;
    }
}
