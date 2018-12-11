#pragma once
#include "Item.h"

typedef struct related_ItemList_Header {

	struct related_ItemList *head;
	struct related_ItemList *rear;

}related_ItemList_Header;

typedef struct related_ItemList {

	int weight;
	int distance;

	struct related_ItemList *rlink;
	struct related_ItemList *llink;

	struct Item *item;

}related_ItemList;

int is_empty_related_ItemList(related_ItemList_Header *R);
int is_inRelatedItemList(related_ItemList_Header *R, Item *certain_item);

void related_Item_Ranking(Item *target_Item);
void print_relatedItemList(related_ItemList_Header *R, Item *target_Item);