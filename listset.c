// pack the playing card structures into bytes of memory
unsigned char * pack_playing_cards(struct playing_card * cards,
	 int number_of_cards) 
{
     unsigned char * pack = malloc(sizeof((unsigned char * number_of_cards))
     for (int i = 0; i < number_of_cards; i += 3)
     { 
       pack[i] |= (cards[i].suit << 6);
       pack[i] |= (cards[i].value << 2);
       if (i + 1 >= number_of_cards){
         break;
       }
       else pack[i] |= cards[i + 1].suit

       pack[i + 1] |= (cards[i + 1].value << 4);
       pack[i + 1] |= (cards[i + 1].suit << 2);
       if(i + 2 >= number_of_cards)){
         break;
       }
       else pack[i + 1] |= (cards[i + 2].value >> 2);

       pack[i + 2] |= (cards[i + 2].value << 6);
       pack[i + 2] |= (cards[i + 2].suit << 4);
       if (i + 2 >= number_of_cards)){
         break;
       }
       else pack[i + 2] |= (cards[i + 2].value);
    }
    return pack;
}
// place the union of src1 and src2 into dest
void listset_union(struct listset * dest, struct listset * src1,
  struct listset * src2) {

  struct listnode * lookup = malloc(sizeof(struct listnode));
  for(lookup = src1 -> head; lookup !=NULL; lookup = lookup -> next)
  {
    listset_add(dest, lookup -> str);
  } 
  for(lookup = src2 -> head; lookup !=NULL; lookup = lookup -> next)
  {
    if((listset_lookup(dest, lookup -> str)) == 1){
    return; 
    }
    else
    {
      listset_add(dest, lookup -> str);
    }
  }
}

// place the intersection of src1 and src2 into dest
void listset_intersect(struct listset * dest, struct listset * src1,
  struct listset * src2) {
  struct listnode * lookup = malloc(sizeof(struct listnode));
  for(lookup = src1 -> head; lookup !=NULL; lookup = lookup -> next){
    char * value = lookup -> str;
    if((listset_lookup(src2, value)) == 1)
    {
      listset_add(dest, value);
    }
  }
}

// return the number of items in the listset
int listset_cardinality(struct listset * this) {
    int count = 0;
    struct listnode * node = malloc(sizeof(struct listnode));
    for(node = this -> head; node !=NULL; node = node -> next)
    {
      count++;
    }
    return count;
}

// print the elements of the list set
void listset_print(struct listset * this) {
  struct listnode * p;
  for ( p = this->head; p != NULL; p = p->next ) {
    printf("%s, ", p->str);
  }
  printf("\n");
}
