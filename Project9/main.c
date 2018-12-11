#include "main.h"

int main(void)
{
	Item_Header *I = (Item_Header*)malloc(sizeof(Item_Header));

	Item_bucket_Header *B = (Item_bucket_Header*)malloc(sizeof(Item_bucket_Header));

	Item *point_I = I->head;
	Item *start_point = I->head;

	int choice = 1;
	int flag;
	int yes_no;
	int i = 0;

	FILE *fp = NULL;
	char *name[10];

	init_Item(I);
	init_Item_bucket(B);

	while (choice != 0)
	{
		flag = 0;
		system("cls");
		printf("===============================================================================\n");
		print_Bucket(B);
		printf("===============================================================================\n");
		print_ItemList(I);
		printf("===============================================================================\n\n\n");

		point_I = I->head;

		if (I->head != NULL)
		{
			while (point_I != NULL)
			{
				if (point_I->related != NULL) {
					related_ItemList_Header *point_R = point_I->related;
					print_relatedItemList(point_R, point_I);

					
				}
				point_I = point_I->rlink;
				
			}
		}

		printf("\n\n원하는 번호를 입력해주세요.\n\n");
		printf("1.장바구니에담기 \n2.장바구니에서 제거 \n3.계산(Training) \n4.연관상품추천해주기 \n5.상품진열(거리배정) 및 최단거리 확인하기 \n");

		fflush(stdin);
		scanf("%d", &choice);


		switch (choice)
		{
			case 1:
				printf("Transaction File명을 입력해주세요.\n");
				fflush(stdin);
				scanf("%s", name);

				fp = fopen(name, "r");

				while(fscanf(fp, "%s", name) != EOF)
					insert_toBucket(B, name);

				fclose(fp);
				break;
			case 2:
				printf("장바구니에 제거할 Item들을 입력해주세요(Item명은 10자 이하).\n");

				fflush(stdin);
				scanf("%s", name);

				delete_fromItemBucket(B, name);
				break;
			case 3:
				insert_toItemList(I, B);
				hit_update(I, B);
				empty_out_Bucket(B);
				break;
			case 4:
				printf("원하시는 Item명을 입력해주세요.(Item명은 10자 이하)\n");

				fflush(stdin);
				scanf("%s", name);

				point_I = I->head;

				// 입력받은 품목명을 아이템 리스트에서 검색하여 포인터 반환
				while (point_I != NULL)
				{
					if (strcmp(point_I->Name, name) == 0)
					{
						break;
					}
					point_I = point_I->rlink;
				}

				// 입력받은 품목명이 리스트에 존재한다면 품목별 랭킹
				// related_Item_Ranking함수 내에서 화면 출력까지 완료
				if (point_I != NULL) {
					related_Item_Ranking(point_I);
				}
				_getch();
				break;
			case 5:
				printf("\n\n상품(Item)간의 거리를 구매 빈도수에 따라 다시 정의해주세요.\n");
				printf("	: 기본 설정 거리 = 100, 재설정 거리 = (기본설정거리 / (해당상품의Hit+weight)) * 10\n");
				printf("	: 입구로부터의 기본 설정 거리 = 10, 재설정 거리 = (기본설정거리 / (해당상품의Hit)) * 10\n\n\n");

				// 품목이 맞게 삽입되었으면, 품목간, 입구로부터 거리 재설정
				reset_Item_Distance(I);
				distanceFromEntrance_update(I);

				printf("구매하시고자 하는 품목을 입력해주세요.(다 작성하였으면 마지막에 end작성)\n\n");
				print_ItemList(I);

				flag = 0;

				start_point = I->head;

				// 사용자로부터 품목들을 입력받아 입구로부터의 거리를 비교한 후,
				// 가장 짧은 거리인 품목을 start_point로 설정 (품목 입력은 end사인을 기준으로 종료)
				while (flag == 0)
				{
					fflush(stdin);
					scanf("%s", name);

					point_I = I->head;

					while (point_I != NULL)
					{
						if (strcmp(point_I->Name, name) == 0)
						{
							if (start_point->distance_fromEntrance > point_I->distance_fromEntrance)
							{
								start_point = point_I;
								break;
							}
							else
								break;
						}
						point_I = point_I->rlink;
					}

					if (strcmp(name, "end") == 0)
						flag = 1;
				}

				printf("\n\n입구에서 가장 가까운 품목은 %s입니다.\n", start_point->Name);
				printf("%s로부터 매장에 있는 품목들까지의 최단 거리들을 안내해드리겠습니다.\n\n\n", start_point->Name);

				print_ItemList(I);
				printf("===============================================================================\n\n\n");

				// 아이템 리스트들에 존재하는 관련 아이템들 사이의 품목간의 거리 출력

				point_I = I->head;

				if (I->head != NULL)
				{
					while (point_I != NULL)
					{
						related_ItemList_Header *point_R = point_I->related;
						print_relatedItemList(point_R, point_I);

						point_I = point_I->rlink;
					}
				}
				// 최단경로 탐색(start_point로부터)
				shortest_path(start_point, I);
				return 0;
		}
	}
	return 0;
}