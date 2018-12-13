#include "common.h"
#include "Searcher.h"

// ������ � �������� ������ ����Ʈ�� �����ϴ��� Ȯ���Ͽ� ��ġ�� ��ȯ.
// ���ٸ�, �ش� �������� ������ ����Ʈ�� �߰��ϰ� �߰����� ��ġ�� ��ȯ ���ִ� �Լ�
// ������ ����Ʈ�� �߰����ֱ� ���ؼ��� related_Item_Update�Լ� ����ؾ� �ϱ� ������
// Bucket Header�� �ʿ��ϴ�
Item* search_ItemLocation(Item_Header *I, Item *certain_Item, Item_bucket_Header *B)
{
	// ���� ��Ʈ
}

// ������ � ���� �������� ���� ������ ����Ʈ�� �����ϴ��� Ȯ���Ͽ� ��ġ�� ��ȯ.
// ���ٸ�, �ش� ���� �������� ���� ������ ����Ʈ�� �߰��ϰ� �߰����� ��ġ�� ��ȯ ���ִ� �Լ�
// ���� ������ ����Ʈ�� �߰����ֱ� ���ؼ��� ������ ����Ʈ ������ �߰��ؾ� �ϴ� �������� ��ġ�� ã�ƾ� �ϱ�
// ������ search_ItemLocation�Լ��� �ʿ��Ͽ�, Item Header, Item Bucket Header�� �ʿ�
related_ItemList* search_relatedItemLocation(related_ItemList_Header *R, related_ItemList *certain_item, Item_Header *I, Item_bucket_Header *B)
{
	// ���� ��Ʈ
}

// target_Item�� ��������� �Ͽ�, ��� ǰ���� �Ÿ��� �ľ��Ͽ�
// ������ ǰ������� �ִ� ��θ� ���ϰ� ������ִ� �Լ�(Djkstra �˰��� ����)
// �������� �������� �� ǰ������ �� �� �ִ� �Ÿ��� Ȯ���ϰ�,
// �ּڰ��� ����, �� �� ������ġ������ weight�� �հ� ������������ �Ÿ��� ���Ͽ�
// �� ���� ������ �ִܰ�� ����.

// distance�� ��� �ִ� ����Ʈ�� �����Ͽ�, �ش� ����Ʈ�� �ڱ��ڽ��� ������
// ������ �Ҵ��ϰ� �̸� ��� ������Ʈ ���־�, ��� ���������� �ִܰ�θ� �����Ѵ�.
void shortest_path(Item *target_Item, Item_Header *I)
{
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

	Item_distanceList *point_rl = idh->head->rlink;
	Item_distanceList *temp_rl = idh->head->rlink;
	while (point_rl != NULL) {
		if (temp_rl->distance > point_rl->distance)temp_rl = point_rl;
		point_rl = point_rl->rlink;
	}
	point_rl = idh->head->rlink;

	while (point_rl != NULL) {
		temp_rl = distance_update(idh, temp_rl, I);
		if (temp_rl == idh->head)break;
		point_rl = point_rl->rlink;
	}

	point_rl = idh->head->rlink;
	while (point_rl != NULL) {
		printf("%s�κ��� %sǰ������� �ִܰŸ��� %d�Դϴ�.\n", target_Item->Name, point_rl->name, point_rl->distance);
		point_rl = point_rl->rlink;
	}
	
	// ���� ��Ʈ
}