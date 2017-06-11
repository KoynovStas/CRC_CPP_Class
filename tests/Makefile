CPPFLAGS += -O2 -Wall
CPP       =  g++
#CPP       =  arm-gcc_4.9.2_cortex_a15-linux-uclibcgnueabi-g++



# list of tests for build
TESTS  = crc_test




.PHONY: all
all: clean  $(TESTS)



.PHONY: clean
clean:
	-@rm -f *.o
	-@rm -f *.*~
	-@rm -f $(TESTS)



.PHONY: $(TESTS)
$(TESTS):
	$(CPP)  $@.cpp ucrc_t.cpp unit_tests.cpp -o $@  $(CPPFLAGS)
	@echo "  ---- Compiled $@ ----"
	@echo ""
	@echo "  ---- Start tests ----"
	@echo ""
	@./crc_test
	@echo ""



.PHONY: asm
asm:
	$(CPP)  crc_test.cpp $(CPPFLAGS) -S
	$(CPP)  ucrc_t.cpp $(CPPFLAGS) -S




.PHONY: help
help:
	@echo "make [command]"
	@echo "command is:"
	@echo "   clean   -  remove all binary files"
	@echo "   all     -  clean and build all tests"
	@echo "   asm     -  get ASM listing"
	@echo "   help    -  This help"

