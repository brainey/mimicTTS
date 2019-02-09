//
// Created by brainey on 2/8/19.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

#define MAX_MATCHES 6
#define max(a,b) \
  ({ __typeof__ (a) _a = (a); \
     __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a,b) \
  ({ __typeof__ (a) _a = (a); \
     __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

struct lookup_t {
  const char *match;
  const char *say;
  const char *say_phonetic;
} lookup[] = {
  { "a", "aay", "alpha" },
  { "b", "bee", "bravo" },
  { "c", "sea", "charlie" },
  { "d", "dee", "delta" },
  { "e", "e", "echo" },
  { "f", "eff", "foxtrot" },
  { "g", "gee", "golf" },
  { "h", "aitch", "hotel" },
  { "i", "i", "india" },
  { "j", "jay", "juliet" },
  { "k" "kay", "kilo" },
  { "l", "el", "lima" },
  { "m", "em", "mike" },
  { "n", "en", "november" },
  { "o", "o", "oscar" },
  { "p", "pee", "papa" },
  { "q" "cue", "quebec" },
  { "r", "ar", "romeo" },
  { "s", "ess", "sierra" },
  { "t", "tee", "tango" },
  { "u", "u", "uniform" },
  { "v", "vee", "victor" },
  { "w", "double-u", "whisky" },
  { "x", "ex", "x-ray" },
  { "y", "wy", "yankee" },
  { "z", "zee", "zulu" }
};

const char callsign_parts[] = "^([A-Z]+[0-9])([A-Z]+)$";

const char *callsigns[] = {
  "kf6emb", "kd6dif", "ka6wrl", "k6mdh", "wa6qys", "kf6otd",
  "ne6rd", "wd6dbm", "kc6afu", "kk6nze", "kk6nzf", "ki6rld",
  "wa6wat", "kg6uwo", "ac6yy", "km6yef", "n6uob", "w6rao",
  "ks6pd", "n6mef", "ki6dsb", "kg6enw"
};

char *
extract_match(char *bp, char *bp_end, const char *src, regmatch_t *matchp) {
  int mlen = matchp->rm_eo - matchp->rm_so;

  if (mlen > 0) {
    mlen = min(mlen, bp_end - bp - 1);
    memcpy(bp, src + matchp->rm_so, mlen);
    bp += mlen;
    *bp++ = '\0';

    return bp;
  }

  return NULL;
}

int
main(int argc, char *argv[]) {
  int nCallsigns = sizeof(callsigns)/sizeof(callsigns[0]);
  int i = 0;
  regex_t regex;
  int r;

  r = regcomp(&regex, callsign_parts, REG_EXTENDED|REG_ICASE);
  if (r) {
    fprintf(stderr, "Could not compile the regular expression <%s>\n",
            callsign_parts);
    exit(1);
  }

  for (i = 0; i < nCallsigns; i++) {
    const char *callsign = callsigns[i];
    char buff[MAX_MATCHES * 10] = "";
    char *bp = &buff[0];
    char *bp_end = bp + sizeof(buff);
    char
      *whole,
      *prefix,
      *suffix;
    regmatch_t matches[MAX_MATCHES];
    int mlen;

    if (regexec(&regex, callsign, MAX_MATCHES, matches, 0) == 0) {
      // printf("m[0] %d - %d\n", matches[0].rm_so, matches[0].rm_eo);
      // printf("m[1] %d - %d\n", matches[1].rm_so, matches[1].rm_eo);
      // printf("m[2] %d - %d\n", matches[2].rm_so, matches[2].rm_eo);
      // printf("m[3] %d - %d\n", matches[3].rm_so, matches[3].rm_eo);
      // printf("m[4] %d - %d\n", matches[4].rm_so, matches[4].rm_eo);
      bp = &buff[0];
      whole = bp;
      regmatch_t *matchp = &matches[0];
      // printf("match %d - %d\n", matchp->rm_so, matchp->rm_eo);
      mlen = matchp->rm_eo - matchp->rm_so;
      memcpy(bp, callsign + matchp->rm_so, mlen);
      bp += mlen;
      *bp++ = '\0';
      prefix = bp;
      matchp++;
      // printf("match %d - %d\n", matchp->rm_so, matchp->rm_eo);
      mlen = matchp->rm_eo - matchp->rm_so;
      memcpy(bp, callsign + matchp->rm_so, mlen);
      bp += mlen;
      *bp++ = '\0';
      suffix = bp;
      matchp++;
      // printf("match %d - %d\n", matchp->rm_so, matchp->rm_eo);
      mlen = matchp->rm_eo - matchp->rm_so;
      memcpy(bp, callsign + matchp->rm_so, mlen);
      bp += mlen;
      *bp++ = '\0';

      printf("whole: %s prefix: %s suffix: %s\n", whole, prefix, suffix);
    }
  }

  return 0;
}
