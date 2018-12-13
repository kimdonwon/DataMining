#pragma once
#include "Item.h"
#include "ItemBucket.h"
#include "ItemDistance.h"
#include "RelatedItemList.h"

Item* search_ItemLocation(Item_Header *I, Item *certain_Item, Item_bucket_Header *B);
related_ItemList* search_relatedItemLocation(related_ItemList_Header *R, Item *point_I, Item_Header *I, Item_bucket_Header *B);

void shortest_path(Item *target_Item, Item_Header *I);