LATEX=pdflatex -shell-escape
BIBTEX=bibtex
RM=rm -f
TITLE=slides-$(shell basename $(shell pwd))
MASTER=slides

all: pdf handout
	cp $(MASTER).pdf $(TITLE).pdf

bibtex:
	$(LATEX) $(MASTER).tex
	$(BIBTEX) $(MASTER)
	$(LATEX) $(MASTER).tex

pdf: bibtex
	$(LATEX) $(MASTER).tex
	$(LATEX) $(MASTER).tex

handout:
	cd handout && $(LATEX) handout.tex

clean:
	$(RM) $(MASTER).aux
	$(RM) $(MASTER).blg
	$(RM) $(MASTER).fdb_latexmk
	$(RM) $(MASTER).lof
	$(RM) $(MASTER).log
	$(RM) $(MASTER).lot
	$(RM) $(MASTER).out 
	$(RM) $(MASTER).toc
	$(RM) $(MASTER).nav
	$(RM) $(MASTER).snm
	$(RM) $(MASTER).vrb
	$(RM) handout/handout.pdf
	$(RM) handout/handout.aux
	$(RM) handout/handout.log

clean-all: clean
	$(RM) $(MASTER).bbl
	$(RM) $(MASTER).pdf
	$(RM) $(TITLE).pdf

.PHONY: handout
