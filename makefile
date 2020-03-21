CC := gcc
CFLAGS += -Wall
CFLAGS += -g
CPPFLAGS += -DDEBUG

CGL_2_D: CGL_2_D.c
	$(LINK.c) $(OUTPUT_OPTION) $^ -lm

CGL_3_C: CGL_3_C.c
	$(LINK.c) $(OUTPUT_OPTION) $^ -lm

CGL_7_D: CGL_7_D.c
	$(LINK.c) $(OUTPUT_OPTION) $^ -lm

CGL_7_E: CGL_7_E.c
	$(LINK.c) $(OUTPUT_OPTION) $^ -lm
