#ifndef REGION_GROWING
#define REGION_GROWING

struct Stack{
    int data;
    struct Stack *next;
};

void push(struct Stack **top, int data){
    struct Stack *ptr = (struct Stack *)malloc(sizeof(struct Stack));
    ptr->data = data;
    ptr->next = *top;
    *top = ptr;
}

void pop(struct Stack **top){
    struct Stack *ptr = *top;
    if(*top ==  NULL){
        // printf("\nStack is empty\n\n");
        return;
    }
    // printf("\nPopped element = %d\n\n", ptr->data);
    ptr = ptr->next;
    *top = ptr;
}

bool is_present_stack (struct Stack *top, int idx)
{
    struct Stack *ptr = top;
    if( top == NULL ){
        return false;
    }

    while( ptr != NULL ){
        if ( idx == ptr->data )
            return true;
        ptr = ptr->next;
    }
    return false;
}

struct Queue{
    int data;
    struct Queue *next;
};

void enqueue(struct Queue **front, struct Queue **rear, int q){
    struct Queue *qptr = (struct Queue *)malloc(sizeof(struct Queue));
    qptr->data = q;
    qptr->next = NULL;
    if(*front == NULL || *rear == NULL){
        *front = qptr;
        *rear = qptr;
    }
    else{
        struct Queue *ptr = *rear;  
        ptr->next = qptr;
        *rear = qptr;
    }
   
}

void dequeue(struct Queue **front, struct Queue **rear){
    if(*rear == NULL || *front == NULL){
        // printf("Queue is EMPTY!\n");
        return;
    }
    struct Queue *qptr = *front;
    // printf("Element out of the queue : %d\n", qptr->data);
    qptr = qptr->next;
    *front = qptr;
}

bool is_empty_queue (struct Queue *front, struct Queue *rear)
{
    if(rear == NULL || front == NULL)
        // printf("Queue is EMPTY!\n");
        return true;
    return false;

}

int generate_seed_row (int height)
{
    // srand(4);
    return (rand() % (height + 1));
}

int generate_seed_col (int width)
{
    // srand(4);
    return (rand() % (width + 1));
}

int get8n (int neighbours[], int idx, int width, int size)
{
    int i = 0;
    if ( (idx + width - 1 >= 0) && (idx + width - 1 < size) )
    {
        neighbours[i] = idx + width - 1;
        i++;
    }
    if ( (idx + width >= 0) && (idx + width < size) )
    {
        neighbours[i] = idx + width;
        i++;
    }
    if ( (idx + width + 1 >= 0) && (idx + width + 1 < size) )
    {
        neighbours[i] = idx + width + 1;
        i++;
    }
    if ( (idx - 1 >= 0) && (idx - 1 < size) )
    {
        neighbours[i] = idx - 1;
        i++;
    }
    if ( (idx + 1 >= 0) && (idx + 1 < size) )
    {
        neighbours[i] = idx + 1;
        i++;
    }
    if ( (idx - width - 1 >= 0) && (idx - width - 1 < size) )
    {
        neighbours[i] = idx - width - 1;
        i++;
    }
    if ( (idx - width >= 0) && (idx - width < size) )
    {
        neighbours[i] = idx - width;
        i++;
    }
    if ( (idx - width + 1 >= 0) && (idx - width + 1 < size) )
    {
        neighbours[i] = idx - width + 1;
        i++;
    }

    return i;

}


void region_growing (Image *input_img, Image *output_img)
{

    Image_create(output_img, input_img->width, input_img->height, input_img->channels, false);
    uint8_t *p, *pg, t = 120;
    int L = 256; 

    for(p = input_img->data, pg = output_img->data; p != (input_img->data + input_img->size); p += input_img->channels, pg += output_img->channels)
    {
   		// if (*p < t)
        // {
        //     *pg = 0;
        // }
        // else
        // {
        //     *pg = L - 1;
        // }
        *pg = *p;

        *p = 0;
    } 
    p = input_img->data;
    pg = output_img->data;

    // initialise seed and processed lists

    // seed queue
    struct Queue *front = (struct Queue *)malloc(sizeof(struct Queue));
    struct Queue *rear = (struct Queue *)malloc(sizeof(struct Queue));
    front = NULL;
    rear = NULL;

    // processed stack
    struct Stack *top = (struct Stack *)malloc(sizeof(struct Stack));
    top = NULL;

    // generate seed
    int row = generate_seed_row(output_img->height);
    int col = generate_seed_col(output_img->width);
    // int row = 100;
    // int col = 100;
    printf("Random pixel coordinate generated = (%d, %d)\n", row, col);

    int idx = output_img->width * row + col; 

    enqueue(&front, &rear, idx);

    int neighbours[8], n, count = 0;

    while( !is_empty_queue(front, rear) )
    // while( count < 100000 || !is_empty_queue(front, rear) )
    {
        idx = front->data;
        *(p + idx) = L - 1;
        n = get8n(neighbours, idx, output_img->width, input_img->size);

        for (int i = 0; i < n; i++)
        {
            if ( abs(*(pg + neighbours[i]) - *(pg + idx)) <= 8 )
            {
                *(p + neighbours[i]) = L - 1;
                if ( !is_present_stack(top, neighbours[i]) )
                {
                    enqueue(&front, &rear, neighbours[i]);
                // }
                    push(&top, neighbours[i]);
                }
            }
        }
        dequeue(&front, &rear);
        // printf("helloooo\n");
        count++;

    }

    // while( !is_empty_queue(front, rear) )
    // // while( count < 100000 || !is_empty_queue(front, rear) )
    // {
    //     idx = front->data;
    //     *(p + idx) = L - 1;
    //     n = get8n(neighbours, idx, output_img->width, input_img->size);

    //     for (int i = 0; i < n; i++)
    //     {
    //         if ( *(pg + neighbours[i]) != 0 )
    //         {
    //             *(p + neighbours[i]) = L - 1;
    //             if ( !is_present_stack(top, neighbours[i]) )
    //             {
    //                 enqueue(&front, &rear, neighbours[i]);
    //             // }
    //                 push(&top, neighbours[i]);
    //             }
    //         }
    //     }
    //     dequeue(&front, &rear);
    //     // printf("helloooo\n");
    //     count++;

    // }

    printf("DONE here\n");

    for(p = input_img->data, pg = output_img->data; p != (input_img->data + input_img->size); p += input_img->channels, pg += output_img->channels)
    {
        *pg = *p;
    } 

}


#endif