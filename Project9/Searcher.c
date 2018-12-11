#include "common.h"
#include "Searcher.h"

// 임의의 어떤 아이템이 아이템 리스트에 존재하는지 확인하여 위치를 반환.
// 없다면, 해당 아이템을 아이템 리스트에 추가하고 추가해준 위치를 반환 해주는 함수
// 아이템 리스트에 추가해주기 위해서는 related_Item_Update함수 사용해야 하기 때문에
// Bucket Header가 필요하다
Item* search_ItemLocation(Item_Header *I, Item *certain_Item, Item_bucket_Header *B)
{
	// 구현 파트
}

// 임의의 어떤 관련 아이템이 관련 아이템 리스트에 존재하는지 확인하여 위치를 반환.
// 없다면, 해당 관련 아이템을 관련 아이템 리스트에 추가하고 추가해준 위치를 반환 해주는 함수
// 관련 아이템 리스트에 추가해주기 위해서는 아이템 리스트 내에서 추가해야 하는 아이템의 위치를 찾아야 하기
// 때문에 search_ItemLocation함수가 필요하여, Item Header, Item Bucket Header가 필요
related_ItemList* search_relatedItemLocation(related_ItemList_Header *R, related_ItemList *certain_item, Item_Header *I, Item_bucket_Header *B)
{
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
	// 구현 파트
}