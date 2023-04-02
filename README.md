# bwa_exact_match

## Function

Exact match one read to a bwa reference.

Result will be print to console.

I think this is useful for beginers to understand the pos system of bwa index. You can manually create small fasta file and apply `bwa index` on it, then manully map reads to it.

You can also read code in `main.c` to learn the basic use of `bwt data structure` in lh3's `bwa` repository.

## Usage

```
Usage:   exact_aln <prefix> <sequence>
```

## Example

input

```
./exact_aln data/a.fa GCAAATAACTTTGG
```

output

```
[M::bwa_idx_load_from_disk] read 0 ALT contigs
prefix: data/a.fa        sequence: GCAAATAACTTTGG       seq_len: 14

exact match of original sequence:
sa_begin: 11265625       sa_end: 11265626
SA[11265625]:   583522  is_rev: 0       depos:  583522
SA[11265626]:   986     is_rev: 0       depos:  986

exact match of Reverse Complement sequence:
sa_begin: 6263887        sa_end: 6263888
SA[6263887]:    19999000        is_rev: 1       depos:  999
SA[6263888]:    19416464        is_rev: 1       depos:  583535

```