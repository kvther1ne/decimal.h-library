#include "s21_div.h"

char num_as_bytes_overflow(num_as_bytes num) {
  char ans = 0;
  num_as_bytes pow2_96 = num_as_bytes_alloc(13);  // 2^96 = MAX_DECIMAL + 1
  pow2_96.byte[0] = 1;

  if (num_as_bytes_is_bigger_or_equal(num, pow2_96) == 1) {
    ans = 1;
  }
  num_as_bytes_free(&pow2_96);
  return ans;
}

void num_as_bytes_bank_rounding_96bit(num_as_bytes* num, num_as_bytes round) {
  num_as_bytes one_num_as_bytes, tmp;

  int int_round = (int)num_as_bytes_to_unsigned_long(round);
  if (int_round == 5) {
    if (num->byte[11] % 2 == 1) {
      int_round = 6;
    }
  }
  if (int_round > 5) {
    uint64_to_num_as_bytes(1, &one_num_as_bytes);
    num_as_bytes_sum_num_as_bytes(*num, one_num_as_bytes, &tmp);
    num_as_bytes_free(num);
    num_as_bytes_free(&one_num_as_bytes);
    *num = tmp;
    num_as_bytes_rm_zeros(num);
  }
}

int num_as_bytes_is_zero(num_as_bytes num) {
  return num.cells == 1 ? num.byte[0] == 0 ? 1 : 0 : 0;
}

unsigned int num_as_bytes_division_dec_fractions(num_as_bytes dividend,
                                                 num_as_bytes divisor,
                                                 num_as_bytes* quotient,
                                                 char* code_error) {
  num_as_bytes tmp_quotient_right, tmp_quotient_left, tmp_remainder, remainder,
      ten_num_as_bytes;
  unsigned int coefficient = 0;
  uint64_to_num_as_bytes(10, &ten_num_as_bytes);

  get_quotient_and_remainder(dividend, divisor, quotient, &remainder);
  tmp_remainder = remainder;
  *code_error = num_as_bytes_overflow(*quotient);
  if (*code_error == 0) {
    tmp_quotient_left = num_as_bytes_alloc(1);
    tmp_quotient_right = num_as_bytes_alloc(1);

    while (quotient->cells < 13 && num_as_bytes_is_zero(tmp_remainder) == 0 &&
           coefficient != 29) {
      num_as_bytes_free(&tmp_quotient_left);
      num_as_bytes_free(&tmp_quotient_right);
      tmp_quotient_left = *quotient;
      num_as_bytes_mul_num_as_bytes(ten_num_as_bytes, tmp_remainder,
                                    &remainder);
      num_as_bytes_free(&tmp_remainder);
      get_quotient_and_remainder(remainder, divisor, &tmp_quotient_right,
                                 &tmp_remainder);
      num_as_bytes_free(&remainder);

      conc_num_as_bytes_as_dec(tmp_quotient_left, tmp_quotient_right, quotient);
      coefficient++;
    }
    if (quotient->cells == 13 || coefficient == 29) {
      num_as_bytes_free(quotient);
      num_as_bytes_cpy_big(tmp_quotient_left, quotient, 12);
      num_as_bytes_bank_rounding_96bit(quotient, tmp_quotient_right);
      if (quotient->cells == 13) {
        *code_error = 1;
      }
      coefficient--;
    }
    num_as_bytes_free(&tmp_quotient_left);
    num_as_bytes_free(&tmp_quotient_right);
  }
  num_as_bytes_free(&tmp_remainder);
  num_as_bytes_free(&ten_num_as_bytes);
  return coefficient;
}

void conc_num_as_bytes_as_dec(num_as_bytes a, num_as_bytes b,
                              num_as_bytes* ans) {
  num_as_bytes ten;
  num_as_bytes temp;
  // num_as_bytes ans;

  uint64_to_num_as_bytes(10, &ten);
  num_as_bytes_mul_num_as_bytes(a, ten, &temp);
  num_as_bytes_sum_num_as_bytes(temp, b, ans);
  num_as_bytes_free(&temp);
  num_as_bytes_free(&ten);

  num_as_bytes_rm_zeros(ans);
}

