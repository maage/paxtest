TARGETS := paxtest.1

all: $(TARGETS)

%.1: %.sgml
	docbook2man $< > $@

clean:
	rm -f $(TARGETS)

.PHONY: all clean
