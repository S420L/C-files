#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "matrix.h"

// Search TODO to find the locations where code needs to be completed

#define     NUM_THREADS     2

typedef struct {
    unsigned int id;
    TMatrix *m, *n, *t;
} thread_arg_t;

static void * thread_main(void * p_arg)
{
    thread_arg_t * thread_data = p_arg;
    //printf("OMG HERE IN THREAD!!\n");
    //printf("Matrix t: %p\n",thread_data->t);
    //printf("Matrix t->nrows: %d\n",thread_data->t->nrows);
    //printf("Matrix t->ncols: %d\n",thread_data->t->ncols);

    int first_half = (int)(thread_data->m->nrows/2);
    for (unsigned int i = first_half; i < thread_data->m->nrows; i++)  {
        for (unsigned int j = 0; j < thread_data->n->ncols; j++) {
            TElement sum = (TElement)0;
            for (unsigned int k = 0; k < thread_data->m->ncols; k++)
                sum += thread_data->m->data[i][k] * thread_data->n->data[k][j];
            thread_data->t->data[i][j] = sum;
        }
    }

    return NULL;
}

/* Return the sum of two matrices.
 *
 * If any pthread function fails, report error and exit. 
 * Return NULL if anything else is wrong.
 *
 * Similar to mulMatrix, but with multi-threading.
 */
TMatrix * mulMatrix_thread(TMatrix *m, TMatrix *n)
{
    if (    m == NULL || n == NULL
         || m->ncols != n->nrows )
        return NULL;

    TMatrix * t = newMatrix(m->nrows, n->ncols);
    
    if (t == NULL)
        return t;
    pthread_t t1;
    thread_arg_t * thread_data = malloc(sizeof(thread_arg_t));
    thread_data->id = 1;
    thread_data->m = m;
    thread_data->n = n;
    thread_data->t = t;
    
    int rc;
    rc = pthread_create(&t1,NULL,&thread_main,thread_data);
    if (rc) {
            		printf("ERROR; return code from pthread_create() is %d\n", rc);
            		exit(-1);
        	}

    int first_half = (int)(m->nrows/2);
    for (unsigned int i = 0; i < first_half; i++)  {
        for (unsigned int j = 0; j < n->ncols; j++) {
            TElement sum = (TElement)0;
            for (unsigned int k = 0; k < m->ncols; k++)
                sum += m->data[i][k] * n->data[k][j];
            t->data[i][j] = sum;
        }
    }
    
    
    pthread_join(t1, NULL);

    return t;
}