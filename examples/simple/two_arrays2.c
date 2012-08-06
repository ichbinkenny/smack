#include <stdio.h>
#include <stdlib.h>
#include "smack.h"

#define RESET 0
#define SET 1

typedef struct {
  short data;
  int count;
  char status;
} elem;

int arraySize;

void __SMACK_anno_resetArray(elem *array) {
  TYPES(__SMACK_requires(__SMACK_typeOf(&arraySize, TYPEP(int))));
  TYPES(__SMACK_requires(__SMACK_forall(__SMACK_x,
                                        __SMACK_ARRAY_COUNT(array, sizeof(elem), arraySize),
                                        __SMACK_typeOf(__SMACK_x, TYPEP(elem)))));
  __SMACK_requires(__SMACK_size(array) == arraySize * sizeof(elem));
  __SMACK_requires(__SMACK_offsetOf(array) == 0);
  __SMACK_requires(__SMACK_allocated(array));
  __SMACK_requires(__SMACK_objectOf(array) != __SMACK_objectOf(&arraySize));
  __SMACK_requires(arraySize > 0);
  __SMACK_ensures(__SMACK_forall(__SMACK_x, __SMACK_ARRAY_COUNT(array, sizeof(elem), arraySize), (((elem*)__SMACK_x)->status) == RESET));
  __SMACK_modifies(__SMACK_addOffsetToSet(__SMACK_ARRAY_COUNT(array, sizeof(elem), arraySize), __SMACK_OFFSET(elem, status)));
  INLINE(__SMACK_inline());
}
void resetArray(elem *array) {
  int i = 0;

  for (i = 0; i < arraySize; i++) {
    // *** loop invariants
    __SMACK_invariant(0 <= i);
    __SMACK_invariant(i <= arraySize);
    __SMACK_invariant(__SMACK_forall(__SMACK_x, __SMACK_ARRAY_COUNT(array, sizeof(elem), i), (((elem*)__SMACK_x)->status) == RESET));
    // modifies fails because arraySize is not allocated and therefore can be changed by the loop
    __SMACK_modifies(__SMACK_union(__SMACK_addOffsetToSet(__SMACK_ARRAY_COUNT(array, sizeof(elem), __SMACK_new(i)),
                                                          __SMACK_OFFSET(elem, status)),
                                   __SMACK_set(&i)));
    // ***

    array[i].status = RESET;
  }
}

void __SMACK_anno_setArray(elem *array) {
  TYPES(__SMACK_requires(__SMACK_typeOf(&arraySize, TYPEP(int))));
  TYPES(__SMACK_requires(__SMACK_forall(__SMACK_x,
                                        __SMACK_ARRAY_COUNT(array, sizeof(elem), arraySize),
                                        __SMACK_typeOf(__SMACK_x, TYPEP(elem)))));
  __SMACK_requires(__SMACK_size(array) == arraySize * sizeof(elem));
  __SMACK_requires(__SMACK_offsetOf(array) == 0);
  __SMACK_requires(__SMACK_allocated(array));
  __SMACK_requires(__SMACK_objectOf(array) != __SMACK_objectOf(&arraySize));
  __SMACK_requires(arraySize > 0);
  __SMACK_ensures(__SMACK_forall(__SMACK_x, __SMACK_ARRAY_COUNT(array, sizeof(elem), arraySize), (((elem*)__SMACK_x)->status) == SET));
  __SMACK_modifies(__SMACK_addOffsetToSet(__SMACK_ARRAY_COUNT(array, sizeof(elem), arraySize), __SMACK_OFFSET(elem, status)));
  INLINE(__SMACK_inline());
}
void setArray(elem *array) {
  int i = 0;

  for (i = 0; i < arraySize; i++) {
    // *** loop invariants
    __SMACK_invariant(0 <= i);
    __SMACK_invariant(i <= arraySize);
    __SMACK_invariant(__SMACK_forall(__SMACK_x, __SMACK_ARRAY_COUNT(array, sizeof(elem), i), (((elem*)__SMACK_x)->status) == SET));
    // modifies fails because arraySize is not allocated and therefore can be changed by the loop
    __SMACK_modifies(__SMACK_union(__SMACK_addOffsetToSet(__SMACK_ARRAY_COUNT(array, sizeof(elem), __SMACK_new(i)),
                                                          __SMACK_OFFSET(elem, status)),
                                   __SMACK_set(&i)));
    // ***

    array[i].status = SET;
  }
}

