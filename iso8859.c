f(r, i, j, d) {
    for (; i < 32; i += 2, puts("")) {
	    for (d = 15*r; --d > 0;) {
		printf("%s", (*(unsigned int*) &("������o������!�C�C���?�"[i]))&(1 << d%15) ? "  " : "##");
	    }
    }
}

main(c, v)char**v;
{
    f(atoi(v[1]), 0);
}