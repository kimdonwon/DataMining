#pragma once
#include "Item.h"
#include "RelatedItemList.h"

typedef struct Item_distanceList {

	char *name;

	int distance;
	int found;
	int possible;

	struct Item_distanceList *rlink;
	struct Item_distanceList *llink;

}Item_distanceList;

typedef struct Item_distanceList_Header {

	int all_checked;

	struct Item_distanceList *head;
	struct Item_distanceList *rear;

}Item_distanceList_Header;

Item_distanceList* distance_update(Item_distanceList_Header *D, Item_distanceList *min_pos, Item_Header *I);