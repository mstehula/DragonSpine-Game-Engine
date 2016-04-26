#ifndef DOD_ARRAY_H
#define DOD_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace util
{
    template <typename T>
    class DODArray
    {
    private:
        size_t current_size;
        size_t min_size;
        size_t allocated_size;

        T* elements;
    public:
        DODArray()
        {
            current_size = 0;
            min_size = 128;
            allocated_size = 128;
            elements = (T*) malloc(allocated_size * sizeof(T));
        }
        DODArray(size_t size)
        {
            current_size = 0;
            min_size = size;
            allocated_size = min_size;
            elements = (T*) malloc(allocated_size * sizeof(T));
            memset(elements, 0, allocated_size * sizeof(T));
        }

        virtual ~DODArray()
        {
            free(elements);
        }

        T& operator[](int i)
        {
            return elements[i];
        }

        size_t Size()
        {
            return current_size;
        }

        size_t AllocatedSize()
        {
            return allocated_size;
        }

        int Add(T& object)
        {
            if(current_size + 1 == allocated_size)
            {
                T* temp = (T*) malloc(allocated_size * 2 * sizeof(T));
                memcpy(temp, elements, current_size);
                allocated_size *= 2;
                free(elements);
                elements = temp;
            }

            memcpy(&elements[current_size], &object, sizeof(T));

            return current_size++;
        }

        /**
        * Func: Delete
        * Args: int i: The index of the element to remove.
        * Comm: No bounds checking on what to remove.
        *   Puts last element in the array in the new slot.
        *   Any data structures that need to be synchronized must be done
        *   outside this method.
        * Also, if the size is < 1/2 allocated size and allocated size > 128,
        *   will deallocate to 1/2 allocated size
        **/
        void Delete(int i)
        {
            T object_to_delete = elements[i];
            current_size -= 1;
            if(current_size > 0)
            {
                memcpy(&elements[i], &elements[current_size], sizeof(T));
            }

            if(current_size < allocated_size/4 && allocated_size > min_size)
            {
                T* temp = (T*) malloc(allocated_size / 2 * sizeof(T));
                allocated_size /= 2;
                memcpy(temp, elements, current_size);
                free(elements);
                elements = temp;
            }
        }
    };

}

#endif // DODARRAY_H
