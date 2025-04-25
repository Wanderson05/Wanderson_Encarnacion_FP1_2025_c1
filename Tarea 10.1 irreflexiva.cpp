def es_irreflexiva(R):
    n = len(R)
    for i in range(n):
        if R[i][i] != 0:
            return False
    return True
