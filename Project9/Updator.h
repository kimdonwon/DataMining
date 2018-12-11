#pragma once
#include "Item.h"
#include "ItemBucket.h"
#include "RelatedItemList.h"

void hit_update(Item_Header *I, Item_bucket_Header *B);
void weight_update(related_ItemList_Header *R, Item_bucket_Header *B);

void related_Item_Update(Item *target_Item, Item_Header *I, Item_bucket_Header *B);

void distanceFromEntrance_update(Item_Header *I);