void num_as_bytes_right_shift(num_as_bytes* src, int shift) {
  set_num_as_bytes_len(src);
  if (src->bin_len != 0) {
    int n = src->bin_len - shift;
    int m = n / ADIG + 1;
    int k = shift / ADIG;
    int a = src->cells - k - 1;

    int real_shift = shift - k * ADIG;
    num_as_bytes ans;
    ans = num_as_bytes_alloc(m);
    char temp = 0;
    char i = 0;
    while (a != -1) {
      temp = src->byte[a] & 1 << real_shift;
      if (temp != 0) {
        ans.byte[m - 1] |= 1 << i;
      }
      i++;
      real_shift++;
      if (real_shift == 8) {
        real_shift = 0;
        a--;
      }
      if (i == 8) {
        m--;
        i = 0;
      }
    }
    set_num_as_bytes_len(&ans);
    num_as_bytes_free(src);
    *src = ans;
  }
}

void conc_many_num_as_bytes(num_as_bytes* trg, num_as_bytes* sources, int t) {
  num_as_bytes temp1;
  num_as_bytes temp2;

  uint64_to_num_as_bytes(0, &temp2);
  uint64_to_num_as_bytes(0, &temp1);

  for (int i = 0; i < t - 1; i++) {
    num_as_bytes_free(&temp2);
    conc_num_as_bytes(temp1, sources[i], &temp2);
    num_as_bytes_free(&temp1);
    num_as_bytes_cpy_big(temp2, &temp1, temp2.cells);
  }
  num_as_bytes_free(&temp2);
  *trg = temp1;
}

void get_quotient_and_remainder(num_as_bytes dend, num_as_bytes sor,
                                num_as_bytes* q, num_as_bytes* r) {
  int m = set_m(sor.bin_len);
  num_as_bytes b, at, a;
  num_as_bytes_cpy_big(sor, &b, m);
  int o = full_left_shift(&b, m);
  dend_left_shift(dend, &at, o);

  int t = set_t(at, b);
  num_as_bytes_cpy_big(at, &a, t * b.cells);
  num_as_bytes* a_t = calloc(t, sizeof(num_as_bytes));
  split_num_as_bytes_t(a, a_t, t);
  num_as_bytes a_c;
  num_as_bytes* q_t = calloc(t - 1, sizeof(num_as_bytes));
  num_as_bytes r_t;
  conc_num_as_bytes(a_t[0], a_t[1], &a_c);
  num_as_bytes_free(&a_t[0]);
  num_as_bytes_free(&a_t[1]);

  for (int i = 0; i < t - 1; i++) {
    if (i != 0) {
      num_as_bytes_free(&r_t);
    }
    div21(a_c, b, &(q_t[i]), &r_t);
    num_as_bytes_free(&a_c);
    if (i != t - 2) {
      conc_num_as_bytes(r_t, a_t[i + 2], &a_c);
      num_as_bytes_free(&a_t[i + 2]);
    }
  }

  conc_many_num_as_bytes(q, q_t, t);
  for (int i = 0; i < t - 1; i++) {
    num_as_bytes_free(&q_t[i]);
  }
  free(q_t);
  free(a_t);

  num_as_bytes_right_shift(&r_t, o);
  num_as_bytes_cpy_big(r_t, r, r_t.cells);
  num_as_bytes_rm_zeros(r);
  num_as_bytes_rm_zeros(q);
  set_num_as_bytes_len(r);
  num_as_bytes_free(&b);
  num_as_bytes_free(&at);
  num_as_bytes_free(&a);
  num_as_bytes_free(&r_t);
}

void split_num_as_bytes_t(num_as_bytes a, num_as_bytes* mass, int t) {
  int m = a.cells / t;

  for (int i = 0; i < t; i++) {
    num_as_bytes_cpy_eq_or_sm(a, &(mass[i]), m, m * i);
  }
}

int set_t(num_as_bytes a, num_as_bytes b) {
  int t = 2;
  while (b.size * t <= a.bin_len) {
    t++;
  }
  return t;
}

void num_as_bytes_rm_zeros(num_as_bytes* a) {
  unsigned int i = 0;

  while (a->byte[i] == 0 && i != a->cells - 1) {
    i++;
  }
  if (i > 0) {
    num_as_bytes tmp;
    num_as_bytes_cpy_eq_or_sm(*a, &tmp, a->cells - i, i);
    num_as_bytes_free(a);
    *a = tmp;
  }
}
void dend_left_shift(num_as_bytes dend, num_as_bytes* a, int o) {
  int plus = o / ADIG + 1;
  num_as_bytes_cpy_eq_or_sm(dend, a, dend.cells, 0);
  num_as_bytes_left_shift(a, o, a->cells + plus);
  num_as_bytes_rm_zeros(a);
}

