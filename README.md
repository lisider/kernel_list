- 是什么

```c

内核链表

```

- 概念性基础
```c
注意: 内核是双链表 ,链表的遍历 是 从 下个节点 到 前一个节点 不包括第一个节点

所以如果从头结点遍历 

//首先当前节点是头结点,头结点的结构和普通节点的结构一样,都有数据信息,但是数据信息是脏的
//我们存储的数据 不在头结点里面 

//下面的遍历不会经过当前节点(头结点)
list_for_each(pos,&list_xxx_head.list){
    tmp_xxx_node = list_entry(pos,list_xxx_t,list);

    //
}

刚好能遍历一圈,头结点的结构和普通节点的结构一样,只是 数据部分没有赋值,是脏的


如果你要从任意一个节点遍历,则要

//首先当前节点已经得到了.

//下面的遍历不会经过当前节点
list_for_each(pos2,&tmp_xxx_node->list){
    tmp_xxx_node2 = list_entry(pos2,list_xxx_t,list);

    if(tmp_xxx_node2 == &list_xxx_head)
        continue;

    //
}

如果你要从任意一个节点遍历到头结点为止,则要


//首先当前节点已经得到了.

//下面的遍历不会经过当前节点
list_for_each(pos2,&tmp_xxx_node->list){
    tmp_xxx_node2 = list_entry(pos2,list_xxx_t,list);

    if(tmp_xxx_node2 == &list_xxx_head)
        break;

    //
}

```

---

- 内核链表 api

```c

链表api
    初始化 init
头插(相对于头)
    尾插 add
    删 del
    替换 replace
移动(mov 到 另一个链表 头 或者 尾部)
    last 判定
    空判定 empty
    镜像翻转 rotate
    singular 判定
    切割一个链表成两个链表 cut
    粘贴两个链表成一个链表 splice

    从 list_head * pos 找 外层链表地址 
    list_entry
    list_first_entry

循环
    list_for_each
    list_for_each_prev
    list_for_each_safe
    list_for_each_prev_safe
    list_for_each_entry

    带safe 的 函数 是为了 删除节点时的安全.可以解决单cpu调度(宏观并发)的问题

    遍历推荐使用
    list_for_each_entry

```





