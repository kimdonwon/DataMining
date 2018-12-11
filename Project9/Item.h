#pragma once
#include "ItemBucket.h"

typedef struct Item {

	char *Name;

	int Hit;
	int distance_fromEntrance;

	struct Item *rlink;
	struct Item *llink;

	struct related_ItemList_Header *related;

}Item;

typedef struct Item_Header {

	struct Item *head;
	struct Item *rear;

}Item_Header;

void init_Item(Item_Header *I);
int is_empty_Item(Item_Header *I);
int is_inItemList(Item_Header *I, Item *certain_item);

void insert_toItemList(Item_Header *I, Item_bucket_Header *B);

void reset_Item_Distance(Item_Header *I);
void print_ItemList(Item_Header *I);
