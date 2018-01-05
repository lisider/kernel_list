#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"


typedef struct  _list_xxx_t{
	char name[20];
	int num;
	struct list_head list;
}list_xxx_t;


int main(void){
	int i;

	//链表头
	list_xxx_t list_xxx_head;
	//临时节点,用作每次遍历
	list_xxx_t *tmp_xxx_node;
	//临时节点 用作冒泡排序 中 的内层节点,是 外层节点的下一个节点
	list_xxx_t *tmp_xxx_node2; 
	//临时节点 用作冒泡排序 中 替换 的 中转
	list_xxx_t *tmp; 
	//临时变量 辅助性链表成员,用来遍历链表
	struct list_head *pos,*pos2,*n;


	// 1. 
	//初始化链表
	INIT_LIST_HEAD(&list_xxx_head.list);  


	// 2.
	//插入节点进链表

	for (i=0;i<3;i++){
		tmp_xxx_node = (list_xxx_t *)malloc(sizeof(list_xxx_t));
		tmp_xxx_node->num= i;
		sprintf(tmp_xxx_node->name,"list_xxx_t%d",i);

#ifdef  TAIL
		list_add_tail(&(tmp_xxx_node->list),&list_xxx_head.list);
#else
		list_add(&(tmp_xxx_node->list),&list_xxx_head.list);
#endif

	}

	// 3.
	//遍历
	list_for_each(pos,&list_xxx_head.list){
		tmp_xxx_node = list_entry(pos,list_xxx_t,list);

			printf("list_xxx_t num :\t%d\tname :\t%s\n",tmp_xxx_node->num,tmp_xxx_node->name);
	}


	// 4.
	// 查空
	if (list_empty(&list_xxx_head.list))
		printf("list is empty\n");
	else
		printf("list is not empty\n");

	// 5.
	//删除 的一种方式 ,代码可用
	
#if 0
	i = 0;
	list_for_each_safe(pos,n,&list_xxx_head.list){  		
		list_del(pos); // 注意,删除链表,是删除的list_head,还需要删除 外层的数据 ,删除一个节点之后,并没有破坏这个节点和外围数据的位置关系
		tmp_xxx_node = list_entry(pos,list_xxx_t,list);//得到外层的数据
		free(tmp_xxx_node);//释放数据
		printf("node %d has removed from the doublelist...\n",i++);
	}

	if (list_empty(&list_xxx_head.list))
		printf("list is empty\n");
	else
		printf("list is not empty\n");

#endif
#if 0

	// 5.
	// 删除的第二种方式,代码可用
	list_for_each_safe(pos,n,&list_xxx_head.list){  		
		tmp_xxx_node = list_entry(pos,list_xxx_t,list);//得到外层的数据
		if(1){ //对链表中的数据进行判断,如果满足条件就删节点
			list_del(pos); // 注意,删除链表,是删除的list_head,还需要删除 外层的数据 ,删除一个节点之后,并没有破坏这个节点和外围数据的位置关系
			free(tmp_xxx_node);//释放数据
		}
	}
#endif


	// 6.
	// 冒泡排序 
	printf("going to sort\n");


	tmp = (list_xxx_t *)malloc(sizeof(list_xxx_t));
	memset(tmp,0,sizeof(list_xxx_t));

	
	list_for_each(pos,&list_xxx_head.list){
		tmp_xxx_node = list_entry(pos,list_xxx_t,list);

		list_for_each(pos2,&tmp_xxx_node->list){
			tmp_xxx_node2 = list_entry(pos2,list_xxx_t,list);

			if(tmp_xxx_node2 == &list_xxx_head)
				break;

			//这里是排序的条件,//TODO
			//if(1 || 1){
			if(tmp_xxx_node->num > tmp_xxx_node2->num){
				//这里是交换,不需要变动,但是注意,结构体定义的时候 struct list_head list 成员要放在最后一个
				memcpy(tmp,tmp_xxx_node,sizeof(list_xxx_t)-sizeof(struct list_head));
				memcpy(tmp_xxx_node,tmp_xxx_node2,sizeof(list_xxx_t)-sizeof(struct list_head));
				memcpy(tmp_xxx_node2,tmp,sizeof(list_xxx_t)-sizeof(struct list_head));
			}
			
		} 
	}

	if (list_empty(&list_xxx_head.list))
		printf("list is empty\n");
	else
		printf("list is not empty\n");


	list_for_each(pos,&list_xxx_head.list){
		tmp_xxx_node = list_entry(pos,list_xxx_t,list);
		printf("list_xxx_t num :\t%d\tname :\t%s\n",tmp_xxx_node->num,tmp_xxx_node->name);
	}
	
	return 0;
}
