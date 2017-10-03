#include <stdlib.h>
#include <heap.h>
#include <verbose.h>

typedef struct heap
{
    void **data;
    int length;
    int (*Sort_Function)(void *, void *);
} heap;

int Set_Sort(heap **provided, int (*Data_Sorting)(void *, void *))
{
    if (!*provided)
    {
        *provided = malloc(sizeof(heap));
        //check to confirm it alloc'd properly;
        if (!*provided)
        {
            Verbose_Print("Failed to allocate new heap.\n");
            return -1;
        }
        else
        {
            (*provided)->length = 0;
            (*provided)->Sort_Function = Data_Sorting;
            Verbose_Print("Allocated new heap.\n");
        }
    }
}

int Push_Data(heap **provided, void **data)
{
    int parent_Index = 0, child_Index = 0;

    if (!*provided)
    {
        *provided = malloc(sizeof(heap));
        //check to confirm it alloc'd properly;
        if (!*provided)
        {
            Verbose_Print("Failed to allocate new heap.\n");
            return -1;
        }
        else
        {
            (*provided)->length = 0;
            (*provided)->Sort_Function = NULL;
            Verbose_Print("Allocated new heap.\n");
        }
    }
    else if ((*provided)->Sort_Function == NULL)
    {
        Verbose_Print("Failed to add data, please set a sort function.\n");
        return -1;
    }

    //(*provided)->data = NULL;
    if ((*provided)->length == 0)
        (*provided)->data = malloc(sizeof(void *));
    else
        (*provided)->data = realloc((*provided)->data, sizeof(void *) * ((*provided)->length + 1));

    if (!(*provided)->data)
    {
        Verbose_Print("Failed to allocate data storage\n");
        return -1;
    }
    else
    {
        Verbose_Print("Allocated data\n");
        (*provided)->data[(*provided)->length] = *data;
        
        if ((*provided)->length !=0){
            child_Index = (*provided)->length;
            if (child_Index%2 == 0)
                parent_Index = child_Index/2 -1;
            else
                parent_Index = child_Index/2;

            
            
            //Verbose_Print("Parent: %d; ", (*provided)->data[parent_Index]);
            //Verbose_Print("Child %d\n", (*provided)->data[(*provided)->length]);
            while((*provided)->Sort_Function(&(*provided)->data[parent_Index],&(*data))==1 && child_Index != 0){
                (*provided)->data[child_Index] = (*provided)->data[parent_Index];
                (*provided)->data[parent_Index] = *data;

                child_Index = parent_Index;
                
                if (child_Index%2 == 0)
                    parent_Index = child_Index/2 -1;
                else
                    parent_Index = child_Index/2;
                

                Verbose_Print("Parent: %d, child: %d\n", parent_Index, child_Index);
            }
        }
        (*provided)->length++;
        return 1;
    }
}

//Delete's the heap and it's internal allocations but not the data
void Delete_Heap(heap **provided)
{
    if (!*provided)
    {
        Verbose_Print("No heap to delete.\n");
    }
    else
    {
        if (!(*provided)->data)
            Verbose_Print("No data stored in heap.\n");
        else
        {
            free((*provided)->data);
            Verbose_Print("Free'd pointers to data\n");
        }
        free(*provided);
    }
}

//Not destructive in the normal sense; but free's the data as well
void Delete_Heap_Destructive(heap **provided, void (*free_Data)(void *))
{
    int i = 0;
    if (!*provided)
        Verbose_Print("No heap to delete.\n");
    else
    {
        if (!(*provided)->data)
            Verbose_Print("No data stored in heap.\n");
        else
        {
            for (i = 0; i < (*provided)->length && (*provided)->data[i] != NULL; i++)
            {
                (*free_Data)((*provided)->data[i]);
            }
            free((*provided)->data);
            Verbose_Print("Free'd data and pointers to it\n");
        }
        free(*provided);
    }
}

void Print_Heap(heap **provided){
    int i = 0;
    
    for (i = 0; i < (*provided)->length; i++){
        Verbose_Print("%d\t", (*provided)->data[i]);
    }
    Verbose_Print("\n\n");
}