#include "downloader.h"
#define textq cs_rawText_queue
#define text  cs_rawText_t

/*
  判断数据队列是否未空
*/
int isDataQueueEmpty(cs_rawText_queue *head) {
  return (head->next == head);
}
/*
新建头节点
*/
textq *initDataQueue() {
  textq *queue = (textq*) malloc(sizeof(textq));
  queue->next = queue;
  queue->prev = queue;
  queue->data = NULL;
  return queue;
}

/*
  创建节点
*/
text *createData(const char* type) {
  text *node = (text*)malloc(sizeof(text));
  
  node->count = 0;
  node->length = 0;
  node->type = type;
  
  return node;
}

/*
  将获取到的数据加入队列
*/
void addData(textq *head, textq *queue) {

  
  queue->next = head;
  queue->prev = head->prev;
  queue->next->prev = queue;
  queue->prev->next = queue;
  return;
}
/*
  从队列中取出数据
*/
textq *removeData(textq *head, text *data) {
  textq *p = head->next;
  textq *res = NULL;

  while (p != head) {
    if (p->data == data) {
      res = p;
      p->prev->next = p->next;
      p->next->prev = p->prev;
      break;
    } else {
      p = p->next;
    }
  }
  
  return res;
}
/*
回收数据
*/
void freeData(textq *node) {
  free(node->data->worker);
  int i;
  for (i = 0; i < node->data->count; i++) {
    //逐个free数据块
    free(node->data->data[i]);
  }
  
  free(node->data);
  free(node);
}
