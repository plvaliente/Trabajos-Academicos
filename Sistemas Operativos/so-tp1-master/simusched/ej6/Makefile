SCHED=../simusched
GRAPH=../graphsched.py
ANALIZE=../analizesched.py

LOTES=lote


all: $(LOTES:=.png) $(LOTES:=.liz)

clean:
	-rm *.png
	-rm *.sched
	-rm *.liz

%.sched: %.tsk $(SCHED)
	$(SCHED) $< 1 1 0 SchedSPJF > $@

%.png: %.sched $(GRAPH)
	cat $< | python $(GRAPH) > $@

%.liz: %.sched $(ANALIZE)
	cat $< | python $(ANALIZE) > $@