#ifndef KITTEN_H
#define KITTEN_H
#include "debug.h"
#include "types.h"

#define OPERATOR_DECLARATION(NAME) \
	void kitten_##NAME(Boxed stack, Boxed definitions)

OPERATOR_DECLARATION(add);
OPERATOR_DECLARATION(div);
OPERATOR_DECLARATION(mod);
OPERATOR_DECLARATION(mul);
OPERATOR_DECLARATION(sub);

#undef OPERATOR_DECLARATION

void  kitten_apply   (Boxed stack, Boxed definitions);
void  kitten_compose (Boxed stack, Boxed definitions);
void  kitten_dup     (Boxed stack, Boxed definitions);
void  kitten_eq      (Boxed stack, Boxed definitions);
void  kitten_ge      (Boxed stack, Boxed definitions);
void  kitten_gt      (Boxed stack, Boxed definitions);
void  kitten_if      (Boxed stack, Boxed definitions);
void  kitten_isf     (Boxed stack, Boxed definitions);
void  kitten_isi     (Boxed stack, Boxed definitions);
void  kitten_isq     (Boxed stack, Boxed definitions);
void  kitten_isw     (Boxed stack, Boxed definitions);
void  kitten_le      (Boxed stack, Boxed definitions);
void  kitten_lt      (Boxed stack, Boxed definitions);
void  kitten_ne      (Boxed stack, Boxed definitions);
void  kitten_pop     (Boxed stack, Boxed definitions);
void  kitten_quote   (Boxed stack, Boxed definitions);
void  kitten_swap    (Boxed stack, Boxed definitions);
void  kitten_write   (Boxed stack, Boxed definitions);
void  push           (Boxed stack, Boxed reference);

/* Literals. */
#define MKF(a)        float_new(a)
#define MKI(a)        integer_new(INT64_C(a))
#define MKQ(n, ...)   quotation_new(n, __VA_ARGS__)
#define MKW(a)        word_new(-a - 1)
#define PUSHF(a)      push(stack, MKF(a));
#define PUSHI(a)      push(stack, MKI(a));
#define PUSHQ(n, ...) push(stack, MKQ(n, __VA_ARGS__));
/* Built-in words. */
#define DUP         map[WORD_DUP]       (stack, definitions);
#define SWAP        map[WORD_SWAP]      (stack, definitions);
#define POP         map[WORD_POP]       (stack, definitions);
#define QUOTE       map[WORD_QUOTE]     (stack, definitions);
#define COMPOSE     map[WORD_COMPOSE]   (stack, definitions);
#define APPLY       map[WORD_APPLY]     (stack, definitions);
#define ADD         map[WORD_ADD]       (stack, definitions);
#define SUB         map[WORD_SUB]       (stack, definitions);
#define MUL         map[WORD_MUL]       (stack, definitions);
#define DIV         map[WORD_DIV]       (stack, definitions);
#define MOD         map[WORD_MOD]       (stack, definitions);
#define ISF         map[WORD_ISF]       (stack, definitions);
#define ISI         map[WORD_ISI]       (stack, definitions);
#define ISQ         map[WORD_ISQ]       (stack, definitions);
#define ISW         map[WORD_ISW]       (stack, definitions);
#define EQ          map[WORD_EQ]        (stack, definitions);
#define NE          map[WORD_NE]        (stack, definitions);
#define LT          map[WORD_LT]        (stack, definitions);
#define GE          map[WORD_GE]        (stack, definitions);
#define GT          map[WORD_GT]        (stack, definitions);
#define LE          map[WORD_LE]        (stack, definitions);
#define IF          map[WORD_IF]        (stack, definitions);
#define WRITE       map[WORD_WRITE]     (stack, definitions);
/* Word literals. */
#define WDUP        word_new(WORD_DUP)
#define WSWAP       word_new(WORD_SWAP)
#define WPOP        word_new(WORD_POP)
#define WQUOTE      word_new(WORD_QUOTE)
#define WCOMPOSE    word_new(WORD_COMPOSE)
#define WAPPLY      word_new(WORD_APPLY)
#define WADD        word_new(WORD_ADD)
#define WSUB        word_new(WORD_SUB)
#define WMUL        word_new(WORD_MUL)
#define WDIV        word_new(WORD_DIV)
#define WMOD        word_new(WORD_MOD)
#define WISF        word_new(WORD_ISF)
#define WISI        word_new(WORD_ISI)
#define WISQ        word_new(WORD_ISQ)
#define WISW        word_new(WORD_ISW)
#define WEQ         word_new(WORD_EQ)
#define WNE         word_new(WORD_NE)
#define WLT         word_new(WORD_LT)
#define WGE         word_new(WORD_GE)
#define WGT         word_new(WORD_GT)
#define WLE         word_new(WORD_LE)
#define WIF         word_new(WORD_IF)
#define WWRITE      word_new(WORD_WRITE)

/* Create and invoke definitions. */

#define DEF(a) quotation_push(definitions, a);

#define DO(a) do {                        \
  assert(a >= 0);                         \
  word_apply(-a - 1, stack, definitions); \
} while (0);

/* Skeleton program. */

#define KITTEN_PROGRAM(...)             \
int main(int argc, char** argv) {       \
  Boxed stack = quotation_new(0);       \
  Boxed definitions = quotation_new(0); \
  __VA_ARGS__                           \
  boxed_free(definitions);              \
  boxed_free(stack);                    \
  return 0;                             \
}

#endif