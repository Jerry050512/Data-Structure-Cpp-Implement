# 线性表

## 顺序表

> 初始化, 插入, 删除, 遍历, 清空, 销毁.  
> 求长度, 判断是否为空, 查找第i元素, 查找第i元素的前驱, 查找第i元素的后继.

- `seqlist-vector-ver.cpp` 是用stl中的vector实现的
- `seqlist-array-ver.cpp` 则是用数组实现的

## 链表

> 基本相同, 单向链表初始化分为前插和后插, 同时分有无头结点两种情况.  

- 单向链表
- 双向链表
- 循环链表 (此处只实现单向循环链表)
  - 示例: 演示约瑟夫问题

- 以上三种链表实现在 `linklist.cpp` 中
- `josephus.cpp` 通过调用 `linklist.cpp` 中的函数实现约瑟夫问题

## 线性表的合并

假设利用两个线性表La和Lb分别表示两个集合A和B, 现要求一个新的集合保存到La.

`linearlistmerge.cpp` 实现了线性表的合并.

## 有序表的合并

已知线性表La 和Lb中的数据元素按值非递减有序排列,现要求将La和Lb归并为一个新的线性表Lc,且Lc中的数据元素仍按值非递减有序排列. 

- 要求合并后的表无重复数据，如何实现？
- 将两个非递减的有序链表合并为一个非递增的有序链表，如何实现？

`orderlistmerge.cpp` 实现了有序表的合并.