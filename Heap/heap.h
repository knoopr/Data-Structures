struct heap;


//pushes data onto the heap; returns -1 if error otherwise 1
int Push_Data(struct heap ** provided, void ** data);

//Delete's the heap and it's internal allocations but not the data
void Delete_Heap(struct heap ** provided);

//Not destructive in the normal sense; but free's the data as well
void Delete_Heap_Destructive(struct heap ** provided, void (*free_Data)(void *));

//Sets the sorting function for the heap, expects 1 or 0 depending on if the second element is larger or smaller
//If max-heap actual greater value, if min heap smaller value should be returned 1
int Set_Sort(struct heap ** provided,  int (*Data_Sorting)(void *,void*));