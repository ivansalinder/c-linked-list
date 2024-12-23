#include <stdio.h>
#include <stdlib.h>

/*
Структура односвязного списка
value: значение целочисленного типа
next: указатель на следующую ноду списка

typedef нужен, что-бы писать
ll_t *root
вместо
struct ll_s *root
(более короткая запись)
*/
typedef struct ll_s {
  int value;
  struct ll_s *next;
} ll_t;

/*
ll_new_node выделяет память под новую ноду списка
и проставляет дефолтные значения
*/
ll_t *ll_new_node(int value) {
  ll_t *node = malloc(sizeof(ll_t));
  node->value = value;
  node->next = NULL;
  return node;
}

// Создаёт новый список из единственной ноды со значением 0
ll_t *ll_new() { return ll_new_node(0); }

// Очищает динамическую память, выделенную под ноды списка
void ll_free(ll_t *root) {
  while (root != NULL) {
    ll_t *next = root->next;
    free(root);
    root = next;
  }
}

// Добавляет значение в конец списка
void ll_append(ll_t *root, int value) {
  while (root->next != NULL) {
    root = root->next;
  }
  root->next = ll_new_node(value);
}

// Добавляет значение в начало спика. Изменяет указатель на начало
void ll_prepend(ll_t **root, int value) {
  ll_t *new_first = ll_new_node(value);
  new_first->next = *root;
  *root = new_first;
}

// Получает указатель на значение по индексу списка
// В случае, если idx больше чем длина_списка-1, возвращает NULL
int *ll_get(ll_t *root, size_t idx) {
  for (int i = 0; i < idx; i++) {
    if (root->next == NULL) {
      return NULL;
    }
    root = root->next;
  }
  return &root->value;
}

// Изменяет значение по индексу в списке
// В случае, если idx больше чем длина_списка-1, ничего не делает
void ll_set(ll_t *root, size_t idx, int value) {
  for (int i = 0; i < idx; i++) {
    if (root->next == NULL) {
      return;
    }
    root = root->next;
  }
  root->value = value;
}

// Вставляет новое значение в список по индексу
void ll_insert(ll_t **root, size_t idx, int value) {
  if (idx == 0) {
    ll_prepend(root, value);
    return;
  }

  ll_t *rootp = *root;
  for (int i = 0; i < idx - 1; i++) {
    if (rootp->next == NULL) {
      return;
    }
    rootp = rootp->next;
  }
  ll_t *new_node = ll_new_node(value);
  new_node->next = rootp->next;
  rootp->next = new_node;
}

// Удаляет ноду по в списке по индексу, очищая память
void ll_delete(ll_t **root, size_t idx) {
  if (idx == 0) {
    ll_t *new_root = (*root)->next;
    free(*root);
    *root = new_root;
    return;
  }

  ll_t *rootp = *root;
  for (int i = 0; i < idx - 1; i++) {
    if (rootp->next == NULL) {
      return;
    }
    rootp = rootp->next;
  }
  ll_t *next = rootp->next;
  rootp->next = next->next;
  free(next);
}

// Получает длину списка
size_t ll_length(ll_t *root) {
  size_t length = 0;
  while (root != NULL) {
    root = root->next;
    length++;
  }
  return length;
}

// Печатает длину спика
void ll_print(ll_t *root) {
  printf("%d", root->value);
  while (root->next != NULL) {
    root = root->next;
    printf(" %d", root->value);
  }
  printf("\n");
}

int main(void) {
  ll_t *ll = ll_new();
  ll_append(ll, 1);
  ll_append(ll, 2);
  ll_append(ll, 3);
  ll_append(ll, 4);
  ll_append(ll, 5);
  ll_prepend(&ll, 42);
  ll_print(ll);

  ll_insert(&ll, 0, 48);
  ll_print(ll);
  ll_delete(&ll, 0);
  ll_print(ll);
  ll_insert(&ll, 2, 256);
  ll_print(ll);
  ll_delete(&ll, 2);
  ll_print(ll);
  ll_free(ll);
}