int full_left_shift(num_as_bytes* trg, int m) {
  unsigned long long int o = ADIG * m - trg->bin_len;
  num_as_bytes_left_shift(trg, o, m);
  return o;
}

void num_as_bytes_left_shift(num_as_bytes* src, int shift, int m) {
  num_as_bytes based;
  num_as_bytes tmp;
  num_as_bytes_base_pow(&based, shift);
  num_as_bytes_mul_num_as_bytes(*src, based, &tmp);
  num_as_bytes_free(src);
  num_as_bytes_cpy_eq_or_sm(tmp, src, m, tmp.cells - m);

  num_as_bytes_free(&based);
  num_as_bytes_free(&tmp);
}

int set_m(int len) {
  int ans = 1;
  while (ans * ADIG <= len) {
    ans <<= 1;
  }
  return ans;
}

unsigned long long num_as_bytes_to_unsigned_long(num_as_bytes a) {
  unsigned long long ans = 0;
  for (unsigned int i = 0; i < a.cells && i <= 8; i++) {
    ans <<= 8;
    ans += a.byte[i];
  }
  return ans;
}

void num_as_bytes_school_div(num_as_bytes a, num_as_bytes b, num_as_bytes* q,
                             num_as_bytes* r) {
  int temp = a.byte[0];
  temp <<= 8;
  temp += a.byte[1];
  *q = num_as_bytes_alloc(b.cells);
  *r = num_as_bytes_alloc(b.cells);
  q->byte[0] = temp / b.byte[0];
  r->byte[0] = temp % b.byte[0];
}

void div21(num_as_bytes a, num_as_bytes b, num_as_bytes* q, num_as_bytes* r) {
  int m = b.cells;
  if (m == 1) {
    num_as_bytes_school_div(a, b, q, r);
  } else {
    num_as_bytes al, ar, a3, a4;
    num_as_bytes r1, q1, q2;

    split_num_as_bytes_twice(a, &al, &ar);
    split_num_as_bytes_twice(ar, &a3, &a4);
    div32(al, a3, b, &q1, &r1);
    div32(r1, a4, b, &q2, r);
    conc_num_as_bytes(q1, q2, q);
    num_as_bytes_free(&al);
    num_as_bytes_free(&ar);
    num_as_bytes_free(&a3);
    num_as_bytes_free(&a4);
    num_as_bytes_free(&r1);
    num_as_bytes_free(&q1);
    num_as_bytes_free(&q2);
  }
}

