const int numFldDsgns = 9;


//
// level 4 is the most difficult (dot - wall- dot thing)
//
int fldDsgns[numFldDsgns][fieldSizeX * fieldSizeY] =
{
   // 000000000000000000000000000000000000000000000000000000000000000000000000
  {  spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc,
     dr , hor, hor, hor, hor, hor, hor, hor, hor, hor, ldr, hor, hor, hor, hor, hor, hor, hor, hor, hor, ld ,
     ver, dot, dot, dot, dot, dot, dot, dot, dot, dot, ver, dot, dot, dot, dot, dot, dot, dot, dot, dot, ver,
     ver, bdt, le , hor, re , dot, le , ldr, re , dot, ver, dot, le , hor, re , dot, le , hor, re , bdt, ver,
     ver, dot, dot, dot, dot, dot, dot, ver, dot, dot, ver, dot, dot, dot, dot, dot, dot, dot, dot, dot, ver,
     dru, hor, re , dot, le , ld , dot, de , dot, le , rul, re , dot, le , re , dot, ue , dot, ue , dot, ver,
     ver, dot, dot, dot, dot, ver, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, ver, dot, ver, dot, ver,
     ver, dot, dr , ld , dot, ver, dot, dr , hor, hor, dor, hor, hor, ld , dot, le , ul , dot, de , dot, ver,
     ver, dot, ver, ver, dot, de , dot, ver, spc, spc, spc, spc, spc, ver, dot, dot, dot, dot, dot, dot, ver,
     ver, dot, ver, ver, dot, dot, dot, ver, spc, spc, spc, spc, spc, ver, dot, dr , hor, hor, ld , dot, ver,
     ver, dot, ru , ul , dot, ue , dot, ru , hor, hor, hor, hor, hor, ul , dot, ru , hor, hor, ul , dot, ver,
     ver, dot, dot, dot, dot, ver, dot, dot, dot, dot, spc, dot, dot, dot, dot, dot, dot, dot, dot, dot, ver,
     dru, hor, re , dot, le , ul , dot, le , hor, hor, ldr, hor, hor, re , dot, ue , dot, lre, dot, le , uld,
     ver, dot, dot, dot, dot, dot, dot, dot, dot, dot, ver, dot, dot, dot, dot, ver, dot, dot, dot, dot, ver,
     ver, bdt, le , hor, hor, hor, hor, hor, re , dot, de , dot, le , hor, hor, rul, hor, hor, re , bdt, ver,
     ver, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, ver,
     ru , hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, ul  },

  // 111111111111111111111111111111111111111111111111111111111111111111111111
  {  spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc,
     dr , hor, hor, hor, hor, hor, hor, hor, hor, hor, ldr, hor, hor, hor, hor, hor, hor, hor, hor, hor, ld ,
     ver, dot, dot, dot, dot, dot, dot, dot, dot, dot, ver, dot, dot, dot, dot, dot, dot, dot, dot, dot, ver,
     ver, bdt, le,  hor, ld , dot, le , hor, re , dot, ver, dot, le , hor, re , dot, dr , hor, re,  bdt, ver,
     ver, dot, dot, dot, ver, dot, dot, dot, dot, dot, ver, dot, dot, dot, dot, dot, ver, dot, dot, dot, ver,
     ver, dot, ue , dot, ru,  hor, hor, hor, re,  dot, de , dot, le , hor, hor, hor, ul , dot, ue , dot, ver,
     ver, dot, ver, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, ver, dot, ver,
     ver, dot, ru , hor, hor, re,  dot, dr , hor, hor, dor, hor, hor, ld , dot, le , hor, hor, ul , dot, ver,
     ver, dot, dot, dot, dot, dot, dot, ver, spc, spc, spc, spc, spc, ver, dot, dot, dot, dot, dot, dot, ver,
     ver, dot, dr , ld , dot, ue , dot, ver, spc, spc, spc, spc, spc, ver, dot, ue , dot, dr , ld , dot, ver,
     ver, dot, ru , ul , dot, ver, dot, ru , hor, hor, hor, hor, hor, ul , dot, ver, dot, ru , ul , dot, ver,
     ver, dot, dot, dot, dot, ver, dot, dot, dot, dot, spc, dot, dot, dot, dot, ver, dot, dot, dot, dot, ver,
     dru, hor, re , dot, le,  ul , dot, le , hor, ld , dot, dr , hor, re , dot, ru , re , dot, le , hor, uld,
     ver, dot, dot, dot, dot, dot, dot, dot, dot, ver, dot, ver, dot, dot, dot, dot, dot, dot, dot, dot, ver,
     ver, bdt, le,  hor, hor, re , dot, ue , dot, de , dot, de , dot, ue , dot, le , hor, hor, re , bdt, ver,
     ver, dot, dot, dot, dot, dot, dot, ver, dot, dot, dot, dot, dot, ver, dot, dot, dot, dot, dot, dot, ver,
     ru , hor, hor, hor, hor, hor, hor, rul, hor, hor, hor, hor, hor, rul, hor, hor, hor, hor, hor, hor, ul  },

   // 222222222222222222222222222222222222222222222222222222222222222222222222
  {  spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc,
     dr , hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, ld ,
     ver, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, ver,
     ver, bdt, dr , hor, re , dot, dr , hor, hor, hor, hor, hor, hor, hor, ld , dot, le , hor, ld , bdt, ver,
     ver, dot, de , dot, dot, dot, ver, dot, dot, dot, dot, dot, dot, dot, ver, dot, dot, dot, de , dot, ver,
     ver, dot, dot, dot, ue , dot, de , dot, le , hor, hor, hor, re , dot, de , dot, ue , dot, dot, dot, ver,
     dru, hor, re , dot, de , dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, de , dot, le , hor, uld,
     ver, dot, dot, dot, dot, ue,  dot, dr , hor, hor, dor, hor, hor, ld , dot, ue , dot, dot, dot, dot, ver,
     ver, dot, le , re , dot, ver, dot, ver, spc, spc, spc, spc, spc, ver, dot, ver, dot, le , re , dot, ver,
     ver, dot, dot, dot, dot, ver, dot, ver, spc, spc, spc, spc, spc, ver, dot, ver, dot, dot, dot, dot, ver,
     ver, dot, dr , re , dot, de , dot, ru , hor, hor, hor, hor, hor, ul , dot, de , dot, le , ld , dot, ver,
     ver, dot, de , dot, dot, dot, dot, dot, dot, dot, spc, dot, dot, dot, dot, dot, dot, dot, de , dot, ver,
     ver, dot, dot, dot, dr,  re , dot, le , ld , dot, ue , dot, dr , re , dot, le , ld , dot, dot, dot, ver,
     ver, dot, ue , dot, ver, dot, dot, dot, ver, dot, ver, dot, ver, dot, dot, dot, ver, dot, ue , dot, ver,
     ver, bdt, de,  dot, de , dot, ue , dot, de , dot, ver, dot, de , dot, ue , dot, de , dot, de , bdt, ver,
     ver, dot, dot, dot, dot, dot, ver, dot, dot, dot, ver, dot, dot, dot, ver, dot, dot, dot, dot, dot, ver,
     ru , hor, hor, hor, hor, hor, rul, hor, hor, hor, rul, hor, hor, hor, rul, hor, hor, hor, hor, hor, ul  },
   // 333333333333333333333333333333333333333333333333333333333333333333333333
  {  spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc,
     dr , hor, hor, hor, hor, hor, ldr, hor, hor, hor, ldr, hor, hor, hor, ldr, hor, hor, hor, hor, hor, ld ,
     ver, dot, dot, dot, dot, dot, ver, dot, dot, dot, ver, dot, dot, dot, ver, dot, dot, dot, dot, dot, ver,
     ver, bdt, lre, dot, ue , dot, de , dot, ue , dot, de , dot, ue , dot, de , dot, ue , dot, lre, bdt, ver,
     ver, dot, dot, dot, ver, dot, dot, dot, ver, dot, dot, dot, ver, dot, dot, dot, ver, dot, dot, dot, ver,
     dru, re , dot, le , rul, re , dot, le , rul, re , dot, le , rul, re , dot, le , rul, re , dot, le , uld,
     ver, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, ver,
     ver, dot, dr , re , dot, lre, dot, dr , hor, hor, dor, hor, hor, ld , dot, lre, dot, le , ld , dot, ver,
     ver, dot, de , dot, dot, dot, dot, ver, spc, spc, spc, spc, spc, ver, dot, dot, dot, dot, de , dot, ver,
     ver, dot, dot, dot, dr , ld , dot, ver, spc, spc, spc, spc, spc, ver, dot, dr , ld , dot, dot, dot, ver,
     ver, dot, lre, dot, ru , ul , dot, ru , hor, hor, hor, hor, hor, ul , dot, ru , ul , dot, lre, dot, ver,
     ver, dot, dot, dot, dot, dot, dot, dot, dot, dot, spc, dot, dot, dot, dot, dot, dot, dot, dot, dot, ver,
     dru, re , dot, le , ldr, re , dot, le , ldr, re , dot, le , ldr, re , dot, le , ldr, re , dot, le , dru,
     ver, dot, dot, dot, ver, dot, dot, dot, ver, dot, dot, dot, ver, dot, dot, dot, ver, dot, dot, dot, ver,
     ver, bdt, lre, dot, de , dot, ue , dot, de , dot, ue , dot, de , dot, ue , dot, de , dot, lre, bdt, ver,
     ver, dot, dot, dot, dot, dot, ver, dot, dot, dot, ver, dot, dot, dot, ver, dot, dot, dot, dot, dot, ver,
     ru , hor, hor, hor, hor, hor, rul, hor, hor, hor, rul, hor, hor, hor, rul, hor, hor, hor, hor, hor, ul  },

   // 44444444444444444444444444444444444444444444444444444444444444444444444
  {  spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc, spc,
     dr , hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, ld ,
     ver, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, ver,
     ver, bdt, lre, dot, lre, dot, lre, dot, lre, dot, lre, dot, lre, dot, lre, dot, lre, dot, lre, bdt, ver,
     ver, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, ver,
     ver, dot, lre, dot, lre, dot, lre, dot, lre, dot, lre, dot, lre, dot, lre, dot, lre, dot, lre, dot, ver,
     ver, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, ver,
     ver, dot, lre, dot, le , re , dot, dr , hor, hor, dor, hor, hor, ld , dot, le , re , dot, lre, dot, ver,
     ver, dot, dot, dot, dot, dot, dot, ver, spc, spc, spc, spc, spc, ver, dot, dot, dot, dot, dot, dot, ver,
     ver, dot, ue , dot, dr , ld , dot, ver, spc, spc, spc, spc, spc, ver, dot, dr , ld , dot, ue , dot, ver,
     ver, dot, de , dot, ru , ul , dot, ru , hor, hor, hor, hor, hor, ul , dot, ru , ul , dot, de , dot, ver,
     ver, dot, dot, dot, dot, dot, dot, dot, dot, dot, spc, dot, dot, dot, dot, dot, dot, dot, dot, dot, ver,
     ver, dot, lre, dot, lre, dot, lre, dot, lre, dot, lre, dot, lre, dot, lre, dot, lre, dot, lre, dot, ver,
     ver, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, ver,
     ver, bdt, lre, dot, lre, dot, lre, dot, lre, dot, lre, dot, lre, dot, lre, dot, lre, dot, lre, bdt, ver,
     ver, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, dot, ver,
     ru , hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, hor, ul  },

   // 55555555555555555555555555555555555555555555555555555555555555555555555
 { 
   19,19,0,0,0,0,0,30,0,0,0,0,0,0,0,0,0,0,0,0,0,
   6,1,1,1,1,1,1,1,1,1,8,1,1,1,1,1,1,1,1,1,3,
   2,15,15,15,15,15,15,15,15,15,2,15,15,15,15,15,15,15,15,15,2,
   2,18,12,13,15,6,1,1,13,15,11,15,12,1,1,3,15,12,13,18,2,
   2,15,15,15,15,2,15,15,15,15,15,15,15,15,15,2,15,15,15,15,2,
   2,15,6,3,15,11,15,12,1,1,1,1,1,13,15,11,15,6,3,15,2,
   2,15,2,2,15,15,15,15,15,15,15,15,15,15,15,15,15,2,2,15,2,
   2,15,2,2,15,14,15,6,1,1,16,1,1,3,15,14,15,2,2,15,2,
   2,15,4,5,15,2,15,2,0,0,0,0,0,2,15,2,15,4,5,15,2,
   2,15,15,15,15,2,15,2,0,0,0,0,0,2,15,2,15,15,15,15,2,
   2,15,12,13,15,11,15,4,1,1,1,1,1,5,15,11,15,6,3,15,2,
   2,15,15,15,15,15,15,15,15,15,0,15,15,15,15,15,15,2,2,15,2,
   7,1,1,13,15,14,15,12,1,1,1,1,1,13,15,14,15,4,5,15,2,
   2,15,15,15,15,2,15,15,15,15,15,15,15,15,15,2,15,15,15,15,2,
   2,18,12,1,1,9,1,1,13,15,14,15,12,1,1,9,1,1,13,18,2,
   2,15,15,15,15,15,15,15,15,15,2,15,15,15,15,15,15,15,15,15,2,
   4,1,1,1,1,1,1,1,1,1,9,1,1,1,1,1,1,1,1,1,5,
   },



/*************************************************************************
  666666666666666666666666666666666666666666666666666666666666666666666666

ллллллллллллллллллллл
ллллллллллллллллллллл
лњњњлњњњњњњњлњњњњњњњл
лллњлњлллллњлњллњлллл
лњлњлњлњњњњњњњњњњњњњл
лњлњњњлњллллњлллњллњл
лњњњлњњњњњњњњњњњњњлњл
лњллллњлллллллњллњлњл
лњњњњњњлллллллњллњњњл
лњллллњлллллллњллњлњл
лњлњњњњлллллллњњњњлњл
лњњњллњњњњлњњњњлњллњл
лњлњњллњлњллњлллњњњњл
лњллњњњњлњњлњњњњњллњл
лллллњллллњлњлллњлллл
лњњњњњњњњњњњњњњњњњњњл
ллллллллллллллллллллл

*/

 { 
    19, 19,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     6,  1,  1,  1,  8,  1,  1,  1,  1,  1,  1,  1,  8,  1,  1,  1,  1,  1,  1,  1,  3,
     2, 15, 15, 15,  2, 15, 15, 15, 15, 15, 15, 15,  2, 15, 15, 15, 15, 15, 15, 15,  2,
     2, 18, 14, 15,  2, 15,  6,  1,  1,  1, 13, 15, 11, 15, 12, 13, 15, 12, 13, 18,  2,
     2, 15,  2, 15, 11, 15,  2, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,  2,
     2, 15, 11, 15, 15, 15, 11, 15, 12,  1,  1, 13, 15, 12,  1, 13, 15, 12,  3, 15,  2,
     2, 15, 15, 15, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,  2, 15,  2,
     2, 15, 12,  1,  9, 13, 15,  6,  1,  1, 16,  1,  1,  3, 15,  6,  3, 15, 11, 15,  2,
     2, 15, 15, 15, 15, 15, 15,  2,  0,  0,  0,  0,  0,  2, 15,  2,  2, 15, 15, 15,  2,
     2, 15,  6,  1,  1, 13, 15,  2,  0,  0,  0,  0,  0,  2, 15,  4,  5, 15, 14, 15,  2,
     2, 15, 11, 15, 15, 15, 15,  4,  1,  1,  1,  1,  1,  5, 15, 15, 15, 15,  2, 15,  2,
     2, 15, 15, 15, 12,  3, 15, 15, 15, 15,  0, 15, 15, 15, 15, 14, 15, 12,  5, 15,  2,
     2, 15, 14, 15, 15,  4, 13, 15, 14, 15, 12,  3, 15, 12,  1,  5, 15, 15, 15, 15,  2,
     2, 15,  7,  3, 15, 15, 15, 15,  2, 15, 15,  2, 15, 15, 15, 15, 15,  6,  3, 15,  2,
     2, 18,  4,  9, 13, 15, 12,  1,  9, 13, 15, 11, 15, 12,  1, 13, 15,  4,  5, 18,  2,
     2, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,  2,
     4,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  5
   },



/****************************************************************************
 7777777777777777777777777777777777777777777777777777777777777777777777777777
ллллллллллллллллллллл
ллллллллллллллллллллл
лњњњњњњњњњлњњњњњњњњњл
лллњлллњлњлњлњлллњллл
лњлњњњњњлњњњлњњњњњлњл
лњњњллњллњлњллњллњњњл
лллњњњњњњњњњњњњллњллл
лњњњллњлллллллњллњњњл
лњлњњњњлллллллњњњњлњл
лњњњллњлллллллњллллњл
лллњллњлллллллњњњњлњл
лњњњллњњњњлњњњњллњњњл
лњлњњњњллњллњлњлњњлњл
лњлњллњњлњњлњлњњњллњл
лллњлллњллњлњлллњлллл
лњњњњњњњњњњњњњњњњњњњл
ллллллллллллллллллллл

*/

 { 
    19, 19,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     6,  1,  1,  1,  1,  1,  1,  1,  1,  1,  8,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3,
     2, 15, 15, 15, 15, 15, 15, 15, 15, 15,  2, 15, 15, 15, 15, 15, 15, 15, 15, 15,  2,
     2, 18, 14, 15, 12,  1, 13, 15, 14, 15, 11, 15, 14, 15, 12,  1, 13, 15, 14, 18,  2,
     2, 15, 11, 15, 15, 15, 15, 15,  2, 15, 15, 15,  2, 15, 15, 15, 15, 15, 11, 15,  2,
     2, 15, 15, 15, 12, 13, 15, 12,  5, 15, 17, 15,  4, 13, 15,  6,  3, 15, 15, 15,  2,
     7,  1, 13, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,  2,  2, 15, 12,  1, 10,
     2, 15, 15, 15, 12, 13, 15,  6,  1,  1, 16,  1,  1,  3, 15,  4,  5, 15, 15, 15,  2,
     2, 15, 17, 15, 15, 15, 15,  2,  0,  0,  0,  0,  0,  2, 15, 15, 15, 15, 14, 15,  2,
     2, 15, 15, 15,  6,  3, 15,  2,  0,  0,  0,  0,  0,  2, 15, 12,  1,  1, 10, 15,  2,
     7,  1, 13, 15,  2,  2, 15,  4,  1,  1,  1,  1,  1,  5, 15, 15, 15, 15, 11, 15,  2,
     2, 15, 15, 15,  4,  5, 15, 15, 15, 15,  0, 15, 15, 15, 15,  6, 13, 15, 15, 15,  2,
     2, 15, 14, 15, 15, 15, 15, 12,  3, 15, 12,  3, 15, 14, 15, 11, 15, 15, 14, 15,  2,
     2, 15,  2, 15,  6,  3, 15, 15,  2, 15, 15,  2, 15,  2, 15, 15, 15,  6, 10, 15,  2,
     2, 18, 11, 15,  4,  9, 13, 15,  4, 13, 15, 11, 15,  4,  1, 13, 15,  4,  5, 18,  2,
     2, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,  2,
     4,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  5,
   },

/************************************************************************
 888888888888888888888888888888888888888888888888888888888888888888888888
 */
 { 
    19, 19,  0,  0,  0,  0,  0, 30,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     6,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3,
     2, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,  2,
     2, 18, 12, 13, 15, 12,  1,  3, 15, 12,  1,  3, 15, 14, 15,  6, 13, 15, 14, 18,  2,
     2, 15, 15, 15, 15, 15, 15,  2, 15, 15, 15,  2, 15,  2, 15,  2, 15, 15,  2, 15,  2,
     2, 15,  6,  1,  1, 13, 15, 11, 15, 17, 15, 11, 15, 11, 15, 11, 15, 12,  5, 15,  2,
     2, 15, 11, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,  2,
     2, 15, 15, 15, 12,  3, 15,  6,  1,  1, 16,  1,  1,  3, 15,  6,  3, 15, 17, 15,  2,
     2, 15, 14, 15, 15, 11, 15,  2,  0,  0,  0,  0,  0,  2, 15,  7,  5, 15, 15, 15,  2,
     2, 15,  4, 13, 15, 15, 15,  2,  0,  0,  0,  0,  0,  2, 15, 11, 15, 15, 14, 15,  2,
     2, 15, 15, 15, 15, 14, 15,  4,  1,  1,  1,  1,  1,  5, 15, 15, 15,  6, 10, 15,  2,
     2, 15, 12, 13, 15, 11, 15, 15, 15, 15,  0, 15, 15, 15, 15, 17, 15,  4,  5, 15,  2,
     2, 15, 15, 15, 15, 15, 15, 12,  8,  3, 15,  6,  8, 13, 15, 15, 15, 15, 15, 15,  2,
     2, 15,  6,  3, 15, 14, 15, 15,  4, 10, 15,  7,  5, 15, 15, 14, 15,  6,  3, 15,  2,
     2, 18,  4,  5, 15,  7,  3, 15, 15, 11, 15, 11, 15, 15,  6, 10, 15,  4,  5, 18,  2,
     2, 15, 15, 15, 15,  4,  9, 13, 15, 15, 15, 15, 15, 12,  9,  5, 15, 15, 15, 15,  2,
     4,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  5,
   } 
};


