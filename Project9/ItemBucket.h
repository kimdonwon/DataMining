#pragma once

typedef struct Item_bucket_Header {

	struct Item *head;
	struct Item *rear;

}Item_bucket_Header;

void init_Item_bucket(Item_bucket_Header *B);
int is_empty_Item_bucket(Item_bucket_Header *B);

void insert_toBucket(Item_bucket_Header *B, char *name);
void delete_fromItemBucket(Item_bucket_Header *B, char *name);
void empty_out_Bucket(Item_bucket_Header *B);

void print_Bucket(Item_bucket_Header *B);