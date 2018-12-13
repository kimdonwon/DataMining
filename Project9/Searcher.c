#include "common.h"
#include "Searcher.h"

// 임의의 어떤 아이템이 아이템 리스트에 존재하는지 확인하여 위치를 반환.
// 없다면, 해당 아이템을 아이템 리스트에 추가하고 추가해준 위치를 반환 해주는 함수
// 아이템 리스트에 추가해주기 위해서는 related_Item_Update함수 사용해야 하기 때문에
// Bucket Header가 필요하다
Item* search_ItemLocation(Item_Header *I, Item *certain_Item, Item_bucket_Header *B)
{
	Item *point_I = I->head;
	Item *point_B = B->head;
	//I가 처음 만들어지면
	if (is_empty_Item(I))
	{
		Item *temp = (Item*)malloc(sizeof(Item));
		temp->Name = point_B->Name;
		temp->Hit = point_B->Hit;
		temp->distance_fromEntrance = 10;
		temp->related = temp->llink = temp->rlink = NULL;

		I->head = temp;
		I->rear = temp;
		return temp;
	}
	// I에서 중복된 데이터가 있을 때
	while (point_I != NULL) {
		if (strcmp(certain_Item->Name, point_I->Name) == 0) {
			return point_I;
		}
		point_I = point_I->rlink;
	}
	// I에 중복된 데이터가 없을 때 새로 추가해줌
	Item *temp = (Item*)malloc(sizeof(Item));
	temp->Name = certain_Item->Name;
	temp->Hit = certain_Item->Hit;
	temp->distance_fromEntrance = 10;
	temp->related = temp->llink = temp->rlink = NULL;

	I->rear->rlink = temp;
	temp->llink = I->rear;
	I->rear = temp;
	return temp;
	// 구현 파트
}

// 임의의 어떤 관련 아이템이 관련 아이템 리스트에 존재하는지 확인하여 위치를 반환.
// 없다면, 해당 관련 아이템을 관련 아이템 리스트에 추가하고 추가해준 위치를 반환 해주는 함수
// 관련 아이템 리스트에 추가해주기 위해서는 아이템 리스트 내에서 추가해야 하는 아이템의 위치를 찾아야 하기
// 때문에 search_ItemLocation함수가 필요하여, Item Header, Item Bucket Header가 필요
related_ItemList* search_relatedItemLocation(related_ItemList_Header *R, Item *point_I, Item_Header *I, Item_bucket_Header *B)
{
	Item *point_B = B->head;
	
	while (point_B != NULL) {
		int flog = 0;
		related_ItemList *temp = point_I->related->head;
		while (temp != NULL) {
			if (strcmp(point_B->Name, temp->item->Name) == 0) {
				flog = 1;
			}

			temp = temp->rlink;
		}
		if (strcmp(point_B->Name, point_I->Name) == 0)flog = 1;
		if (flog == 0) {
			related_ItemList *ri = (related_ItemList*)malloc(sizeof(related_ItemList));
			Item *Itemp = I->head;
			while (Itemp != NULL) {
				if (strcmp(Itemp->Name, point_B->Name) == 0)break;
				Itemp = Itemp->rlink;
			}
			ri->item = Itemp;
			ri->distance = 100;
			ri->weight = 1;
			ri->rlink = NULL;

			point_I->related->rear->rlink = ri;
			ri->llink = point_I->related->rear;
			point_I->related->rear = ri;

		}
		point_B = point_B->rlink;
	}
	// 구현 파트
}

// target_Item을 출발점으로 하여, 모든 품목간의 거리를 파악하여
// 각각의 품목까지의 최단 경로를 구하고 출력해주는 함수(Djkstra 알고리즘 적용)
// 시작점을 기준으로 각 품목으로 갈 수 있는 거리를 확인하고,
// 최솟값을 선택, 이 때 직전위치까지의 weight와 합과 시작점에서의 거리를 비교하여
// 더 작은 값으로 최단경로 설정.

// distance가 들어 있는 리스트를 선언하여, 해당 리스트에 자기자신을 제외한
// 노드들을 할당하고 이를 계속 업데이트 해주어, 모든 지점까지의 최단경로를 설정한다.
void shortest_path(Item *target_Item, Item_Header *I)
{
	//다익스트라 알고르즘에 사용될 리스트 생성
	Item_distanceList_Header *idh = (Item_distanceList_Header*)malloc(sizeof(Item_distanceList_Header));
	idh->all_checked = 0;
	idh->head = idh->rear = NULL;
	Item *i = I->head;
	int count = 0;
	while (i != NULL) {
		count++;
		i = i->rlink;
	}
	related_ItemList *rl = target_Item->related->head;
	Item_distanceList *temp = (Item_distanceList*)malloc(sizeof(Item_distanceList));
	temp->name = target_Item->Name;
	temp->distance = 0;
	temp->found = 1;
	temp->possible = 0;
	temp->rlink = temp->llink = NULL;
	idh->head = idh->rear = temp;
	
	// 다익스트라 알고리즘에 사용될 리스트에 초기 데이터를 넣어줌
	while (rl != NULL) {
		Item_distanceList *temp = (Item_distanceList*)malloc(sizeof(Item_distanceList));
		temp->name = rl->item->Name;
		temp->distance = rl->distance;
		temp->found = 0;
		temp->possible = 0;
		temp->rlink = temp->llink = NULL;
		idh->rear->rlink = temp;
		temp->llink = idh->rear;
		idh->rear = temp;
		rl = rl->rlink;
	}

	// 제일 처음 최소 거리를 찾아줌
	Item_distanceList *point_rl = idh->head->rlink;
	Item_distanceList *temp_rl = idh->head->rlink;
	while (point_rl != NULL) {
		if (temp_rl->distance > point_rl->distance)temp_rl = point_rl;
		point_rl = point_rl->rlink;
	}
	point_rl = idh->head->rlink;
	// 최소 거리에 있는 노드를 기준으로 최소 거리를 찾아줌
	while (point_rl != NULL) {
		temp_rl = distance_update(idh, temp_rl, I);
		if (temp_rl == idh->head)break;
		point_rl = point_rl->rlink;
	}

	point_rl = idh->head->rlink;
	while (point_rl != NULL) {
		printf("%s로부터 %s품목까지의 최단거리는 %d입니다.\n", target_Item->Name, point_rl->name, point_rl->distance);
		point_rl = point_rl->rlink;
	}
	
	// 구현 파트
}