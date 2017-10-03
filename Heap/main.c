#include <stdlib.h>
#include <stdio.h>
#include <Verbose.h>
#include <heap.h>
#include <string.h>

int sort_Int(void * a, void * b){
    int val0 = (*(int *) a);
    int val1 = (*(int *) b);
    
    if (val0 > val1)
        return 0;
    else{
        return 1;
    }
    
}

int main(int argc, char * argv[]){
    struct heap * the_heap = NULL;
    int data[20];
    int i;
    //int *a;
    

    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-v") == 0)
        {
            Set_Verbose(true);
            Verbose_Print("Setting verbose flag\n");
        }
    }

    Set_Sort(&the_heap, sort_Int);

    
    for (i = 0; i < 10; i++){
        data[i] = i;
        //Verbose_Print("%d\n", i);
        Push_Data(&the_heap, (void *) &data[i]);
    }
    i = 100;
    Push_Data(&the_heap, (void *) &i);
    Delete_Heap(&the_heap);

    
    
    /* One pointer multiple allocations all free'd as per valgrind
    a = malloc(sizeof(int));
    *a = 5;
    Add_Data(&the_heap, (void *) &a);
    a = malloc(sizeof(int));
    *a = 6;
    Add_Data(&the_heap, (void *) &a);
    a = malloc(sizeof(int));
    *a = 7;
    Add_Data(&the_heap, (void *) &a);
    Delete_Heap_Destructive(&the_heap, free);*/
}

