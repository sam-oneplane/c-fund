#include <math.h>
#include "c_class.h"

double func(double arg) {
    double x = log(arg);
    return x;
}

double nums[] = {30, 40, 50};

int main(int argc, char **argv) {

    func_ptr f = &func;
    task_t *t_new = task_create(10, f);
    printf("%lf\n", (t_new->f)(nums[2])); 
    
    task_t *t_clone = task_clone(t_new);
    fprintf(stdout, "%lf\n", t_clone->f(nums[0]));

    task_t *t_move = task_move(t_new);
    fprintf(stdout, "%lf\n", t_move->f(nums[1]));

    task_free(t_clone);
    task_free(t_move);
    
    return 0;
}
