#include "bitset.h"

// create a new, empty bit vector set with a universe of 'size' items
struct bitset * bitset_new(int size) {
    struct bitset * set = malloc(sizeof(struct bitset));
    set -> universe_size = size;
    int extra = 0;
    if((size%64) > 0){ // Incase the extra bits which don't complete full word are left out
        extra = 1;
    }
    int size_in_words = size/ (sizeof (uint64_t) * 8 + extra);   //If extra == 1, an additional word is created to compensate for the bits which don't complete a full word
    set -> size_in_words = size_in_words;
    set -> bits = malloc (sizeof (uint64_t) * size_in_words);  
    for(int c = 0; c < size_in_words; c++){
        set -> bits[c] = 0;
    }
    return set;
}

// get the size of the universe of items that could be stored in the set
int bitset_size(struct bitset * this) {
    return this -> universe_size;
}

// get the number of items that are stored in the set
int bitset_cardinality(struct bitset * this){
    int count = 0;
    for(int c = 0; c < this -> size_in_words ; c++){
        while(this -> bits[c]){
        count += (this -> bits[c] & 1);
        this -> bits[c] >>= 1;
        }
    }
    return count;
}

// check to see if an item is in the set
int bitset_lookup(struct bitset * this, int item){
    double arrayIndex = item / 64;
    int array_index = (int) arrayIndex;
    int bit_index = item % 64;
    return((this -> bits[array_index] & 1ULL << bit_index) >> bit_index);
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set
void bitset_add(struct bitset * this, int item) {
    double arrayIndex = item/ 64;
    int array_index = (int) arrayIndex;  // to make sure the double value gets truncated
    int bit_index = item % 64;
    this -> bits[array_index] |= 1ULL << bit_index;
}

// remove an item with number 'item' from the set
void bitset_remove(struct bitset * this, int item) {
    double arrayIndex = item / 64;
    int array_index = (int) arrayIndex;
    int bit_index = item % 64;
    this -> bits[array_index] &= (-1ULL ^ (1ULL << bit_index));
}

// place the union of src1 and src2 into dest;
// all of src1, src2, and dest must have the same size universe
void bitset_union(struct bitset * dest, struct bitset * src1,
    struct bitset * src2) {
        int destSize = dest -> universe_size;
        int src1Size = src1 -> universe_size;
        int src2Size = src2 -> universe_size;
        if(destSize == src1Size && destSize == src2Size && src1Size == src2Size){
        for(int i = 0; i < src1 -> size_in_words; i++){
         dest -> bits[i] =  ((src1 -> bits[i]) | (src2 -> bits[i]));
        }
        }
}

// place the intersection of src1 and src2 into dest
// all of src1, src2, and dest must have the same size universe
void bitset_intersect(struct bitset * dest, struct bitset * src1,
    struct bitset * src2) {
        int destSize = dest -> universe_size;
        int src1Size = src1 -> universe_size;
        int src2Size = src2 -> universe_size;
        if(destSize == src1Size && destSize == src2Size && src1Size == src2Size){
        for(int i = 0; i < src1 -> size_in_words; i++){
            dest->bits[i] = (src1->bits[i]) & (src2->bits[i]);
            }
        }
}
