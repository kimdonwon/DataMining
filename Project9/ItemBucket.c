#include "common.h"
#include "ItemBucket.h"
#include "Item.h"

// 아이템 리스트에 붙어 있는 관련 아이템 리스트를 초기화해주는 함수
void init_Item_bucket(Item_bucket_Header *B)
{
	B->head = B->rear = NULL;
}

// 장바구니가 비어있는지 확인
int is_empty_Item_bucket(Item_bucket_Header *B)
{
	return (B->head == NULL);
}

// 품목명을 입력받아 장바구니에 추가해주는 함수
void insert_toBucket(Item_bucket_Header *B, char *name)
{
	Item *temp = (Item*)malloc(sizeof(Item));
	char* tmp_name;

	tmp_name = (char*)malloc(sizeof(char) * 10);

	if (temp == NULL) {
		fprintf(stderr, "메모리를 할당할 수 없습니다");
		exit(1);
	}
	else
	{
		strcpy(tmp_name, name);

		temp->Name = tmp_name;
		temp->rlink = NULL;
		temp->Hit = 0;
		temp->distance_fromEntrance = 10;
		temp->related = NULL;

		if (is_empty_Item_bucket(B)) {
			B->head = temp;
			B->rear = temp;
			temp->llink = NULL;
		}
		else {
			B->rear->rlink = temp;
			temp->llink = B->rear;
			B->rear = temp;
		}

	}
}

// 품목명을 입력받아 해당 품목을 장바구니에서 검색하여 삭제해주는 함수
void delete_fromItemBucket(Item_bucket_Header *B, char *name)
{
	Item *temp = B->head;

	int flag = 0;

	if (is_empty_Item_bucket(B)) {
		printf("장바구니가 비어있습니다.\n");
	}
	else {
		while (temp != NULL)
		{
			if (strcmp(temp->Name, name) == 0)
			{

				if (temp->llink == NULL && temp->rlink != NULL)
				{
					B->head = temp->rlink;
					temp->rlink->llink = NULL;
					free(temp);
					flag = 1;
					break;
				}
				else if (temp->rlink == NULL && temp->llink != NULL)
				{
					B->rear = temp->llink;
					temp->llink->rlink = NULL;
					free(temp);
					flag = 1;
					break;
				}
				else if (temp->rlink == NULL && temp->llink == NULL)
				{
					B->head = NULL;
					B->rear = NULL;
					free(temp);
					flag = 1;
					break;
				}
				else
				{
					temp->rlink->llink = temp->llink;
					temp->llink->rlink = temp->rlink;
					free(temp);
					flag = 1;
					break;
				}
			}
			temp = temp->rlink;
		}
	}

	if (flag == 0)
		printf("장바구니에 해당 상품이 없어 삭제할 수 없습니다.\n");

}

// 장바구니를 비워주는 함수
void empty_out_Bucket(Item_bucket_Header *B)
{
	

	B->rear = NULL;
	B->head = NULL;

	
}

// bucket에 들어 있는 품목들 출력
void print_Bucket(Item_bucket_Header *B)
{
	Item *point_B = B->head;

	printf("  Item Bucket Contents\n\n");
	printf("|		Name		|\n");

	if (is_empty_Item_bucket(B))
		printf("Bucket is empty now\n");
	else
	{
		while (point_B != NULL)
		{
			printf("|		%s		|\n", point_B->Name);

			point_B = point_B->rlink;
		}
	}

	printf("\n\n");
}