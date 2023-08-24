// DO NOT INCLUDE ANY OTHER LIBRARIES/FILES
#include "pointer.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// In this assignment, you can assume that function parameters are valid and the memory is managed by the caller //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Returns the area of a rectangle
// The shape is guaranteed to be a valid rectangle
double rectangle_area(void* shape)
{
    rectangle_t* rectangle = (rectangle_t*)shape;
    // IMPLEMENT THIS
    //double area = rectangle->length*rectangle->width;
    double area = (double)rectangle->length*(double)rectangle->width;
    printf("area = %f",area);
    return area;
}

// Returns the area of an equilateral triangle
// The shape is guaranteed to be a valid triangle
// The area of an equilateral triangle is sqrt(3)/4 times length squared
double triangle_area(void* shape)
{
    triangle_t* triangle = (triangle_t*)shape;
    // IMPLEMENT THIS
    double area = (double)triangle->length * ((double)triangle->length)*sqrt(3)/4;
    return area;
}

// Returns the perimeter of a rectangle
// The shape is guaranteed to be a valid rectangle
double rectangle_perimeter(void* shape)
{
    rectangle_t* rectangle = (rectangle_t*)shape;
    // IMPLEMENT THIS
    double perimeter = (double)rectangle->length*2 + (double)rectangle->width*2;
    return perimeter;
}

// Returns the perimeter of an equilateral triangle
// The shape is guaranteed to be a valid triangle
double triangle_perimeter(void* shape)
{
    triangle_t* triangle = (triangle_t*)shape;
    // IMPLEMENT THIS
    double perimeter = triangle->length*3;
    return perimeter;
}

// Initializes a rectangle shape
void rectangle_construct(rectangle_t* shape, const char* name, double width, double length)
{
    // IMPLEMENT THIS
    //rectangle_t s1;
    
    shape->width = width;
    shape->length = length; 
    shape->shape.name = name;
    shape->shape.edges = 4;
    shape->shape.virtual_func_table.area = rectangle_area;
    shape->shape.virtual_func_table.perimeter = rectangle_perimeter;
    //shape=&s1;
    }

// Initializes a triangle shape
void triangle_construct(triangle_t* shape, const char* name, double length)
{
    // IMPLEMENT THIS
    //triangle_t s2;

    shape->length = length;
    shape->shape.name = name;
    shape->shape.edges = 3;
    shape->shape.virtual_func_table.area= triangle_area;
    shape->shape.virtual_func_table.perimeter = triangle_perimeter;
    //shape=&s2;
}

// Compares the area of shape1 with shape2
// Returns -1 if the area of shape1 is less than the area of shape2
// Returns 1 if the area of shape1 is greater than the area of shape2
// Returns 0 if the area of shape1 is equal to the area of shape2
int compare_by_area(shape_t* shape1, shape_t* shape2)
{
    double area1 = shape1->virtual_func_table.area(shape1);
    double area2 = shape2->virtual_func_table.area(shape2);
    // IMPLEMENT THIS
    if(area1 == area2){
        return 0;        
    }
    else if(area1>area2){
        return 1;
    }
    else{
        return -1;
    }

    
}

// Compares the perimeter of shape1 with shape2
// Returns -1 if the perimeter of shape1 is less than the perimeter of shape2
// Returns 1 if the perimeter of shape1 is greater than the perimeter of shape2
// Returns 0 if the perimeter of shape1 is equal to the perimeter of shape2
int compare_by_perimeter(shape_t* shape1, shape_t* shape2)
{
    double perimeter1 = shape1->virtual_func_table.perimeter(shape1);
    double perimeter2 = shape2->virtual_func_table.perimeter(shape2);

    // IMPLEMENT THIS
    if(perimeter1 == perimeter2){
        return 0;        
    }
    else if(perimeter1>perimeter2){
        return 1;
    }
    else{
        return -1;
    }
}

//
// Linked list functions
//

