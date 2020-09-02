SCHED=../simusched
GRAPH=../graphsched.py
ANALIZE=../analizesched.py

.PHONY: all

define sched
	$(SCHED) $(1) $(2) $(3) $(4) $(5) $(6) > tmp.sched
	cat tmp.sched | python $(ANALIZE) > $(1).$(5).$(2)C.$(3)S.$(4)M.liz;
	cat tmp.sched | python $(GRAPH) > $(1).$(5).$(2)C.$(3)S.$(4)M.png
	rm tmp.sched
endef

all:
	$(call sched,LoteControl,1,1,1,SchedNoMistery,)
	$(call sched,LoteControl,2,1,1,SchedNoMistery,)
	$(call sched,LoteControl,1,1,1,SchedRR,5)
	$(call sched,LoteControl,2,1,1,SchedRR,5)
	$(call sched,LoteGrande,1,1,1,SchedRR,5)
	$(call sched,LoteGrande,2,1,1,SchedRR,5)
	$(call sched,LoteInOrder,1,1,1,SchedNoMistery,)
	$(call sched,LoteInOrder,2,1,1,SchedNoMistery,)
	$(call sched,LoteInOrder,1,1,1,SchedRR,5)
	$(call sched,LoteInOrder,2,1,1,SchedRR,5)
	$(call sched,LoteNoOrder,1,1,1,SchedNoMistery,)
	$(call sched,LoteNoOrder,2,1,1,SchedNoMistery,)
	$(call sched,LoteNoOrder,1,1,1,SchedRR,5)
	$(call sched,LoteNoOrder,2,1,1,SchedRR,5)
	$(call sched,LotePrioCre,1,1,1,SchedSPJF,)
	$(call sched,LotePrioCre,2,1,1,SchedSPJF,)
	$(call sched,LotePrioDec,1,1,1,SchedSPJF,)
	$(call sched,LotePrioDec,2,1,1,SchedSPJF,)
	$(call sched,LotePrioRnd,1,1,1,SchedSPJF,)
	$(call sched,LotePrioRnd,2,1,1,SchedSPJF,)
	$(call sched,LotePrioRnd2,1,1,1,SchedSPJF,)
	$(call sched,LotePrioRnd2,2,1,1,SchedSPJF,)


clean:
	-rm *.png
	-rm *.sched
	-rm *.liz
