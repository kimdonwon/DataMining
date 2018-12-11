#include "common.h"
#include "Updator.h"

// 현재 bucket에 존재하는 품목들의 hit값을 업데이트 해준다.
// 이 때, 해당 품목의 관련 상품들의 weight 역시 업데이트 해준다.
void hit_update(Item_Header *I, Item_bucket_Header *B)
{
	Item *point_I = I->head;
	Item *point_B = B->head;

	while (point_I != NULL)
	{
		while (point_B != NULL)
		{
			if (strcmp(point_I->Name, point_B->Name) == 0)
			{
				point_I->Hit++;
				if(point_I->related!=NULL)
				weight_update(point_I->related, B);
			}
			point_B = point_B->rlink;
		}
		point_B = B->head;
		point_I = point_I->rlink;
	}
}

// weight값을 업데이트 해주는 함수
// bucket에 존재하는 상품 중, 관련 아이템 리스트에 존재하는 품목의 
// weight값을 업데이트 
void weight_update(related_ItemList_Header *R, Item_bucket_Header *B)
{
	related_ItemList *point_R = R->head;
	Item *point_B = B->head;

	while (point_R != NULL)
	{
		while (point_B != NULL)
		{
			if (strcmp(point_R->item->Name, point_B->Name) == 0)
			{
				point_R->weight++;
			}
			point_B = point_B->rlink;
		}
		point_B = B->head;
		point_R = point_R->rlink;
	}

}

// target_Item의 관련 리스트에 bucket에 존재하는 관련 품목들을 추가/업데이트 해주는 함수
// 존재하지 않는경우에만 추가 (hit, weight의 업데이트는 hit / weight update함수에서 따로 구현)
// 추가 하는 경우에는 hit, weight는 기본 설정 값으로 추가 해주며,
// 관련 아이템의 item field는 해당 품목명을 Item List I에서 검색해주어 
// 주소값을 넣어준다.
void related_Item_Update(Item *target_Item, Item_Header *I, Item_bucket_Header *B)
{
	
	
	Item *point_I = I->head;
	Item *point_B = B->head;
	

	if (target_Item->llink != NULL) {
		target_Item->llink->rlink = NULL;
		B->head = target_Item;
		target_Item->llink = NULL;
		B->rear->rlink = point_B;
		point_B->llink = B->rear;
		B->rear = point_B;
	}

	
	

	point_B = B->head;
	point_I = I->head;
	while (point_I != NULL)
	{
		if (strcmp(point_I->Name, point_B->Name) == 0) {
			if (point_I->related == NULL) {
				related_ItemList_Header *rih = (related_ItemList_Header*)malloc(sizeof(related_ItemList_Header));
				related_ItemList *ri = (related_ItemList*)malloc(sizeof(related_ItemList));
				related_ItemList *temp = ri;
				point_I->related = rih;
				rih->head = rih->rear = ri;

				Item *point_B2 = B->head->rlink;
				while (point_B2 != NULL) {
					Item *point_I2 = I->head;
					while (point_I2 != NULL) {
						if (strcmp(point_I2->Name, point_B2->Name) == 0) {
							break;
						}
						point_I2 = point_I2->rlink;
						
					}
					temp->item = point_I2;
					temp->weight = 1;
					temp->distance = 100;
					related_ItemList *ri2 = (related_ItemList*)malloc(sizeof(related_ItemList));
					temp->rlink = ri2;
					if (point_B2->rlink == NULL)
						temp->rlink = NULL;
					temp = ri2;
					point_B2 = point_B2->rlink;
				}
			}
			else {

				Item *point_B = B->head->rlink;

				while (point_B != NULL)
				{
					related_ItemList *point_R = point_I->related->head;
					int flog = 0;
					while (point_R!=NULL) {
						if (strcmp(point_R->item->Name, point_B->Name) == 0) {
							flog = 1;
							break;
						}
						if (point_R->rlink == NULL)break;
						point_R = point_R->rlink;
					}

					if (flog == 0) {
						related_ItemList *ri2 = (related_ItemList*)malloc(sizeof(related_ItemList));
						ri2->item = point_B;
						ri2->weight = 1;
						ri2->distance = 100;
						ri2->rlink = NULL;
						point_R->rlink = ri2;
					}
					
					point_B = point_B->rlink;
				}
			}
			break;
		}
		point_I = point_I->rlink;
	}

	// 구현 파트
}

// 아이템리스트에 존재하는 아이템들을
// hit값을 기준으로 입구로부터의 거리를 재설정해주는 함수
void distanceFromEntrance_update(Item_Header *I)
{
	Item *point_I = I->head;

	while (point_I != NULL)
	{
		point_I->distance_fromEntrance /= point_I->Hit;
		point_I->distance_fromEntrance *= 10;

		point_I = point_I->rlink;
	}
}