void div32(num_as_bytes al, num_as_bytes a3, num_as_bytes b, num_as_bytes* q,
           num_as_bytes* r) {
  int m = b.cells / 2;
  num_as_bytes b1, b2;
  num_as_bytes a1, a2, one;
  uint64_to_num_as_bytes(1, &one);
  num_as_bytes wq2, wq3, wq, r1, rr1, rw, rw2, rw3;
  num_as_bytes temp, temp2, based;
  split_num_as_bytes_twice(b, &b1, &b2);
  split_num_as_bytes_twice(al, &a1, &a2);

  if (num_as_bytes_is_bigger_or_equal(a1, b1) == 1) {
    set_q_one(&wq, m);
    num_as_bytes_mul_num_as_bytes(wq, b1, &temp);  // 2m
    num_as_bytes_sub_num_as_bytes(al, temp, &r1);  // 2m
    num_as_bytes_free(&temp);
  } else {
    div21(al, b1, &wq, &rr1);
    num_as_bytes_cpy_big(rr1, &r1, 2 * m);  // 2m
    num_as_bytes_free(&rr1);
  }

  num_as_bytes d;
  num_as_bytes_mul_num_as_bytes(wq, b2, &d);  // 2m
  d.sign = 1;
  num_as_bytes_base_pow(&based, m * ADIG);
  num_as_bytes_mul_num_as_bytes(r1, based, &temp);
  num_as_bytes_sum_num_as_bytes(temp, a3, &temp2);
  num_as_bytes_sum_num_as_bytes(temp2, d, &rw);
  if (rw.sign == 1) {
    num_as_bytes_sum_num_as_bytes(rw, b, &rw2);
    num_as_bytes_sub_num_as_bytes(wq, one, &wq2);
    if (rw2.sign == 1) {
      num_as_bytes_sum_num_as_bytes(rw2, b, &rw3);
      num_as_bytes_sub_num_as_bytes(wq2, one, &wq3);
      num_as_bytes_cpy_eq_or_sm(rw3, r, 2 * m, rw3.cells - 2 * m);
      num_as_bytes_cpy_eq_or_sm(wq3, q, m, wq3.cells - m);
      num_as_bytes_free(&rw3);
      num_as_bytes_free(&wq3);
    } else {
      num_as_bytes_cpy_eq_or_sm(rw2, r, 2 * m, rw2.cells - 2 * m);
      num_as_bytes_cpy_eq_or_sm(wq2, q, m, wq2.cells - m);
    }
    num_as_bytes_free(&rw2);
    num_as_bytes_free(&wq2);
  } else {
    num_as_bytes_cpy_eq_or_sm(rw, r, 2 * m, rw.cells - 2 * m);
    num_as_bytes_cpy_eq_or_sm(wq, q, m, wq.cells - m);
  }
  num_as_bytes_free(&based);
  num_as_bytes_free(&r1);
  num_as_bytes_free(&rw);
  num_as_bytes_free(&wq);
  num_as_bytes_free(&one);
  num_as_bytes_free(&b1);
  num_as_bytes_free(&b2);
  num_as_bytes_free(&a1);
  num_as_bytes_free(&a2);
  num_as_bytes_free(&temp);
  num_as_bytes_free(&temp2);
  num_as_bytes_free(&d);
}

void num_as_bytes_base_pow(num_as_bytes* based, int pow) {
  if (pow == 0) {
    *based = num_as_bytes_alloc(1);
    based->byte[0] = 1;
  } else {
    int m = pow / ADIG + 1;
    *based = num_as_bytes_alloc(m);
    int i = m * ADIG - pow;
    based->byte[0] = 1;
    based->byte[0] <<= ADIG - i;
    based->bin_len = pow + 1;
  }
}

void set_q_one(num_as_bytes* q, int m) {
  *q = num_as_bytes_alloc(m);
  for (int i = 0; i < m; i++) {
    q->byte[i] = 0b11111111;
  }
  q->bin_len = q->size;
}

int num_as_bytes_is_bigger_or_equal(num_as_bytes a, num_as_bytes b) {
  int ans = 3;
  int m = a.cells;
  num_as_bytes a_temp = a;
  num_as_bytes b_temp = b;

  if (a.cells > b.cells) {
    m = a.cells;
    num_as_bytes_cpy_big(b, &b_temp, m);
  } else if (a.cells < b.cells) {
    m = b.cells;
    num_as_bytes_cpy_big(a, &a_temp, m);
  }

  for (int i = 0; i < m && ans == 3; i++) {
    if (a_temp.byte[i] > b_temp.byte[i]) {
      ans = 1;
    }
    if (a_temp.byte[i] < b_temp.byte[i]) {
      ans = 0;
    }
  }
  if (ans == 3) {
    ans = 1;
  }

  if (a.cells > b.cells) {
    num_as_bytes_free(&b_temp);
  } else if (a.cells < b.cells) {
    num_as_bytes_free(&a_temp);
  }

  return ans;
}

void num_as_bytes_sub_num_as_bytes(num_as_bytes a, num_as_bytes b,
                                   num_as_bytes* res) {
  int m = a.cells;

  num_as_bytes a_temp;
  num_as_bytes b_temp;

  if (a.cells > b.cells) {
    m = a.cells;
  } else if (a.cells < b.cells) {
    m = b.cells;
  }
  num_as_bytes_cpy_big(b, &b_temp, m);
  num_as_bytes_cpy_big(a, &a_temp, m);

  *res = num_as_bytes_alloc(m);

  if (num_as_bytes_is_bigger_or_equal(a_temp, b_temp) == 0) {
    res->sign = 1;
    num_as_bytes_sub_helper(res->byte, b_temp.byte, a_temp.byte, m);
  } else {
    num_as_bytes_sub_helper(res->byte, a_temp.byte, b_temp.byte, m);
  }
  set_num_as_bytes_len(res);

  num_as_bytes_free(&a_temp);
  num_as_bytes_free(&b_temp);
}

