struct variant
{
	union {
		char c;
		int i;
		long l;
	} value;
	
	enum {
		CHAR,
		INT,
		LONG
	} kind;
};

int f(int x, int y) requires (x > 0 && y > 0)
                    ensures (RETURN < 0)
{
	/* blabla */
}

char* getChar(struct variant* vp)
{
	if (vp->kind == CHAR)
		return (char*)vp->value.c;
	return NULL;
}
int* getInt(struct variant* vp);
long* getLong(struct variant* vp);

#define SETTER(T, M, K) \
	void set##T(struct variant* vp, \
			    T M)
     {
	    vp->kind = K;
	    vp->value.##M = ##M;
	 }

SETTER(char, c, CHAR)
SETTER(int, i, INT)
SETTER(long, l, LONG)
                      

void setChar_(struct variant* vp, char c)
{
	vp->kind = CHAR;
	vp->value.c = c;
}
