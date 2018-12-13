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
	
		// 연관 품목을 추가할 때 I의 주소로 추가함 ( hit update함수에서 I의 값을 올려주기 때문)
		while (point_I != NULL) {
			if (strcmp(point_I->Name, target_Item->Name) == 0) {
				//I의 연관 품목이 처음 생성될 때
				if (point_I->related == NULL) {
					related_ItemList_Header *rih = (related_ItemList_Header*)malloc(sizeof(related_ItemList_Header));
					point_I->related = rih;
					rih->head = rih->rear = NULL;

					Item *tempb = B->head;
					if (strcmp(point_I->Name, tempb->Name) == 0) {
						tempb = tempb->rlink;
					}
					related_ItemList *ri = (related_ItemList*)malloc(sizeof(related_ItemList));
					//연관 품목에 데이터를 처음 추가함
					Item *Itemp = I->head;
					while (Itemp != NULL) {
						if (strcmp(Itemp->Name, tempb->Name) == 0)break;
						Itemp = Itemp->rlink;
					}
					ri->item = Itemp;
					ri->weight = 0;
					ri->distance = 100;
					ri->rlink = ri->llink = NULL;
					rih->head = rih->rear = ri;
					tempb = tempb->rlink;
					//연관 품목에 데이터를 추가함
					while (tempb != NULL) {
						if (strcmp(point_I->Name, tempb->Name) != 0) {
							related_ItemList *ri = (related_ItemList*)malloc(sizeof(related_ItemList));
							Item *Itemp = I->head;
							while (Itemp != NULL) {
								if (strcmp(Itemp->Name, tempb->Name) == 0)break;
								Itemp = Itemp->rlink;
							}
							ri->item = Itemp;
							ri->weight = 0;
							ri->distance = 100;
							ri->rlink = ri->llink = NULL;
							rih->rear->rlink = ri;
							ri->llink = rih->rear;
							rih->rear = ri;
						}
						tempb = tempb->rlink;
					}
				}
				else {
					//연관 품목이 이미 만들어져 있을 때 중복을 찾고, 중복된 데이터가 없으면 추가함
					search_relatedItemLocation(I->head->related, point_I, I, B);
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