void __SMACK_anno_initializeCount(elem *array) {
  TYPES(__SMACK_requires(__SMACK_typeOf(&arraySize, TYPEP(int))));
  TYPES(__SMACK_requires(__SMACK_forall(__SMACK_x,
                                        __SMACK_ARRAY_COUNT(array, sizeof(elem), arraySize),
                                        __SMACK_typeOf(__SMACK_x, TYPEP(elem)))));
  __SMACK_requires(__SMACK_size(array) == arraySize * sizeof(elem));
  __SMACK_requires(__SMACK_offsetOf(array) == 0);
  __SMACK_requires(__SMACK_allocated(array));
  __SMACK_requires(__SMACK_objectOf(array) != __SMACK_objectOf(&arraySize));
  __SMACK_requires(arraySize > 0);
  __SMACK_ensures(__SMACK_forall(__SMACK_x, __SMACK_ARRAY_COUNT(array, sizeof(elem), arraySize), (((elem*)__SMACK_x)->count) == 0));
  __SMACK_modifies(__SMACK_addOffsetToSet(__SMACK_ARRAY_COUNT(array, sizeof(elem), arraySize), __SMACK_OFFSET(elem, count)));
  INLINE(__SMACK_inline());
}
void initializeCount(elem *array) {
  int i = 0;

  for (i = 0; i < arraySize; i++) {
    // *** loop invariants
    __SMACK_invariant(0 <= i);
    __SMACK_invariant(i <= arraySize);
    __SMACK_invariant(__SMACK_forall(__SMACK_x, __SMACK_ARRAY_COUNT(array, sizeof(elem), i), (((elem*)__SMACK_x)->count) == 0));
    // modifies fails because arraySize is not allocated and therefore can be changed by the loop
    __SMACK_modifies(__SMACK_union(__SMACK_addOffsetToSet(__SMACK_ARRAY_COUNT(array, sizeof(elem), __SMACK_new(i)),
                                                          __SMACK_OFFSET(elem, count)),
                                   __SMACK_set(&i)));
    // ***

    array[i].count = 0;
  }
}

void __SMACK_anno_main() {
  __SMACK_requires(arraySize > 0);
  __SMACK_requires(__SMACK_allocated(&arraySize));
  TYPES(__SMACK_requires(__SMACK_typeOf(&arraySize, TYPEP(int))));
}
int main() {
  int i = 0;
  elem *arrayOne = (elem*)malloc(arraySize * sizeof(elem));
  elem *arrayTwo = (elem*)malloc(arraySize * sizeof(elem));

  resetArray(arrayOne);
  setArray(arrayTwo);
  initializeCount(arrayTwo);

  for (i = 0; i < arraySize; i++) {
    // *** loop invariants
    __SMACK_invariant(0 <= i);
    __SMACK_invariant(i <= arraySize);
    __SMACK_modifies(__SMACK_set(&i));
    // ***

    __SMACK_assert(arrayOne[i].status == RESET);
    __SMACK_assert(arrayTwo[i].status == SET);
    __SMACK_assert(arrayTwo[i].count == 0);
  }

  initializeCount(arrayOne);
  setArray(arrayOne);
  resetArray(arrayTwo);

  for (i = 0; i < arraySize; i++) {
    // *** loop invariants
    __SMACK_invariant(0 <= i);
    __SMACK_invariant(i <= arraySize);
    __SMACK_modifies(__SMACK_set(&i));
    // ***

    __SMACK_assert(arrayOne[i].count == 0);
    __SMACK_assert(arrayOne[i].status == SET);
    __SMACK_assert(arrayTwo[i].status == RESET);
  }

  free(arrayOne);
  free(arrayTwo);
  return 0;
}
