/*
 * mm-naive.c - The least memory-efficient malloc package.
 * 
 * In this naive approach, a block is allocated by allocating a
 * new page as needed.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/* always use 16-byte alignment */
#define ALIGNMENT 16

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~(ALIGNMENT-1))

/* rounds up to the nearest multiple of mem_pagesize() */
#define PAGE_ALIGN(size) (((size) + (mem_pagesize()-1)) & ~(mem_pagesize()-1))

#define CHUNK_SIZE (1 << 14)
#define CHUNK_ALIGN(size) (((size)+(CHUNK_SIZE-1)) & ~(CHUNK_SIZE-1))

//Sum macros from pdf.
#define GET(p) (*(size_t *)(p))
#define GET_ALLOC(p) (GET(p) & 0x1)
#define GET_SIZE(p) (GET(p) & ~0xF)
#define PUT(p, val) (*(size_t *)(p) = (val))
#define PACK(size, alloc) ((size) | (alloc))


#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp))
#define PREV_BLKP(bp) ((char *)(bp)-GET_SIZE((char *)(bp)-OVERHEAD))

#define OVERHEAD (sizeof(block_header)+sizeof(block_footer))
#define FTRP(bp) ((char *)(bp)+GET_SIZE(HDRP(bp))-OVERHEAD)
#define HDRP(bp) ((char *)(bp) - sizeof(block_header))


//Structs from pdf

typedef struct {
  size_t size;
  char allocated;
} block_header;
typedef struct {
  size_t size;
  int filler;
} block_footer;

typedef struct list_node {
  struct list_node *prev;
  struct list_node *next;
} list_node;

void *current_avail = NULL;
int current_avail_size = 0;
void * mem_list;

/* 
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
  //Need to figure out what the intial structure looks like.
  current_avail = NULL;
  current_avail_size = 0;

  return 0;
}

/* 
 * mm_malloc - Allocate a block by using bytes from current_avail,
 *     grabbing a new page if necessary.
 */
void *mm_malloc(size_t size)
{
  //32 for the total size of header and footer, and the aligned size.
  int total_size = 32 + ALIGN(size);
  //printf("Total size: %d", total_size);

  //Find place with enough room to fit.
  //Place it in.
  int newsize = ALIGN(size);
  void *p;
  
  if (current_avail_size < newsize) {
    current_avail_size = PAGE_ALIGN(newsize);
    current_avail = mem_map(current_avail_size);
    if (current_avail == NULL)
      return NULL;
  }

  p = current_avail;
  current_avail += newsize;
  current_avail_size -= newsize;

  // printf("Current avail: %p, Current_avail size: %d, P: %p\n", current_avail, current_avail_size, p);

  return p;
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr)
{
  //Get the size of previously allocated block.
  //Set the headers and footers for the newly unallocated block.
  //See if their is any coalesceing to be done.
  coalesce_it(NULL);
}

void coalesce_it(void *bp){
}


/*
 * Method to check heap after running a trace.
 */
void heap_check(void * ptr){
  //Traverse the tree ensuring correct size and stuff is next
  //check to make sure sizes match on ends

  //Inside the loop also check that no two unallocated bytes are next to each other.
  //swagggg

}
