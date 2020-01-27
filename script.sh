#!/bin/bash
./asm ./test/test_my.s
./vm_champs/asm ./test/test_org.s 
hexdump -C ./test/test_my.cor > my
hexdump -C ./test/test_org.cor > org
diff my org
