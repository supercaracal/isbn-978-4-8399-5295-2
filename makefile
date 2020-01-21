CC := gcc
CFLAGS += -Wall
CFLAGS += -g

CGL_2_D: CGL_2_D.c
	$(LINK.c) $(OUTPUT_OPTION) $^ -lm