void num_as_bytes_sub_helper(unsigned char* res, unsigned char* a,
                             unsigned char* b, unsigned int m) {
  int temp = 0;
  for (int i = m - 1; i >= 0; i--) {
    temp = (int)a[i] - (int)b[i];
    if (temp < 0) {
      int k = 1;
      while (a[i - k] == 0) {
        a[i - k] -= 1;
        k++;
      }
      a[i - k] -= 1;
      temp = base_pow(ADIG) + temp;
    }
    res[i] = (unsigned char)temp;
  }
}

void num_as_bytes_mul_num_as_bytes(num_as_bytes a, num_as_bytes b,
                                   num_as_bytes* res) {
  int m = a.cells;

  num_as_bytes a_temp = a;
  num_as_bytes b_temp = b;

  if (a.cells > b.cells) {
    m = a.cells;
    num_as_bytes_cpy_big(b, &b_temp, m);
  } else if (a.cells < b.cells) {
    m = b.cells;
    num_as_bytes_cpy_big(a, &a_temp, m);
  }
  *res = num_as_bytes_alloc(2 * m);
  num_as_bytes_mul_help(res->byte, a_temp.byte, b_temp.byte, m);
  set_num_as_bytes_len(res);

  if (a.cells > b.cells) {
    num_as_bytes_free(&b_temp);
  } else if (a.cells < b.cells) {
    num_as_bytes_free(&a_temp);
  }
  if (a.sign == 1 && b.sign == 0) {
    res->sign = 1;
  } else if (a.sign == 0 && b.sign == 1) {
    res->sign = 1;
  }
}

void num_as_bytes_mul_help(unsigned char* res, unsigned char* a,
                           unsigned char* b, unsigned int m) {
  int k = 0;
  unsigned char add = 0;
  unsigned long long temp = 0;
  unsigned char* res_temp = calloc(m * 4, sizeof(char));
  unsigned char** arr_temp = calloc(m, sizeof(char*));
  for (unsigned int i = 0; i < m; i++) {
    arr_temp[i] = calloc(m * 2, sizeof(char));
  }
  for (int i = m - 1, n = 0; i >= 0; i--, n++) {
    add = 0;
    k = 0;
    for (int j = m - 1; j >= 0; j--, k++) {
      temp = a[j] * b[i] + add;
      arr_temp[i][m * 2 - k - 1 - n] = temp;
      add = temp >> ADIG;
    }
    arr_temp[i][m * 2 - k - 1 - n] = add;
    add_arr(res_temp, res, arr_temp[i], m * 2);
    for (unsigned int j = 0; j < m * 2; j++) {
      res[j] = res_temp[j + 2 * m];
    }
  }
  for (unsigned int i = 0; i < m; i++) {
    free(arr_temp[i]);
  }
  free(arr_temp);
  free(res_temp);
}

void add_arr(unsigned char* res, unsigned char* a, unsigned char* b,
             unsigned int m) {
  char add = 0;
  int temp = 0;
  int j = m * 2;
  for (int i = m - 1; i >= 0; i--) {
    temp = a[i] + b[i] + add;
    add = 0;
    if (temp > 0b11111111) {
      temp = temp - 0b100000000;
      add = 1;
    }
    res[j - 1] = (char)temp;
    j--;
  }
  res[j - 1] = add;
}

void num_as_bytes_sum_num_as_bytes(num_as_bytes a, num_as_bytes b,
                                   num_as_bytes* res) {
  if (a.sign == 1 && b.sign == 0) {
    num_as_bytes_sub_num_as_bytes(b, a, res);
  } else if (b.sign == 1 && a.sign == 0) {
    num_as_bytes_sub_num_as_bytes(a, b, res);
  } else {
    char add = 0;
    int temp = 0;
    int m = a.cells;

    num_as_bytes a_temp = a;
    num_as_bytes b_temp = b;

    if (a.cells > b.cells) {
      m = a.cells;
      num_as_bytes_cpy_big(b, &b_temp, m);
    } else if (a.cells < b.cells) {
      m = b.cells;
      num_as_bytes_cpy_big(a, &a_temp, m);
    }

    *res = num_as_bytes_alloc(m * 2);
    int j = m * 2;

    for (int i = m - 1; i >= 0; i--) {
      temp = a_temp.byte[i] + b_temp.byte[i] + add;
      add = 0;
      if (temp > 0b11111111) {
        temp = temp - 0b100000000;
        add = 1;
      }
      res->byte[j - 1] = (char)temp;
      j--;
    }
    res->byte[j - 1] = add;
    set_num_as_bytes_len(res);
    if (a.sign == 1 && b.sign == 1) {
      res->sign = 1;
    }
    if (a.cells > b.cells) {
      num_as_bytes_free(&b_temp);
    } else if (a.cells < b.cells) {
      num_as_bytes_free(&a_temp);
    }
  }
}

