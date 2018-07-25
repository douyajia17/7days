SOURCES := sim.c processor.c load_program.c disassemble.c memory.c
HEADERS := elf.h load_program.h processor.h disassemble.h memory.h

ASM_TESTS := simple insts rt3 rt13 rt25 oritests sll test1 swaptest nchoosektest test2

all: mips-sim $(addprefix test/, $(ASM_TESTS))

.PHONY: disasmtest runtest %_test

test/%.o: test/%.s
	mipsel-linux-gcc -c -o $@ $<

$(addprefix test/, $(ASM_TESTS)): %: %.s test/mips.ld
	mipsel-linux-gcc -o $(patsubst %.s, %.o, $<) -c $<
	mipsel-linux-ld -o $@ $(patsubst %.s, %.o, $<) -T test/mips.ld

mips-sim: $(SOURCES) $(HEADERS)
	gcc -g -Wall -Werror -Wfatal-errors -O2 -o $@ $(SOURCES)

disasmtest: mips-sim test/insts
	./mips-sim -d test/insts > insts.dump
	@diff insts.dump test/insts.dump && echo "DISASSEMBLY TEST PASSED!" || echo "DISASSEMBLY TEST FAILED!"

%_test: test/% test/%.trace
	./mips-sim -r $< > test.trace
	@diff test.trace $(addsuffix .trace, $(basename $<)) && echo "$@ PASSED" || echo "$@ FAILED"

runtest: mips-sim insts_test rt3_test rt13_test rt25_test
	@echo "Tests Complete"

clean:
	rm -f mips-sim $(addprefix test/,  $(ASM_TESTS)) $(addsuffix .o, $(addprefix test/,  $(ASM_TESTS))) *.dump *.trace
