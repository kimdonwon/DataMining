#include "common.h"
#include "RelatedItemList.h"

// 아이템 리스트에 붙어 있는 관련 아이템 리스트가 비어있는지 확인
int is_empty_related_ItemList(related_ItemList_Header *R)
{
	return (R->head == NULL);
}

// 임의의 어떤 품목 노드의 주소가 관련 아이템 리스트들의 item자리에 존재하는지 확인
int is_inRelatedItemList(related_ItemList_Header *R, Item *certain_item)
{
	related_ItemList *point_R = R->head;

	int flag = 0;

	while (point_R != NULL)
	{
		if (strcmp(point_R->item->Name, certain_item->Name) == 0)
		{
			flag = 1;
			return 1;
		}

		point_R = point_R->rlink;
	}

	if (flag == 0)
		return 0;
}

// 해당 아이템에 연관되어 있는 관련 아이템들을
// weight를 기준으로 내림차순으로 랭킹해주는 함수
// 화면 출력까지 이 함수 내에서 해준다.
void related_Item_Ranking(Item *target_Item)
{
	if (target_Item->related == NULL)return;
	related_ItemList *point_R = target_Item->related->head;
	related_ItemList *point_R2 = target_Item->related->head;
	printf("|           추천상품리스트            |\n");
	//weight의 내림차순 으로 정렬
	while (point_R != NULL) {
		point_R2 = target_Item->related->head;
		while (point_R2 != NULL) {
			//비교 후 데이터를 바꿈
			if (point_R->weight > point_R2->weight) {
				int temp = point_R->distance;
				point_R->distance = point_R2->distance;
				point_R2->distance = temp;

				temp = point_R->weight;
				point_R->weight = point_R2->weight;
				point_R2->weight = temp;

				Item *tp = point_R->item;
				point_R->item = point_R2->item;
				point_R2->item = tp;
			}
			point_R2 = point_R2->rlink;
		}
		point_R = point_R->rlink;
	}
	point_R = target_Item->related->head;
	int c = 1;
	while (point_R != NULL) {
		printf("추천상품 %d : %s    (연관도: %d)\n",c, point_R->item->Name, point_R->weight);
		c++;
		point_R = point_R->rlink;
	}
	// 구현 파트
}

// 해당 품목에 존재하는 관련 아이템들을 출력해주는 함수
void print_relatedItemList(related_ItemList_Header *R, Item *target_Item)
{
	related_ItemList *point_R = R->head;

	printf("  %s 's Related Item List Contents\n\n", target_Item->Name);
	printf("|	name		Hit		Weight		Distance	|\n", point_R->item->Name, point_R->item->Hit, point_R->weight);

	if (R->head == NULL)
		printf("Item List is empty now\n");
	else
	{
		while (point_R != NULL)
		{
			printf("|	%s		%d		%d		%d		|\n", point_R->item->Name, point_R->item->Hit, point_R->weight, point_R->distance);

			point_R = point_R->rlink;
		}
	}

	printf("\n\n");
}