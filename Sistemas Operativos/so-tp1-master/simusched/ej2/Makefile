SCHED=../simusched
GRAPH=../graphsched.py
ANALIZE=../analizesched.py

CASOS=caso1 caso2 caso3

all: $(CASOS:=.png) $(CASOS:=.liz)

clean:
	-rm *.png
	-rm *.sched
	-rm *.liz

%.sched: %.def $(SCHED)
	@echo `cat $<`
	$(SCHED) `cat $<` > $@

%.png: %.sched $(GRAPH)
	cat $< | python $(GRAPH) > $@

%.liz: %.sched $(ANALIZE)
	cat $< | python $(ANALIZE) > $@
