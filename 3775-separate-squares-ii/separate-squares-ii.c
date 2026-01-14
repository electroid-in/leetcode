#include <stdlib.h>
#include <string.h>

typedef long long ll;

/* ---------- Event ---------- */
typedef struct {
    ll y;
    int type;   // +1 = enter, -1 = exit
    ll x1, x2;
} Event;

/* ---------- Segment Tree ---------- */
typedef struct {
    int count;
    ll length;
} Node;

static Node *seg;
static ll *xs;
static int XN;

/* ---------- Utilities ---------- */
int cmp_event(const void *a, const void *b) {
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;
    if (e1->y < e2->y) return -1;
    if (e1->y > e2->y) return 1;
    return e1->type - e2->type;
}

int cmp_ll(const void *a, const void *b) {
    ll x = *(ll *)a, y = *(ll *)b;
    return (x > y) - (x < y);
}

/* lower_bound for xs[] */
int getX(ll x) {
    int l = 0, r = XN;
    while (l < r) {
        int m = (l + r) / 2;
        if (xs[m] < x) l = m + 1;
        else r = m;
    }
    return l;
}

/* ---------- Segment Tree Ops ---------- */
void push_up(int idx, int l, int r) {
    if (seg[idx].count > 0) {
        seg[idx].length = xs[r] - xs[l];
    } else if (r - l == 1) {
        seg[idx].length = 0;
    } else {
        seg[idx].length =
            seg[idx * 2].length + seg[idx * 2 + 1].length;
    }
}

void update(int idx, int l, int r, int ql, int qr, int val) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {
        seg[idx].count += val;
        push_up(idx, l, r);
        return;
    }
    int m = (l + r) / 2;
    update(idx * 2, l, m, ql, qr, val);
    update(idx * 2 + 1, m, r, ql, qr, val);
    push_up(idx, l, r);
}

/* ---------- Main ---------- */
double separateSquares(int **squares, int n, int *cols) {
    Event *events = malloc(sizeof(Event) * 2 * n);
    xs = malloc(sizeof(ll) * 2 * n);

    for (int i = 0; i < n; i++) {
        ll x = squares[i][0];
        ll y = squares[i][1];
        ll l = squares[i][2];

        events[2*i]   = (Event){y, +1, x, x + l};
        events[2*i+1] = (Event){y + l, -1, x, x + l};

        xs[2*i]   = x;
        xs[2*i+1] = x + l;
    }

    qsort(events, 2*n, sizeof(Event), cmp_event);
    qsort(xs, 2*n, sizeof(ll), cmp_ll);

    XN = 0;
    for (int i = 0; i < 2*n; i++) {
        if (i == 0 || xs[i] != xs[i-1])
            xs[XN++] = xs[i];
    }

    seg = calloc(4 * XN, sizeof(Node));

    /* ---------- First sweep: total area ---------- */
    ll prevY = events[0].y;
    long double total = 0;

    for (int i = 0; i < 2*n; i++) {
        ll y = events[i].y;
        ll dy = y - prevY;
        if (dy > 0)
            total += (long double)seg[1].length * dy;

        int l = getX(events[i].x1);
        int r = getX(events[i].x2);
        update(1, 0, XN - 1, l, r, events[i].type);

        prevY = y;
    }

    long double target = total / 2.0;

    /* ---------- Second sweep: find y ---------- */
    memset(seg, 0, sizeof(Node) * 4 * XN);
    prevY = events[0].y;
    long double acc = 0;

    for (int i = 0; i < 2*n; i++) {
        ll y = events[i].y;
        ll dy = y - prevY;
        ll L = seg[1].length;

        if (dy > 0 && L > 0) {
            long double slab = (long double)L * dy;
            if (acc + slab >= target) {
                long double need = target - acc;
                return (double)(prevY + need / L);
            }
            acc += slab;
        }

        int l = getX(events[i].x1);
        int r = getX(events[i].x2);
        update(1, 0, XN - 1, l, r, events[i].type);

        prevY = y;
    }

    return (double)prevY;
}
