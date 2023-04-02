#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "bwa.h"

void one(bwaidx_t *idx, size_t len, ubyte_t *str) {
    bwtint_t sa_begin, sa_end;
    // bwt match
    bwt_match_exact(idx->bwt, len, str, &sa_begin, &sa_end);
    printf("sa_begin: %ld\t sa_end: %ld\n", sa_begin, sa_end);
    
    // sa
    for (bwtint_t i = sa_begin; i <= sa_end; i++) {
        bwtint_t pos = bwt_sa(idx->bwt, i);
        int is_rev;
        bwtint_t depos = bns_depos(idx->bns, pos, &is_rev);
        printf("SA[%ld]:\t%ld\tis_rev:\t%d\tdepos:\t%ld\n", i, pos, is_rev, depos);
    }

    printf("\n");
}

int main(int argc, char **argv)
{
    if (argc < 3) {
		fprintf(stderr, "\nUsage:   exact_aln <prefix> <sequence>\n\n");
		return 1;
	}

    char *prefix = argv[1];
    char *sequence = argv[2];
    size_t seq_len = strlen(sequence);
    bwaidx_t *idx = bwa_idx_load(prefix, BWA_IDX_ALL); // load idx

    // load sequence
    ubyte_t seq_f[seq_len], seq_b[seq_len];
    for (int i = 0; i < seq_len; i++) {
        seq_f[i] = nst_nt4_table[(int)sequence[i]];
        seq_b[seq_len - i - 1] = seq_f[i] == 4 ? 4 : 3 - seq_f[i];
    }

    printf("prefix: %s\t sequence: %s\tseq_len: %ld\n\n", prefix, sequence, seq_len);

    printf("exact match of original sequence:\n");
    one(idx, seq_len, seq_f);

    printf("exact match of Reverse Complement sequence:\n");
    one(idx, seq_len, seq_b);
}