extern struct atom *mem[MAXBLOCKS];
extern struct atom *free_list;

extern int tos; // top of stack
extern int tof; // top of frame
extern int toj; // top of journal
 
extern struct atom *stack[STACKSIZE];
extern struct atom *frame[FRAMESIZE];
extern struct atom *journal[JOURNALSIZE];
 
extern struct atom *symtab[];
extern struct atom *binding[];
extern struct atom *usrfunc[];
 
extern struct atom *zero;
extern struct atom *one;
extern struct atom *minusone;
extern struct atom *imaginaryunit;

extern int level;
extern int expanding;
extern int drawing;
extern int journaling;
extern int interrupt;
extern jmp_buf jmpbuf0;
extern jmp_buf jmpbuf1;

extern int alloc_count;
extern int block_count;
extern int free_count;
extern int gc_count;
extern int bignum_count;
extern int ksym_count;
extern int usym_count;
extern int string_count;
extern int tensor_count;
extern int max_level;
extern int max_stack;
extern int max_frame;
extern int max_journal;
 
extern char strbuf[];

extern char *outbuf;
extern int outbuf_index;
extern int outbuf_length;
