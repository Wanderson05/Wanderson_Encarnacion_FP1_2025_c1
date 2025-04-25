def es_reflexiva(R):
    n = len(R)
    for i in range(n):
        if R[i][i] != 1:
            return False
    return True
