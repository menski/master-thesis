LATEX=pdflatex -shell-escape
BIBTEX=bibtex
RM=rm -f
TITLE=SebastianMenski-Masterarbeit

all: pdf
	cp master.pdf $(TITLE).pdf

bibtex:
	$(LATEX) master.tex
	$(BIBTEX) master
	$(LATEX) master.tex

pdf: bibtex
	$(LATEX) master.tex
	$(LATEX) master.tex

clean:
	$(RM) master.aux
	$(RM) master.blg
	$(RM) master.fdb_latexmk
	$(RM) master.lof
	$(RM) master.log
	$(RM) master.lot
	$(RM) master.out 
	$(RM) master.toc

clean-all: clean
	$(RM) master.bbl
	$(RM) master.pdf
	$(RM) $(TITLE).pdf
	$(RM) images/*-converted-to.pdf