void set_num_as_bytes_len(num_as_bytes* a) {
  for (unsigned int i = 0; i < a->cells; i++) {
    if (a->byte[i] != 0) {
      for (int j = 0; j < ADIG; j++) {
        if (a->byte[i] & (unsigned char)(0b10000000 >> j)) {
          a->bin_len = ADIG - j + (a->cells - i - 1) * ADIG;
          break;
        }
      }

      break;
    }
  }
}

void num_as_bytes_cpy_eq_or_sm(num_as_bytes src, num_as_bytes* trg,
                               unsigned int how_much, unsigned int start) {
  *trg = num_as_bytes_alloc(how_much);
  for (unsigned int i = start; i < start + how_much; i++) {
    trg->byte[i - start] = src.byte[i];
  }
  set_num_as_bytes_len(trg);
}

void num_as_bytes_cpy_big(num_as_bytes src, num_as_bytes* trg,
                          unsigned int size) {
  *trg = num_as_bytes_alloc(size);
  for (unsigned int i = 0; i < src.cells; i++) {
    trg->byte[i + size - src.cells] = src.byte[i];
  }
  trg->bin_len = src.bin_len;
  trg->sign = src.sign;
}

void split_num_as_bytes_twice(num_as_bytes a, num_as_bytes* a1,
                              num_as_bytes* a2) {
  num_as_bytes_cpy_eq_or_sm(a, a2, a.cells / 2, a.cells / 2);
  num_as_bytes_cpy_eq_or_sm(a, a1, a.cells / 2, 0);
}

void conc_num_as_bytes(num_as_bytes a, num_as_bytes b, num_as_bytes* trg) {
  *trg = num_as_bytes_alloc(a.cells + b.cells);
  for (unsigned int i = 0; i < a.cells; i++) {
    trg->byte[i] = a.byte[i];
  }
  for (unsigned int i = a.cells; i < trg->cells; i++) {
    trg->byte[i] = b.byte[i - a.cells];
  }
}

void uint64_to_num_as_bytes(uint64_t num, num_as_bytes* arr) {
  union uint64_char temp;
  int n = len_of_unsigned_int(num, BASE);
  int m = n / ADIG + 1;
  *arr = num_as_bytes_alloc(m);
  temp.num = num;

  for (unsigned int i = 0; i < arr->cells && i < 8; i++) {
    arr->byte[arr->cells - 1 - i] = temp.p[i];
  }
  arr->bin_len = n;
}

void uint32_to_num_as_bytes(uint32_t num, num_as_bytes* arr) {
  union uint32_char temp;
  *arr = num_as_bytes_alloc(4);
  temp.num = num;

  for (unsigned int i = 0; i < arr->cells && i < 4; i++) {
    arr->byte[arr->cells - 1 - i] = temp.p[i];
  }
  arr->bin_len = len_of_unsigned_int(num, BASE);
}

num_as_bytes num_as_bytes_alloc(unsigned int amount_of_cells) {
  num_as_bytes temp;

  temp.cells = amount_of_cells;
  temp.byte = calloc(temp.cells, sizeof(char));
  temp.size = amount_of_cells * ADIG;
  temp.bin_len = 0;
  temp.sign = 0;

  return temp;
}

void num_as_bytes_free(num_as_bytes* num) { free(num->byte); }

unsigned int len_of_unsigned_int(const unsigned long long num, int base) {
  int ans = 0;

  if (num != 0) {
    if (base == 2) {
      ans = help_len_of_unsigned_int(num);
    } else if (base == 10) {
      ans = (int)floor(log10(num)) + 1;
    }
  }

  return ans;
}

unsigned int help_len_of_unsigned_int(unsigned long long num) {
  int ans = 64;
  unsigned long long temp = 9223372036854775808u;
  while (ans != 1 && num < temp) {
    temp >>= 1;
    ans--;
  }

  return ans;
}

