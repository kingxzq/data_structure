#define _CRT_SECURE_NO_WARNINGS 1
#include"Heap.h"

void Swap(HPDataType* px, HPDataType* py)
{
	HPDataType tmp = *px;
	*px = *py;
	*py = tmp;
}
void HeapInit(HP* hp)
{
	assert(hp);
	hp->a = NULL;
	hp->size = hp->capacity = 0;
}
void HeapDestroy(HP* hp)
{
	assert(hp);
	free(hp->a);
	hp->capacity = hp->size = 0;
}
void AdjustUp(int* a,int child)//向上调整
{
	assert(a);

	int parent = (child - 1) / 2;
	while (child>0)
	{
		if (a[child] < a[parent])
		{
			Swap(&a[child], &a[parent]);

			child = parent;
			parent = (child - 1) / 2;
		}
		else
			break; 
	}
}
void AdjustDown(int* a, int n, int parent)
{
	int child = parent * 2 + 1;
	while (child < n)
	{
		// 选出左右孩子中小的那一个
		if (child + 1 < n && a[child + 1] < a[child])
		{
			++child;
		}

		// 如果小的孩子小于父亲，则交换，并继续向下调整
		if (a[child] < a[parent])
		{
			Swap(&a[child], &a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}
void HeapPush(HP* hp, HPDataType x)
{
	assert(hp);
	if (hp->size == hp->capacity)
	{
		size_t newCapacity = hp->capacity == 0 ? 4 : hp->capacity * 2;
		HPDataType* tmp = realloc(hp->a, sizeof(HPDataType) * newCapacity);
		if (tmp == NULL)
		{
			printf("relloc fail\n");
			exit(-1);
		}
		hp->a = tmp;
		hp->capacity = newCapacity;
	}
	hp->a[hp->size] = x;
	hp->size++;

	AdjustUp(hp->a,hp->size - 1);
}
void HeapPrint(HP* hp)
{
	for (int i = 0; i < hp->size; ++i)
	{
		printf("%d ", hp->a[i]);
	}
	printf("\n");
}
bool HeadEmpty(HP* hp)
{
	assert(hp);

	return hp->size == 0;
}
int HeapSize(HP* hp)
{
	assert(hp);

	return hp->size;
}
void HeapPop(HP* hp)
{
	assert(hp);
	assert(!HeadEmpty(hp));

	Swap(&hp->a[0], &hp->a[hp->size - 1]);
	hp->size--;

	AdjustDown(hp->a, hp->size, 0);
}