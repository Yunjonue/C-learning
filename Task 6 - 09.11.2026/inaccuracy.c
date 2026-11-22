double Inaccuracy (double t1, double t2, double accuracy) {
    double res = fabs(t2)/(1 - fabs(t2/t1));
    if ((fabs(t2/t1) < 1) && (res < accuracy))
        return 1;
    return 0;
};