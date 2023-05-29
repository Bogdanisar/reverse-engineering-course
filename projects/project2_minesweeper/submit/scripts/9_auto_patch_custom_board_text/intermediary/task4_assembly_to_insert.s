.intel_syntax noprefix
_main:

mov     r10d, 1    # This is the instruction we replaced to call this codecave

push r8
push r9


# Only proceed for the highest difficulty
mov r8, 0x140008034  #  &selectedDifficulty
mov r8d, dword ptr [r8]

cmp r8d, 3   #  3 == "Large" difficulty
jne end_label


# Remove the generated bombs from all the cells

mov r8, 0x14000d140
mov r9, 1600  # number of cells for the entire allocated matrix

clean_matrix_loop:
    mov dword ptr [r8], 0
    add r8, 4
    dec r9
    test r9, r9
    jnz clean_matrix_loop



mov r8, 0x14000d140
mov r9, 172
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 176
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 180
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 184
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 188
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 192
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 196
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 200
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 204
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 208
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 212
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 216
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 220
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 224
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 228
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 232
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 236
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 240
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 244
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 248
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 252
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 256
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 260
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 264
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 268
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 272
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 332
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 432
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 492
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 592
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 652
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 752
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 812
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 828
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 832
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 836
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 840
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 844
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 848
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 852
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 856
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 860
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 864
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 868
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 872
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 876
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 880
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 884
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 888
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 892
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 896
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 912
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 972
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 988
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1016
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1020
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1024
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1028
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1056
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1072
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1132
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1148
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1176
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1180
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1184
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1188
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1216
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1232
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1292
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1336
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1340
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1344
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1348
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1376
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1392
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1452
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1536
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1552
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1612
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1696
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1712
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1772
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1856
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1872
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1932
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1936
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1940
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1944
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1948
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1952
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1956
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1960
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1964
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1968
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1972
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1976
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1980
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1984
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1988
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1992
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 1996
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2000
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2004
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2008
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2012
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2016
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2032
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2192
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2352
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2512
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2564
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2568
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2572
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2576
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2580
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2584
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2588
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2592
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2596
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2600
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2604
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2608
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2612
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2616
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2620
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2624
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2628
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2632
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2636
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2640
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2644
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2648
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2652
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2656
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2660
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2664
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2668
add r9, r8
mov dword ptr [r9], 42  # bomb

mov r8, 0x14000d140
mov r9, 2672
add r9, r8
mov dword ptr [r9], 42  # bomb

    mov r8, 0x140008620  # numTotalBombs
    mov dword ptr [r8], 138

    end_label:
    pop r9
    pop r8
    ret

    