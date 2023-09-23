#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

// Helper function to create a new node with the given value.
node_t *create_node(elem value) {
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (new_node == NULL) {
        perror("Failed to allocate memory for node");
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

list_t *list_alloc() {
    list_t *new_list = (list_t *)malloc(sizeof(list_t));
    if (new_list == NULL) {
        perror("Failed to allocate memory for list");
        exit(EXIT_FAILURE);
    }
    new_list->head = NULL;
    return new_list;
}

void list_free(list_t *l) {
    if (l == NULL) {
        return; // Nothing to free if the list is NULL.
    }

    node_t *current = l->head;
    while (current != NULL) {
        node_t *next = current->next;
        free(current);
        current = next;
    }

    free(l);
}

void list_print(list_t *l) {
    if (l == NULL) {
        printf("List is NULL\n");
        return;
    }

    node_t *current = l->head;
    while (current != NULL) {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

int list_length(list_t *l) {
    if (l == NULL) {
        return 0;
    }

    int length = 0;
    node_t *current = l->head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

void list_add_to_back(list_t *l, elem value) {
    if (l == NULL) {
        return;
    }

    node_t *new_node = create_node(value);

    if (l->head == NULL) {
        l->head = new_node;
    } else {
        node_t *current = l->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void list_add_to_front(list_t *l, elem value) {
    if (l == NULL) {
        return;
    }

    node_t *new_node = create_node(value);

    new_node->next = l->head;
    l->head = new_node;
}

void list_add_at_index(list_t *l, elem value, int index) {
    if (l == NULL || index < 0) {
        return;
    }

    if (index == 0) {
        list_add_to_front(l, value);
        return;
    }

    node_t *new_node = create_node(value);
    node_t *current = l->head;
    int current_index = 0;

    while (current != NULL && current_index < index - 1) {
        current = current->next;
        current_index++;
    }

    if (current == NULL) {
        free(new_node); // Index out of bounds; free the new node.
        return;
    }

    new_node->next = current->next;
    current->next = new_node;
}

elem list_remove_from_back(list_t *l) {
    if (l == NULL || l->head == NULL) {
        return -1; // List is empty, or it's NULL.
    }

    if (l->head->next == NULL) {
        // Only one element in the list.
        elem value = l->head->value;
        free(l->head);
        l->head = NULL;
        return value;
    }

    node_t *current = l->head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    elem value = current->next->value;
    free(current->next);
    current->next = NULL;
    return value;
}

elem list_remove_from_front(list_t *l) {
    if (l == NULL || l->head == NULL) {
        return -1; // List is empty, or it's NULL.
    }

    node_t *front = l->head;
    elem value = front->value;
    l->head = front->next;
    free(front);
    return value;
}

elem list_remove_at_index(list_t *l, int index) {
    if (l == NULL || l->head == NULL || index < 0) {
        return -1; // List is empty, or it's NULL, or index is negative.
    }

    if (index == 0) {
        return list_remove_from_front(l);
    }

    node_t *current = l->head;
    int current_index = 0;

    while (current->next != NULL && current_index < index - 1) {
        current = current->next;
        current_index++;
    }

    if (current->next == NULL) {
        return -1; // Index out of bounds.
    }

    node_t *removed_node = current->next;
    elem value = removed_node->value;
    current->next = removed_node->next;
    free(removed_node);
    return value;
}

bool list_is_in(list_t *l, elem value) {
    if (l == NULL) {
        return false;
    }

    node_t *current = l->head;
    while (current != NULL) {
        if (current->value == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

elem list_get_elem_at(list_t *l, int index) {
    if (l == NULL || l->head == NULL || index < 0) {
        return -1; // List is empty, or it's NULL, or index is negative.
    }

    node_t *current = l->head;
    int current_index = 0;

    while (current != NULL && current_index < index) {
        current = current->next;
        current_index++;
    }

    if (current == NULL) {
        return -1; // Index out of bounds.
    }

    return current->value;
}

int list_get_index_of(list_t *l, elem value) {
    if (l == NULL) {
        return -1;
    }

    node_t *current = l->head;
    int index = 0;

    while (current != NULL) {
        if (current->value == value) {
            return index;
        }
        current = current->next;
        index++;
    }

    return -1; // Value not found in the list.
}