const int numLevels = 18;

int levelData[numLevels][12] = {
{      
    0,       // Field Design
    10*32,   // Pill duration, in ticks
    4.7*32,  // Ghost hatch time, in ticks
    10,20,30,40,       // Ghost IQ
    60*32,   // time between fruits
    18*32,   // fruit duration
    200,     // fruit value
    0,       // fruit value icon from makman
    cherry   // fruit icon
    },
{
    0,       // Field Design
    10*32,    // Pill duration, in ticks
    4*32,    // Ghost hatch time, in ticks
    20,30,40,50,      // Ghost IQ
    60*32,   // time between fruits
    18*32,   // fruit duration
    200,     // fruit value
    0,       // fruit value icon from makman
    cherry // fruit icon
    },
{
    1,       // Field Design
    9*32,    // Pill duration, in ticks
    4*32,    // Ghost hatch time, in ticks
    30,40,50,60,      // Ghost IQ
    60*32,   // time between fruits
    18*32,   // fruit duration
    400,     // fruit value
    1,       // fruit value icon from makman
    strawberry // fruit icon
    },
{
    1,       // Field Design
    9*32,    // Pill duration, in ticks
    4*32,    // Ghost hatch time, in ticks
    50,60,70,80,      // Ghost IQ
    60*32,   // time between fruits
    18*32,   // fruit duration
    400,     // fruit value
    1,       // fruit value icon from makman
    strawberry // fruit icon
    },
{
    2,      // Field Design
    8*32,    // Pill duration, in ticks
    4*32,    // Ghost hatch time, in ticks
    60,70,80,90,      // Ghost IQ
    60*32,   // time between fruits
    14*32,   // fruit duration
    600,     // fruit value
    2,       // fruit value icon from makman
    strawberry // fruit icon
    },

{
    2,      // Field Design
    8*32,    // Pill duration, in ticks
    4*32,    // Ghost hatch time, in ticks
    60,70,80,90,      // Ghost IQ
    60*32,   // time between fruits
    14*32,   // fruit duration
    600,     // fruit value
    2,       // fruit value icon from makman
    strawberry // fruit icon
    },
{
    3,      // Field Design
    7*32,    // Pill duration, in ticks
    3*32,    // Ghost hatch time, in ticks
    60,70,80,90,      // Ghost IQ
    50*32,   // time between fruits
    14*32,   // fruit duration
    800,     // fruit value
    3,       // fruit value icon from makman
    strawberry // fruit icon
    },
{
    3,      // Field Design
    7*32,    // Pill duration, in ticks
    3*32,    // Ghost hatch time, in ticks
    60,70,80,90,      // Ghost IQ
    50*32,   // time between fruits
    14*32,   // fruit duration
    800,     // fruit value
    3,       // fruit value icon from makman
    strawberry // fruit icon
    },
{
    8,      // Field Design
    6*32,    // Pill duration, in ticks
    3*32,    // Ghost hatch time, in ticks
    60,70,80,90,      // Ghost IQ
    50*32,   // time between fruits
    12*32,   // fruit duration
    1000,     // fruit value
    4,       // fruit value icon from makman
    strawberry // fruit icon
    },
{
    8,      // Field Design
    6*32,    // Pill duration, in ticks
    3*32,    // Ghost hatch time, in ticks
    60,70,80,90,      // Ghost IQ
    50*32,   // time between fruits
    12*32,   // fruit duration
    1000,     // fruit value
    4,       // fruit value icon from makman
    strawberry // fruit icon
    },
{
    5,      // Field Design
    5*32,    // Pill duration, in ticks
    3*32,    // Ghost hatch time, in ticks
    60,70,80,90,      // Ghost IQ
    50*32,   // time between fruits
    12*32,   // fruit duration
    1500,     // fruit value
    5,       // fruit value icon from makman
    strawberry // fruit icon
    },
{
    5,      // Field Design
    5*32,    // Pill duration, in ticks
    3*32,    // Ghost hatch time, in ticks
    60,70,80,90,      // Ghost IQ
    50*32,   // time between fruits
    12*32,   // fruit duration
    1500,     // fruit value
    5,       // fruit value icon from makman
    strawberry // fruit icon
    },
{
    6,      // Field Design
    4*32,    // Pill duration, in ticks
    2*32,    // Ghost hatch time, in ticks
    60,70,80,90,      // Ghost IQ
    40*32,   // time between fruits
    10*32,   // fruit duration
    3000,     // fruit value
    6,       // fruit value icon from makman
    strawberry // fruit icon
    },
{
    6,      // Field Design
    4*32,    // Pill duration, in ticks
    2*32,    // Ghost hatch time, in ticks
    60,70,80,90,      // Ghost IQ
    40*32,   // time between fruits
    10*32,   // fruit duration
    3000,     // fruit value
    6,       // fruit value icon from makman
    strawberry // fruit icon
    },
{
    7,      // Field Design
    3*32,    // Pill duration, in ticks
    2*32,    // Ghost hatch time, in ticks
    60,70,80,90,      // Ghost IQ
    40*32,   // time between fruits
    10*32,   // fruit duration
    6000,     // fruit value
    7,       // fruit value icon from makman
    strawberry // fruit icon
    },
{
    7,      // Field Design
    3*32,    // Pill duration, in ticks
    2*32,    // Ghost hatch time, in ticks
    60,70,80,90,      // Ghost IQ
    40*32,   // time between fruits
    10*32,   // fruit duration
    6000,     // fruit value
    7,       // fruit value icon from makman
    strawberry // fruit icon
    },
{
    4,      // Field Design
    3*32,    // Pill duration, in ticks
    2*32,    // Ghost hatch time, in ticks
    60,70,80,90,      // Ghost IQ
    30*32,   // time between fruits
    8*32,   // fruit duration
    12000,     // fruit value
    8,       // fruit value icon from makman
    strawberry // fruit icon
    },
{
    4,      // Field Design
    2*32,    // Pill duration, in ticks
    2*32,    // Ghost hatch time, in ticks
    60,70,80,90,      // Ghost IQ
    30*32,   // time between fruits
    8*32,   // fruit duration
    12000,     // fruit value
    8,       // fruit value icon from makman
    strawberry // fruit icon
    }
};