// Initializes a singly linked list
// If compare is NULL, the list is unsorted and new nodes are inserted at the head of the list
// If compare is not NULL, the list is sorted in increasing order based on the comparison function
void linked_list_init(linked_list_t* list, compare_fn compare)
{
    // IMPLEMENT THIS
    //
    if (compare == NULL){
        list->head = NULL;
        list->compare = NULL;
    }
    else {
        list->head = NULL;
        list->compare = compare;
        
    }

}

// Inserts a node into the linked list based on the list comparison function
void linked_list_insert(linked_list_t* list, linked_list_node_t* node)
{
    // IMPLEMENT THIS
    if (list->compare == NULL){
        if(list->head == NULL){
            list->head = node;
            node->next = NULL;
        }
        else{
            node->next = list->head;
            list->head = node;
        }
    }
    else{
        if(list->head == NULL){
            list->head = node;
            node->next = NULL;
        }
        else if(list->head->next == NULL){
          
           
            if(list->compare(list->head->shape, node->shape)== -1){
                node->next = NULL;
                list->head->next = node;
            }
            else{
                node->next = list->head;
                list->head = node;
            }
           }
        else if(list->compare(list->head->shape, node->shape)== 1){
            node->next = list->head;
            list->head = node;
        }
        else{
            linked_list_node_t* current = list->head;
            while (current->next != NULL && list->compare(current->next->shape, node->shape)== -1){
            current = current->next;
           }
           if(current->next == NULL){
            if(list->compare(current->shape, node->shape)== -1){
                node->next = NULL;
                current->next = node;
            }
            else{
                node->next = NULL;
                current->next = node;
            }
           }
           else{
            node->next = current->next;
            current->next = node;
           }
        }
        
           
    }
    
}

// Removes all nodes from the linked list containing the given shape
void linked_list_remove(linked_list_t* list, shape_t* shape)
{
    // IMPLEMENT THIS
    while(list->head->shape == shape){
        list->head = list->head->next;
    }
    linked_list_node_t* current = list->head;
    while (current->next != NULL && current != NULL ){
        if(current->next->shape == shape){
            if(current->next->next == NULL){
                current->next = NULL;
                break;
            }
            current->next = current->next->next;
        }
        else{
            current = current->next;
        }
    }
}

//
// Tree iterator functions
//
int num = 0;
// Initializes an iterator to the beginning of a tree (i.e., first in-order node)
void tree_iterator_begin(tree_iterator_t* iter, tree_node_t* root)
{
   // IMPLEMENT THIS
   if(root == NULL){
        iter->curr = NULL;
        iter->depth = 0;
        //iter->parents = NULL;
    }
    else{
        iter->curr = root;
        iter->depth = 0;
    }
    
}

// Updates an iterator to move to the next in-order node in the tree if possible
// Moving past the last in-order node in the tree results in the iterator reaching a NULL state representing the end of the tree
void tree_iterator_next(tree_iterator_t* iter)
{
    //IMPLEMENT THIS
    if(iter->curr != NULL){
        if(iter->curr->right == NULL && iter->curr->left == NULL){
            iter->curr = NULL;
           
        } 
        else if(iter->curr->left != NULL){
            while (iter->curr->left != NULL)
            {
                iter->parents[num]=(iter->curr);
                num += 1;
                iter->depth += 1;
                iter->curr = iter->curr->left;
            }
            
        }
        else if(iter->curr->right != NULL){
            iter->curr = iter->curr->right;
            iter->depth = iter->depth+1;
        }
        else{
            iter->curr = iter->parents[iter->depth - 1];
        }
    }


}

// Returns true if iterator is at the end of the tree or false otherwise
// The end of the tree is the position after the last in-order node in the tree (i.e., NULL state from tree_iterator_next)
bool tree_iterator_at_end(tree_iterator_t* iter)
{
    //IMPLEMENT THIS
    if(iter->curr == NULL){
        return true;
    }
    //tree_iterator_next(iter);
    return false;
}

