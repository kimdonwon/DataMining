#include "common.h"
#include "ItemDistance.h"

// distance가 들어 있는 리스트의 헤더를 인자로 받아, 인접 품목 노드들 중의 거리들을
// 비교하여 최소의 위치값을 계속 업데이트 해주는 함수이다. 
// 업데이트 하기 이전까지의 weight를 인자로 받아 넘긴다.
Item_distanceList* distance_update(Item_distanceList_Header *D, Item_distanceList *min_pos, Item_Header *I, int weight)
{
	// 구현 파트
}