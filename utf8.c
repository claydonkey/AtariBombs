*w = L"ÿóÿ­ÿþoÜüðààÀ!ÀCÀCàðø?þ";

f(r, i, j, m) {
    for (i; i < 32; i += 2, puts("")) {
	for (j = r; j--;) {
	    for (m = 65536; m > 1; (m >>= 1, printf(((w[i+1] << 8) + w[i ] & m) ? "  " : "##")));
	}
    }
}

main(c, v)char**v;
{
    f(atoi(v[1]),0);
}