// Returns the current node that the iterator references or NULL if the iterator is at the end of the list
tree_node_t* tree_iterator_get_node(tree_iterator_t* iter)
{
    // IMPLEMENT THIS
    if(tree_iterator_at_end(iter)==true){
        return NULL;
    }
    else{
        return iter->curr;
    }
    return NULL;
}

// Returns the current shape that the iterator references or NULL if the iterator is at the end of the list
shape_t* tree_iterator_get_shape(tree_iterator_t* iter)
{
    //IMPLEMENT THIS
    if(tree_iterator_at_end(iter)==true){
        return NULL;
    }
    else{
        return iter->curr->shape;
    }
    return NULL;
}

//
// Tree analysis functions
//

// Returns the maximum, minimum, and average area of shapes in the tree
// An empty tree should not modify the maximum, minimum, or average
void max_min_avg_area(tree_node_t* root, double* max, double* min, double* avg)
{
    // IMPLEMENT THIS
    if(root == NULL){
        double neg = -1;
        *max = neg;
        *min = neg;
        *avg = neg;
    }
    else if (root->left == NULL&&root->right == NULL)
    {
        *max = rectangle_area(root->shape);
        *min = rectangle_area(root->shape);
        *avg = rectangle_area(root->shape);
    }
    else{
        *max=0;
        if(root->shape->edges == 4){
                *min = rectangle_area(root->shape);
            }
            else{
                *min = triangle_area(root->shape);
            }
        //*min = rectangle_area(root->shape);
        *avg = 0;
        double nums = 0;
        while (root->left != NULL || root->right != NULL)
        {
            double area;
            if(root->shape->edges == 4){
                area = rectangle_area(root->shape);
            }
            else{
                area = triangle_area(root->shape);
            }
            if(*max < area){
                *max = area;
            }
            if(*min > area){
                *min = area;
            }
            *avg+=area;
            nums += 1;
            if(root->left == NULL){
                root = root->right;
            }
            else if (root->right == NULL){
                root = root -> left;
            }
            else{

            }
        }
        double area;
        if(root->shape->edges == 4){
            area = rectangle_area(root->shape);
            }
            else{
                area = triangle_area(root->shape);
            }
            if(*max < area){
                *max = area;
            }
            if(*min > area){
                *min = area;
            }
            *avg+=area;
            nums += 1;
        *avg = (double)*avg/nums;
    }
}

// Executes the func function for each node in the tree in-order
// The function takes in an input data and returns an output data, which is used as input to the next call to the function
// The initial input data is provided as a parameter to foreach, and foreach returns the final output data
// For example, if there are three nodes, foreach should behave like: return func(node3, func(node2, func(node1, data)))
double foreach(tree_node_t* root, foreach_fn func, double data)
{
    // IMPLEMENT THIS
    if(root == NULL){
        return 1;
    }
    else if (root->left == NULL&&root->right == NULL)
    {
        return func(root->shape,data);
    }
    else{
        int si =0;
        double result = func(root->shape,(data));
        shape_t li[7];
        int a = 0;
        while (root->left != NULL || root->right != NULL)
        {
            if(root->left == NULL){
                root = root->right;
                result = func(root->shape, result);
            }
            else {
                // si =1;
                // li[a]=root->shape;
                // a+=1;
                // root = root -> left;
                //result = func(root->shape, result);
            }
        }
        //printf("%f",result);
        // if(si ==1){
        //     result = func(root->shape,(data));
        //     for (int i = 6;i >= 0;i--){
        //         result = func(li[i]->shape,result);

        //     }
        //     while (root->left != NULL || root->right != NULL)
        // {
        //     if(root->left == NULL){
        //         root = root->right;
        //         result = func(root->shape, result);
        //     }
        //     else {
        //         si =1;
        //         root = root -> left;
        //         //result = func(root->shape, result);
        //     }
        // }
       // }
        return result;
    }
}