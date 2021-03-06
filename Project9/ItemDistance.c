#include "common.h"
#include "ItemDistance.h"

// distance가 들어 있는 리스트의 헤더를 인자로 받아, 인접 품목 노드들 중의 거리들을
// 비교하여 최소의 위치값을 계속 업데이트 해주는 함수이다. 
// 업데이트 하기 이전까지의 weight를 인자로 받아 넘긴다.
Item_distanceList* distance_update(Item_distanceList_Header *D, Item_distanceList *min_pos, Item_Header *I)
{
	int tempdis = min_pos->distance;
	min_pos->found = 1;
	Item *point_I = I->head;
	Item *temp_I;
	//연관 품목에 연결된 노드를 찾아줌
	while (point_I != NULL) {
		if (strcmp(point_I->Name, min_pos->name) == 0) {
			temp_I = point_I;
			break;
		}
		point_I = point_I->rlink;
	}
	related_ItemList *temp_R = temp_I->related->head;
	Item_distanceList *temp_id = D->head;
	while (temp_R != NULL) {
		int flog = 0;
		temp_id = D->head;
		while (temp_id != NULL) {
			//노드의 연관 품목을 검사하여 거리가 더 짧으면 새로 고쳐줌
			if (strcmp(temp_id->name, temp_R->item->Name) == 0) {
				if (temp_id->distance > temp_R->distance + tempdis) {
					temp_id->distance = temp_R->distance + tempdis;
				}
				flog = 1;
				break;
			}
			temp_id = temp_id->rlink;
		}
		// 노드의 연관 품목 중에 새로운 물품이 있으면 추가해줌
		if (flog == 0) {
			Item_distanceList *temp = (Item_distanceList*)malloc(sizeof(Item_distanceList));
			temp->name = temp_R->item->Name;
			temp->distance = temp_R->distance;
			temp->found = 0;
			temp->possible = 0;
			temp->rlink = temp->llink = NULL;
			D->rear->rlink = temp;
			temp->llink = D->rear;
			D->rear = temp;
			
		}
		temp_R = temp_R->rlink;
	}

	temp_id = D->head;
	Item_distanceList *tm=D->head;
	//최소 거리 검사가 끝난 데이터는 found =1임, 
	// 검사가 필요한 데이터 중에 최소 거리 데이터를 찾아서 return함 
	while (temp_id != NULL) {
		if (temp_id->found != 1 && tm->distance > temp_id->distance) {
			tm = temp_id;	
		}
		temp_id = temp_id->rlink;
	}
	return tm;
	// 구현 파트
}