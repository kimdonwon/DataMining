#include "common.h"
#include "Item.h"
#include "RelatedItemList.h"

// 아이템 리스트를 초기화해주는 함수
void init_Item(Item_Header *I)
{
	I->head = I->rear = NULL;
}

// 아이템 리스트가 비어있는지 확인
int is_empty_Item(Item_Header *I)
{
	return (I->head == NULL);
}

// 임의의 어떤 아이템(품목)이 아이템 리스트에 존재하는지 검색해주는 함수
int is_inItemList(Item_Header *I, Item *certain_item)
{
	Item *point_I = I->head;

	int flag = 0;

	while (point_I != NULL)
	{
		if (strcmp(point_I->Name, certain_item->Name) == 0)
		{
			flag = 1;
			return 1;
		}

		point_I = point_I->rlink;
	}

	if (flag == 0)
		return 0;
}

// Item List I에 장바구니(B)에 존재하는 품목들을 추가해주는 함수.
// 이 때, 하나의 품목들을 접근하면서 그 품목이 I에 존재하는지 확인해야 하며
// 그 때마다 bucket에 들어 있는 관련 아이템들을 업데이트 해줘야 함(related_Item_Update함수 사용)
// 또한, bucket에 들어 있는 아이템 중 아이템 리스트 I에 없는 것이 있다면 추가해주어야 한다.
void insert_toItemList(Item_Header *I, Item_bucket_Header *B)
{
	Item *point_B = B->head;

	//I를 검색하고 중복된 데이터가 없을 때 추가함
	while (point_B != NULL)
	{
		search_ItemLocation(I, point_B, B);
		point_B = point_B->rlink;
	}
	// 추가한 데이터에 연관 품목을 추가함
	point_B = B->head;
	while (point_B != NULL)
	{
		related_Item_Update(point_B, I, B);
		point_B = point_B->rlink;
	}

	// 구현 파트
}

// 아이템 리스트들에 존재하는 관련 아이템들의 품목간의
// 거리를 기준으로 재설정해주는 함수
// 품목간의 거리가 생성된다.(아이템에 존재하는 관련 아이템마다)
//printf("	: 기본 설정 거리 = 100, 재설정 거리 = (기본설정거리 / (해당상품의Hit+weight)) * 10\n");
void reset_Item_Distance(Item_Header *I)
{
	//주어진 공식에 따라 거리 설정
	Item *i = I->head;
	while (i != NULL) {
		related_ItemList *il = i->related->head;
		while (il != NULL) {
			il->distance = (il->distance / (il->item->Hit+il->weight)) * 10;
			il = il->rlink;
		}
		i = i->rlink;
	}
	// 구현 파트
}

// Item리스트에 들어 있는 품목들 출력
void print_ItemList(Item_Header *I)
{
	Item *point_I = I->head;

	printf("  Purchased Item List Contents\n\n");
	printf("|	Name		Hit		Distance(Entrance)|\n");

	if (is_empty_Item(I))
		printf("Item List is empty now\n");
	else
	{
		while (point_I != NULL)
		{
			printf("|	%s		%d		%d		|\n", point_I->Name, point_I->Hit, point_I->distance_fromEntrance);

			point_I = point_I->rlink;
		}
	}

	printf("\n\n");
}