unsigned long long int int_pow(const unsigned int pow, int num) {
  unsigned long long int ans = num;
  for (unsigned int i = 1; i < pow; i++) {
    ans = ans * num;
  }
  if (pow == 0) {
    ans = 1;
  }
  return ans;
}

unsigned long long int base_pow(const unsigned int pow) {
  return int_pow(pow, BASE);
}

void num_as_bytes_to_s21_decimal(int sign_result, unsigned int result_scale,
                                 num_as_bytes src, s21_decimal* result) {
  num_as_bytes buffer = src;
  if (src.cells != 12) {
    num_as_bytes_cpy_big(src, &buffer, 12);
  }
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      result->bits[i] <<= 8;
      result->bits[i] += buffer.byte[11 - 3 + j - i * 4];
    }
  }
  if (src.cells != 12) {
    num_as_bytes_free(&buffer);
  }
  result->bits[3] = (char)result_scale;
  result->bits[3] <<= 16;

  if (sign_result == 1) {
    set_bit(&result->bits[3], 31, 1);
  }
}

void scale_before_div(s21_decimal value_1, s21_decimal value_2,
                      num_as_bytes* dividend, num_as_bytes* divisor) {
  int scale_value_1 = get_scale(value_1);
  int scale_value_2 = get_scale(value_2);
  num_as_bytes tmp_dividend, tmp_divisor, ten;

  decimal_to_num_as_bytes(value_1, &tmp_dividend);
  decimal_to_num_as_bytes(value_2, &tmp_divisor);
  int scale_tmp = 0;
  if (scale_value_1 == scale_value_2) {
    *dividend = tmp_dividend;
    *divisor = tmp_divisor;
  } else if (scale_value_1 > scale_value_2) {
    scale_tmp = scale_value_1 - scale_value_2;
    *dividend = tmp_dividend;
    ten_pow(scale_tmp, &ten);
    num_as_bytes_mul_num_as_bytes(tmp_divisor, ten, divisor);
    num_as_bytes_free(&ten);
    num_as_bytes_free(&tmp_divisor);
  } else {
    scale_tmp = scale_value_2 - scale_value_1;
    *divisor = tmp_divisor;
    ten_pow(scale_tmp, &ten);
    num_as_bytes_mul_num_as_bytes(tmp_dividend, ten, dividend);
    num_as_bytes_free(&ten);
    num_as_bytes_free(&tmp_dividend);
  }
  num_as_bytes_rm_zeros(dividend);
  num_as_bytes_rm_zeros(divisor);
  set_num_as_bytes_len(dividend);
  set_num_as_bytes_len(divisor);
}

void ten_pow(int pow, num_as_bytes* ten) {
  if (pow <= 19) {
    unsigned long long int powed = int_pow(pow, 10);
    uint64_to_num_as_bytes(powed, ten);
  } else {
    num_as_bytes temp1, temp2;
    uint64_to_num_as_bytes(int_pow(19, 10), &temp1);
    uint64_to_num_as_bytes(int_pow(pow - 19, 10), &temp2);

    num_as_bytes_mul_num_as_bytes(temp1, temp2, ten);
    num_as_bytes_free(&temp1);
    num_as_bytes_free(&temp2);
    num_as_bytes_rm_zeros(ten);
  }
}

void decimal_to_num_as_bytes(s21_decimal src, num_as_bytes* trg) {
  num_as_bytes high, mid, low, tmp;
  uint32_to_num_as_bytes(src.bits[0], &low);
  uint32_to_num_as_bytes(src.bits[1], &mid);
  uint32_to_num_as_bytes(src.bits[2], &high);
  conc_num_as_bytes(high, mid, &tmp);
  conc_num_as_bytes(tmp, low, trg);
  num_as_bytes_free(&high);
  num_as_bytes_free(&mid);
  num_as_bytes_free(&low);
  num_as_bytes_free(&tmp);
}

unsigned int get_result_scale_mod(s21_decimal value_1, s21_decimal value_2) {
  int scale1 = (value_1.bits[3] & MASK_SCALE) >> 16;
  int scale2 = (value_2.bits[3] & MASK_SCALE) >> 16;

  return scale1 > scale2 ? scale1 : scale2;
}