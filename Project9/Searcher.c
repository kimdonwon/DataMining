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
	// ���� ��Ʈ
}